#pragma once
typedef struct TDWMBHdr_s
{
	BYTE				id[4];				// 0
	unsigned int		version;			// 4
	int					unknownA;			// 8
	unsigned int		vertexFormat;		// C
	short				unknownB;			// E
	short				unknownC;			//10
	float				boundingBox[6];		//14
	unsigned int		ofsVertexGroups;	//2C
	int					numVertexGroups;	//30
	unsigned int		ofsBatches;			//34
	int					numBatches;			//38
	unsigned int		ofsBatchGroups;		//3C
	unsigned int		ofsBones;			//40
	int					numBones;			//44
	unsigned int		ofsBoneIndexTT;		//48
	int					sizeBoneIndexTT;	//4C
	unsigned int		ofsBoneSets;		//50
	int					numBoneSets;		//54
	unsigned int		ofsMaterials;		//58
	int					numMaterials;		//5C
	unsigned int		ofsTextureIDs;		//60
	int					numTextureIDs;		//64
	unsigned int		ofsMeshes;			//68
	int					numMeshes;			//6C
} TDWMBHdr_t;
template <bool big>
struct TDWMBHdr : public TDWMBHdr_s {
	TDWMBHdr(TDWMBHdr_t * ptr) : TDWMBHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(version);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(vertexFormat);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(unknownC);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(boundingBox[i]);
			}
			LITTLE_BIG_SWAP(ofsVertexGroups);
			LITTLE_BIG_SWAP(numVertexGroups);
			LITTLE_BIG_SWAP(ofsBatches);
			LITTLE_BIG_SWAP(numBatches);
			LITTLE_BIG_SWAP(ofsBatchGroups);
			LITTLE_BIG_SWAP(ofsBones);
			LITTLE_BIG_SWAP(numBones);
			LITTLE_BIG_SWAP(ofsBoneIndexTT);
			LITTLE_BIG_SWAP(sizeBoneIndexTT);
			LITTLE_BIG_SWAP(ofsBoneSets);
			LITTLE_BIG_SWAP(numBoneSets);
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(ofsTextureIDs);
			LITTLE_BIG_SWAP(numTextureIDs);
			LITTLE_BIG_SWAP(ofsMeshes);
			LITTLE_BIG_SWAP(numMeshes);
		}
	}
};
typedef struct TDVertexGroup_s {
	unsigned int	ofsVerts;
	unsigned int	ofsVertsExData;
	unsigned int	unknownA;
	unsigned int	unknownB;
	unsigned int	sizeVert;
	unsigned int	sizeVertExData;
	unsigned int	unknownD;
	unsigned int	unknownE;
	unsigned int	numVerts;
	unsigned int	ofsIndexBuffer;
	unsigned int	numIndexes;
} TDVertexGroup_t;
template <bool big>
struct TDVertexGroup : public TDVertexGroup_s {
	TDVertexGroup(TDVertexGroup_t * ptr) : TDVertexGroup_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsVerts);
			LITTLE_BIG_SWAP(ofsVertsExData);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(sizeVert);
			LITTLE_BIG_SWAP(sizeVertExData);
			LITTLE_BIG_SWAP(unknownD);
			LITTLE_BIG_SWAP(unknownE);
			LITTLE_BIG_SWAP(numVerts);
			LITTLE_BIG_SWAP(ofsIndexBuffer);
			LITTLE_BIG_SWAP(numIndexes);
		}
	}
};
typedef struct TDBatch_s {
	unsigned int	vertexGroupIndex;
	unsigned int	vertexStart;
	unsigned int	indexStart;
	unsigned int	numVerts;
	unsigned int	numIndices;
} TDBatch_t;
template <bool big>
struct TDBatch : public TDBatch_s {
	TDBatch(TDBatch_t * ptr) : TDBatch_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(vertexGroupIndex);
			LITTLE_BIG_SWAP(vertexStart);
			LITTLE_BIG_SWAP(indexStart);
			LITTLE_BIG_SWAP(numVerts);
			LITTLE_BIG_SWAP(numIndices);
		}
	}
};
typedef struct TDBatcGroups_s {
	struct {
		unsigned int ofsBatchGroup;
		unsigned int numBatch;
	} groups[5];
} TDBatchGroups_t;
template <bool big>
struct TDBatchGroups : public TDBatcGroups_s {
	TDBatchGroups(TDBatchGroups_t * ptr) : TDBatcGroups_s(*ptr) {
		if (big) {
			for (int i = 0; i < 5; i++) {
				LITTLE_BIG_SWAP(groups[i].ofsBatchGroup);
				LITTLE_BIG_SWAP(groups[i].numBatch);
			}
		}
	}
};
typedef struct TDBatchInfo_s
{
	unsigned int	batchIndex;
	unsigned int	meshIndex;
	unsigned short	materialIndex;
	short			boneSetIndex;
	int				unknown;
} TDBatchInfo_t;
template <bool big>
struct TDBatchInfo : TDBatchInfo_s {
	TDBatchInfo(TDBatchInfo_t * ptr) : TDBatchInfo_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(batchIndex);
			LITTLE_BIG_SWAP(meshIndex);
			LITTLE_BIG_SWAP(materialIndex);
			LITTLE_BIG_SWAP(boneSetIndex);
			LITTLE_BIG_SWAP(unknown);
		}
	}
};
typedef struct TDBone_s
{
	short			globalId;
	short			ttIndex;
	short			parentIndex;
	short			padding;
	bayoVector_t	localPosition;
	bayoVector_t	position;
} TDBone_t;
template <bool big>
struct TDBone : public TDBone_s {
	TDBone(TDBone_t * ptr) : TDBone_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(globalId);
			LITTLE_BIG_SWAP(ttIndex);
			LITTLE_BIG_SWAP(parentIndex);
			LITTLE_BIG_SWAP(padding);
			localPosition.swap();
			position.swap();
		}
	}
};
typedef struct TDBoneSet_s {
	unsigned int	ofsBoneSet;
	unsigned int	numBoneIndices;
} TDBoneSet_t;
template <bool big>
struct TDBoneSet : public TDBoneSet_s {
	TDBoneSet(TDBoneSet_t * ptr) : TDBoneSet_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsBoneSet);
			LITTLE_BIG_SWAP(numBoneIndices);
		}
	}
};
typedef struct TDMaterial_s
{

	unsigned int	ofsShaderName;
	unsigned int	ofsTextures;
	unsigned int	unknownA;
	unsigned int	ofsParameters;
	unsigned short	unknownB;
	unsigned short	numTextures;
	unsigned short	unknownC;
	unsigned short	numParameters;
} TDMaterial_t;
template <bool big>
struct TDMaterial : public TDMaterial_s {
	TDMaterial(TDMaterial_t * ptr) : TDMaterial_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsShaderName);
			LITTLE_BIG_SWAP(ofsTextures);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(ofsParameters);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(numTextures);
			LITTLE_BIG_SWAP(unknownC);
			LITTLE_BIG_SWAP(numParameters);
		}
	}
};
typedef struct TDTexture_s
{
	unsigned int	ofsName;
	int				textureIndex;
} TDTexture_t;
template <bool big>
struct TDTexture : public TDTexture_s {
	TDTexture(TDTexture_t * ptr) : TDTexture_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			LITTLE_BIG_SWAP(textureIndex);
		}
	}
};
typedef struct TDMesh_s {
	unsigned int	ofsName;
	float			boundingBox[6];
	struct {
		unsigned int	ofsBatchGroupIndex;
		unsigned int	numBatchGroupIndices;
	} groups[5];
	unsigned int	ofsMaterials;
	unsigned int	numMaterials;
} TDMesh_t;
template <bool big>
struct TDMesh : public TDMesh_s {
	TDMesh(TDMesh_t * ptr) : TDMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(boundingBox[i]);
			}
			for (int i = 0; i < 5; i++) {
				LITTLE_BIG_SWAP(groups[i].ofsBatchGroupIndex);
				LITTLE_BIG_SWAP(groups[i].numBatchGroupIndices);
			}
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMaterials);
		}
	}
};

