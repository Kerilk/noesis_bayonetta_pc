#pragma once
#include <map>
#include <tuple>
#include <set>
#include <algorithm>
#include <iterator>

typedef struct nierWMBHdr_s
{
	uint8_t  id[4];				// 0
	uint32_t version;			// 4
	int32_t  unknownA;			// 8
	uint16_t flags;				// C Seems related to vertex index size
	int16_t  referenceBone;		// E
	float    boundingBox[6];	//10
	uint32_t ofsBones;			//28
	int32_t  numBones;			//2C
	uint32_t ofsBoneIndexTT;	//30
	int32_t  sizeBoneIndexTT;	//34
	uint32_t ofsVertexGroups;	//38
	int32_t  numVertexGroups;	//3C
	uint32_t ofsBatches;		//40
	int32_t  numBatches;		//44
	uint32_t ofsLods;			//48
	int32_t  numLods;			//4C
	uint32_t ofsUnknownD;		//50
	int32_t  numUnknownE;		//54
	uint32_t ofsBoneMap;		//58
	int32_t  sizeBoneMap;		//5C
	uint32_t ofsBoneSets;		//60
	int32_t  numBoneSets;		//64
	uint32_t ofsMaterials;		//68
	int32_t  numMaterials;		//6C
	uint32_t ofsMeshes;			//70
	int32_t  numMeshes;			//74
	uint32_t ofsMeshMaterial;	//78
	int32_t  numMeshMaterial;	//7C
	uint32_t ofsUnknownF;		//80
	int32_t  numUnknownG;		//84
} nierWMBHdr_t;
template <bool big>
struct nierWMBHdr : public nierWMBHdr_s {
	nierWMBHdr(nierWMBHdr_t * ptr) : nierWMBHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(version);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(flags);
			LITTLE_BIG_SWAP(referenceBone);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(boundingBox[i]);
			}
			LITTLE_BIG_SWAP(ofsBones);
			LITTLE_BIG_SWAP(numBones);
			LITTLE_BIG_SWAP(ofsBoneIndexTT);
			LITTLE_BIG_SWAP(sizeBoneIndexTT);
			LITTLE_BIG_SWAP(ofsVertexGroups);
			LITTLE_BIG_SWAP(numVertexGroups);
			LITTLE_BIG_SWAP(ofsBatches);
			LITTLE_BIG_SWAP(numBatches);
			LITTLE_BIG_SWAP(ofsLods);
			LITTLE_BIG_SWAP(numLods);
			LITTLE_BIG_SWAP(ofsUnknownD);
			LITTLE_BIG_SWAP(numUnknownE);
			LITTLE_BIG_SWAP(ofsBoneMap);
			LITTLE_BIG_SWAP(sizeBoneMap);
			LITTLE_BIG_SWAP(ofsBoneSets);
			LITTLE_BIG_SWAP(numBoneSets);
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(ofsMeshes);
			LITTLE_BIG_SWAP(numMeshes);
			LITTLE_BIG_SWAP(ofsMeshMaterial);
			LITTLE_BIG_SWAP(numMeshMaterial);
			LITTLE_BIG_SWAP(ofsUnknownF);
			LITTLE_BIG_SWAP(numUnknownG);
		}
	}
};
typedef struct nierMaterial_s
{
	int16_t  version[4];
	uint32_t ofsName;
	uint32_t ofsShaderName;
	uint32_t ofsTechniqueName;
	uint32_t unknownA;
	uint32_t ofsTextures;
	uint32_t numTextures;
	uint32_t ofsParameterGroups;
	uint32_t numParametersGroup;
	uint32_t ofsVariables;
	uint32_t numVariables;
} nierMaterial_t;
template <bool big>
struct nierMaterial : public nierMaterial_s {
	nierMaterial(nierMaterial_t * ptr) : nierMaterial_s(*ptr) {
		if (big) {
			for (int i = 0; i < 4; i++) {
				LITTLE_BIG_SWAP(version[i]);
			}
			LITTLE_BIG_SWAP(ofsName);
			LITTLE_BIG_SWAP(ofsShaderName);
			LITTLE_BIG_SWAP(ofsTechniqueName);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(ofsTextures);
			LITTLE_BIG_SWAP(numTextures);
			LITTLE_BIG_SWAP(ofsParameterGroups);
			LITTLE_BIG_SWAP(numParametersGroup);
			LITTLE_BIG_SWAP(ofsVariables);
			LITTLE_BIG_SWAP(numVariables);
		}
	}
};
typedef struct nierMaterialVariable_s
{
	uint32_t ofsName;
	float    value;
} nierMaterialVariable_t;
template <bool big>
struct nierMaterialVariable : public nierMaterialVariable_s {
	nierMaterialVariable(nierMaterialVariable_t * ptr) : nierMaterialVariable_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			LITTLE_BIG_SWAP(value);
		}
	}
};
typedef struct nierTexture_s
{
	uint32_t ofsName;
	int32_t  id;
} nierTexture_t;
template <bool big>
struct nierTexture : public nierTexture_s {
	nierTexture(nierTexture_t * ptr) : nierTexture_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			LITTLE_BIG_SWAP(id);
		}
	}
};
typedef struct nierBone_s
{
	int16_t			id;
	int16_t			parentIndex;
	bayoVector_t	localPosition;
	bayoVector_t	localRotation;
	bayoVector_t	localScale;
	bayoVector_t	position;
	bayoVector_t	rotation;
	bayoVector_t	scale;
	bayoVector_t	tPosition;
} nierBone_t;
template <bool big>
struct nierBone : public nierBone_s {
	nierBone(nierBone_t * ptr) : nierBone_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(id);
			LITTLE_BIG_SWAP(parentIndex);
			localPosition.swap();
			localRotation.swap();
			localScale.swap();
			position.swap();
			rotation.swap();
			scale.swap();
			tPosition.swap();
		}
	}
};
typedef struct nierVertexGroup_s {
	uint32_t	ofsVerts;
	uint32_t	ofsVertsExData;
	uint32_t	unknownA;
	uint32_t	unknownB;
	uint32_t	sizeVert;
	uint32_t	sizeVertExData;
	uint32_t	unknownD;
	uint32_t	unknownE;
	uint32_t	numVerts;
	uint32_t	vertFlags;
	uint32_t	ofsIndexBuffer;
	uint32_t	numIndexes;
} nierVertexGroup_t;
template <bool big>
struct nierVertexGroup : public nierVertexGroup_s {
	nierVertexGroup(nierVertexGroup_t * ptr) : nierVertexGroup_s(*ptr) {
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
			LITTLE_BIG_SWAP(vertFlags);
			LITTLE_BIG_SWAP(ofsIndexBuffer);
			LITTLE_BIG_SWAP(numIndexes);
		}
	}
};
typedef struct nierMesh_s {
	uint32_t	ofsName;
	float		boundingBox[6];
	uint32_t	ofsMaterials;
	uint32_t	numMaterials;
	uint32_t	ofsBones;
	uint32_t	numBones;
} nierMesh_t;
template <bool big>
struct nierMesh : public nierMesh_s {
	nierMesh(nierMesh_t * ptr) : nierMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(boundingBox[i]);
			}
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(ofsBones);
			LITTLE_BIG_SWAP(numBones);
		}
	}
};
typedef struct nierLod_s
{
	uint32_t	ofsName;
	int32_t		lodLevel;
	uint32_t	batchStart;
	uint32_t	ofsBatchInfos;
	uint32_t	numBatchInfos;
} nierLod_t;
template <bool big>
struct nierLod : public nierLod_s {
	nierLod(nierLod_t * ptr) : nierLod_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsName);
			LITTLE_BIG_SWAP(lodLevel);
			LITTLE_BIG_SWAP(batchStart);
			LITTLE_BIG_SWAP(ofsBatchInfos);
			LITTLE_BIG_SWAP(numBatchInfos);
		}
	}
};
typedef struct nierBatchInfo_s
{
	uint32_t	vertexGroupIndex;
	uint32_t	meshIndex;
	uint32_t	materialIndex;
	int32_t		unknownA;
	uint32_t	meshMaterialPairIndex;
	int32_t		unknownB;
} nierBatchInfo_t;
template <bool big>
struct nierBatchInfo : nierBatchInfo_s {
	nierBatchInfo(nierBatchInfo_t * ptr) : nierBatchInfo_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(vertexGroupIndex);
			LITTLE_BIG_SWAP(meshIndex);
			LITTLE_BIG_SWAP(materialIndex);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(meshMaterialPairIndex);
			LITTLE_BIG_SWAP(unknownB);
		}
	}
};
typedef struct nierBatch_s {
	uint32_t	vertexGroupIndex;
	int32_t		boneSetIndex;
	uint32_t	vertexStart;
	uint32_t	indexStart;
	uint32_t	numVerts;
	uint32_t	numIndices;
	uint32_t	numPrimitives;
} nierBatch_t;
template <bool big>
struct nierBatch : public nierBatch_s {
	nierBatch(nierBatch_t * ptr) : nierBatch_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(vertexGroupIndex);
			LITTLE_BIG_SWAP(boneSetIndex);
			LITTLE_BIG_SWAP(vertexStart);
			LITTLE_BIG_SWAP(indexStart);
			LITTLE_BIG_SWAP(numVerts);
			LITTLE_BIG_SWAP(numIndices);
			LITTLE_BIG_SWAP(numPrimitives);
		}
	}
};
typedef struct nierBoneSet_s {
	uint32_t	ofsBoneSet;
	uint32_t	numBoneIndices;
} nierBoneSet_t;
template <bool big>
struct nierBoneSet : public nierBoneSet_s {
	nierBoneSet(nierBoneSet_t * ptr) : nierBoneSet_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsBoneSet);
			LITTLE_BIG_SWAP(numBoneIndices);
		}
	}
};
typedef struct nierCOL2Hdr_s {
	uint8_t  id[4];
	uint32_t version;
	uint32_t ofsNames;
	uint32_t numNames;
	uint32_t ofsMeshes;
	uint32_t numMeshes;
	uint32_t ofsBoneMap;
	uint32_t sizeBoneMap;
	uint32_t ofsBoneMap2;
	uint32_t sizeBoneMap2;
	uint32_t ofsMeshMap;
	uint32_t sizeMeshMap;
	uint32_t ofsColTreeNodes;
	uint32_t numColTreeNodes;
} nierCOL2Hdr_t;
template <bool big>
struct nierCOL2Hdr : public nierCOL2Hdr_s {
	nierCOL2Hdr(nierCOL2Hdr_t * ptr) : nierCOL2Hdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(version);
			LITTLE_BIG_SWAP(ofsNames);
			LITTLE_BIG_SWAP(numNames);
			LITTLE_BIG_SWAP(ofsMeshes);
			LITTLE_BIG_SWAP(numMeshes);
			LITTLE_BIG_SWAP(ofsBoneMap);
			LITTLE_BIG_SWAP(sizeBoneMap);
			LITTLE_BIG_SWAP(ofsBoneMap2);
			LITTLE_BIG_SWAP(sizeBoneMap2);
			LITTLE_BIG_SWAP(ofsMeshMap);
			LITTLE_BIG_SWAP(sizeMeshMap);
			LITTLE_BIG_SWAP(ofsColTreeNodes);
			LITTLE_BIG_SWAP(numColTreeNodes);
		}
	}
};
typedef struct nierCOL2MeshHdr_s {
	uint32_t flags;
	uint32_t nameIndex;
	uint32_t batchType;
	uint32_t ofsBatches;
	uint32_t numBatches;
} nierCOL2MeshHdr_t;
template <bool big>
struct nierCOL2MeshHdr : public nierCOL2MeshHdr_s {
	nierCOL2MeshHdr(nierCOL2MeshHdr_t * ptr) : nierCOL2MeshHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flags);
			LITTLE_BIG_SWAP(nameIndex);
			LITTLE_BIG_SWAP(batchType);
			LITTLE_BIG_SWAP(ofsBatches);
			LITTLE_BIG_SWAP(numBatches);
		}
	}
};
typedef struct nierCOL2BatchHdr2_s {
	int32_t  boneIndex;
	uint32_t ofsVertices;
	uint32_t numVertices;
	uint32_t ofsIndices;
	uint32_t numIndices;
}nierCOL2BatchHdr2_t;
template <bool big>
struct nierCOL2BatchHdr2 : public nierCOL2BatchHdr2_s {
	nierCOL2BatchHdr2(nierCOL2BatchHdr2_t * ptr) : nierCOL2BatchHdr2_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(ofsVertices);
			LITTLE_BIG_SWAP(numVertices);
			LITTLE_BIG_SWAP(ofsIndices);
			LITTLE_BIG_SWAP(numIndices);
		}
	}
};
typedef struct nierCOL2BatchHdr3_s {
	uint32_t ofsVertices;
	uint32_t numVertices;
	uint32_t ofsIndices;
	uint32_t numIndices;
}nierCOL2BatchHdr3_t;
template <bool big>
struct nierCOL2BatchHdr3 : public nierCOL2BatchHdr3_s {
	nierCOL2BatchHdr3(nierCOL2BatchHdr3_t * ptr) : nierCOL2BatchHdr3_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(ofsVertices);
			LITTLE_BIG_SWAP(numVertices);
			LITTLE_BIG_SWAP(ofsIndices);
			LITTLE_BIG_SWAP(numIndices);
		}
	}
};

