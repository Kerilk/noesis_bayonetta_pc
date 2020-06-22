#pragma once
template <>
static void Model_Bayo_GetTextureBundle<VANQUISH>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA>(texFiles, dfiles, df, rapi);
}

template <>
static void Model_Bayo_LoadTextures<false, VANQUISH>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	Model_Bayo_LoadTextures_impl(textures, texFiles, rapi);	//insert a flat normal map placeholder
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
	snprintf(texName, MAX_NOESIS_PATH, "%s%08x.wtb", texDir, texId);
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
