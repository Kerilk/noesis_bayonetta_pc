#pragma once
template <>
static void Model_Bayo_GetTextureBundle<VANQUISH>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA>(texFiles, dfiles, df, rapi);
}

template <>
static void Model_Bayo_LoadTextures<false, VANQUISH>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr<false> hdr((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "WTB\0", 4))
	{ //not a valid texture bundle
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}
	DBGLOG("Found %d textures\n", hdr.numTex);
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *tflags = (int *)(data + hdr.ofsTexFlags);
	for (int i = 0; i < hdr.numTex; i++)
	{
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayotex%03i", rapi->Noesis_GetOption("texpre"), i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		int ofs = tofs[i];
		int size = tsizes[i];
		if (ofs < 0 || ofs > dataSize)
		{
			continue;
		}
		BYTE *texData = data + ofs;
		BYTE *pix;
		int globalIdx = -1;
		ddsTexHdr_t tex;
		if (hdr.texIdxOffset)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
		}
		if (hdr.texInfoOffset)
		{ //texture info is contiguous in its own section
			ddsTexHdr_t *thdr = (ddsTexHdr_t  *)(data + hdr.texInfoOffset + sizeof(ddsTexHdr_t)*i);
			tex = *thdr;
			pix = texData;
		}
		else
		{
			tex = *((ddsTexHdr_t *)texData);
			pix = texData + sizeof(ddsTexHdr_t);
		}
		if (memcmp(tex.id, "DDS ", 4))
		{
			noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
			continue;
		}
		int width = tex.width;
		int height = tex.height;

		bool endianSwap = false;
		bool untile = false;//!!(tex.unknownJ & 32768);
		bool uncompressed = false;
		bool channelSwiz = false;
		int dxtFmt = NOESISTEX_RGBA32;
		int texFlags = 0;
		/*
		if (tex.unknownJ > 0)
		{ //just a guess
		texFlags |= NTEXFLAG_SEGMENTED;
		}
		*/
		DBGLOG("\t%03d (idx %x, flags %x): ", i, globalIdx, tflags[i]);
		if (tex.pixelFormat.flags & 0x4) { //DDPF_FOURCC
			DBGLOG("%4s\n", (char *)&(tex.pixelFormat.id));
			switch (tex.pixelFormat.id)
			{
			case 0x31545844: //"DXT1"
				dxtFmt = NOESISTEX_DXT1;
				break;
			case 0x33545844: //"DXT3"
				dxtFmt = NOESISTEX_DXT3;
				break;
			case 0x34545844: //"DXT4"
			case 0x35545844: //"DXT5"
				dxtFmt = NOESISTEX_DXT5;
				break;
				/*		case 134:
				dxtFmt = NOESISTEX_RGBA32;
				uncompressed = true;
				channelSwiz = true;
				break;*/
			default:
				assert(0);
				rapi->LogOutput("WARNING: Unknown texture format %x.\n", tex.pixelFormat.id);
				dxtFmt = NOESISTEX_DXT1;
				break;
			}
		}
		else if (tex.pixelFormat.flags & 0x41) {
			DBGLOG("RGBA\n");
			dxtFmt = NOESISTEX_RGBA32;
			uncompressed = true;
			channelSwiz = true;
		}
		else {
			assert(0);
			rapi->LogOutput("WARNING: Unknown texture format %x.\n", tex.pixelFormat.id);
			dxtFmt = NOESISTEX_DXT1;
		}
		int mipSize;
		BYTE *untiledMip;
		if (uncompressed)
		{
			int bytesPerPixel = (dxtFmt == NOESISTEX_RGB24) ? 3 : 4;
			mipSize = (width*height)*bytesPerPixel;
			untiledMip = (BYTE *)rapi->Noesis_PooledAlloc(mipSize);
			if (untile)
			{
				rapi->Noesis_UntileImageRAW(untiledMip, pix, mipSize, width, height, bytesPerPixel);
			}
			else
			{
				memcpy(untiledMip, pix, mipSize);
			}
			if (endianSwap)
			{
				int swapCount = bytesPerPixel;
				for (int i = 0; i < mipSize - swapCount; i += swapCount)
				{
					LittleBigSwap(untiledMip + i, swapCount);
				}
			}
			if (channelSwiz)
			{
				int swapCount = 4;
				for (int i = 0; i < mipSize - swapCount; i += swapCount)
				{
					BYTE *p = untiledMip + i;
					BYTE t = p[0];
					p[0] = p[2];
					p[2] = t;
					p[3] = 255;
					//if i knew which textures were normal maps, they could be made consistent with this
					//rapi->Noesis_SwizzleNormalPix(p, false, true, false);
				}
			}
		}
		else
		{
			mipSize = (dxtFmt == NOESISTEX_DXT1) ? (width*height) / 2 : (width*height);
			untiledMip = (BYTE *)rapi->Noesis_PooledAlloc(mipSize);
			if (untile)
			{
				rapi->Noesis_UntileImageDXT(untiledMip, pix, mipSize, width, height, (dxtFmt == NOESISTEX_DXT1) ? 8 : 16);
			}
			else
			{
				memcpy(untiledMip, pix, mipSize);
			}
			if (endianSwap)
			{
				int swapCount = 2;
				for (int j = 0; j < mipSize - swapCount; j += swapCount)
				{
					LittleBigSwap(untiledMip + j, swapCount);
				}
			}
		}
		noesisTex_t *nt = rapi->Noesis_TextureAlloc(fname, width, height, untiledMip, dxtFmt);
		nt->flags |= texFlags;
		nt->shouldFreeData = false; //because the untiledMip data is pool-allocated, it does not need to be freed
		nt->globalIdx = globalIdx;
		textures.Append(nt);
	}
}

template <>
static void Model_Bayo_CreateNormal<false, VANQUISH>(char *src, float *dst) {
	Model_Bayo_CreateNormal<false, BAYONETTA>(src, dst);
}

template <>
static void Model_Bayo_CreateTangents<false, VANQUISH>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
	Model_Bayo_CreateTangents<false, BAYONETTA>(data, dsts, numVerts, stride, m);
}

template <bool big, game_t game>
static void Model_Vanquish_LoadExtraTex(char *texDir, int texId, noeRAPI_t *rapi, CArrayList<noesisTex_t *> &textures) {
	//Try to load from texture directory
	char texName[MAX_NOESIS_PATH];
	snprintf(texName, MAX_NOESIS_PATH, "%s%0x.wtb", texDir, texId);
	DBGLOG("Trying to load %s...\n", texName);
	bayoDatFile_t wtbFile;
	wtbFile.name = texName;
	wtbFile.data = (BYTE *)rapi->Noesis_ReadFile(texName, &wtbFile.dataSize);
	if (wtbFile.data && wtbFile.dataSize > 0)
	{
		CArrayList<bayoDatFile_t *> texFiles;
		int numText = textures.Num();
		texFiles.Append(&wtbFile);
		DBGLOG("...Found Texture!\n");
		Model_Bayo_LoadTextures<big, game>(textures, texFiles, rapi);
	}
	else {
		DBGLOG("...Texture not found!\n");
	}
}

template <>
static void Model_Bayo_LoadScenery<false, VANQUISH>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
}