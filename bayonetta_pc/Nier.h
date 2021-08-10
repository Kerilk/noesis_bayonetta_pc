#pragma once
typedef struct nierWMBHdr_s
{
	BYTE				id[4];				// 0
	unsigned int		version;			// 4
	int					unknownA;			// 8
	short				flags;				// C Seems related to vertex index size
	short				referenceBone;		// E
	float				boundingBox[6];		//10
	unsigned int		ofsBones;			//28
	int					numBones;			//2C
	unsigned int		ofsBoneIndexTT;		//30
	int					sizeBoneIndexTT;	//34
	unsigned int		ofsVertexGroups;	//38
	int					numVertexGroups;	//3C
	unsigned int		ofsBatches;			//40
	int					numBatches;			//44
	unsigned int		ofsLods;			//48
	int					numLods;			//4C
	unsigned int		ofsUnknownD;		//50
	int					numUnknownE;		//54
	unsigned int		ofsBoneMap;			//58
	int					sizeBoneMap;		//5C
	unsigned int		ofsBoneSets;		//60
	int					numBoneSets;		//64
	unsigned int		ofsMaterials;		//68
	int					numMaterials;		//6C
	unsigned int		ofsMeshes;			//70
	int					numMeshes;			//74
	unsigned int		ofsMeshMaterial;	//78
	int					numMeshMaterial;	//7C
	unsigned int		ofsUnknownF;		//80
	int					numUnknownG;		//84
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

	short			version[4];
	unsigned int	ofsName;
	unsigned int	ofsShaderName;
	unsigned int	ofsTechniqueName;
	unsigned int	unknownA;
	unsigned int	ofsTextures;
	unsigned int	numTextures;
	unsigned int	ofsParameterGroups;
	unsigned int	numParametersGroup;
	unsigned int	ofsVariables;
	unsigned int	numVariables;
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
typedef struct nierTexture_s
{
	unsigned int	ofsName;
	int				id;
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
	short			id;
	short			parentIndex;
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
	unsigned int	ofsVerts;
	unsigned int	ofsVertsExData;
	unsigned int	unknownA;
	unsigned int	unknownB;
	unsigned int	sizeVert;
	unsigned int	sizeVertExData;
	unsigned int	unknownD;
	unsigned int	unknownE;
	unsigned int	numVerts;
	unsigned int	vertFlags;
	unsigned int	ofsIndexBuffer;
	unsigned int	numIndexes;
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
	unsigned int	ofsName;
	float			boundingBox[6];
	unsigned int	ofsMaterials;
	unsigned int	numMaterials;
	unsigned int	ofsBones;
	unsigned int	numBones;
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
	unsigned int	ofsName;
	int				lodLevel;
	unsigned int	batchStart;
	unsigned int	ofsBatchInfos;
	unsigned int	numBatchInfos;
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
	unsigned int	vertexGroupIndex;
	unsigned int	meshIndex;
	unsigned int	materialIndex;
	int				unknownA;
	unsigned int	meshMaterialPairIndex;
	int				unknownB;
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
	unsigned int	vertexGroupIndex;
	int				boneSetIndex;
	unsigned int	vertexStart;
	unsigned int	indexStart;
	unsigned int	numVerts;
	unsigned int	numIndices;
	unsigned int	numPrimitives;
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
	unsigned int	ofsBoneSet;
	unsigned int	numBoneIndices;
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

template <>
static void Model_Bayo_GetTextureBundle<NIER_AUTOMATA>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi) {
	Model_Bayo_GetTextureBundle<BAYONETTA2>(texFiles, dfiles, df, rapi);
}

template <>
static void Model_Bayo_LoadTextures<false, NIER_AUTOMATA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	const bool big = true;
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
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *tflags = (int *)(data + hdr.ofsTexFlags);
	int *tidx = (int *)(data + hdr.texIdxOffset);
	for (int i = 0; i < hdr.numTex; i++)
	{
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%0x", rapi->Noesis_GetOption("texpre"), tidx[i]);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		int ofs = tofs[i];
		int size = tsizes[i];
		if (ofs < 0 || ofs > dataSize2)
		{
			continue;
		}
		BYTE *texData = data2 + ofs;
		BYTE *pix;
		int globalIdx = -1;
		ddsTexHdr_t tex;
		globalIdx = tidx[i];
		tex = *((ddsTexHdr_t *)texData);
		pix = texData + sizeof(ddsTexHdr_t);
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
static void Model_Nier_LoadMaterials(nierWMBHdr<big> &hdr,
	CArrayList<noesisTex_t *> &textures,
	CArrayList<noesisMaterial_t *> &matList,
	CArrayList<noesisMaterial_t *> &matListLightMap,
	CArrayList<noesisMaterial_t *> &totMatList,
	BYTE *data,
	noeRAPI_t *rapi) {
	std::map<int, int> texIdxMap;
	for (int j = 0; j < textures.Num() - 1; j++) {
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
			if ((difTexId == 0 || texIdxMap.find(difTexId) == texIdxMap.end())&& (
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
		DBGLOG("Found vertex groups %d %d %x\n", bayoVertSize, bayoVertExSize, vg.vertFlags);
		if (bayoVertExSize == 20 && vg.vertFlags == 0xb) {
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
		else if (bayoVertExSize == 12 && vg.vertFlags == 0x7) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_indexes, verts + 20, bayoVertSize);
			__set_bone_infos<big, game>(buffers[i].bone_weights, verts + 24, bayoVertSize);

			__set_mapping<big, game>(buffers[i].mapping2, vertsEx, bayoVertExSize);
			__set_hnormal<big, game>(buffers[i].normal, vertsEx + 4, bayoVertExSize, numVerts, rapi, pretransform);
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
		else if (bayoVertExSize == 16 && vg.vertFlags == 0xe) {
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
		else if (bayoVertSize == 24 && bayoVertExSize == 8 && vg.vertFlags == 0x3) {
			__set_position<big, game>(buffers[i].position, verts, bayoVertSize, numVerts, pretransform);
			__set_tangents<big, game>(buffers[i].tangents, verts + 12, bayoVertSize, numVerts, rapi, pretransform);
			__set_mapping<big, game>(buffers[i].mapping, verts + 16, bayoVertSize);
			__set_color<big, game>(buffers[i].color, verts + 20, bayoVertSize);

			__set_hnormal<big, game>(buffers[i].normal, vertsEx, bayoVertExSize, numVerts, rapi, pretransform);
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
static void Model_Bayo_LoadWMB3Model(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset, const char *prefix, CArrayList<noesisMaterial_t *> *globalMatList) {
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

			unsigned int vertexGroupIndex = batchInfo.vertexGroupIndex;
			unsigned int materialIndex = batchInfo.materialIndex;

			sprintf_s(batch_name, 256, "%s_%d_%s", (char *)(data + lod.ofsName), j, (char *)(data + mesh.ofsName));
			DBGLOG("\t%s\n", batch_name);
			int *boneIndices = NULL;
			if (bones && batch.boneSetIndex >= 0) {
				boneIndices = (int *)rapi->Noesis_UnpooledAlloc(boneSet.numBoneIndices * sizeof(int));
				unsigned short *originalBoneIndices = (unsigned short *)(data + boneSet.ofsBoneSet);
				for (unsigned int j = 0; j < boneSet.numBoneIndices; j++) {
					unsigned short sourceIndex;
					sourceIndex = originalBoneIndices[j];
					if (big) {
						LITTLE_BIG_SWAP(sourceIndex);
					}
					boneIndices[j] = boneMap[sourceIndex];
				}
			}
			else if (bones && boneMap) {
				boneIndices = (int *)rapi->Noesis_UnpooledAlloc(hdr.sizeBoneMap * sizeof(int));
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