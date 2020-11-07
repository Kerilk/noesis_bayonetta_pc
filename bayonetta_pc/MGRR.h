#pragma once
typedef struct MGRRWmbHdr_s {
	char			id[4]; //WMB4
	unsigned int	u_a;
	unsigned int	vertexFormat;
	unsigned short	u_b;
	short			u_c;
	float			position1[3];
	float			position2[3];
	unsigned int	offsetVertexGroups;
	unsigned int	numVertexGroups;
	unsigned int	offsetBatches;
	unsigned int	numBatches;
	unsigned int	offsetBatchDescription;
	unsigned int	offsetBones;
	unsigned int	numBones;
	unsigned int	offsetBoneIndexTranslateTable;
	unsigned int	sizeBoneIndexTranslateTable;
	unsigned int	offsetBoneSets;
	unsigned int	numBoneSets;
	unsigned int	offsetMaterials;
	unsigned int	numMaterials;
	unsigned int	offsetTextures;
	unsigned int	numTextures;
	unsigned int	offsetMeshes;
	unsigned int	numMeshes;
} MGRRWmbHdr_t;

template <bool big>
struct MGRRWmbHdr : public MGRRWmbHdr_s {
	MGRRWmbHdr(MGRRWmbHdr_t *ptr) : MGRRWmbHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(u_a);
			LITTLE_BIG_SWAP(vertexFormat);
			LITTLE_BIG_SWAP(u_b);
			LITTLE_BIG_SWAP(u_c);
			for (int i = 0; i < 3; i++) {
				LITTLE_BIG_SWAP(position1[i]);
				LITTLE_BIG_SWAP(position2[i]);
			}
			LITTLE_BIG_SWAP(offsetVertexGroups);
			LITTLE_BIG_SWAP(numVertexGroups);
			LITTLE_BIG_SWAP(offsetBatches);
			LITTLE_BIG_SWAP(numBatches);
			LITTLE_BIG_SWAP(offsetBatchDescription);
			LITTLE_BIG_SWAP(offsetBones);
			LITTLE_BIG_SWAP(numBones);
			LITTLE_BIG_SWAP(offsetBoneIndexTranslateTable);
			LITTLE_BIG_SWAP(sizeBoneIndexTranslateTable);
			LITTLE_BIG_SWAP(offsetBoneSets);
			LITTLE_BIG_SWAP(numBoneSets);
			LITTLE_BIG_SWAP(offsetMaterials);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(offsetTextures);
			LITTLE_BIG_SWAP(numTextures);
			LITTLE_BIG_SWAP(offsetMeshes);
			LITTLE_BIG_SWAP(numMeshes);
		}
	}
};

typedef struct MGRRMaterial_s {
	unsigned int	offsetShaderName;
	unsigned int	offsetTextures;
	unsigned int	u_a;
	unsigned int	offsetParameters;
	unsigned short	numTextures;
	unsigned short	u_c;
	unsigned short	u_d;
	unsigned short	numParameters;
} MGRRMaterial_t;

template <bool big>
struct MGRRMaterial : public MGRRMaterial_s {
	MGRRMaterial(MGRRMaterial_t *ptr) : MGRRMaterial_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offsetShaderName);
			LITTLE_BIG_SWAP(offsetTextures);
			LITTLE_BIG_SWAP(u_a);
			LITTLE_BIG_SWAP(offsetParameters);
			LITTLE_BIG_SWAP(numTextures);
			LITTLE_BIG_SWAP(u_c);
			LITTLE_BIG_SWAP(u_d);
			LITTLE_BIG_SWAP(numParameters);
		}
	}
};

typedef struct MGRRTextures_s {
	unsigned int	tex0;
	unsigned int	albedoMap;
	unsigned int	tex2;
	unsigned int	tex3;
	unsigned int	tex4;
	unsigned int	tex5;
	unsigned int	tex6;
	unsigned int	normalMap;
} MGRRTextures_t;

template <bool big>
struct MGRRTextures : public MGRRTextures_s {
	MGRRTextures(MGRRTextures_t *ptr) : MGRRTextures_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(tex0);
			LITTLE_BIG_SWAP(albedoMap);
			LITTLE_BIG_SWAP(tex2);
			LITTLE_BIG_SWAP(tex3);
			LITTLE_BIG_SWAP(tex4);
			LITTLE_BIG_SWAP(tex5);
			LITTLE_BIG_SWAP(tex6);
			LITTLE_BIG_SWAP(normalMap);
		}
	}
};