typedef struct nierWTBInfoSwitch_s {
	uint8_t  id[4];
	uint32_t format;
	uint32_t textureType;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t numMipMap;
	uint32_t headerSize;
	uint64_t textureSize;
	uint8_t  padding[216];
} nierWTBInfoSwitch_t;
template <bool big>
struct nierWTBInfoSwitch : public nierWTBInfoSwitch_s {
	nierWTBInfoSwitch(nierWTBInfoSwitch_t * ptr) : nierWTBInfoSwitch_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(textureType);
			LITTLE_BIG_SWAP(width);
			LITTLE_BIG_SWAP(height);
			LITTLE_BIG_SWAP(depth);
			LITTLE_BIG_SWAP(numMipMap);
			LITTLE_BIG_SWAP(headerSize);
			LITTLE_BIG_SWAP(textureSize);
		}
	}
};

template <>
static void Model_Bayo_GetTextureBundle<NIER_AUTOMATA>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}

static inline noesisTex_t *Model_Nier_LoadTexture_PC(bayoDatFile_t *wta, bayoDatFile_t *wtp, bayoWTBHdr<false> &hdr, char * texName, int32_t texIndex, noeRAPI_t *rapi) {
	int dataSize = wta->dataSize;
	BYTE * data = wta->data;
	int dataSize2 = wtp->dataSize;
	BYTE * data2 = wtp->data;
	
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *tflags = (int *)(data + hdr.ofsTexFlags);
	int *tidx = (int *)(data + hdr.texIdxOffset);

	char fname[8192];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%0x", rapi->Noesis_GetOption("texpre"), tidx[texIndex]);
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);

	int ofs = tofs[texIndex];
	int size = tsizes[texIndex];
	int globalIdx = tidx[texIndex];
	if (ofs < 0 || ofs > dataSize2)
	{
		return NULL;
	}
	BYTE *texData = data2 + ofs;
	BYTE *pix;

	ddsTexHdr_t tex;
	tex = *((ddsTexHdr_t *)texData);
	pix = texData + sizeof(ddsTexHdr_t);
	if (memcmp(tex.id, "DDS ", 4))
	{
		return NULL;
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
	DBGLOG("\t%03d (idx %x, flags %x): ", texIndex, globalIdx, tflags[texIndex]);
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
	return nt;
}

