#pragma once
typedef struct ACWTBInfo_s {
	BYTE				id[4];
	DWORD				u_a;
	unsigned long long	textureSize;
	unsigned int		headerSize;
	unsigned int		numMipMap;
	unsigned int		textureType;
	unsigned int		format;
	unsigned int		width;
	unsigned int		height;
	unsigned int		depth;
	unsigned int		u_b;
	unsigned int		blockHeightLog2;
	unsigned int		u_c;
} ACWTBInfo_t;
template <bool big>
struct ACWTBInfo : ACWTBInfo_s {
	ACWTBInfo(ACWTBInfo_t *ptr) : ACWTBInfo_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(u_a);
			LITTLE_BIG_SWAP(textureSize);
			LITTLE_BIG_SWAP(headerSize);
			LITTLE_BIG_SWAP(numMipMap);
			LITTLE_BIG_SWAP(textureType);
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(width);
			LITTLE_BIG_SWAP(height);
			LITTLE_BIG_SWAP(depth);
			LITTLE_BIG_SWAP(u_b);
			LITTLE_BIG_SWAP(blockHeightLog2);
			LITTLE_BIG_SWAP(u_c);
		}
	}
};

template <>
static void Model_Bayo_GetTextureBundle<ASTRAL_CHAIN>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}
template <>
static void Model_Bayo_LoadTextures<false, ASTRAL_CHAIN>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	const bool big = false;
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	int dataSize2 = texFiles[1]->dataSize;
	BYTE * data2 = texFiles[1]->data;
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr<big> hdr((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "WTB\0", 4))
	{ //not a valid texture bundle
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}
	DBGLOG("found valid texture header file, containing %d textures, headers offset: %x\n", hdr.numTex, hdr.texInfoOffset);

	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *idxs = (int  *)(data + hdr.texIdxOffset);
	ACWTBInfo_t *tinfs = (ACWTBInfo_t  *)(data + hdr.texInfoOffset);
	typedef void(*Noesis_UntileBlockLinearGOBs_p)(void *untiledMip, int untiledMipSize, void *textureData, int mipSize, int widthInBlocks, int heightInBlocks, int blockSize, int maxBlockHeight, noeRAPI_t *rapi);
	Noesis_UntileBlockLinearGOBs_p Noesis_UntileBlockLinearGOBs = NULL;
	Noesis_UntileBlockLinearGOBs = (Noesis_UntileBlockLinearGOBs_p)g_nfn->NPAPI_GetUserExtProc("Noesis_UntileBlockLinearGOBs");
	DBGLOG("Noesis_UntileBlockLinearGOBs: %p\n", Noesis_UntileBlockLinearGOBs);
	typedef void(*NoesisMisc_ASTC_DecodeRaw32_p)(void *pix, void *untiledMip, int mipSize, int *blockDims, int *dims);
	NoesisMisc_ASTC_DecodeRaw32_p NoesisMisc_ASTC_DecodeRaw32 = NULL;
	NoesisMisc_ASTC_DecodeRaw32 = (NoesisMisc_ASTC_DecodeRaw32_p)g_nfn->NPAPI_GetUserExtProc("NoesisMisc_ASTC_DecodeRaw32");
	DBGLOG("NoesisMisc_ASTC_DecodeRaw32: %p\n", NoesisMisc_ASTC_DecodeRaw32);

	for (int i = 0; i < hdr.numTex; i++)
	{
		int tof = tofs[i];
		int tsize = tsizes[i];
		int idx = idxs[i];
		ACWTBInfo<big> info(tinfs + i);

		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);
		DBGLOG("%s: 0x%0x, type: %d, format: %x, width: %d, height: %d, blockSize: %d\n", fname, idx, info.textureType, info.format, info.width, info.height, 1 << (info.blockHeightLog2 & 7));

		int width = info.width;
		int height = info.height;
		int depth = info.depth;
		size_t mipSize = (size_t)info.textureSize;
		BYTE *untiledMip;
		BYTE *pix;
		int blockWidth;
		int blockHeight;
		int blockDepth = 1;
		int blockSize = 1 << (info.blockHeightLog2 & 7);;
		int maxBlockHeight;
		bool astc = false;
		bool decode_dxt = false;
		int fourcc = 0;
		noesisTexType_e type = NOESISTEX_UNKNOWN;
		if (info.textureType != 1) continue;
		if (info.format == 0x80 || info.format == 0x8e) {
			blockWidth = 8;
			blockHeight = 8;
			maxBlockHeight = 16;
			astc = true;
			DBGLOG("Found ASTC 8x8\n");
		}
		else if (info.format == 0x79 || info.format == 0x87) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 16;
			astc = true;
			DBGLOG("Found ASTC 4x4\n");
		}
		else if (info.format == 0x50) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 16;
			fourcc = FOURCC_BC6H;
			decode_dxt = true;
			DBGLOG("Found BC6H\n");
		}
		else if (info.format == 0x45 || info.format == 0x49) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 16;
			fourcc = FOURCC_BC4;
			decode_dxt = true;
			DBGLOG("Found BC4\n");
		}
		else if (info.format == 0x44 || info.format == 0x48) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 16;
			type = NOESISTEX_DXT5;
			DBGLOG("Found DXT5\n");
		}
		else if (info.format == 0x43 || info.format == 0x47) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 16;
			type = NOESISTEX_DXT3;
			DBGLOG("Found DXT3\n");
		}
		else if (info.format == 0x42 || info.format == 0x46) {
			blockWidth = 4;
			blockHeight = 4;
			maxBlockHeight = 8;
			type = NOESISTEX_DXT1;
			DBGLOG("Found DXT1\n");
		}
		else if (info.format == 0x25) {
			blockWidth = 1;
			blockHeight = 1;
			maxBlockHeight = 8;
			type = NOESISTEX_RGBA32;
			DBGLOG("Found RGBA32\n");
		}
		else {
			continue;
		}

		int widthInBlocks = (width + (blockWidth - 1)) / blockWidth;
		int heightInBlocks = (height + (blockHeight - 1)) / blockHeight;


		noesisTex_t *nt;
		if (astc) {
			untiledMip = (BYTE *)rapi->Noesis_UnpooledAlloc(mipSize);
			pix = (BYTE *)rapi->Noesis_PooledAlloc((width*height) * 4);
			Noesis_UntileBlockLinearGOBs(untiledMip, mipSize, data2 + tof, mipSize, widthInBlocks, heightInBlocks, blockSize, maxBlockHeight, rapi);
			DBGLOG("Untiled\n");
			int blockDims[3] = { blockWidth, blockHeight, blockDepth };
			int dims[3] = { width, height, depth };
			NoesisMisc_ASTC_DecodeRaw32(pix, untiledMip, mipSize, blockDims, dims);
			DBGLOG("Decoded ASTC\n");
			nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
			rapi->Noesis_UnpooledFree(untiledMip);
			nt->shouldFreeData = false; //because the untiledMip data is pool-allocated, it does not need to be freed
		}
		else if (decode_dxt) {
			untiledMip = (BYTE *)rapi->Noesis_UnpooledAlloc(mipSize);
			Noesis_UntileBlockLinearGOBs(untiledMip, mipSize, data2 + tof, mipSize, widthInBlocks, heightInBlocks, blockSize, maxBlockHeight, rapi);
			pix = rapi->Noesis_ConvertDXT(width, height, untiledMip, fourcc);
			DBGLOG("Decoded BC\n");
			nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
			rapi->Noesis_UnpooledFree(untiledMip);
			nt->shouldFreeData = true;
		}
		else {
			untiledMip = (BYTE *)rapi->Noesis_PooledAlloc(mipSize);
			Noesis_UntileBlockLinearGOBs(untiledMip, mipSize, data2 + tof, mipSize, widthInBlocks, heightInBlocks, blockSize, maxBlockHeight, rapi);
			DBGLOG("Untiled\n");
			nt = rapi->Noesis_TextureAlloc(fname, width, height, untiledMip, type);
			nt->shouldFreeData = false; //because the untiledMip data is pool-allocated, it does not need to be freed
		}

		//nt->flags |= texFlags;
		nt->globalIdx = idx;
		textures.Append(nt);
	}
	//insert a flat normal map placeholder
	char fname[MAX_NOESIS_PATH];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayoflatnormal", rapi->Noesis_GetOption("texpre"));
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);
	noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, true);
	textures.Append(nt);
}

template <>
static void Model_Bayo_CreateTangents<false, ASTRAL_CHAIN>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
	Model_Bayo_CreateTangents<false, BAYONETTA>(data, dsts, numVerts, stride, m);
}

template <>
static void Model_Bayo_LoadModel<false, ASTRAL_CHAIN>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset, const char *prefix, CArrayList<noesisMaterial_t *> *globalMatList) {
	Model_Bayo_LoadWMB3Model<false, ASTRAL_CHAIN>(dfiles, df, rapi, models, givenTextures, pretransform, sharedtextureoffset, prefix, globalMatList);
}

template <>
static void Model_Bayo_LoadScenery<false, ASTRAL_CHAIN>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
}