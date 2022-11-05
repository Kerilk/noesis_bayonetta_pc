#pragma once
typedef struct ACWTBInfo_s {
	uint8_t			id[4];
	uint32_t		u_a;
	uint64_t		textureSize;
	uint32_t		headerSize;
	uint32_t		numMipMap;
	uint32_t		textureType;
	uint32_t		format;
	uint32_t		width;
	uint32_t		height;
	uint32_t		depth;
	uint32_t		specialPad;
	uint8_t			blockHeightLog2;
	uint8_t			flags;
	uint8_t			u_b[2];
	uint32_t		u_c;
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
			LITTLE_BIG_SWAP(specialPad);
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
	typedef void(*Noesis_UntileBlockLinearGOBs_p)(void *untiledMip, unsigned int untiledMipSize, void *textureData, unsigned int mipSize, int widthInBlocks, int heightInBlocks, int blockSize, int maxBlockHeight, noeRAPI_t *rapi);
	Noesis_UntileBlockLinearGOBs_p Noesis_UntileBlockLinearGOBs = NULL;
	Noesis_UntileBlockLinearGOBs = (Noesis_UntileBlockLinearGOBs_p)g_nfn->NPAPI_GetUserExtProc("Noesis_UntileBlockLinearGOBs");
	DBGLOG("Noesis_UntileBlockLinearGOBs: %p\n", Noesis_UntileBlockLinearGOBs);
	typedef void(*NoesisMisc_ASTC_DecodeRaw32_p)(void *pix, void *untiledMip, unsigned int mipSize, int *blockDims, int *dims);
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
		int maxBlockHeight = 1 << (info.blockHeightLog2 & 7);
		bool special = info.flags & 0x4;
		int  special_pad = info.specialPad;
		Model_loadTextureSwitch(idx, data2 + tof, info.textureType, info.format, width, height, depth, maxBlockHeight, mipSize, special, special_pad, fname, textures, rapi, Noesis_UntileBlockLinearGOBs, NoesisMisc_ASTC_DecodeRaw32);
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