// There exist two Nier automata format PC and Switch
static void Model_Nier_LoadTextures_PC(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	int dataSize = texFiles[0]->dataSize;
	uint8_t * data = texFiles[0]->data;
	int dataSize2 = texFiles[1]->dataSize;
	uint8_t * data2 = texFiles[1]->data;
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	if (dataSize < sizeof(bayoWTAHdr_t))
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
	DBGLOG("found valid texture header file, containing %d textures\n", hdr.numTex);
	for (int i = 0; i < hdr.numTex; i++)
	{
		noesisTex_t *nt = Model_Nier_LoadTexture_PC(texFiles[0], texFiles[1], hdr, texName, i, rapi);
		if (nt)
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

static void Model_Nier_LoadTextures_Set_PC(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi, std::set<int32_t> indices) {
	int dataSize = texFiles[0]->dataSize;
	uint8_t * data = texFiles[0]->data;
	int dataSize2 = texFiles[1]->dataSize;
	uint8_t * data2 = texFiles[1]->data;
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	if (dataSize < sizeof(bayoWTAHdr_t))
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
	DBGLOG("found valid texture header file, containing %d textures\n", hdr.numTex);
	noesisTex_t *placeholder = NULL;
	if (textures.Num() > 0)
		placeholder = textures.Pop();
	for (auto it = indices.begin(); it != indices.end(); it++) {
		noesisTex_t *nt = Model_Nier_LoadTexture_PC(texFiles[0], texFiles[1], hdr, texName, *it, rapi);
		if (nt)
			textures.Append(nt);
	}
	if (placeholder)
		textures.Append(placeholder);
}

static inline int div_rnd_up(int x, int y) {
	return (x + y - 1) / y;
}

static inline int rnd_up(int x, int y) {
	return ((x - 1) | (y - 1)) + 1;
}

static inline int getOffsetBlockLinear(unsigned int x, unsigned int y, unsigned int w, const int bytesPerElem, int blockHeight, int specialPad) {
	int image_width_in_gobs = div_rnd_up(rnd_up(w, specialPad) * bytesPerElem, 64);
	int gob_offset =
		(y / (8 * blockHeight)) * 512 * blockHeight * image_width_in_gobs +
		(x * bytesPerElem / 64) * 512 * blockHeight +
		(y % (8 * blockHeight) / 8) * 512;
	x *= bytesPerElem;
	return gob_offset + ((x % 64) / 32) * 256 + ((y % 8) / 2) * 64 + ((x % 32) / 16) * 32 + (y % 2) * 16 + (x % 16);
}
void Image_UntileBlockLinearGOBs2(unsigned char *pDest, const unsigned int destSize, const unsigned char *pSrc, const unsigned int srcSize, const unsigned int w, const unsigned int h, const unsigned int blockHeight, const int bytesPerElem, const int specialPad) {
	for (unsigned int y = 0; y < h; y++)
		for (unsigned int x = 0; x < w; x++) {
			int pos_tiled = getOffsetBlockLinear(x, y, w, bytesPerElem, blockHeight, specialPad);
			int pos_untiled = (y * w + x) * bytesPerElem;
			memcpy(pDest + pos_untiled, pSrc + pos_tiled, bytesPerElem);
		}
}

typedef enum {
	T_1D,
	T_2D,
	T_3D,
	T_Cube,
	T_1D_Array,
	T_2D_Array,
	T_2D_Mulitsample,
	T_2D_Multisample_Array,
	T_Cube_Array
} xt1_texture_type_t;

typedef enum {
	R8_G8_B8_A8_UNORM = 0x25,
	R8_G8_B8_A8_SRGB = 0x38,

	BC1_UNORM = 0x42, //DXT1
	BC2_UNORM, //DXT3
	BC3_UNORM, //DXT5
	BC4_UNORM,
	BC1_SRGB,
	BC2_SRGB,
	BC3_SRGB,
	BC4_SRGB,

	BC5_UNORM = 0x4b,
	BC5_SRGB,
	BC7_UNORM,
	BC7_SRGB,
	BC6_FLOAT,
	BC6_UFLOAT,

	ASTC_4x4_UNORM = 0x79,
	ASTC_5x4_UNORM,
	ASTC_5x5_UNORM,
	ASTC_6x5_UNORM,
	ASTC_6x6_UNORM,
	ASTC_8x5_UNORM,
	ASTC_8x6_UNORM,
	ASTC_8x8_UNORM,
	ASTC_10x5_UNORM,
	ASTC_10x6_UNORM,
	ASTC_10x8_UNORM,
	ASTC_10x10_UNORM, // Thanks DniweTamp
	ASTC_12x10_UNORM,
	ASTC_12x12_UNORM,
	ASTC_4x4_SRGB,
	ASTC_5x4_SRGB,
	ASTC_5x5_SRGB,
	ASTC_6x5_SRGB,
	ASTC_6x6_SRGB,
	ASTC_8x5_SRGB,
	ASTC_8x6_SRGB,
	ASTC_8x8_SRGB,
	ASTC_10x5_SRGB,
	ASTC_10x6_SRGB,
	ASTC_10x8_SRGB,
	ASTC_10x10_SRGB,  // Thanks DniweTamp
	ASTC_12x10_SRGB,
	ASTC_12x12_SRGB
} xt1_texture_format_t;

// bytesPerBlock, blockWidth, blockHeight, blockDepth
const std::map<xt1_texture_format_t, std::tuple<char, char, char, char>> swizzle_block_dims = {
	{R8_G8_B8_A8_UNORM, { 4,  1,  1, 1}},
	{R8_G8_B8_A8_SRGB,  { 4,  1,  1, 1}},
	{BC1_UNORM,         { 8,  4,  4, 1}},
	{BC2_UNORM,         {16,  4,  4, 1}},
	{BC3_UNORM,         {16,  4,  4, 1}},
	{BC4_UNORM,         { 8,  4,  4, 1}},
	{BC1_SRGB,          { 8,  4,  4, 1}},
	{BC2_SRGB,          {16,  4,  4, 1}},
	{BC3_SRGB,          {16,  4,  4, 1}},
	{BC4_SRGB,          { 8,  4,  4, 1}},
	{BC5_UNORM,         {16,  4,  4, 1}},
	{BC5_SRGB,          {16,  4,  4, 1}},
	{BC7_UNORM,         {16,  4,  4, 1}},
	{BC7_SRGB,          {16,  4,  4, 1}},
	{BC6_FLOAT,         {16,  4,  4, 1}},
	{BC6_UFLOAT,        {16,  4,  4, 1}},
	{ASTC_4x4_UNORM,    {16,  4,  4, 1}},
	{ASTC_5x4_UNORM,    {16,  5,  4, 1}},
	{ASTC_5x5_UNORM,    {16,  5,  5, 1}},
	{ASTC_6x5_UNORM,    {16,  6,  5, 1}},
	{ASTC_6x6_UNORM,    {16,  6,  6, 1}},
	{ASTC_8x5_UNORM,    {16,  8,  5, 1}},
	{ASTC_8x6_UNORM,    {16,  8,  6, 1}},
	{ASTC_8x8_UNORM,    {16,  8,  8, 1}},
	{ASTC_10x5_UNORM,   {16, 10,  5, 1}},
	{ASTC_10x6_UNORM,   {16, 10,  6, 1}},
	{ASTC_10x8_UNORM,   {16, 10,  8, 1}},
	{ASTC_10x10_UNORM,  {16, 10, 10, 1}},
	{ASTC_12x10_UNORM,  {16, 12, 10, 1}},
	{ASTC_12x12_UNORM,  {16, 12, 12, 1}},
	{ASTC_4x4_SRGB,     {16,  4,  4, 1}},
	{ASTC_5x4_SRGB,     {16,  5,  4, 1}},
	{ASTC_5x5_SRGB,     {16,  5,  5, 1}},
	{ASTC_6x5_SRGB,     {16,  6,  5, 1}},
	{ASTC_6x6_SRGB,     {16,  6,  6, 1}},
	{ASTC_8x5_SRGB,     {16,  8,  5, 1}},
	{ASTC_8x6_SRGB,     {16,  8,  6, 1}},
	{ASTC_8x8_SRGB,     {16,  8,  8, 1}},
	{ASTC_10x5_SRGB,    {16, 10,  5, 1}},
	{ASTC_10x6_SRGB,    {16, 10,  6, 1}},
	{ASTC_10x8_SRGB,    {16, 10,  8, 1}},
	{ASTC_10x10_SRGB,   {16, 10, 10, 1}},
	{ASTC_12x10_SRGB,   {16, 12, 10, 1}},
	{ASTC_12x12_SRGB,   {16, 12, 12, 1}}
};

static noesisTex_t * Model_LoadTextureSwitch(int idx, BYTE *data, xt1_texture_type_t textureType, xt1_texture_format_t format, unsigned int width, unsigned int height, unsigned int depth, unsigned int maxBlockHeight, size_t mipSize, bool special, int specialPad, char *fname, noeRAPI_t *rapi) {
	BYTE *untiledMip;
	BYTE *pix;
	int bytesPerBlock;
	int blockWidth;
	int blockHeight;
	int blockDepth;
	bool astc = false;
	bool decode_dxt = false;
	int fourcc = 0;
	noesisTexType_e type = NOESISTEX_UNKNOWN;
	if (textureType != T_2D)
		return NULL;
	auto it = swizzle_block_dims.find(format);
	if (it == swizzle_block_dims.end())
		return NULL;
	bytesPerBlock = std::get<0>(it->second);
	blockWidth    = std::get<1>(it->second);
	blockHeight   = std::get<2>(it->second);
	blockDepth    = std::get<3>(it->second);
	if (format >= ASTC_4x4_UNORM && format <= ASTC_12x12_SRGB) {
		astc = true;
		DBGLOG("Found ASTC %dx%d\n", blockWidth, blockHeight);
	}
	else if (format == BC6_UFLOAT) {
		fourcc = FOURCC_BC6H;
		decode_dxt = true;
		DBGLOG("Found BC6H\n");
	}
	else if (format == BC6_FLOAT) {
		fourcc = FOURCC_BC6S;
		decode_dxt = true;
		DBGLOG("Found BC6S\n");
	}
	else if (format == BC4_UNORM || format == BC4_SRGB) {
		fourcc = FOURCC_BC4;
		decode_dxt = true;
		DBGLOG("Found BC4\n");
	}
	else if (format == BC5_UNORM || format == BC5_SRGB) {
		fourcc = FOURCC_BC5;
		decode_dxt = true;
		DBGLOG("Found BC5\n");
	}
	else if (format == BC7_UNORM || format == BC7_SRGB) {
		fourcc = FOURCC_BC7;
		decode_dxt = true;
		DBGLOG("Found BC7\n");
	}
	else if (format == BC3_UNORM || format == BC3_SRGB) {
		type = NOESISTEX_DXT5;
		DBGLOG("Found BC3 (DXT5)\n");
	}
	else if (format == BC2_UNORM || format == BC2_SRGB) {
		type = NOESISTEX_DXT3;
		DBGLOG("Found BC2 (DXT3)\n");
	}
	else if (format == BC1_UNORM || format == BC1_SRGB) {
		type = NOESISTEX_DXT1;
		DBGLOG("Found BC1 (DXT1)\n");
	}
	else if (format == R8_G8_B8_A8_UNORM || format == R8_G8_B8_A8_SRGB) {
		type = NOESISTEX_RGBA32;
		DBGLOG("Found RGBA32\n");
	}
	else {
		return NULL;
	}

	int widthInBlocks = (width + (blockWidth - 1)) / blockWidth;
	int heightInBlocks = (height + (blockHeight - 1)) / blockHeight;

	DBGLOG("widthInBlocks %d\n", widthInBlocks);
	DBGLOG("heightInBlocks %d\n", heightInBlocks);
	DBGLOG("special %d\n", special);
	if (special)
		DBGLOG("specialPad %d\n", specialPad);

	noesisTex_t *nt;
	if (astc || decode_dxt)
		untiledMip = (BYTE *)rapi->Noesis_UnpooledAlloc(mipSize);
	else
		untiledMip = (BYTE *)rapi->Noesis_PooledAlloc(mipSize);

	if (special)
		Image_UntileBlockLinearGOBs2(untiledMip, (unsigned int)mipSize, data, (unsigned int)mipSize, widthInBlocks, heightInBlocks, maxBlockHeight, bytesPerBlock, specialPad);
	else
		rapi->Image_UntileBlockLinearGOBs(untiledMip, (unsigned int)mipSize, data, (unsigned int)mipSize, widthInBlocks, heightInBlocks, maxBlockHeight, bytesPerBlock);
	DBGLOG("Untiled\n");

	if (astc) {
		pix = (BYTE *)rapi->Noesis_PooledAlloc((width*height) * 4);
		int blockDims[3] = { blockWidth, blockHeight, blockDepth };
		int dims[3] = { (int)width, (int)height, (int)depth };
		rapi->Image_DecodeASTC(pix, untiledMip, (unsigned int)mipSize, blockDims, dims);
		DBGLOG("Decoded ASTC\n");
		nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
		nt->shouldFreeData = false; //because the pix data is pool-allocated, it does not need to be freed
	}
	else if (decode_dxt) {
		pix = rapi->Noesis_ConvertDXT(width, height, untiledMip, fourcc);
		DBGLOG("Decoded BC\n");
		nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
		nt->shouldFreeData = true;
	}
	else {
		nt = rapi->Noesis_TextureAlloc(fname, width, height, untiledMip, type);
		nt->shouldFreeData = false; //because the untiledMip data is pool-allocated, it does not need to be freed
	}
	if (astc || decode_dxt)
		rapi->Noesis_UnpooledFree(untiledMip);

	//nt->flags |= texFlags;
	nt->globalIdx = idx;
	return nt;
}

template <game_t game>
static inline noesisTex_t * Model_Game_LoadTexture_Switch(bayoDatFile_t *wta, bayoDatFile_t *wtp, bayoWTBHdr<false> &hdr, char * texName, int32_t texIndex, noeRAPI_t *rapi);

template <>
static inline noesisTex_t * Model_Game_LoadTexture_Switch<NIER_AUTOMATA>(bayoDatFile_t *wta, bayoDatFile_t *wtp, bayoWTBHdr<false> &hdr, char * texName, int32_t texIndex, noeRAPI_t *rapi) {
	const bool big = false;
	int dataSize = wta->dataSize;
	BYTE * data = wta->data;
	int dataSize2 = wtp->dataSize;
	BYTE * data2 = wtp->data;

	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *idxs = (int  *)(data + hdr.texIdxOffset);
	nierWTBInfoSwitch_t *tinfs = (nierWTBInfoSwitch_t  *)(data + hdr.texInfoOffset);

	int tof = tofs[texIndex];
	int tsize = tsizes[texIndex];
	int idx = idxs[texIndex];
	nierWTBInfoSwitch<big> info(tinfs + texIndex);

	char fname[8192];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, texIndex);
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);
	DBGLOG("%s: 0x%0x, type: %d, format: %x, width: %d, height: %d, depth: %d\n", fname, idx, info.textureType, info.format, info.width, info.height, info.depth);

	int width = info.width;
	int height = info.height;
	int depth = info.depth;
	size_t mipSize = (size_t)info.textureSize;
	//heuristic
	int widthInBits = 0;
	for (int tmp = width; tmp > 0; tmp /= 2) {
		widthInBits++;
	}
	DBGLOG("Width in bits: %d\n", widthInBits);
	int blockHeightLog2 = widthInBits - 6;
	if (blockHeightLog2 < 0)
		blockHeightLog2 = 0;
	else if (blockHeightLog2 > 4)
		blockHeightLog2 = 4;
	int maxBlockHeight = 1 << blockHeightLog2;
	return Model_LoadTextureSwitch(idx, data2 + tof, (xt1_texture_type_t)info.textureType, (xt1_texture_format_t)info.format, width, height, depth, maxBlockHeight, mipSize, false, 0, fname, rapi);
}