typedef struct MGRRTexture_s {
	unsigned int flags;
	int id;
} MGRRTexture_t;
template <bool big>
struct MGRRTexture : public MGRRTexture_s {
	MGRRTexture(MGRRTexture_t *ptr) : MGRRTexture_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flags);
			LITTLE_BIG_SWAP(id);
		}
	}
};

typedef struct MGRRVertexGroup_s {
	unsigned int	offsetVertexes;
	unsigned int	offsetVertexesExData;
	unsigned int	unknownOffsets[2];
	unsigned int	numVertexes;
	unsigned int	offsetIndexes;
	unsigned int	numIndexes;
} MGRRVertexGroup_t;
template <bool big>
struct MGRRVertexGroup : public MGRRVertexGroup_s {
	MGRRVertexGroup(MGRRVertexGroup_t *ptr) : MGRRVertexGroup_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offsetVertexes);
			LITTLE_BIG_SWAP(offsetVertexesExData);
			LITTLE_BIG_SWAP(unknownOffsets[0]);
			LITTLE_BIG_SWAP(unknownOffsets[1]);
			LITTLE_BIG_SWAP(numVertexes);
			LITTLE_BIG_SWAP(offsetIndexes);
			LITTLE_BIG_SWAP(numIndexes);
		}
	}
};

typedef struct MGRRBone_s {
	short	unknownNumber1;
	short	unknownNumber2;
	short	parentIndex;
	short	u_a;
	float	relativePosition[3];
	float	position[3];
} MGRRBone_t;
template <bool big>
struct MGRRBone : public MGRRBone_s {
	MGRRBone(MGRRBone_t *ptr) : MGRRBone_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownNumber1);
			LITTLE_BIG_SWAP(unknownNumber2);
			LITTLE_BIG_SWAP(parentIndex);
			LITTLE_BIG_SWAP(u_a);
			for (int i = 0; i < 3; i++) {
				LITTLE_BIG_SWAP(relativePosition[i]);
				LITTLE_BIG_SWAP(position[i]);
			}
		}
	}
};

typedef struct MGRRBoneSet_s {
	unsigned int	offsetBoneRefs;
	unsigned int	numBones;
} MGRRBoneSet_t;
template <bool big>
struct MGRRBoneSet : public MGRRBoneSet_s {
	MGRRBoneSet(MGRRBoneSet_t * ptr) : MGRRBoneSet_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offsetBoneRefs);
			LITTLE_BIG_SWAP(numBones);
		}
	}
};

typedef struct MGRRMesh_s {
	unsigned int	offsetName;
	float			boundingBox[6];
	unsigned int	offsetBatches;
	unsigned int	numBatches;
	unsigned int	offsetBatches1;
	unsigned int	numBatches1;
	unsigned int	offsetBatches2;
	unsigned int	numBatches2;
	unsigned int	offsetBatches3;
	unsigned int	numBatches3;
	unsigned int	offsetMaterials;
	unsigned int	numMaterials;
} MGRRMesh_t;
template <bool big>
struct MGRRMesh : public MGRRMesh_s {
	MGRRMesh(MGRRMesh_t *ptr) : MGRRMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offsetName);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(boundingBox[i]);
			}
			LITTLE_BIG_SWAP(offsetBatches);
			LITTLE_BIG_SWAP(numBatches);
			LITTLE_BIG_SWAP(offsetBatches1);
			LITTLE_BIG_SWAP(numBatches1);
			LITTLE_BIG_SWAP(offsetBatches2);
			LITTLE_BIG_SWAP(numBatches2);
			LITTLE_BIG_SWAP(offsetBatches3);
			LITTLE_BIG_SWAP(numBatches3);
			LITTLE_BIG_SWAP(offsetMaterials);
			LITTLE_BIG_SWAP(numMaterials);
		}
	}
};

