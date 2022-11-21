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
static inline noesisTex_t * Model_Game_LoadTexture_Switch<ASTRAL_CHAIN>(bayoDatFile_t *wta, bayoDatFile_t *wtp, bayoWTBHdr<false> &hdr, char * texName, int32_t texIndex, noeRAPI_t *rapi) {
	const bool big = false;
	int dataSize = wta->dataSize;
	BYTE * data = wta->data;
	int dataSize2 = wtp->dataSize;
	BYTE * data2 = wtp->data;

	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *idxs = (int  *)(data + hdr.texIdxOffset);
	ACWTBInfo_t *tinfs = (ACWTBInfo_t  *)(data + hdr.texInfoOffset);

	int tof = tofs[texIndex];
	int tsize = tsizes[texIndex];
	int idx = idxs[texIndex];
	ACWTBInfo<big> info(tinfs + texIndex);

	char fname[8192];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, texIndex);
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);
	DBGLOG("%s: 0x%0x, type: %d, format: %x, width: %d, height: %d, depth: %d, maxBlockHeight: %d\n", fname, idx, info.textureType, info.format, info.width, info.height, info.depth, 1 << (info.blockHeightLog2 & 7));

	int width = info.width;
	int height = info.height;
	int depth = info.depth;
	size_t mipSize = (size_t)info.textureSize;
	int maxBlockHeight = 1 << (info.blockHeightLog2 & 7);
	bool special = info.flags & 0x4;
	int  special_pad = info.specialPad;
	return Model_LoadTextureSwitch(idx, data2 + tof, (xt1_texture_type_t)info.textureType, (xt1_texture_format_t)info.format, width, height, depth, maxBlockHeight, mipSize, special, special_pad, fname, rapi);
}

template <>
static void Model_Bayo_LoadTextures<false, ASTRAL_CHAIN>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	Model_LoadTextures_Switch<ASTRAL_CHAIN>(textures, texFiles, rapi);
}

template <>
static void Model_Bayo_LoadTextures_Set<false, ASTRAL_CHAIN>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi, std::set<int32_t> indices) {
	Model_LoadTextures_Set_Switch<ASTRAL_CHAIN>(textures, texFiles, rapi, indices);
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