template <game_t game>
static void Model_LoadTextures_Switch(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
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
	for (int i = 0; i < hdr.numTex; i++)
	{
		noesisTex_t *nt = Model_Game_LoadTexture_Switch<game>(texFiles[0], texFiles[1], hdr, texName, i, rapi);
		if (nt)
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

template <game_t game>
static void Model_LoadTextures_Set_Switch(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi, std::set<int32_t> indices) {
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
	noesisTex_t *placeholder = NULL;
	if (textures.Num() > 0)
		placeholder = textures.Pop();
	for (auto it = indices.begin(); it != indices.end(); it++) {
		noesisTex_t *nt = Model_Game_LoadTexture_Switch<game>(texFiles[0], texFiles[1], hdr, texName, *it, rapi);
		if (nt)
			textures.Append(nt);
	}
	if (placeholder)
		textures.Append(placeholder);
}
template <>
static void Model_Bayo_LoadTextures<false, NIER_AUTOMATA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	if (texFiles.Num() < 2)
		return;
	int dataSize = texFiles[0]->dataSize;
	uint8_t * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTAHdr_t))
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
	char *tinfo = (char *)(data + hdr.texInfoOffset);
	DBGLOG("Checking tinfo tag: %.4s\n", tinfo);
	if (memcmp(tinfo, ".tex", 4)) {
		DBGLOG("found Nier PC texture file\n");
		Model_Nier_LoadTextures_PC(textures, texFiles, rapi);
	}
	else {
		DBGLOG("found Nier Switch texture file\n");
		Model_LoadTextures_Switch<NIER_AUTOMATA>(textures, texFiles, rapi);
	}
}

template <bool, game_t>
static void Model_Bayo_LoadTextures_Set(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi, std::set<int32_t> idxSet);

template <>
static void Model_Bayo_LoadTextures_Set<false, NIER_AUTOMATA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi, std::set<int32_t> indices) {
	if (texFiles.Num() < 2)
		return;
	int dataSize = texFiles[0]->dataSize;
	uint8_t * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTAHdr_t))
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
	char *tinfo = (char *)(data + hdr.texInfoOffset);
	DBGLOG("Checking tinfo tag: %.4s\n", tinfo);
	if (memcmp(tinfo, ".tex", 4)) {
		DBGLOG("found Nier PC texture file\n");
		Model_Nier_LoadTextures_Set_PC(textures, texFiles, rapi, indices);
	}
	else {
		DBGLOG("found Nier Switch texture file\n");
		Model_LoadTextures_Set_Switch<NIER_AUTOMATA>(textures, texFiles, rapi, indices);
	}
}

template <>
static void Model_Bayo_CreateTangents<false, NIER_AUTOMATA>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
	Model_Bayo_CreateTangents<false, BAYONETTA>(data, dsts, numVerts, stride, m);
}

template <bool big>
modelBone_t *Model_Nier_CreateBones(nierWMBHdr<big> &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT)
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
		nierBone<big> nBone((nierBone_t *)(data + hdr.ofsBones + i * sizeof(nierBone_t)));
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
		sprintf_s(bone->name, 30, "bone%03i", nBone.id);
		bone->mat = g_identityMatrix;

		float pos[3];
		pos[0] = nBone.localPosition.x;
		pos[1] = nBone.localPosition.y;
		pos[2] = nBone.localPosition.z;
		g_mfn->Math_TranslateMatrix(&bone->mat, pos);
		g_mfn->Math_RotateMatrix(&bone->mat, -nBone.localRotation.z * g_flRadToDeg, 0.0f, 0.0f, 1.0f);
		g_mfn->Math_RotateMatrix(&bone->mat, nBone.localRotation.y * g_flRadToDeg, 0.0f, 1.0f, 0.0f);
		g_mfn->Math_RotateMatrix(&bone->mat, -nBone.localRotation.x * g_flRadToDeg, 1.0f, 0.0f, 0.0f);

		float scale[3];
		scale[0] = nBone.localScale.x;
		scale[1] = nBone.localScale.y;
		scale[2] = nBone.localScale.z;
		for (int i = 0; i < 3; i++) {
			bone->mat.x1[i] *= scale[i];
			bone->mat.x2[i] *= scale[i];
			bone->mat.x3[i] *= scale[i];
		}
		bone->userIndex = 5;
		/*
		pos[0] = nBone.position.x;
		pos[1] = nBone.position.y;
		pos[2] = nBone.position.z;
		g_mfn->Math_VecCopy(pos, bone->mat.o);*/
	}
	bones[numBones].index = numBones;
	bones[numBones].eData.parent = NULL;
	sprintf_s(bones[numBones].name, 30, "bone-1");
	bones[numBones].mat = g_identityMatrix;
	bones[numBones].userIndex = 5;
	rapi->rpgMultiplyBones(bones, numBones);
	return bones;
}