template <>
static void Model_Bayo_GetTextureBundle<TD>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}

template <>
static void Model_Bayo_LoadTextures<false, TD>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	Model_Bayo_LoadTextures<false, NIER_AUTOMATA>(textures, texFiles, rapi);
}

template <bool big, game_t game>
static void Model_TD_LoadMaterials(
	TDWMBHdr<big> &hdr,
	CArrayList<noesisTex_t *> &textures,
	CArrayList<noesisMaterial_t *> &matList,
	CArrayList<noesisMaterial_t *> &matListLightMap,
	CArrayList<noesisMaterial_t *> &totMatList,
	BYTE *data,
	noeRAPI_t *rapi,
	const char *prefix = "bayomat") {

	TDMaterial_t *matPtr = (TDMaterial_t *)(data + hdr.ofsMaterials);
	unsigned int *textureIDs = (unsigned int *)(data + hdr.ofsTextureIDs);

	DBGLOG("Found %d materials\n", hdr.numMaterials);
	for (int i = 0; i < hdr.numMaterials; i++)
	{
		TDMaterial<big> mat(matPtr + i);
		DBGLOG("\tFound %s\n", data + mat.ofsShaderName);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		char matName[128];
		sprintf_s(matName, 128, "%s_%03i", prefix, i);
		DBGLOG(" name: %s,", matName);
		nmat->name = rapi->Noesis_PooledString(matName);
		nmat->noDefaultBlend = false;
		nmat->texIdx = -1;
		DBGLOG("Deactivating normal\n"); //cell shaded game.
		nmat->ex->flags2 |= NMATFLAG2_PREFERPPL;
		nmat->normalTexIdx = -1;
		nmat->specularTexIdx = -1;
		int difTexId = 0;
		int nrmTexId = 0;
		int specTexId = 0;
		int maskTexId = 0;
		DBGLOG("\tFound %d textures\n", mat.numTextures);
		TDTexture_t * texPtr = (TDTexture_t *)(data + mat.ofsTextures);
		for (unsigned int j = 0; j < mat.numTextures; j++) {
			TDTexture<big> tex(texPtr + j);
			if (strcmp((char*)(data + tex.ofsName), "Albedo0") == 0) {
				difTexId = textureIDs[tex.textureIndex];
			}
			if (strcmp((char*)(data + tex.ofsName), "NormalMap0") == 0) {
				nrmTexId = textureIDs[tex.textureIndex];
			}
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
				nmat->ex->flags2 &= ~NMATFLAG2_PREFERPPL;
			}
		}
		matListLightMap.Append(NULL);
		matList.Append(nmat);
		totMatList.Append(nmat);
	}
}