typedef struct MGRRBatch_s {
	unsigned int	vertexGroupIndex;
	int				vertexStart;
	int				indexStart;
	unsigned int	numVertices;
	unsigned int	numIndices;
} MGRRBatch_t;
template <bool big>
struct MGRRBatch : public MGRRBatch_s {
	MGRRBatch(MGRRBatch_t *ptr) : MGRRBatch_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(vertexGroupIndex);
			LITTLE_BIG_SWAP(vertexStart);
			LITTLE_BIG_SWAP(indexStart);
			LITTLE_BIG_SWAP(numVertices);
			LITTLE_BIG_SWAP(numIndices);
		}
	}
};

typedef struct MGRRBatchData_s {
	unsigned int	batchIndex;
	unsigned int	meshIndex;
	unsigned short	materialIndex;
	unsigned short	boneSetIndex;
	unsigned int	u_a;
} MGRRBatchData_t;
template <bool big>
struct MGRRBatchData : public MGRRBatchData_s {
	MGRRBatchData(MGRRBatchData_t *ptr) : MGRRBatchData_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(batchIndex);
			LITTLE_BIG_SWAP(meshIndex);
			LITTLE_BIG_SWAP(materialIndex);
			LITTLE_BIG_SWAP(boneSetIndex);
			LITTLE_BIG_SWAP(u_a);
		}
	}
};

typedef struct MGRRBatchDescription_s {
	unsigned int	offsetBatchData;
	unsigned int	numBatchData;
	unsigned int	offsetBatchData1;
	unsigned int	numBatchData1;
	unsigned int	offsetBatchData2;
	unsigned int	numBatchData2;
	unsigned int	offsetBatchData3;
	unsigned int	numBatchData3;
} MGRRBatchDescription_t;
template <bool big>
struct MGRRBatchDescription : public MGRRBatchDescription_s {
	MGRRBatchDescription(MGRRBatchDescription_t *ptr) : MGRRBatchDescription_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offsetBatchData);
			LITTLE_BIG_SWAP(numBatchData);
			LITTLE_BIG_SWAP(offsetBatchData1);
			LITTLE_BIG_SWAP(numBatchData1);
			LITTLE_BIG_SWAP(offsetBatchData2);
			LITTLE_BIG_SWAP(numBatchData2);
			LITTLE_BIG_SWAP(offsetBatchData3);
			LITTLE_BIG_SWAP(numBatchData3);
		}
	}
};

template <>
static void Model_Bayo_GetTextureBundle<MGRR>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}

static void Model_MGRR_GetSCRTextureBundle(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, "scr.wtb");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
}

