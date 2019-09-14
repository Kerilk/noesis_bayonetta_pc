#pragma once
template <>
static void Model_Bayo_CreateNormal<true, ANARCHY_REIGNS>(char *src, float *dst) {
	DWORD r;
	memcpy(&r, src, sizeof(r));
	LITTLE_BIG_SWAP(r);
	int xBits = 11;
	int yBits = 11;
	int zBits = 10;
	int x = ((r >> 0) & ((1 << xBits) - 1));
	int y = ((r >> xBits) & ((1 << yBits) - 1));
	int z = ((r >> (xBits + yBits)) & ((1 << zBits) - 1));
	dst[0] = (float)SignedBits(x, xBits) / (float)((1 << (xBits - 1)) - 1);
	dst[1] = (float)SignedBits(y, yBits) / (float)((1 << (yBits - 1)) - 1);
	dst[2] = (float)SignedBits(z, zBits) / (float)((1 << (zBits - 1)) - 1);
}

template <>
static void Model_Bayo_CreateTangents<true, ANARCHY_REIGNS>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m)
{
	Model_Bayo_CreateTangents<true, BAYONETTA>(data, dsts, numVerts, stride, m);
}

template <>
static void Model_Bayo_LoadTextures<true, ANARCHY_REIGNS>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr_t hdr = *((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "\0BTW", 4))
	{ //not a valid texture bundle
		return;
	}
	LITTLE_BIG_SWAP(hdr.numTex);
	LITTLE_BIG_SWAP(hdr.ofsTexOfs);
	LITTLE_BIG_SWAP(hdr.ofsTexSizes);
	LITTLE_BIG_SWAP(hdr.ofsTexFlags);
	LITTLE_BIG_SWAP(hdr.texIdxOffset);
	LITTLE_BIG_SWAP(hdr.texInfoOffset);
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}

	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	DBGLOG("Found %d textures\n", hdr.numTex);
	for (int i = 0; i < hdr.numTex; i++)
	{
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayotex%03i", rapi->Noesis_GetOption("texpre"), i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		int ofs = tofs[i];
		int size = tsizes[i];
		LITTLE_BIG_SWAP(ofs);
		LITTLE_BIG_SWAP(size);
		if (ofs < 0 || ofs > dataSize)
		{
			continue;
		}
		BYTE *texData = data + ofs;
		BYTE *pix;
		int globalIdx = -1;
		wtbTexHdr_t tex;
		if (hdr.texIdxOffset)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
			LITTLE_BIG_SWAP(globalIdx);
		}
		if (hdr.texInfoOffset)
		{ //texture info is contiguous in its own section
			wtbTexHdr_t *thdr = (wtbTexHdr_t  *)(data + hdr.texInfoOffset + sizeof(wtbTexHdr_t)*i);
			tex = *thdr;
			pix = texData;
		}
		else
		{
			tex = *((wtbTexHdr_t *)texData);
			pix = texData + sizeof(wtbTexHdr_t);
		}
		LITTLE_BIG_SWAP(tex.unknownJ);
		LITTLE_BIG_SWAP(tex.unknownO);
		LITTLE_BIG_SWAP(tex.unknownP);
		LITTLE_BIG_SWAP(tex.unknownQ);
		LITTLE_BIG_SWAP(tex.texFmt);
		LITTLE_BIG_SWAP(tex.heightBits);
		LITTLE_BIG_SWAP(tex.widthBits);
		if (tex.texFmt == 0)
		{
			noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
			continue;
		}
		int width = (((tex.widthBits >> 5) & 127) + 1) << 5;
		int height = ((tex.heightBits & 1023) + 1) << 3;

		bool endianSwap = true;
		bool untile = !!(tex.unknownJ & 32768);
		bool uncompressed = false;
		bool channelSwiz = false;
		int dxtFmt = NOESISTEX_RGBA32;
		int texFlags = 0;
		if (tex.unknownJ > 0)
		{ //just a guess
			texFlags |= NTEXFLAG_SEGMENTED;
		}
		DBGLOG("\t%03d (idx %x): ", i, globalIdx);
		switch (tex.texFmt)
		{
		case 82:
			dxtFmt = NOESISTEX_DXT1;
			DBGLOG("DXT1\n");
			break;
		case 83:
			dxtFmt = NOESISTEX_DXT3;
			DBGLOG("DXT3\n");
			break;
		case 84:
			dxtFmt = NOESISTEX_DXT5;
			DBGLOG("DXT5\n");
			break;
		case 134:
			dxtFmt = NOESISTEX_RGBA32;
			DBGLOG("RGBA32\n");
			uncompressed = true;
			channelSwiz = true;
			break;
		default:
			assert(0);
			rapi->LogOutput("WARNING: Unknown texture format %i.\n", tex.texFmt);
			dxtFmt = NOESISTEX_DXT1;
			break;
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
				rapi->Noesis_UntileImageRAWEx(untiledMip, pix, mipSize, width, height, bytesPerPixel,size, 0, 0);
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
				rapi->Noesis_UntileImageDXTEx(untiledMip, pix, mipSize, width, height, (dxtFmt == NOESISTEX_DXT1) ? 8 : 16, size, 0, 0);
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
static void Model_Bayo_GetTextureBundle<ANARCHY_REIGNS>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA>(texFiles, dfiles, df, rapi);
}

template <>
static void Model_Bayo_LoadScenery<true, ANARCHY_REIGNS>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
}