template <>
static void Model_Bayo_CreateTangents<false, TD>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
	Model_Bayo_CreateTangents<false, BAYONETTA>(data, dsts, numVerts, stride, m);
}

typedef struct TDBuffers_s : public buffers_s {
	buffer_t indices;
} TDBuffers_t;

template <bool big, game_t game>
static void Model_TD_SetBuffers(bayoDatFile_t &df, noeRAPI_t *rapi, TDWMBHdr<false> &hdr, TDBuffers_t *buffers, modelMatrix_t * pretransform) {
	BYTE *data = df.data;
	bool bHasBones = ((hdr.numBones > 0) && (hdr.ofsBones != 0));
	for (int i = 0; i < hdr.numVertexGroups; i++) {
		TDVertexGroup<big> vg((TDVertexGroup_t*)(data + hdr.ofsVertexGroups + i * sizeof(TDVertexGroup_t)));
		int bayoVertSize = vg.sizeVert;
		int bayoVertExSize = vg.sizeVertExData;
		int numVerts = vg.numVerts;
		BYTE *indices = data + vg.ofsIndexBuffer;
		BYTE *verts = data + vg.ofsVerts;
		BYTE *vertsEx = data + vg.ofsVertsExData;
		if (bayoVertSize != 0x14 && bayoVertSize != 0x18 && bayoVertSize != 0x1C) {
			DBGLOG("Unknown vertex size format: %d!!!\n", bayoVertSize);
#ifdef _DEBUG
			g_nfn->NPAPI_PopupDebugLog(0);
#endif
			continue;
		}
		DBGLOG("Found vertex groups %d %d\n", bayoVertSize, bayoVertExSize);
		DBGLOG("Found flags %x\n", hdr.vertexFormat);
		__set_sindices<big, game>(buffers[i].indices, indices, 2);
		DBGLOG("Found vertex groups %d %d\n", bayoVertSize, bayoVertExSize);
		if (bayoVertSize == 0x14 && bayoVertExSize == 0x14 && hdr.vertexFormat == 0x10137) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, vertsEx + 8, bayoVertExSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, vertsEx + 12, bayoVertExSize);
			__set_color<big, game>(buffers[i].color, vertsEx + 16, bayoVertExSize);
		} else if (bayoVertSize == 0x14 && bayoVertExSize == 0x18 && hdr.vertexFormat == 0x10337) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, vertsEx + 8, bayoVertExSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, vertsEx + 12, bayoVertExSize);
			__set_color<big, game>(buffers[i].color, vertsEx + 16, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping2, vertsEx + 20, bayoVertExSize);
		}
		else if (bayoVertSize == 0x18 && bayoVertExSize == 8 && hdr.vertexFormat == 0x10107) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_color<big, game>(buffers[i].color, verts + 20, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);

			//bond to first bone if it exists
			if (bHasBones) {
				DBGLOG("Binding vertexes to first bone.\n");
				unsigned char indexes[4] = { 0, 0, 0, 0 };
				unsigned char weights[4] = { 255, 0, 0, 0 };
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_indexes, numVerts, 4, indexes, rapi);
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_weights, numVerts, 4, weights, rapi);
			}
		}
		else if (bayoVertSize == 0x1C && bayoVertExSize == 8 && hdr.vertexFormat == 0x10307) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
			__set_color<big, game>(buffers[i].color, verts + 20, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 24, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);

			//bond to first bone if it exists
			if (bHasBones) {
				DBGLOG("Binding vertexes to first bone.\n");
				unsigned char indexes[4] = { 0, 0, 0, 0 };
				unsigned char weights[4] = { 255, 0, 0, 0 };
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_indexes, numVerts, 4, indexes, rapi);
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_weights, numVerts, 4, weights, rapi);
			}
		} else if (bayoVertSize == 0x14 && bayoVertExSize == 0x10 && hdr.vertexFormat == 0x137) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, vertsEx + 8, bayoVertExSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, vertsEx + 12, bayoVertExSize);
		}
		else if (bayoVertSize == 0x14 && bayoVertExSize == 8 && hdr.vertexFormat == 0x107) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 12, bayoVertSize);
			__set_tangents<big, game>(buffers[i].tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);

			//bond to first bone if it exists
			if (bHasBones) {
				DBGLOG("Binding vertexes to first bone.\n");
				unsigned char indexes[4] = { 0, 0, 0, 0 };
				unsigned char weights[4] = { 255, 0, 0, 0 };
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_indexes, numVerts, 4, indexes, rapi);
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_weights, numVerts, 4, weights, rapi);
			}
		}
		else {
			DBGLOG("Unknown vertex size, EX size, and format: %d %d %x!!!\n", bayoVertSize, bayoVertExSize, hdr.vertexFormat);
#ifdef _DEBUG
			g_nfn->NPAPI_PopupDebugLog(0);
#endif
		}
	}
}