static void Model_MGRR_LoadWtbTextures(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	const bool big = false;
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}

	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	bayoWTBHdr<big> hdr((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "WTB\0", 4) != 0)
	{
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}
	DBGLOG("found valid texture file, containing %d textures\n", hdr.numTex);
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	for (int i = 0; i < hdr.numTex; i++)
	{
		int globalIdx;
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		if (hdr.texIdxOffset)
		{
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
		}
		DBGLOG("%s: 0x%0x\n", fname, globalIdx);


		noesisTex_t	*nt = rapi->Noesis_LoadTexByHandler(data + tofs[i], tsizes[i], ".dds");
		if (nt) {
			nt->filename = rapi->Noesis_PooledString(fname);
			textures.Append(nt);
		}
		else {
			DBGLOG("Could not load texture %s\n", fname);
			nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
		}

		nt->globalIdx = globalIdx;

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
static void Model_Bayo_LoadTextures<false, MGRR>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	const bool big = false;
	if (texFiles.Num() == 1) {
		Model_MGRR_LoadWtbTextures(textures, texFiles, rapi);
		return;
	}
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	int dataSize2 = texFiles[1]->dataSize;
	BYTE * data2 = texFiles[1]->data;
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	if (dataSize < sizeof(bayoWTAHdr_t))
	{
		return;
	}
	bayoWTAHdr<big> hdr((bayoWTAHdr_t *)data);
	if (memcmp(hdr.id, "WTB\0", 4))
	{
		Model_MGRR_LoadWtbTextures(textures, texFiles, rapi);
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}
	DBGLOG("found valid texture header file, containing %d textures\n", hdr.numTex);
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	for (int i = 0; i < hdr.numTex; i++)
	{
		int globalIdx;
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		if (hdr.texIdxOffset)
		{
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
		}
		DBGLOG("%s: 0x%0x\n", fname, globalIdx);

		noesisTex_t	*nt = rapi->Noesis_LoadTexByHandler(data2 + tofs[i], tsizes[i], ".dds");
		if (nt) {
			nt->filename = rapi->Noesis_PooledString(fname);
			textures.Append(nt);
		}
		else {
			DBGLOG("Could not load texture %s\n", fname);
			nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
		}
		nt->globalIdx = globalIdx;

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
static void Model_Bayo_CreateNormal<false, MGRR>(char *src, float *dst) {
	DWORD r;
	memcpy(&r, src, sizeof(r));
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
static void Model_Bayo_CreateTangents<false, MGRR>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
	for (int i = 0; i < numVerts; i++)
	{
		BYTE *src = data + stride * i;
		float tmp[3];
		float *dst = dsts + i * 4;
		for (int j = 0; j < 4; j++) {
			dst[j] = (src[j] - (float)127) / (float)127;
		}
		// handedness is reverse here:
		if (m) {
			g_mfn->Math_TransformPointByMatrixNoTrans(m, dst, tmp);
			g_mfn->Math_VecCopy(tmp, dst);
		}
	}
}

template <bool big>
modelBone_t *Model_MGRR_CreateBones(MGRRWmbHdr<big> &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT)
{
	numBones = 0;
	if (hdr.numBones <= 0 || hdr.offsetBones == 0)
	{
		return NULL;
	}
	animBoneTT = (short int *)(data + hdr.offsetBoneIndexTranslateTable);
	std::map<short int, short int> boneMap;
	for (short int i = 0; i < 0x1000; i++) {
		short int decoded_index = Model_Bayo_DecodeMotionIndex<big, MGRR>(animBoneTT, i);
		if (decoded_index != 0x0fff) {
			boneMap.insert(std::pair <short int, short int>(decoded_index, i));
		}
	}

	numBones = hdr.numBones;
	DBGLOG("Found %d bones\n", numBones);
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones + 1);

	for (int i = 0; i < numBones; i++)
	{
		modelBone_t *bone = bones + i;
		MGRRBone<big> mgrrBone((MGRRBone_t*)(data + hdr.offsetBones + i * sizeof(MGRRBone_t)));
		bone->index = i;
		short parent = mgrrBone.parentIndex;
		if (parent == -1) {
			bone->eData.parent = bones + numBones;
		}
		else if (parent >= 0) {
			bone->eData.parent = bones + parent;
		}
		else {
			bone->eData.parent = NULL;
		}
		sprintf_s(bone->name, 30, "bone%03i", boneMap.at((short int)i));
		bone->mat = g_identityMatrix;
		g_mfn->Math_VecCopy(mgrrBone.position, bone->mat.o);
		bone->userIndex = 5;
	}

	bones[numBones].index = numBones;
	bones[numBones].eData.parent = NULL;
	sprintf_s(bones[numBones].name, 30, "bone-1");
	bones[numBones].mat = g_identityMatrix;
	bones[numBones].userIndex = 5;

	return bones;
}

template <bool big, game_t game>
static void Model_MGRR_LoadMaterials(MGRRWmbHdr<big> &hdr,
	CArrayList<noesisTex_t *> &textures,
	CArrayList<noesisMaterial_t *> &matList,
	CArrayList<noesisMaterial_t *> &matListLightMap,
	CArrayList<noesisMaterial_t *> &totMatList,
	BYTE *data,
	noeRAPI_t *rapi,
	const char *prefix = "bayomat") {

	MGRRMaterial_t *matPtr = (MGRRMaterial_t *)(data + hdr.offsetMaterials);

	DBGLOG("Found %d materials\n", hdr.numMaterials);
	for (unsigned int i = 0; i < hdr.numMaterials; i++)
	{
		char name[256];
		MGRRMaterial<big> mat(matPtr + i);
		sprintf_s(name, 256, "%s_%03d_%s", prefix, i, data + mat.offsetShaderName);
		DBGLOG("\tFound %s\n", name);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		nmat->name = rapi->Noesis_PooledString(name);
		nmat->noDefaultBlend = true;
		nmat->texIdx = -1;
		nmat->normalTexIdx = textures.Num() - 1;
		nmat->specularTexIdx = -1;
		unsigned int difTexIndex = 0;
		unsigned int nrmTexIndex = 0;
		//int specTexIndex = 0;
		DBGLOG("\tFound %d textures\n", mat.numTextures);
		MGRRTextures<big> texs((MGRRTextures_t*)(data + mat.offsetTextures));
		difTexIndex = texs.albedoMap;
		nrmTexIndex = texs.normalMap;


		int difTexId = 0;
		int nrmTexId = 0;
		if (difTexIndex < hdr.numTextures) {
			MGRRTexture<big> difTex((MGRRTexture_t*)(data + hdr.offsetTextures + difTexIndex * sizeof(MGRRTexture_t)));
			difTexId = difTex.id;
		}
		if (nrmTexIndex < hdr.numTextures) {
			MGRRTexture<big> nrmTex((MGRRTexture_t*)(data + hdr.offsetTextures + nrmTexIndex * sizeof(MGRRTexture_t)));
			nrmTexId = nrmTex.id;
		}

		for (int j = 0; j < textures.Num(); j++) {
			noesisTex_t *tex = textures[j];
			if (difTexId && tex->globalIdx == difTexId) {
				DBGLOG("Found matching texture %d\n", j);
				nmat->texIdx = j;
			}
			if (nrmTexId && tex->globalIdx == nrmTexId) {
				DBGLOG("Found matching normal %d\n", j);
				nmat->normalTexIdx = j;
			}
			/*			if (specTexId && tex->globalIdx == specTexId) {
							DBGLOG("Found matching specular %d\n", j);
							nmat->specularTexIdx = j;
							nmat->flags |= NMATFLAG_PBR_SPEC_IR_RG;
						}*/
		}
		if (nmat->texIdx == -1 && strncmp(name, "cnm21", 5) == 0) {
			nmat->skipRender = true;
		}
		matListLightMap.Append(NULL);
		matList.Append(nmat);
		totMatList.Append(nmat);
	}
}

typedef struct MGRRBuffers_s : public buffers_s {
	buffer_t indices;
} MGRRBuffers_t;

template <bool big, game_t game>
static void Model_MGRR_SetBuffers(bayoDatFile_t &df, noeRAPI_t *rapi, MGRRWmbHdr<false> &hdr, MGRRBuffers_t *buffers, modelMatrix_t * pretransform) {
	BYTE *data = df.data;
	for (unsigned int i = 0; i < hdr.numVertexGroups; i++) {
		MGRRVertexGroup<big> vg((MGRRVertexGroup_t*)(data + hdr.offsetVertexGroups + i * sizeof(MGRRVertexGroup_t)));

		int numVerts = vg.numVertexes;
		BYTE *indices = data + vg.offsetIndexes;
		BYTE *verts = data + vg.offsetVertexes;
		BYTE *vertsEx = data + vg.offsetVertexesExData;
		DBGLOG("Found format %x\n", hdr.vertexFormat);
		if (hdr.vertexFormat == 0x10337) {
			int bayoVertSize = 0x20;
			int bayoVertExSize = 0x8;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 24, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 28, bayoVertSize);

			__set_color<big, game>(buffers[i].color, vertsEx, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping2, vertsEx + 4, bayoVertExSize);
		}
		else if (hdr.vertexFormat == 0x337) {
			int bayoVertSize = 0x20;
			int bayoVertExSize = 0x8;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 24, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 28, bayoVertSize);

			__set_color<big, game>(buffers[i].color, vertsEx, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping2, vertsEx + 4, bayoVertExSize);
		}
		else if (hdr.vertexFormat == 0x10307) {
			int bayoVertSize = 0x20;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 28, bayoVertSize);
		}
		else if (hdr.vertexFormat == 0x10137) {
			int bayoVertSize = 0x20;
			int bayoVertExSize = 0x4;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 24, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 28, bayoVertSize);

			__set_color<big, game>(buffers[i].color, vertsEx, bayoVertExSize);
		}
		else if (hdr.vertexFormat == 0x10107) {
			int bayoVertSize = 0x1c;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);
		}
		else if (hdr.vertexFormat == 0x137) {
			int bayoVertSize = 0x20;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 24, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 28, bayoVertSize);
		}
		else if (hdr.vertexFormat == 0x107) {
			int bayoVertSize = 0x18;
			__set_sindices<big, game>(buffers[i].indices, indices, 2);

			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_normal<big, game>(buffers[i].normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		}
		else {
			DBGLOG("Unknown vertex format: %x!!!\n", hdr.vertexFormat);
#ifdef _DEBUG
			g_nfn->NPAPI_PopupDebugLog(0);
#endif
			continue;
		}
	}
}

