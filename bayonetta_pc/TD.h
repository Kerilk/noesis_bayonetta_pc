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
	unsigned int ofsBatchGroup0;
	unsigned int numBatch0;
	unsigned int ofsBatchGroup1;
	unsigned int numBatch1;
	unsigned int ofsBatchGroup2;
	unsigned int numBatch2;
	unsigned int ofsBatchGroup3;
	unsigned int numBatch3;
	unsigned int ofsBatchGroup4;
	unsigned int numBatch4;
} TDBatchGroups_t;
template <bool big>
struct TDBatchGroups : public TDBatcGroups_s {
	TDBatchGroups(TDBatchGroups_t * ptr) : TDBatcGroups_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsBatchGroup0);
			LITTLE_BIG_SWAP(numBatch0);
			LITTLE_BIG_SWAP(ofsBatchGroup1);
			LITTLE_BIG_SWAP(numBatch1);
			LITTLE_BIG_SWAP(ofsBatchGroup2);
			LITTLE_BIG_SWAP(numBatch2);
			LITTLE_BIG_SWAP(ofsBatchGroup3);
			LITTLE_BIG_SWAP(numBatch3);
			LITTLE_BIG_SWAP(ofsBatchGroup4);
			LITTLE_BIG_SWAP(numBatch4);
		}
	}
};
typedef struct TDBatchInfo_s
{
	unsigned int	batchIndex;
	unsigned int	meshIndex;
	unsigned int	materialIndex;
	int				boneSetIndex;
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
	unsigned int	unknownB;
	unsigned int	numTextures;
	unsigned int	unknownC;
	unsigned int	numParameters;
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
	unsigned int	ofsBatchGroup0Index;
	unsigned int	numBatchGroup0Indices;
	unsigned int	ofsBatchGroup1Index;
	unsigned int	numBatchGroup1Indices;
	unsigned int	ofsBatchGroup2Index;
	unsigned int	numBatchGroup2Indices;
	unsigned int	ofsBatchGroup3Index;
	unsigned int	numBatchGroup3Indices;
	unsigned int	ofsBatchGroup4Index;
	unsigned int	numBatchGroup4Indices;
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
			LITTLE_BIG_SWAP(ofsBatchGroup0Index);
			LITTLE_BIG_SWAP(numBatchGroup0Indices);
			LITTLE_BIG_SWAP(ofsBatchGroup1Index);
			LITTLE_BIG_SWAP(numBatchGroup1Indices);
			LITTLE_BIG_SWAP(ofsBatchGroup2Index);
			LITTLE_BIG_SWAP(numBatchGroup2Indices);
			LITTLE_BIG_SWAP(ofsBatchGroup3Index);
			LITTLE_BIG_SWAP(numBatchGroup3Indices);
			LITTLE_BIG_SWAP(ofsBatchGroup4Index);
			LITTLE_BIG_SWAP(numBatchGroup4Indices);
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMaterials);
		}
	}
};