template <bool big, game_t game>
static void Model_Nier_FindUsedTexIdx(
		nierWMBHdr<big> &hdr,
		std::set<int32_t> &usedTexIdx,
		BYTE *data) {
	nierMaterial_t *matPtr = (nierMaterial_t *)(data + hdr.ofsMaterials);
	for (int i = 0; i < hdr.numMaterials; i++)
	{
		nierMaterial<big> mat(matPtr + i);
		nierTexture_t * texPtr = (nierTexture_t *)(data + mat.ofsTextures);
		for (unsigned int j = 0; j < mat.numTextures; j++) {
			nierTexture<big> tex(texPtr + j);
			usedTexIdx.insert(tex.id);
		}
	}
}


template <bool big, game_t game>
static void Model_Nier_LoadMaterials(
		nierWMBHdr<big> &hdr,
		CArrayList<noesisTex_t *> &textures,
		CArrayList<noesisMaterial_t *> &matList,
		CArrayList<noesisMaterial_t *> &matListLightMap,
		CArrayList<noesisMaterial_t *> &totMatList,
		BYTE *data,
		noeRAPI_t *rapi) {
	std::map<int, int> texIdxMap;
	for (int j = 0; j < textures.Num() - 1; j++) {
		if (textures[j]->globalIdx)
			texIdxMap.insert(std::pair <int, int>(textures[j]->globalIdx,j));
	}

	nierMaterial_t *matPtr = (nierMaterial_t *)(data + hdr.ofsMaterials);

	DBGLOG("Found %d materials\n", hdr.numMaterials);
	for (int i = 0; i < hdr.numMaterials; i++)
	{
		nierMaterial<big> mat(matPtr + i);
		DBGLOG("\tFound %s, %s, %s\n", data + mat.ofsName, data + mat.ofsShaderName, data + mat.ofsTechniqueName);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		nmat->name = rapi->Noesis_PooledString((char*)(data + mat.ofsName));
		nmat->noDefaultBlend = false;
		nmat->texIdx = -1;
		nmat->normalTexIdx = textures.Num() - 1;
		nmat->specularTexIdx = -1;
		int difTexId = 0;
		int nrmTexId = 0;
		int specTexId = 0;
		int maskTexId = 0;
		DBGLOG("\tFound %d textures\n", mat.numTextures);
		nierTexture_t * texPtr = (nierTexture_t *)(data + mat.ofsTextures);
		for (unsigned int j = 0; j < mat.numTextures; j++) {
			nierTexture<big> tex(texPtr + j);
			if ((difTexId == 0 || texIdxMap.find(difTexId) == texIdxMap.end()) && (
					strcmp((char*)(data + tex.ofsName), "g_AlbedoMap") == 0 || 
					strcmp((char*)(data + tex.ofsName), "g_AlbedoMap1") == 0 ||
					strcmp((char*)(data + tex.ofsName), "g_AlbedoMap2") == 0 )) {
				difTexId = tex.id;
				if (strcmp((char*)(data + tex.ofsName), "g_AlbedoMap2") == 0)
					nmat->flags |= NMATFLAG_USELMUVS;
			}
			if (strcmp((char*)(data + tex.ofsName), "g_NormalMap") == 0 || strcmp((char*)(data + tex.ofsName), "g_NormalMap1") == 0) {
				nrmTexId = tex.id;
			}
			if (strcmp((char*)(data + tex.ofsName), "g_MaskMap") == 0) {
				maskTexId = tex.id;
			}
			if (strcmp((char*)(data + tex.ofsName), "g_MaskMap2") == 0) {
				specTexId = tex.id;
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
			}
			if (specTexId && tex->globalIdx == specTexId) {
				DBGLOG("Found matching specular %d\n", j);
				nmat->specularTexIdx = j;
				nmat->flags |= NMATFLAG_PBR_SPEC_IR_RG;
			}
			if (maskTexId && tex->globalIdx == maskTexId) {
				DBGLOG("Found matching mask %d\n", j);
				//nmat->ex->occlTexIdx = j;
			}
		}

		bayoV4F_t scaleBias = { 1.0, 1.0, 0.0, 0.0 };
		nierMaterialVariable_t * varPtr = (nierMaterialVariable_t *)(data + mat.ofsVariables);
		for (uint32_t j = 0; j < mat.numVariables; j++) {
			nierMaterialVariable<big> var(varPtr + j);
			if (strcmp((char*)(data + var.ofsName), "g_Tile_X") == 0) {
				scaleBias.x = var.value;
			}
			else if (strcmp((char*)(data + var.ofsName), "g_Tile_Y") == 0) {
				scaleBias.y = var.value;
			}
		}
		if (scaleBias.x != 1.0f || scaleBias.y != 1.0f || scaleBias.z != 0.0f || scaleBias.w != 0.0f) {
			float *p_scaleBias = (float *)rapi->Noesis_PooledAlloc(4 * sizeof(float));
			p_scaleBias[0] = scaleBias.x;
			p_scaleBias[1] = scaleBias.y;
			p_scaleBias[2] = scaleBias.z;
			p_scaleBias[3] = scaleBias.w;
			nmat->ex->pUvScaleBias = p_scaleBias;
		}
		matListLightMap.Append(NULL);
		matList.Append(nmat);
		totMatList.Append(nmat);
	}
}

typedef struct nierBuffers_s : public buffers_s {
	buffer_t indices;
	buffer_t mapping3;
	buffer_t mapping4;
	buffer_t mapping5;
} nierBuffers_t;

template <bool big, game_t game>
static void Model_Nier_SetBuffers(bayoDatFile_t &df, noeRAPI_t *rapi, nierWMBHdr<false> &hdr, nierBuffers_t *buffers, modelMatrix_t * pretransform) {
	BYTE *data = df.data;
	bool bHasBones = ((hdr.numBones > 0) && (hdr.ofsBones != 0));
	for (int i = 0; i < hdr.numVertexGroups; i++) {
		nierVertexGroup<big> vg((nierVertexGroup_t*)(data + hdr.ofsVertexGroups + i * sizeof(nierVertexGroup_t)));
		int bayoVertSize = vg.sizeVert;
		int bayoVertExSize = vg.sizeVertExData;
		int numVerts = vg.numVerts;
		BYTE *indices = data + vg.ofsIndexBuffer;
		BYTE *verts = data + vg.ofsVerts;
		BYTE *vertsEx = data + vg.ofsVertsExData;
		if (!vg.ofsVerts || !vg.ofsIndexBuffer) {
			DBGLOG("Invalid vertex group Found, skipping!\n");
			continue;
		}
		if (bayoVertSize != 28 && bayoVertSize != 24) {
			DBGLOG("Unknown vertex size format: %d!!!\n", bayoVertSize);
#ifdef _DEBUG
			g_nfn->NPAPI_PopupDebugLog(0);
#endif
			continue;
		}
		DBGLOG("Found vertex groups %d %d %x\n", bayoVertSize, bayoVertExSize, vg.vertFlags);
		DBGLOG("Found flags %x\n", hdr.flags);
		if (hdr.flags & 0x8) {
			__set_indices<big, game>(buffers[i].indices, indices, 4);
		}
		else {
			__set_sindices<big, game>(buffers[i].indices, indices, 2);
		}
		if (bayoVertExSize == 16 && vg.vertFlags == 0xe) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 20, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping3, vertsEx + 8, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping4, vertsEx + 12, bayoVertExSize);
		}
		else if (bayoVertExSize == 20 && vg.vertFlags == 0xc) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 20, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping3, vertsEx + 8, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping4, vertsEx + 12, bayoVertExSize);
			__set_mapping<big, game>(buffers[i].mapping5, vertsEx + 16, bayoVertExSize);
		}
		else if (bayoVertExSize == 20 && vg.vertFlags == 0xb) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 20, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 24, bayoVertSize);

			__set_mapping<big, game>(buffers[i].mapping2, vertsEx, bayoVertExSize);
			__set_color<big, game>(buffers[i].color, vertsEx + 4, bayoVertExSize);
			__set_hnormal<big, game>(buffers[i].normal, vertsEx + 8, bayoVertExSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping3, vertsEx + 16, bayoVertExSize);
		}
		else if (bayoVertExSize == 16 && vg.vertFlags == 0xa) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 20, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 24, bayoVertSize);

			__set_mapping<big, game>(buffers[i].mapping2, vertsEx, bayoVertExSize);
			__set_color<big, game>(buffers[i].color, vertsEx + 4, bayoVertExSize);
			__set_hnormal<big, game>(buffers[i].normal, vertsEx + 8, bayoVertExSize, numVerts, rapi, pretransform);
		}
		else if (bayoVertExSize == 16 && vg.vertFlags == 0x8) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 20, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 24, bayoVertSize);

			__set_mapping<big, game>(buffers[i].mapping2, vertsEx, bayoVertExSize);
			__set_hnormal<big, game>(buffers[i].normal, vertsEx + 4, bayoVertExSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping3, vertsEx + 12, bayoVertExSize);
		}
		else if (bayoVertExSize == 12 && vg.vertFlags == 0x7) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 20, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 24, bayoVertSize);

			__set_mapping<big, game>(buffers[i].mapping2, vertsEx, bayoVertExSize);
			__set_hnormal<big, game>(buffers[i].normal, vertsEx + 4, bayoVertExSize, numVerts, rapi, pretransform);
		}
		else if (bayoVertExSize == 12 && vg.vertFlags == 0x5) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 20, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping3, vertsEx + 8, bayoVertExSize);

			//bond to first bone if it exists
			if (bHasBones) {
				DBGLOG("Binding vertexes to first bone.\n");
				unsigned char indexes[4] = { 0, 0, 0, 0 };
				unsigned char weights[4] = { 255, 0, 0, 0 };
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_indexes, numVerts, 4, indexes, rapi);
				__set_static_info<big, game, RPGEODATA_UBYTE>(buffers[i].bone_weights, numVerts, 4, weights, rapi);
			}
		}
		else if (bayoVertExSize == 8 && vg.vertFlags == 0x4) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 20, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 24, bayoVertSize);

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
		else if (bayoVertSize == 24 && bayoVertExSize == 8 && vg.vertFlags == 0x3) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 20, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
		}
		else if (bayoVertSize == 24 && bayoVertExSize == 8 && vg.vertFlags == 0x1) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_mapping<big, game>(buffers[i].mapping2, verts + 20, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
		}
		else if (bayoVertSize == 28 && bayoVertExSize == 0 && vg.vertFlags == 0x0) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_hnormal<big, game>(buffers[i].normal, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		}
		else {
			DBGLOG("Unknown vertex EX size format: %d %x!!!\n", bayoVertExSize, vg.vertFlags);
#ifdef _DEBUG
			g_nfn->NPAPI_PopupDebugLog(0);
#endif
		}
	}
}