template <bool big>
modelBone_t *Model_TD_CreateBones(TDWMBHdr<big> &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT)
{
	numBones = 0;
	if (hdr.numBones <= 0 || hdr.ofsBones <= 0 || hdr.ofsBoneIndexTT <= 0) {
		return NULL;
	}
	numBones = hdr.numBones;
	animBoneTT = (short int *)(data + hdr.ofsBoneIndexTT);
	DBGLOG("Found %d bones\n", numBones);
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones + 1);
	for (int i = 0; i < numBones; i++)
	{
		TDBone<big> nBone((TDBone_t *)(data + hdr.ofsBones + i * sizeof(TDBone_t)));
		modelBone_t *bone = bones + i;
		short parent = nBone.parentIndex;
		assert(parent < numBones);
		bone->index = i;
		if (parent == -1) {
			bone->eData.parent = bones + numBones;
		}
		else if (parent >= 0) {
			bone->eData.parent = bones + parent;
		}
		else {
			bone->eData.parent = NULL;
		}
		sprintf_s(bone->name, 30, "bone%03i", nBone.globalId);
		bone->mat = g_identityMatrix;

		bone->userIndex = 5;

		float pos[3];
		pos[0] = nBone.position.x;
		pos[1] = nBone.position.y;
		pos[2] = nBone.position.z;
		g_mfn->Math_VecCopy(pos, bone->mat.o);
	}
	bones[numBones].index = numBones;
	bones[numBones].eData.parent = NULL;
	sprintf_s(bones[numBones].name, 30, "bone-1");
	bones[numBones].mat = g_identityMatrix;
	bones[numBones].userIndex = 5;
	return bones;
}