template <>
static void Model_Bayo_LoadModel<false, MGRR>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset, const char *prefix, CArrayList<noesisMaterial_t *> *globalMatList) {
	static const bool big = false;
	static const game_t game = MGRR;
	DBGLOG("Loading %s\n", df.name);
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(MGRRWmbHdr_t))
	{
		return;
	}
	MGRRWmbHdr<big> hdr((MGRRWmbHdr_t *)data);
	if (memcmp(hdr.id, "WMB4", 4) || hdr.numVertexGroups == 0)
	{ //invalid header
		return;
	}

	CArrayList<bayoDatFile_t *> motfiles;
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<bayoDatFile_t *> expfile;
	CArrayList<noesisTex_t *> textures;
	CArrayList<noesisMaterial_t *> matList;
	CArrayList<noesisMaterial_t *> matListLightMap;
	CArrayList<noesisMaterial_t *> totMatList;
	CArrayList<noesisAnim_t *> animList;

	MGRRBuffers_t *buffers = (MGRRBuffers_t *)rapi->Noesis_UnpooledAlloc(hdr.numVertexGroups * sizeof(MGRRBuffers_t));
	memset(buffers, 0, hdr.numVertexGroups * sizeof(MGRRBuffers_t));

	if (givenTextures.Num() == 0) {
		Model_Bayo_GetTextureBundle<game>(texFiles, dfiles, df, rapi);
		if (texFiles.Num() > 0)
		{
			for (int i = 0; i < texFiles.Num(); i++) {
				DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
			}

			CArrayList<bayoDatFile_t *> newTexFiles;
			for (int i = 0; i < texFiles.Num(); i += 2) {
				CArrayList<bayoDatFile_t *> newTexFiles;
				newTexFiles.Append(texFiles[i]);
				newTexFiles.Append(texFiles[i + 1]);
				Model_Bayo_LoadTextures<big, game>(textures, newTexFiles, rapi);
			}
		}
	}
	else {
		for (int i = 0; i < givenTextures.Num(); i++) {
			textures.Append(givenTextures[i]);
		}
	}

	Model_MGRR_LoadMaterials<big, game>(hdr, textures, matList, matListLightMap, globalMatList ? *globalMatList : totMatList, data, rapi, globalMatList ? prefix : "bayomat");
	Model_MGRR_SetBuffers<big, game>(df, rapi, hdr, buffers, pretransform);
	if (!buffers[0].position.address) {
		rapi->Noesis_UnpooledFree(buffers);
		return;
	}

	void *pgctx = NULL;
	int numBones = 0;
	short int * animBoneTT = NULL;
	modelBone_t *bones = NULL;
	if (!prefix) {
		pgctx = rapi->rpgCreateContext();
		rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
		rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);

		bones = Model_MGRR_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);
		Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
		Model_Bayo_GetEXPFile(dfiles, df, rapi, expfile);
		if (bones) {
			Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT, data + hdr.offsetBones);
			Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT, data + hdr.offsetBones);
		}
	}

	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	DBGLOG("Found %d batches\n", hdr.numBatches);

	MGRRMesh_t *meshes = (MGRRMesh_t *)(data + hdr.offsetMeshes);
	MGRRBatch_t *batches = (MGRRBatch_t *)(data + hdr.offsetBatches);
	MGRRBoneSet_t *boneSets = NULL;
	if (hdr.offsetBoneSets != 0) {
		boneSets = (MGRRBoneSet_t *)(data + hdr.offsetBoneSets);
	}
	MGRRBatchDescription<big> batchDescription((MGRRBatchDescription_t *)(data + hdr.offsetBatchDescription));

	for (unsigned int i = 0; i < hdr.numMeshes; i++) {
		MGRRMesh<big> mesh(meshes + i);
		for (unsigned int j = 0; j < mesh.numBatches; j++) {
			char batch_name[256];
			if (prefix)
				sprintf_s(batch_name, 256, "%s_%02d(%s)_%02d", prefix, i, (char *)(data + mesh.offsetName), j);
			else
				sprintf_s(batch_name, 256, "%02d(%s)_%02d", i, (char *)(data + mesh.offsetName), j);
			DBGLOG("\t%s\n", batch_name);

			short batchDataIndex = *(short *)(data + mesh.offsetBatches + j * sizeof(short));
			if (big) {
				LITTLE_BIG_SWAP(batchDataIndex);
			}
			MGRRBatchData<big> batchData((MGRRBatchData_t*)(data + batchDescription.offsetBatchData + batchDataIndex * sizeof(MGRRBatchData_t)));
			MGRRBatch<big> batch(batches + batchData.batchIndex);

			unsigned int vertexGroupIndex = batch.vertexGroupIndex;
			unsigned int materialIndex = batchData.materialIndex;
			int vertexStart = batch.vertexStart;

			int *boneIndices = NULL;
			if (bones && batchData.boneSetIndex != 0xffff) {
				MGRRBoneSet<big> boneSet(boneSets + batchData.boneSetIndex);
				boneIndices = (int *)rapi->Noesis_UnpooledAlloc(boneSet.numBones * sizeof(int));
				BYTE* boneRefs = (BYTE*)(data + boneSet.offsetBoneRefs);
				for (unsigned int k = 0; k < boneSet.numBones; k++) {
					boneIndices[k] = boneRefs[k];
				}
			}
			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			rapi->rpgSetBoneMap(boneIndices);
			if (bones && buffers[vertexGroupIndex].bone_indexes.address)
			{
				rapi->rpgBindBoneIndexBuffer(buffers[vertexGroupIndex].bone_indexes.address + vertexStart * buffers[vertexGroupIndex].bone_indexes.stride, buffers[vertexGroupIndex].bone_indexes.type, buffers[vertexGroupIndex].bone_indexes.stride, 4);
				rapi->rpgBindBoneWeightBuffer(buffers[vertexGroupIndex].bone_weights.address + vertexStart * buffers[vertexGroupIndex].bone_weights.stride, buffers[vertexGroupIndex].bone_weights.type, buffers[vertexGroupIndex].bone_weights.stride, 4);
			}
			rapi->rpgBindPositionBuffer(buffers[vertexGroupIndex].position.address + vertexStart * buffers[vertexGroupIndex].position.stride, buffers[vertexGroupIndex].position.type, buffers[vertexGroupIndex].position.stride);
			rapi->rpgBindNormalBuffer(buffers[vertexGroupIndex].normal.address + vertexStart * buffers[vertexGroupIndex].normal.stride, buffers[vertexGroupIndex].normal.type, buffers[vertexGroupIndex].normal.stride);
			rapi->rpgBindUV1Buffer(buffers[vertexGroupIndex].mapping.address + vertexStart * buffers[vertexGroupIndex].mapping.stride, buffers[vertexGroupIndex].mapping.type, buffers[vertexGroupIndex].mapping.stride);
			rapi->rpgSetMaterial(matList[materialIndex]->name);
			rapi->rpgCommitTriangles(buffers[vertexGroupIndex].indices.address + batch.indexStart * buffers[vertexGroupIndex].indices.stride, buffers[vertexGroupIndex].indices.type, batch.numIndices, RPGEO_TRIANGLE, true);

			if (bones && batchData.boneSetIndex != 0xffff) {
				rapi->rpgSetBoneMap(NULL);
				rapi->Noesis_UnpooledFree(boneIndices);
			}
		}
	}

	if (!globalMatList) {
		noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(totMatList, textures);
		rapi->rpgSetExData_Materials(md);
	}
	if (bones) {
		rapi->rpgSetExData_Bones(bones, numBones + 1);
	}
	if (!prefix) {
		int anims_num = animList.Num();
		DBGLOG("Found %d anims\n", anims_num);
		if (anims_num > 700) {
			DBGLOG("Only displaying 700 first animations");
			anims_num = 700;
		}

		noesisAnim_t *anims = rapi->Noesis_AnimFromAnimsList(animList, anims_num);
		if (anims) {
			rapi->rpgSetExData_AnimsNum(anims, 1);
		}
		else if (animList.Num() > 0) {
			DBGLOG("Could not create animation block\n");
		}

		noesisModel_t *mdl = rapi->rpgConstructModel();
		if (mdl) {
			models.Append(mdl);
		}

		rapi->rpgDestroyContext(pgctx);
	}

	rapi->Noesis_UnpooledFree(buffers);
	animList.Clear();
	matList.Clear();
	motfiles.Clear();
	texFiles.Clear();
	textures.Clear();
	matListLightMap.Clear();
	totMatList.Clear();
}