template <bool big, game_t game>
static void Model_Bayo_LoadCOL2Model(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t *df, noeRAPI_t *rapi, const char *prefix, modelBone_t *bones, short int * &animBoneTT, CArrayList<noesisMaterial_t *> &totMatList) {
	DBGLOG("Loading %s\n", df->name);
	BYTE *data = df->data;
	int dataSize = df->dataSize;
	if (dataSize < sizeof(nierCOL2Hdr_t))
	{
		return;
	}
	nierCOL2Hdr<big> hdr((nierCOL2Hdr_t *)data);
	if (memcmp(hdr.id, "COL2", 4))
	{ //invalid header
		return;
	}
	noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
	nmat->name = "collision";
	nmat->noDefaultBlend = false;
	nmat->texIdx = -1;
	nmat->normalTexIdx = - 1;
	nmat->specularTexIdx = -1;
	nmat->flags = NMATFLAG_TWOSIDED;
	totMatList.Append(nmat);
	uint32_t *ofsNames = (uint32_t *)(data + hdr.ofsNames);
	int32_t *boneMap = NULL;
	int32_t *boneMap2 = NULL;

	rapi->rpgClearBufferBinds();
	rapi->rpgSetMaterial(nmat->name);
	if (bones && hdr.ofsBoneMap) {
		boneMap = (int32_t*)(data + hdr.ofsBoneMap);
		for (uint32_t i = 0; i < hdr.sizeBoneMap; i++) {
			if (big)
				LITTLE_BIG_SWAP(boneMap[i]);
			boneMap[i] = Model_Bayo_DecodeMotionIndex<big, game>(animBoneTT, boneMap[i]);
			if (big)
				LITTLE_BIG_SWAP(boneMap[i]);
		}
	}
	if (bones && hdr.ofsBoneMap2) {
		boneMap2 = (int32_t*)(data + hdr.ofsBoneMap2);
		for (uint32_t i = 0; i < hdr.sizeBoneMap2; i++) {
			if (big)
				LITTLE_BIG_SWAP(boneMap2[i]);
			boneMap2[i] = Model_Bayo_DecodeMotionIndex<big, game>(animBoneTT, boneMap2[i]);
			if (big)
				LITTLE_BIG_SWAP(boneMap2[i]);
		}
	}
	for (uint32_t i = 0; i < hdr.numMeshes; i++) {
		DBGLOG("Mesh %d\n", i);
		nierCOL2MeshHdr<big> meshHdr((nierCOL2MeshHdr_t *)(data + hdr.ofsMeshes + i * sizeof(nierCOL2MeshHdr_t)));
		uint32_t ofsName = ofsNames[meshHdr.nameIndex];
		if (big)
			LITTLE_BIG_SWAP(ofsName);
		char *meshName = (char *)(data + ofsName);

		for (uint32_t j = 0; j < meshHdr.numBatches; j++) {
			DBGLOG("\tBatch %d\n", j);
			int boneIndex = -1;
			uint32_t ofsVertices;
			uint32_t numVertices;
			uint32_t ofsIndices;
			uint32_t numIndices;
			BYTE boneWeight = 0xff;
			char batch_name[256];

			if (meshHdr.batchType == 2) {
				nierCOL2BatchHdr2<big> batchHdr((nierCOL2BatchHdr2_t *)(data + meshHdr.ofsBatches + j * sizeof(nierCOL2BatchHdr2_t)));
				boneIndex = batchHdr.boneIndex;
				ofsVertices = batchHdr.ofsVertices;
				numVertices = batchHdr.numVertices;
				ofsIndices = batchHdr.ofsIndices;
				numIndices = batchHdr.numIndices;
			} else if (meshHdr.batchType == 3) {
				nierCOL2BatchHdr3<big> batchHdr((nierCOL2BatchHdr3_t *)(data + meshHdr.ofsBatches + j * sizeof(nierCOL2BatchHdr3_t)));
				ofsVertices = batchHdr.ofsVertices;
				numVertices = batchHdr.numVertices;
				ofsIndices = batchHdr.ofsIndices;
				numIndices = batchHdr.numIndices;
			}
			else {//unknown vertex format
				DBGLOG("Found unknown collision vertex format: %d\n", meshHdr.batchType);
				continue;
			}
			int archBoneIndex = boneIndex;
			if (big)
				LITTLE_BIG_SWAP(archBoneIndex);

			sprintf_s(batch_name, 256, "col_%d_%s_%d", i, meshName, j);
			DBGLOG("\t%s\n", batch_name);
			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			if (meshHdr.batchType == 2) {
				if (boneIndex != -1 && bones) {
					int32_t realBoneIndex = boneIndex;
					if (boneMap) {
						realBoneIndex = boneMap[realBoneIndex];
						if (big)
							LITTLE_BIG_SWAP(realBoneIndex);
						rapi->rpgSetBoneMapSafe(boneMap, hdr.sizeBoneMap);
					}
					rapi->rpgBindBoneIndexBufferSafe(&archBoneIndex, RPGEODATA_INT, 0, 1, sizeof(int32_t));
					rapi->rpgBindBoneWeightBufferSafe(&boneWeight, RPGEODATA_BYTE, 0, 1, sizeof(BYTE));
					Model_Bayo_PretransformPositions<big>(data + ofsVertices, numVertices, 4 * sizeof(float), &bones[realBoneIndex].mat);
				}
				rapi->rpgBindPositionBufferSafe(data + ofsVertices, RPGEODATA_FLOAT, 4 * sizeof(float), 4 * sizeof(float) * numVertices);
				int result = rapi->rpgCommitTrianglesSafe(data + ofsIndices, RPGEODATA_USHORT, numIndices, RPGEO_TRIANGLE, true);
				DBGLOG("committed triangles: %d:\n", result);
				if (boneIndex != -1 && bones) {
					rapi->rpgBindBoneIndexBuffer(NULL, RPGEODATA_INT, 0, 0);
					rapi->rpgBindBoneWeightBuffer(NULL, RPGEODATA_BYTE, 0, 0);
				}
			}
			else if (meshHdr.batchType == 3) {
				if (boneMap2)
					rapi->rpgSetBoneMapSafe(boneMap2, hdr.sizeBoneMap2);
				rapi->rpgBindPositionBufferSafe(data + ofsVertices, RPGEODATA_FLOAT, 0x30, 0x30 * (numVertices - 1) + 0x10);
				if (bones) {
					rapi->rpgBindBoneWeightBufferSafe(data + ofsVertices + 0x10, RPGEODATA_FLOAT, 0x30, 4, 0x30 * (numVertices - 1) + 0x10);
					rapi->rpgBindBoneIndexBufferSafe(data + ofsVertices + 0x20, RPGEODATA_INT, 0x30, 4, 0x30 * (numVertices - 1) + 0x10);
				}
				int result = rapi->rpgCommitTrianglesSafe(data + ofsIndices, RPGEODATA_USHORT, numIndices, RPGEO_TRIANGLE, true);
				DBGLOG("committed triangles: %d\n", result);
				if (bones) {
					rapi->rpgBindBoneIndexBuffer(NULL, RPGEODATA_INT, 0, 0);
					rapi->rpgBindBoneWeightBuffer(NULL, RPGEODATA_BYTE, 0, 0);
				}
			}
			rapi->rpgSetBoneMap(NULL);
		}
	}
	rapi->rpgClearBufferBinds();
}