template <>
static void Model_Bayo_LoadModel<false, TD>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset, const char *prefix, CArrayList<noesisMaterial_t *> *globalMatList) {
	const bool big = false;
	const game_t game = TD;
	DBGLOG("Loading %s\n", df.name);
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(TDWMBHdr_t))
	{
		return;
	}
	TDWMBHdr<big> hdr((TDWMBHdr_t *)data);
	if (memcmp(hdr.id, "WMB3", 4))
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

	TDBuffers_t *buffers = (TDBuffers_t *)rapi->Noesis_UnpooledAlloc(hdr.numVertexGroups * sizeof(TDBuffers_t));
	memset(buffers, 0, hdr.numVertexGroups * sizeof(TDBuffers_t));

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

	Model_TD_LoadMaterials<big, game>(hdr, textures, matList, matListLightMap, globalMatList ? *globalMatList : totMatList, data, rapi, globalMatList ? prefix : "bayomat");
	Model_TD_SetBuffers<big, game>(df, rapi, hdr, buffers, pretransform);

	void *pgctx = NULL;
	int numBones = 0;
	short int * animBoneTT = NULL;
	modelBone_t *bones = NULL;
	if (!prefix) {
		pgctx = rapi->rpgCreateContext();
		rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
		rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);
		bones = Model_TD_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

		Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
		Model_Bayo_GetEXPFile(dfiles, df, rapi, expfile);
		if (bones) {
			Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBones);
			Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBones);
		}
	}

	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	DBGLOG("Found %d batches\n", hdr.numBatches);

	TDMesh_t *meshes = (TDMesh_t *)(data + hdr.ofsMeshes);
	TDBatchGroups<big> batchGroups((TDBatchGroups_t *)(data + hdr.ofsBatchGroups));
	TDBatch_t *batches = (TDBatch_t *)(data + hdr.ofsBatches);
	TDBoneSet_t *boneSets = (TDBoneSet_t *)(data + hdr.ofsBoneSets);
	if (!hdr.numBatches)
		return;
	for (int i = 0; i < 1; i++)
	{
		TDBatchInfo_t * batchInfos = (TDBatchInfo_t *)(data + batchGroups.groups[i].ofsBatchGroup);
		for (unsigned int j = 0; j < batchGroups.groups[i].numBatch; j++) {
			char batch_name[256];
			TDBatchInfo<big> batchInfo(batchInfos + j);
			TDBatch<big> batch(batches + batchInfo.batchIndex);
			TDMesh<big> mesh(meshes + batchInfo.meshIndex);
			TDBoneSet<big> boneSet(boneSets + batchInfo.boneSetIndex);

			unsigned int vertexGroupIndex = batch.vertexGroupIndex;
			unsigned int materialIndex = batchInfo.materialIndex;

			if (prefix)
				sprintf_s(batch_name, 256, "%s_%02d(%s)_%02d", prefix, i, (char *)(data + mesh.ofsName), j);
			else
				sprintf_s(batch_name, 256, "%02d(%s)_%02d", i, (char *)(data + mesh.ofsName), j);
			DBGLOG("\t%s\n", batch_name);
			DBGFLUSH();
			int *boneIndices = NULL;
			if (bones && batchInfo.boneSetIndex >= 0) {
				boneIndices = (int *)rapi->Noesis_UnpooledAlloc(boneSet.numBoneIndices * sizeof(int));
				unsigned char *originalBoneIndices = (unsigned char *)(data + boneSet.ofsBoneSet);
				for (unsigned int j = 0; j < boneSet.numBoneIndices; j++) {
					unsigned char sourceIndex;
					sourceIndex = originalBoneIndices[j];
					if (big) {
						LITTLE_BIG_SWAP(sourceIndex);
					}
					boneIndices[j] = sourceIndex;
				}
			}
			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			rapi->rpgSetBoneMap(boneIndices);
			if (bones && buffers[vertexGroupIndex].bone_indexes.address)
			{
				rapi->rpgBindBoneIndexBuffer(buffers[vertexGroupIndex].bone_indexes.address + batch.vertexStart * buffers[vertexGroupIndex].bone_indexes.stride, buffers[vertexGroupIndex].bone_indexes.type, buffers[vertexGroupIndex].bone_indexes.stride, 4);
				rapi->rpgBindBoneWeightBuffer(buffers[vertexGroupIndex].bone_weights.address + batch.vertexStart * buffers[vertexGroupIndex].bone_weights.stride, buffers[vertexGroupIndex].bone_weights.type, buffers[vertexGroupIndex].bone_weights.stride, 4);
			}
			rapi->rpgBindPositionBuffer(buffers[vertexGroupIndex].position.address + batch.vertexStart * buffers[vertexGroupIndex].position.stride, buffers[vertexGroupIndex].position.type, buffers[vertexGroupIndex].position.stride);
			rapi->rpgBindNormalBuffer(buffers[vertexGroupIndex].normal.address + batch.vertexStart * buffers[vertexGroupIndex].normal.stride, buffers[vertexGroupIndex].normal.type, buffers[vertexGroupIndex].normal.stride);
			rapi->rpgBindUV1Buffer(buffers[vertexGroupIndex].mapping.address + batch.vertexStart * buffers[vertexGroupIndex].mapping.stride, buffers[vertexGroupIndex].mapping.type, buffers[vertexGroupIndex].mapping.stride);
			rapi->rpgSetMaterial(matList[materialIndex]->name);
			rapi->rpgCommitTriangles(buffers[vertexGroupIndex].indices.address + batch.indexStart * buffers[vertexGroupIndex].indices.stride, buffers[vertexGroupIndex].indices.type, batch.numIndices, RPGEO_TRIANGLE, true);

			if (bones) {
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

template <>
static void Model_Bayo_LoadScenery<false, TD>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	const bool big = false;
	const game_t game = TD;
	DBGLOG("Loading %s\n", df.name);
	bayo2SCRHdr<big> hdr((bayo2SCRHdr_t *)df.data);
	if (memcmp(hdr.id, "SCR\0", 4))
	{ //invalid header
		DBGLOG("Invalid SCR file\n");
		return;
	}
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<noesisTex_t *> textures;
	Model_Bayo2_GetSCRTextureBundle(texFiles, olddfiles, df, rapi);
	if (texFiles.Num() > 0)
	{
		for (int i = 0; i < texFiles.Num(); i++) {
			DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
		}
		Model_Bayo_LoadTextures<big, game>(textures, texFiles, rapi);
	}
	char scrName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(scrName, df.name);
	Model_Bayo_LoadSharedTextures<big, game>(textures, scrName, rapi);

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
		Model_Bayo_LoadModel<big, game>(dfiles, modelFile, rapi, models, textures, &m, -1,
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