template <bool big>
static void Model_MGRR_LoadScenery(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	const bool big = false;
	DBGLOG("Loading %s\n", df.name);
	bayo2SCRHdr<big> hdr((bayo2SCRHdr_t *)df.data);
	if (memcmp(hdr.id, "SCR\0", 4))
	{ //invalid header
		DBGLOG("Invalid SCR file\n");
		return;
	}
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<noesisTex_t *> textures;
	Model_MGRR_GetSCRTextureBundle(texFiles, olddfiles, df, rapi);
	if (texFiles.Num() > 0)
	{
		for (int i = 0; i < texFiles.Num(); i++) {
			DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
		}
		Model_Bayo_LoadTextures<big, MGRR>(textures, texFiles, rapi);
	}

	CArrayList<bayoDatFile_t> dfiles;

	unsigned int * ofsOffsetsModels = (unsigned int *)(df.data + hdr.ofsOffsetsModels);

	DBGLOG("found %d models in %s\n", hdr.numModels, df.name);
	void *pgctx = NULL;
	CArrayList<noesisMaterial_t *> totMatList;
	if (gpPGOptions->bFuseModels) {
		pgctx = rapi->rpgCreateContext();
		rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
		rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);
	}
	for (int i = 0; i < hdr.numModels; i++) {
		bayoDatFile_t modelFile;
		int dscrOffset = ofsOffsetsModels[i];
		if (big) {
			LITTLE_BIG_SWAP(dscrOffset);
		}
		bayo2SCRModelDscr<big> modelDscr((bayo2SCRModelDscr_t *)(df.data + dscrOffset));
		char modelName[65];
		char fileName[69];
		char prefix[69];
		memset(modelName, 0, 65);
		for (int j = 0; j < 64; j++) {
			modelName[j] = modelDscr.name[j];
		}
		snprintf(fileName, 69, "%s.wmb", modelName);
		snprintf(prefix, 69, "%03d_%s", i, modelName);
		DBGLOG(" model name: %s, ", fileName);
		modelFile.name = rapi->Noesis_PooledString(fileName);
		modelFile.data = df.data + modelDscr.offset;
		if (i < (hdr.numModels - 1)) {
			int nextDscrOffset = ofsOffsetsModels[i + 1];
			if (big) {
				LITTLE_BIG_SWAP(nextDscrOffset);
			}
			modelFile.dataSize = nextDscrOffset - modelDscr.offset;
		}
		else {
			modelFile.dataSize = df.dataSize - modelDscr.offset;
		}
		DBGLOG("start: %d, size: %d\n", modelDscr.offset, modelFile.dataSize);
		modelMatrix_t m;
		Model_Bayo_CreatePreTransformMatrix(modelDscr.transform, m);
		Model_Bayo_LoadModel<big, MGRR>(dfiles, modelFile, rapi, models, textures, &m, - 1,
		                                gpPGOptions->bFuseModels ? prefix : NULL, gpPGOptions->bFuseModels ? &totMatList : NULL);
	}
	if (gpPGOptions->bFuseModels) {
		noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(totMatList, textures);
		rapi->rpgSetExData_Materials(md);
		noesisModel_t *mdl = rapi->rpgConstructModel();
		if (mdl) {
			models.Append(mdl);
		}
		rapi->rpgDestroyContext(pgctx);
	}
	else {
		rapi->SetPreviewOption("drawAllModels", "1");
	}
}

template <>
static void Model_Bayo_LoadScenery<false, MGRR>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	Model_MGRR_LoadScenery<false>(olddfiles, df, rapi, models);
}