static void findTextureIndex(noeRAPI_t *rapi, BYTE * &data, int &sz) {
	wchar_t *inFile = rapi->Noesis_GetInputNameW();
	wchar_t searchPath[MAX_NOESIS_PATH];
	rapi->Noesis_GetDirForFilePathW(searchPath, inFile);
	data = NULL;
	sz = 0;
	while (!data && wcslen(searchPath) > 0) {
		DBGLOG("Searching for texture index in: %ls\n", searchPath);
		wchar_t path[MAX_NOESIS_PATH];
		wcscpy(path, searchPath);
		wcscat_s(path, MAX_NOESIS_PATH, L"bayo_texture_index");
		data = (BYTE *)rapi->Noesis_ReadFileW(path, &sz);
		if (!data) {
			wcscpy(path, searchPath);
			path[wcslen(path) - 1] = 0;
			rapi->Noesis_GetDirForFilePathW(searchPath, path);
		}
	}
	if (data)
		DBGLOG("Found texture index in: %ls\n", searchPath);
}

static inline void dataAdvance(BYTE * &data, size_t &sz, size_t amount) {
	data += amount;
	sz -= amount;
}

static void loadTextureIndex(BYTE *data, size_t sz, std::map<int32_t, std::tuple<wchar_t*, char*, int32_t>> &textureIndex) {
	while (sz) {
		if (sz < sizeof(uint32_t))
			break;
		uint32_t pathlen = *(uint32_t *)data;
		dataAdvance(data, sz, sizeof(uint32_t));
		if (sz < pathlen * sizeof(wchar_t))
			break;
		wchar_t *path = (wchar_t *)data;
		dataAdvance(data, sz, pathlen * sizeof(wchar_t));
		if (sz < sizeof(uint32_t))
			break;
		uint32_t namelen = *(uint32_t *)data;
		dataAdvance(data, sz, sizeof(uint32_t));
		if (sz < namelen * sizeof(char))
			break;
		char *name = (char *)data;
		dataAdvance(data, sz, namelen * sizeof(char));
		if (sz < sizeof(int32_t))
			break;
		int32_t numTex = *(int32_t *)data;
		dataAdvance(data, sz, sizeof(int32_t));
		for (int32_t i = 0; i < numTex; i++) {
			if (sz < sizeof(int32_t))
				return;
			int32_t idx = *(int32_t *)data;
			dataAdvance(data, sz, sizeof(int32_t));
			textureIndex.insert(std::pair<int32_t, std::tuple<wchar_t*, char*, int32_t>>(idx, std::tuple<wchar_t*, char*, int32_t>(path, name, i)));
		}
	}
}

template <bool big, game_t game>
static void loadMissingTexture(std::set<int32_t> &missingTexIdx, std::map<int32_t, std::tuple<wchar_t*, char*, int32_t>> &textureIndex, CArrayList<noesisTex_t *> &textures, noeRAPI_t *rapi) {
	std::map<wchar_t*, std::map<char *, std::set<int32_t>>> fileMap;
	if (missingTexIdx.size() > 0)
		DBGLOG("Found missing textures:\n");
	for (auto it = missingTexIdx.begin(); it != missingTexIdx.end(); it++) {
		auto itmap = textureIndex.find(*it);
		if (itmap != textureIndex.end()) {
			fileMap[std::get<0>(itmap->second)][std::get<1>(itmap->second)].insert(std::get<2>(itmap->second));
			DBGLOG("\t%08x: %ls:%s:%d\n", *it, std::get<0>(itmap->second), std::get<1>(itmap->second), std::get<2>(itmap->second));
		}
	}
	DBGLOG("Task list:\n");
	for (auto it = fileMap.begin(); it != fileMap.end(); it++) {
		DBGLOG("\t%ls:\n", it->first);
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			DBGLOG("\t\t%s:\n", it2->first);
			for (auto it3 = it2->second.begin(); it3 != it2->second.end(); it3++) {
				DBGLOG("\t\t\t%d:\n", *it3);
			}
		}
	}
	for (auto it = fileMap.begin(); it != fileMap.end(); it++) {
		CArrayList<bayoDatFile_t> dfiles;
		int datLen = 0;
		BYTE *datFile = (BYTE *)rapi->Noesis_ReadFileW(it->first, &datLen);
		if (datFile && datLen > 0)
			Model_Bayo_GetDATEntries<big>(dfiles, datFile, datLen);
		BYTE *dttFile = Bayo_LoadCompanionDxx<big>(it->first, dfiles, rapi);
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			CArrayList<bayoDatFile_t*> texFiles;
			for (int i = 0; i < dfiles.Num(); i++) {
				bayoDatFile_t &dft = dfiles[i];
				if (!_stricmp(dft.name, it2->first))
					texFiles.Append(&dft);
			}
			if (rapi->Noesis_CheckFileExt(it2->first, ".wta")) {
				char texName[MAX_NOESIS_PATH];
				rapi->Noesis_GetExtensionlessName(texName, it2->first);
				strcat_s(texName, MAX_NOESIS_PATH, ".wtp");
				for (int i = 0; i < dfiles.Num(); i++) {
					bayoDatFile_t &dft = dfiles[i];
					if (!_stricmp(dft.name, texName))
						texFiles.Append(&dft);
				}
			}
			Model_Bayo_LoadTextures_Set<big, game>(textures, texFiles, rapi, it2->second);
		}
		if (datFile)
			rapi->Noesis_UnpooledFree(datFile);
		if (dttFile)
			rapi->Noesis_UnpooledFree(dttFile);
	}
}

template <bool big, game_t game>
static void Model_Bayo_LoadWMB3Model(
		CArrayList<bayoDatFile_t> &dfiles,
		bayoDatFile_t &df,
		noeRAPI_t *rapi,
		CArrayList<noesisModel_t *> &models,
		CArrayList<noesisTex_t *> &givenTextures,
		modelMatrix_t * pretransform,
		int sharedtextureoffset,
		const char *prefix,
		CArrayList<noesisMaterial_t *> *globalMatList) {
	DBGLOG("Loading %s\n", df.name);
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(nierWMBHdr_t))
	{
		return;
	}
	nierWMBHdr<big> hdr((nierWMBHdr_t *)data);
	if (memcmp(hdr.id, "WMB3", 4))
	{ //invalid header
		return;
	}

	CArrayList<bayoDatFile_t *> motfiles;
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<bayoDatFile_t *> expfile;
	CArrayList<bayoDatFile_t *> colfile;
	CArrayList<noesisTex_t *> textures;
	CArrayList<noesisMaterial_t *> matList;
	CArrayList<noesisMaterial_t *> matListLightMap;
	CArrayList<noesisMaterial_t *> totMatList;
	CArrayList<noesisAnim_t *> animList;

	nierBuffers_t *buffers = (nierBuffers_t *)rapi->Noesis_UnpooledAlloc(hdr.numVertexGroups * sizeof(nierBuffers_t));
	memset(buffers, 0, hdr.numVertexGroups * sizeof(nierBuffers_t));

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

	std::set<int32_t> texIdx;
	for (int i = 0; i < textures.Num(); i++)
		if (textures[i]->globalIdx)
			texIdx.insert(textures[i]->globalIdx);
	std::set<int32_t> usedTexIdx;
	Model_Nier_FindUsedTexIdx<big,game>(hdr, usedTexIdx, data);
	std::set<int32_t> missingTexIdx;
	std::set_difference(usedTexIdx.begin(), usedTexIdx.end(), texIdx.begin(), texIdx.end(), std::inserter(missingTexIdx, missingTexIdx.end()));
	if (missingTexIdx.size() > 0)
		DBGLOG("Missing %zu textures:\n", missingTexIdx.size());
	for (auto it = missingTexIdx.begin(); it != missingTexIdx.end(); it++)
		DBGLOG("\t%08x\n", *it);

	BYTE *textureIndex = NULL;
	int textureIndexSize = 0;
	findTextureIndex(rapi, textureIndex, textureIndexSize);
	std::map<int32_t, std::tuple<wchar_t*, char*, int32_t>> textureIndexMap;
	if (gpPGOptions->bUseTextureIndex)
		loadTextureIndex(textureIndex, textureIndexSize, textureIndexMap);
