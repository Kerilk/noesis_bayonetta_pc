#pragma once
template <>
static void Model_Bayo_GetTextureBundle<ASTRAL_CHAIN>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}
template <>
static void Model_Bayo_LoadTextures<false, ASTRAL_CHAIN>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
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
static void Model_Bayo_LoadModel<false, ASTRAL_CHAIN>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset) {
	Model_Bayo_LoadWMB3Model<false, ASTRAL_CHAIN>(dfiles, df, rapi, models, givenTextures, pretransform, sharedtextureoffset);
}

template <>
static void Model_Bayo_LoadScenery<false, ASTRAL_CHAIN>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
}