/*	DBGLOG("Texture cache content:\n");
	for (auto it = textureIndexMap.begin(); it != textureIndexMap.end(); it++) {
		DBGLOG("\t%08x: %ls:%s\n", it->first, std::get<0>(it->second), std::get<1>(it->second));
	}*/
	loadMissingTexture<big, game>(missingTexIdx, textureIndexMap, textures, rapi);

	Model_Nier_LoadMaterials<big, game>(hdr, textures, matList, matListLightMap, totMatList, data, rapi);

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_Nier_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

	if (hdr.referenceBone != -1) {
		Model_Nier_SetBuffers<big, game>(df, rapi, hdr, buffers, &bones[hdr.referenceBone].mat);
	}
	else {
		Model_Nier_SetBuffers<big, game>(df, rapi, hdr, buffers, pretransform);
	}

	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
	rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);

	Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
	Model_Bayo_GetEXPFile(dfiles, df, rapi, expfile);
	Model_Bayo_GetCOLFile(dfiles, df, rapi, colfile);
	if (bones) {
		Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBones);
		Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBones);
	}

	DBGLOG("Found %d lods\n", hdr.numLods);
	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	DBGLOG("Found %d batches\n", hdr.numBatches);

	nierMesh_t *meshes = (nierMesh_t *)(data + hdr.ofsMeshes);
	nierLod_t *lods = (nierLod_t *)(data + hdr.ofsLods);
	nierBatch_t *batches = (nierBatch_t *)(data + hdr.ofsBatches);
	nierBoneSet_t *boneSets = (nierBoneSet_t *)(data + hdr.ofsBoneSets);
	unsigned int *boneMap = (unsigned int *)(data + hdr.ofsBoneMap);
	for (int i = 0; i < (gpPGOptions->bDisplayLODs ? hdr.numLods : std::min(hdr.numLods, 1)); i++)
	{
		nierLod<big> lod(lods + i);
		DBGLOG("LOD %d: name: %s\n", i, (char*)(data + lod.ofsName));
		unsigned int batchStart = lod.batchStart;
		nierBatchInfo_t * batchInfos = (nierBatchInfo_t *)(data + lod.ofsBatchInfos);
		for (unsigned int j = 0; j < lod.numBatchInfos; j++) {
			char batch_name[256];
			nierBatchInfo<big> batchInfo(batchInfos + j);
			nierBatch<big> batch(batches + batchStart + j);
			nierMesh<big> mesh(meshes + batchInfo.meshIndex);
			nierBoneSet<big> boneSet(boneSets + batch.boneSetIndex);

			uint32_t vertexGroupIndex = batchInfo.vertexGroupIndex;
			uint32_t materialIndex = batchInfo.materialIndex;

			sprintf_s(batch_name, 256, "%s_%d_%s", (char *)(data + lod.ofsName), j, (char *)(data + mesh.ofsName));
			DBGLOG("\t%s\n", batch_name);
			if (!buffers[vertexGroupIndex].position.address) {
				DBGLOG("Invalid vertex group used, skipping!\n");
				continue;
			}
			int32_t *boneIndices = NULL;
			if (bones && batch.boneSetIndex >= 0) {
				boneIndices = (int32_t *)rapi->Noesis_UnpooledAlloc(boneSet.numBoneIndices * sizeof(int32_t));
				uint16_t *originalBoneIndices = (uint16_t *)(data + boneSet.ofsBoneSet);
				for (uint32_t j = 0; j < boneSet.numBoneIndices; j++) {
					uint16_t sourceIndex;
					sourceIndex = originalBoneIndices[j];
					if (big) {
						LITTLE_BIG_SWAP(sourceIndex);
					}
					boneIndices[j] = boneMap[sourceIndex];
				}
			}
			else if (bones && boneMap) {
				boneIndices = (int *)rapi->Noesis_UnpooledAlloc(hdr.sizeBoneMap * sizeof(int32_t));
				for (int j = 0; j < hdr.sizeBoneMap; j++) {
					boneIndices[j] = boneMap[j];
				}
			}

			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			rapi->rpgSetBoneMap(boneIndices);
			if (bones && buffers[vertexGroupIndex].bone_indexes.address)
			{
				rapi->rpgBindBoneIndexBuffer(buffers[vertexGroupIndex].bone_indexes.address, buffers[vertexGroupIndex].bone_indexes.type, buffers[vertexGroupIndex].bone_indexes.stride, 4);
				rapi->rpgBindBoneWeightBuffer(buffers[vertexGroupIndex].bone_weights.address, buffers[vertexGroupIndex].bone_weights.type, buffers[vertexGroupIndex].bone_weights.stride, 4);
			}
			rapi->rpgBindPositionBuffer(buffers[vertexGroupIndex].position.address, buffers[vertexGroupIndex].position.type, buffers[vertexGroupIndex].position.stride);
			rapi->rpgBindNormalBuffer(buffers[vertexGroupIndex].normal.address, buffers[vertexGroupIndex].normal.type, buffers[vertexGroupIndex].normal.stride);
			rapi->rpgBindUV1Buffer(buffers[vertexGroupIndex].mapping.address, buffers[vertexGroupIndex].mapping.type, buffers[vertexGroupIndex].mapping.stride);
			if (buffers[vertexGroupIndex].mapping2.address) {
				rapi->rpgBindUV2Buffer(buffers[vertexGroupIndex].mapping2.address, buffers[vertexGroupIndex].mapping2.type, buffers[vertexGroupIndex].mapping2.stride);
			}
			else {
				rapi->rpgBindUV2Buffer(NULL, RPGEODATA_HALFFLOAT, 0);
			}
			if (buffers[vertexGroupIndex].mapping3.address) {
				rapi->rpgBindUVXBuffer(buffers[vertexGroupIndex].mapping3.address, buffers[vertexGroupIndex].mapping3.type, buffers[vertexGroupIndex].mapping3.stride, 2, 2);
			}
			else {
				rapi->rpgBindUVXBuffer(NULL, RPGEODATA_HALFFLOAT, 0, 2, 2);
			}
			if (buffers[vertexGroupIndex].mapping4.address) {
				rapi->rpgBindUVXBuffer(buffers[vertexGroupIndex].mapping4.address, buffers[vertexGroupIndex].mapping4.type, buffers[vertexGroupIndex].mapping4.stride, 3, 2);
			}
			else {
				rapi->rpgBindUVXBuffer(NULL, RPGEODATA_HALFFLOAT, 0, 3, 2);
			}
			if (buffers[vertexGroupIndex].mapping5.address) {
				rapi->rpgBindUVXBuffer(buffers[vertexGroupIndex].mapping5.address, buffers[vertexGroupIndex].mapping5.type, buffers[vertexGroupIndex].mapping5.stride, 4, 2);
			}
			else {
				rapi->rpgBindUVXBuffer(NULL, RPGEODATA_HALFFLOAT, 0, 4, 2);
			}
			rapi->rpgSetMaterial(matList[materialIndex]->name);
			rapi->rpgCommitTriangles(buffers[vertexGroupIndex].indices.address + batch.indexStart * buffers[vertexGroupIndex].indices.stride, buffers[vertexGroupIndex].indices.type, batch.numIndices, RPGEO_TRIANGLE, true);

			if (bones) {
				rapi->rpgSetBoneMap(NULL);
				rapi->Noesis_UnpooledFree(boneIndices);
			}
		}

	}

	if (gpPGOptions->bCollisionModels && colfile.Num() > 0) {
		Model_Bayo_LoadCOL2Model<big, game>(dfiles, colfile[0], rapi, prefix, bones, animBoneTT, totMatList);
	}

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(totMatList, textures);
	rapi->rpgSetExData_Materials(md);
	if (bones) {
		rapi->rpgSetExData_Bones(bones, numBones + 1);
	}
	int anims_num = animList.Num();
	DBGLOG("Found %d anims\n", anims_num);
#ifndef _NOE64
	if (anims_num > 700) {
		DBGLOG("Only displaying 700 first animations");
		anims_num = 700;
	}
#endif

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

	rapi->Noesis_UnpooledFree(buffers);
	if (textureIndex)
		rapi->Noesis_UnpooledFree(textureIndex);
	animList.Clear();
	matList.Clear();
	motfiles.Clear();
	texFiles.Clear();
	textures.Clear();
	matListLightMap.Clear();
	totMatList.Clear();
}

template <>
static void Model_Bayo_LoadModel<false, NIER_AUTOMATA>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset, const char *prefix, CArrayList<noesisMaterial_t *> *globalMatList) {
	Model_Bayo_LoadWMB3Model<false, NIER_AUTOMATA>(dfiles, df, rapi, models, givenTextures, pretransform, sharedtextureoffset, prefix, globalMatList);
}


template <>
static void Model_Bayo_LoadScenery<false, NIER_AUTOMATA>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
}