#pragma once
typedef struct madWorldTPLHdr_s
{
	uint8_t				id[4];
	uint32_t            numImages;
	uint32_t            imageTableOffset;
} madWorldTPLHdr_t;

template <bool big>
struct madWorldTPLHdr : public madWorldTPLHdr_s {
	madWorldTPLHdr(madWorldTPLHdr_t *ptr) : madWorldTPLHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(numImages);
			LITTLE_BIG_SWAP(imageTableOffset);
		}
	}
};

typedef struct madWorldTPLRecord_s
{
	uint32_t			imageOffset;
	uint32_t			paletteOffset;
} madWorldTPLRecord_t;

template <bool big>
struct madWorldTPLRecord : public madWorldTPLRecord_s {
	madWorldTPLRecord(madWorldTPLRecord_t *ptr) : madWorldTPLRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(imageOffset);
			LITTLE_BIG_SWAP(paletteOffset);
		}
	}
};

typedef struct madWorldTPLImage_s
{
	uint16_t		height;
	uint16_t		width;
	uint32_t		format;
	uint32_t		offset;
	uint32_t		wrapS;
	uint32_t		wrapT;
	uint32_t		minFilter;
	uint32_t		magFilter;
	float			LODBias;
	uint8_t			edgeLODEnable;
	uint8_t			minLOD;
	uint8_t			maxLOD;
	uint8_t			unpacked;
} madWorldTPLImage_t;

template <bool big>
struct madWorldTPLImage : public madWorldTPLImage_s {
	madWorldTPLImage(madWorldTPLImage_t * ptr) : madWorldTPLImage_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(height);
			LITTLE_BIG_SWAP(width);
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(offset);
			LITTLE_BIG_SWAP(wrapS);
			LITTLE_BIG_SWAP(wrapT);
			LITTLE_BIG_SWAP(minFilter);
			LITTLE_BIG_SWAP(magFilter);
			LITTLE_BIG_SWAP(LODBias);
		}
	}
};

typedef struct madWorldTPLPalette_s {
	uint16_t	numEntries;
	uint8_t		unpacked;
	uint8_t		padding;
	uint32_t	format;
	uint32_t	offset;
} madWorldTPLPalette_t;

template <bool big>
struct madWorldTPLPalette : public madWorldTPLPalette_s {
	madWorldTPLPalette(madWorldTPLPalette_t * ptr) : madWorldTPLPalette_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numEntries);
			LITTLE_BIG_SWAP(format);
			LITTLE_BIG_SWAP(offset);
		}
	}
};

typedef struct madWorldMDBHeader_s {
	char		id[2];
	uint16_t	flags; //0x200 extended descriptors
	uint32_t	numVertexPos;
	uint32_t	vertexPosOffset;
	uint32_t	numNormals;
	uint32_t	normalsOffset;
	uint32_t	numUVs;
	uint32_t	UVsOffset;
	uint32_t	numColors;
	uint32_t	colorsOffset;
	uint32_t	numBonePalette;
	uint32_t	bonePaletteOffset;
	uint32_t	numBones;
	uint32_t	boneParentOffset;
	uint32_t	boneRelativePositionOffset;
	uint32_t	bonePositionOffset;
	uint32_t	numMaterials;
	uint32_t	materialsOffset;
	uint32_t	unknownCount; //Distinc triangles?
	uint32_t	meshesOffset;
	int16_t		vertexPosDivisorBit;
	int16_t		UVsDivisorBit;
	uint32_t	uc;
	uint32_t	unknownBoneRelatedOffset1;
	uint32_t	unknownBoneRelatedOffset2;
	uint32_t	boneNameOffset;
	uint32_t	bonePaletteReferenceCountOffset;
	uint16_t	numMeshes; //if vertexFlags & 0x200
	uint8_t		ud;
	uint8_t		uf;
	uint32_t	ug[5];
	uint32_t	strangeFlags; // 0x100: additional byte in index
} madWorldMDBHeader_t;

template <bool big>
struct madWorldMDBHeader : public madWorldMDBHeader_s {
	madWorldMDBHeader(madWorldMDBHeader_t * ptr) : madWorldMDBHeader_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flags);
			LITTLE_BIG_SWAP(numVertexPos);
			LITTLE_BIG_SWAP(vertexPosOffset);
			LITTLE_BIG_SWAP(numNormals);
			LITTLE_BIG_SWAP(normalsOffset);
			LITTLE_BIG_SWAP(numUVs);
			LITTLE_BIG_SWAP(UVsOffset);
			LITTLE_BIG_SWAP(numColors);
			LITTLE_BIG_SWAP(colorsOffset);
			LITTLE_BIG_SWAP(numBonePalette);
			LITTLE_BIG_SWAP(bonePaletteOffset);
			LITTLE_BIG_SWAP(numBones);
			LITTLE_BIG_SWAP(boneParentOffset);
			LITTLE_BIG_SWAP(boneRelativePositionOffset);
			LITTLE_BIG_SWAP(bonePositionOffset);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(materialsOffset);
			LITTLE_BIG_SWAP(unknownCount);
			LITTLE_BIG_SWAP(meshesOffset);
			LITTLE_BIG_SWAP(vertexPosDivisorBit);
			LITTLE_BIG_SWAP(UVsDivisorBit);
			LITTLE_BIG_SWAP(uc);
			LITTLE_BIG_SWAP(unknownBoneRelatedOffset1);
			LITTLE_BIG_SWAP(unknownBoneRelatedOffset2);
			LITTLE_BIG_SWAP(boneNameOffset);
			LITTLE_BIG_SWAP(bonePaletteReferenceCountOffset);
			LITTLE_BIG_SWAP(numMeshes);
			for (int i = 0; i < 5; i++)
				LITTLE_BIG_SWAP(ug[i]);
			LITTLE_BIG_SWAP(strangeFlags);
		}
	}
};

typedef struct madWorldMDBMesh_s {
	uint32_t	nextMeshOffset;
	uint8_t		materialID;
	uint8_t		flags;
	uint8_t		ua;
	uint8_t		ub;
	int16_t		data[6];
	uint32_t	indexBuffersSize;
	uint32_t	numIndexBuffers;
	uint32_t	u_c;
	//char		name[0x3c]; if (madWorldMDBHeader.flags & 0x200)
	//uint32_t	u_d; if (madWorldMDBHeader.flags & 0x200)
	//char      name[0x20]; if (!(madWorldMDBHeader.flags & 0x200))
} madWorldMDBMesh_t;

template <bool big>
struct madWorldMDBMesh : public madWorldMDBMesh_s {
	madWorldMDBMesh(madWorldMDBMesh_t * ptr) : madWorldMDBMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(nextMeshOffset);
			for (int i = 0; i < 6; i++) {
				LITTLE_BIG_SWAP(data[i]);
			}
			LITTLE_BIG_SWAP(indexBuffersSize);
			LITTLE_BIG_SWAP(numIndexBuffers);
			LITTLE_BIG_SWAP(u_c);
		}
	}
};

typedef struct madWorldSCRHdr_s
{
	BYTE				id[4];
	int					numModels;
	unsigned int		texturesOffset;
	BYTE				unknown[4];
} madWorldSCRHdr_t;
template <bool big>
struct madWorldSCRHdr : public madWorldSCRHdr_s {
	madWorldSCRHdr(madWorldSCRHdr_t * ptr) : madWorldSCRHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numModels);
			LITTLE_BIG_SWAP(texturesOffset);
		}
	}
};

typedef struct madWorldSCRModelDscr_s
{
	char		name[0x30];
	uint32_t	offset;
	float		transform[9];
	uint32_t    unknownA[2];
}madWorldSCRModelDscr_t;
template <bool big>
struct madWorldSCRModelDscr : public madWorldSCRModelDscr_s {
	madWorldSCRModelDscr(madWorldSCRModelDscr_t * ptr) : madWorldSCRModelDscr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offset);
			for (int i = 0; i < 9; i++) {
				LITTLE_BIG_SWAP(transform[i]);
			}
			for (int i = 0; i < 2; i++) {
				LITTLE_BIG_SWAP(unknownA[i]);
			}
		}
	}
};

template <>
static void Model_Bayo_LoadTextures<true, MADWORLD>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi) {
	const bool big = true;
	uint32_t dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	char texName[MAX_NOESIS_PATH];
	if (dataSize < sizeof(madWorldTPLHdr_t))
	{
		return;
	}
	madWorldTPLHdr<big> hdr((madWorldTPLHdr_t *)data);
	if (memcmp(hdr.id, "\x30\xAF\x20\x00", 4))
	{ //not a valid texture bundle
		return;
	}
	rapi->Noesis_GetExtensionlessName(texName, texFiles[0]->name);
	if (hdr.numImages < 0 || hdr.imageTableOffset > dataSize || dataSize < hdr.imageTableOffset + hdr.numImages * sizeof(madWorldTPLRecord_t))
	{ //not a valid texture bundle
		return;
	}

	for (uint32_t i = 0; i < hdr.numImages; i++) {
		madWorldTPLRecord<big> record((madWorldTPLRecord_t*)(data + hdr.imageTableOffset) + i);
		if (!record.imageOffset || record.imageOffset >= dataSize)
			return;
		madWorldTPLImage<big> image((madWorldTPLImage_t *)(data + record.imageOffset));
		uint32_t height = image.height;
		uint32_t width = image.width;

		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);
		DBGLOG("%s: %d, format: %x, width: %d, height: %d\n", fname, i, image.format, image.width, image.height);

		BYTE *pix = (BYTE *)rapi->Noesis_PooledAlloc((width*height) * 4);

		if (record.paletteOffset) {
			madWorldTPLPalette<big> palette((madWorldTPLPalette_t *)(data + record.paletteOffset));
			tplDecodeImage(pix, data + image.offset, image.width, image.height, (tplFormats)image.format, (tplPaletteFormats)palette.format, data + palette.offset);
		}
		else {
			tplDecodeImage(pix, data + image.offset, image.width, image.height, (tplFormats)image.format);
		}
		noesisTex_t *nt = rapi->Noesis_TextureAlloc(fname, width, height, pix, NOESISTEX_RGBA32);
		nt->shouldFreeData = false;

		nt->globalIdx = -1;
		textures.Append(nt);
	}

	char fname[MAX_NOESIS_PATH];
	rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
	char nameStr[MAX_NOESIS_PATH];
	sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayoflatnormal", rapi->Noesis_GetOption("texpre"));
	strcat_s(fname, MAX_NOESIS_PATH, nameStr);
	noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, true);
	textures.Append(nt);
}
template <>
static void Model_Bayo_GetTextureBundle<MADWORLD>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, ".tpl");
	DBGLOG("texName: %s\n", texName);
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
}

template <bool big>
modelBone_t * Model_MadWorld_CreateBones(madWorldMDBHeader<big> &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT) {
	animBoneTT = NULL;
	if (hdr.numBones == 0 || hdr.bonePositionOffset == 0) {
		numBones = 0;
		return NULL;
	}

	int8_t *parentList = (int8_t *)(data + hdr.boneParentOffset);
	float  *posList = (float *)(data + hdr.bonePositionOffset);
	float  *relPosList = (float *)(data + hdr.boneRelativePositionOffset);
	int8_t *nameList = (int8_t *)(data + hdr.boneNameOffset);
	animBoneTT = (short int*)(rapi->Noesis_PooledAlloc(sizeof(short int) * 256));
	for (int i = 0; i < 256; i++) {
		animBoneTT[i] = -1;
	}
	numBones = hdr.numBones;
	DBGLOG("Found %d bones\n", numBones);
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones + 1);
	for (int i = 0; i < numBones; i++)
	{
		modelBone_t *bone = bones + i;
		float *ppos = posList + i * 3;
		int8_t parent = parentList[i];
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
		sprintf_s(bone->name, 30, "bone%03i", nameList[i]);
		animBoneTT[nameList[i]] = i;
		bone->mat = g_identityMatrix;
		float pos[3];
		memcpy(pos, ppos, sizeof(pos));
		if (big) {
			LITTLE_BIG_SWAP(pos[0]);
			LITTLE_BIG_SWAP(pos[1]);
			LITTLE_BIG_SWAP(pos[2]);
		}
		g_mfn->Math_VecCopy(pos, bone->mat.o);
		bone->userIndex = 5;
	}
	bones[numBones].index = numBones;
	bones[numBones].eData.parent = NULL;
	sprintf_s(bones[numBones].name, 30, "bone-1");
	bones[numBones].mat = g_identityMatrix;
	bones[numBones].userIndex = 5;

	DBGALOG("-------------------------------\n");
	for (int bi = 0; bi < numBones; bi++) {
		DBGALOG("bone %d (%d)\n", bi, bones[bi].index);
		DBGALOG("parent %d\n", bones[bi].eData.parent ? bones[bi].eData.parent->index : -1);
		DBGALOG("\ttranslate: %f, %f, %f\n", bones[bi].mat.o[0], bones[bi].mat.o[1], bones[bi].mat.o[2]);
		DBGALOG("\trelative_c: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));
		float relPos[3];
		memcpy(relPos, relPosList + 3 * bi, sizeof(relPos));
		if (big) {
			LITTLE_BIG_SWAP(relPos[0]);
			LITTLE_BIG_SWAP(relPos[1]);
			LITTLE_BIG_SWAP(relPos[2]);
		}
		DBGALOG("\trelative_g: %f, %f, %f\n", relPos[0], relPos[1], relPos[2]);
	}
	return bones;
}

template <bool big>
void Model_MadWorld_LoadMaterials(madWorldMDBHeader<big> &hdr, CArrayList<noesisTex_t *> &textures, CArrayList<noesisMaterial_t *> &matList, BYTE *data, noeRAPI_t *rapi) {
	char *inFile = rapi->Noesis_GetInputName();
	int8_t *pMaterials = (int8_t*)data + hdr.materialsOffset;
	for (int i = 0; i < (int)hdr.numMaterials; i++) {
		int8_t *pMaterial = pMaterials + i * 0x10;
		char matName[128];
		sprintf_s(matName, 128, "bayomat%i", i);
		DBGLOG("Material name: %s\n", matName);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		nmat->name = rapi->Noesis_PooledString(matName);
		nmat->noDefaultBlend = false; //can't find a way to determine how blending mode should be selected
		nmat->noLighting = true; //the engine didn't support dynamic lighting
		nmat->flags |= NMATFLAG_TWOSIDED;
		nmat->texIdx = *pMaterial;
		nmat->normalTexIdx = textures.Num() - 1;
		matList.Append(nmat);
	}
}

template <bool big>
int Model_MadWorld_NumMeshes(madWorldMDBHeader<big> &hdr, BYTE *data) {
	// lets not trust the header...
	//if (hdr.flags & 0x200)
	//	return hdr.numMeshes;
	if (!hdr.meshesOffset)
		return 0;
	uint32_t *pMesh = (uint32_t *)(data + hdr.meshesOffset);
	int count = 1;
	//DBGLOG("%x\n", hdr.meshesOffset);
	while (*pMesh) {
		uint32_t off = *pMesh;
		if (big)
			LITTLE_BIG_SWAP(off);
		//DBGLOG("%x\n", off);
		count++;
		pMesh = (uint32_t*)((BYTE*)pMesh + off);
	}
	return count;
}

template <bool big>
BYTE* Model_MadWorld_MeshIndexBuffer(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE* pMesh, BYTE *data, size_t dataSize) {
	uint32_t indexBufferOffset = 0;
	if (mesh.indexBuffersSize) {
		if (mesh.nextMeshOffset)
			indexBufferOffset = (pMesh - data) + mesh.nextMeshOffset - mesh.indexBuffersSize;
		else
			indexBufferOffset = dataSize - mesh.indexBuffersSize;
	}
	else {
		indexBufferOffset = (pMesh - data) + sizeof(madWorldMDBHeader_t);
		if (hdr.flags & 0x200)
			indexBufferOffset += 0x40;
		else
			indexBufferOffset += 0x20;
		if (indexBufferOffset)
			indexBufferOffset += 0x20 - indexBufferOffset % 0x20;
	}
	return data + indexBufferOffset;
}

template <bool big>
uint8_t Model_MadWorld_VertexSize(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh) {
	uint8_t vertexSize = 0;
	vertexSize += 3 * sizeof(float); //position
	if (hdr.numBonePalette)
		vertexSize += 8;
	if (hdr.numNormals && !(mesh.flags & 0x4))
		vertexSize += 3 * sizeof(float); //normal
	if (hdr.numColors && mesh.flags & 0x1)
		vertexSize += 4; //color
	if (hdr.numUVs && !(mesh.flags & 0x8))
		vertexSize += 2 * sizeof(float); //uv
	return vertexSize;
}

template <bool big>
void Model_MadWorld_NumTriangleIndices(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE* pMesh, BYTE *data, size_t dataSize, uint32_t &numVertexes, uint32_t &numTriangles) {
	BYTE* pIndexBuffers = Model_MadWorld_MeshIndexBuffer<big>(hdr, mesh, pMesh, data, dataSize);
	numVertexes = 0;
	numTriangles = 0;
	uint32_t numIndexBuffers = (mesh.numIndexBuffers ? mesh.numIndexBuffers : 1);
	for (uint32_t i = 0; i < numIndexBuffers; i++) {
		uint8_t type = *(uint8_t*)pIndexBuffers;
		pIndexBuffers++;
		uint16_t numIndexes = *(uint16_t*)pIndexBuffers;
		if (big)
			LITTLE_BIG_SWAP(numIndexes);
		pIndexBuffers += 2;
		numVertexes += numIndexes;
		if (type == 0x98 || type == 0xa0) //triangle strip
			numTriangles += numIndexes - 2;
		else if (type == 0x90)
			numTriangles += numIndexes / 3;
		else {
			DBGLOG("Unknown vertex buffer type: %02x\n", type);
			return;
		}
		uint8_t indexSize = 0;
		if (hdr.strangeFlags & 0x100)
			indexSize += 1;
		//if (hdr.numVertexPos)
		indexSize += 2;
		if (hdr.numNormals && !(mesh.flags & 0x4))
			indexSize += 2;
		if (hdr.numColors && mesh.flags & 0x1)
			indexSize += 2;
		if (hdr.numUVs && !(mesh.flags & 0x8))
			indexSize += 2;
		pIndexBuffers += indexSize * numIndexes;
	}
}

template <bool big>
inline void
Model_MadWorld_DecodeIndexes(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pIndex, uint16_t &positionIndex, uint16_t &normalIndex, uint16_t &colorIndex, uint16_t &UVIndex) {
	if (hdr.strangeFlags & 0x100)
		pIndex += 1;
	//if (hdr.numVertexPos)
	positionIndex = *(uint16_t *)pIndex;
	if (big)
		LITTLE_BIG_SWAP(positionIndex);
	pIndex += 2;
	//if (hdr.numNormals)
	if (hdr.numNormals && !(mesh.flags & 0x4)) {
		normalIndex = *(uint16_t *)pIndex;
		if (big)
			LITTLE_BIG_SWAP(normalIndex);
		pIndex += 2;
	}
	if (hdr.numColors && mesh.flags & 0x1) {
		colorIndex = *(uint16_t *)pIndex;
		if (big)
			LITTLE_BIG_SWAP(colorIndex);
		pIndex += 2;
	}
	if (hdr.numUVs && !(mesh.flags & 0x8)) {
		UVIndex = *(uint16_t *)pIndex;
		if (big)
			LITTLE_BIG_SWAP(UVIndex);
		pIndex += 2;
	}
}

template <bool big>
inline void
Model_MadWorld_DecodeVertexPosition(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pPos, BYTE *pPositions, uint16_t positionIndex, modelMatrix_t * pretransform) {
	if (hdr.vertexPosDivisorBit == -1) { //float positions
		float *pPosit = (float *)(pPositions + 0x10 * positionIndex);
		for (int i = 0; i < 3; i++) {
			((float *)pPos)[i] = pPosit[i];
			LITTLE_BIG_SWAP((((float *)pPos)[i]));
		}
	}
	else {
		int16_t *pPosit = (int16_t *)(pPositions + 0x8 * positionIndex);
		for (int i = 0; i < 3; i++) {
			int16_t p = pPosit[i];
			if (big)
				LITTLE_BIG_SWAP(p);
			((float *)pPos)[i] = p / (float)(1 << hdr.vertexPosDivisorBit);
		}
	}
	if (pretransform) {
		float tmp[3];
		g_mfn->Math_TransformPointByMatrixNoTrans(pretransform, (float *)pPos, tmp);
		g_mfn->Math_VecCopy(tmp, (float *)pPos);
	}
	pPos += 3 * sizeof(float);
}

template <bool big>
inline void
Model_MadWorld_DecodeVextexBoneWeights(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE* &pBoneWeights, BYTE* pPositions, BYTE* pBonePalette, uint16_t positionIndex) {
	int16_t bonePaletteIndex;
	if (hdr.vertexPosDivisorBit == -1) { //float positions
		bonePaletteIndex = *(uint16_t *)(pPositions + 0x10 * positionIndex + 3 * sizeof(float));
	}
	else {
		bonePaletteIndex = *(uint16_t *)(pPositions + 0x8 * positionIndex + 3 * sizeof(int16_t));
	}
	if (big)
		LITTLE_BIG_SWAP(bonePaletteIndex);
	//DBGLOG("bonePaletteIndex: %d\n", bonePaletteIndex);
	int8_t* pBonePaletteEntry = (int8_t*)(pBonePalette + 0x8 * bonePaletteIndex);
	for (int i = 0; i < 4; i++) {
		if (pBonePaletteEntry[2 * i] != -1)
			pBoneWeights[i] = pBonePaletteEntry[2 * i];
		else
			pBoneWeights[i] = 0;
		if (pBonePaletteEntry[2 * i + 1] != -1)
			pBoneWeights[i + 4] = pBonePaletteEntry[2 * i + 1];
		else
			pBoneWeights[i + 4] = 0;
	}
	pBoneWeights += 8;
}

template <bool big>
inline void
Model_MadWorld_DecodeVertexNormal(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pNor, BYTE *pNormals, uint16_t normalIndex, modelMatrix_t * pretransform) {
	int8_t *pNorm = (int8_t*)(pNormals + 3 * normalIndex);
	for (int i = 0; i < 3; i++) {
		((float *)pNor)[i] = pNorm[i] / 64.0f;
	}
	if (pretransform) {
		float tmp[3];
		g_mfn->Math_TransformPointByMatrixNoTrans(pretransform, (float *)pNor, tmp);
		g_mfn->Math_VecCopy(tmp, (float *)pNor);
	}
	pNor += 3 * sizeof(float);
}

template <bool big>
inline void
Model_MadWorld_DecodeVertexColor(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pCol, BYTE *pColors, uint16_t colorIndex) {
	uint8_t *pColo = pColors + 4 * colorIndex;
	for (int i = 0; i < 4; i++) {
		pCol[i] = pColo[i];
	}
	pCol += 4;
}

template <bool big>
inline void
Model_MadWorld_DecodeVertexUV(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pUV, BYTE *pUVs, uint16_t UVIndex) {
	int16_t *puv = (int16_t*)(pUVs + 2 * UVIndex * sizeof(int16_t));
	for (int i = 0; i < 2; i++) {
		int16_t p = puv[i];
		if (big)
			LITTLE_BIG_SWAP(p);
		((float*)pUV)[i] = p / (float)(1 << hdr.UVsDivisorBit);
	}
	pUV += 2 * sizeof(float);
}


template <bool big>
void Model_MadWorld_DecodeVertex(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * &pVertex, BYTE * &pIndex,
		BYTE *pPositions, BYTE* pNormals, BYTE* pColors, BYTE* pUVs, BYTE* pBonePalette, modelMatrix_t * pretransform) {
	uint16_t positionIndex = 0;
	uint16_t normalIndex = 0;
	uint16_t colorIndex = 0;
	uint16_t UVIndex = 0;
	Model_MadWorld_DecodeIndexes(hdr, mesh, pIndex, positionIndex, normalIndex, colorIndex, UVIndex);
	//DBGLOG("positionIndex: %d, normalIndex: %d, colorIndex: %d, UVIndex: %d\n", positionIndex, normalIndex, colorIndex, UVIndex);
	Model_MadWorld_DecodeVertexPosition(hdr, mesh, pVertex, pPositions, positionIndex, pretransform);
	if (hdr.numBonePalette)
		Model_MadWorld_DecodeVextexBoneWeights(hdr, mesh, pVertex, pPositions, pBonePalette, positionIndex);
	if (hdr.numNormals && !(mesh.flags &0x4))
		Model_MadWorld_DecodeVertexNormal(hdr, mesh, pVertex, pNormals, normalIndex, pretransform);
	if (hdr.numColors && mesh.flags & 0x1)
		Model_MadWorld_DecodeVertexColor(hdr, mesh, pVertex, pColors, colorIndex);
	if (hdr.numUVs && !(mesh.flags & 0x8))
		Model_MadWorld_DecodeVertexUV(hdr, mesh, pVertex, pUVs, UVIndex);
}



template <bool big>
int Model_MadWorld_DecodeTriangles(madWorldMDBHeader<big> &hdr, madWorldMDBMesh<big> &mesh, BYTE * pVertexBuffer, uint32_t * pIndexBuffer, uint8_t vertexSize, BYTE* pMesh, BYTE *data, size_t dataSize, modelMatrix_t * pretransform) {
	BYTE* pIndexBuffers = Model_MadWorld_MeshIndexBuffer<big>(hdr, mesh, pMesh, data, dataSize);
	int16_t vertexPosDivisorBit = hdr.vertexPosDivisorBit;
	int16_t UVsDivisorBit = hdr.UVsDivisorBit;
	uint32_t numVertexes = 0;
	uint32_t numTriangles = 0;
	uint32_t numIndexBuffers = (mesh.numIndexBuffers ? mesh.numIndexBuffers : 1);
	BYTE *pPositions = data + hdr.vertexPosOffset;
	BYTE *pNormals = data + hdr.normalsOffset;
	BYTE *pColors = data + hdr.colorsOffset;
	BYTE *pUVs = data + hdr.UVsOffset;
	BYTE *pBonePalette = data + hdr.bonePaletteOffset;
	for (uint32_t i = 0; i < numIndexBuffers; i++) {
		uint8_t type = *(uint8_t*)pIndexBuffers;
		pIndexBuffers++;
		uint16_t numIndexes = *(uint16_t*)pIndexBuffers;
		if (big)
			LITTLE_BIG_SWAP(numIndexes);
		pIndexBuffers += 2;
		if (type == 0x98 || type == 0xa0) {
			Model_MadWorld_DecodeVertex(hdr, mesh, pVertexBuffer, pIndexBuffers,
				pPositions, pNormals, pColors, pUVs, pBonePalette, pretransform);
			numVertexes++;
			Model_MadWorld_DecodeVertex(hdr, mesh, pVertexBuffer, pIndexBuffers,
				pPositions, pNormals, pColors, pUVs, pBonePalette, pretransform);
			numVertexes++;
			for (uint16_t j = 2; j < numIndexes; j++) {
				Model_MadWorld_DecodeVertex(hdr, mesh, pVertexBuffer, pIndexBuffers,
					pPositions, pNormals, pColors, pUVs, pBonePalette, pretransform);
				if (j & 1) {
					*(pIndexBuffer++) = numVertexes - 1;
					*(pIndexBuffer++) = numVertexes - 2;
				}
				else {
					*(pIndexBuffer++) = numVertexes - 2;
					*(pIndexBuffer++) = numVertexes - 1;
				}
				*(pIndexBuffer++) = numVertexes++;
				numTriangles++;
			}
		}
		else if (type == 0x90) {
			for (uint16_t j = 0; j < numIndexes/3; j++) {
				for (uint8_t k = 0; k < 3; k++) {
					Model_MadWorld_DecodeVertex(hdr, mesh, pVertexBuffer, pIndexBuffers,
						pPositions, pNormals, pColors, pUVs, pBonePalette, pretransform);
					*(pIndexBuffer++) = numVertexes++;
				}
				numTriangles++;
			}
		}
		else {
			return -1;
		}
	}
	return 0;
}

template <>
static void Model_Bayo_LoadModel<true, MADWORLD>(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset)
{
	DBGLOG("Loading %s\n", df.name);
	const bool big = true;
	const game_e game = MADWORLD;
	CArrayList<noesisMaterial_t *> matList;
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<noesisTex_t *> textures;
	CArrayList<bayoDatFile_t *> motfiles;
	CArrayList<noesisAnim_t *> animList;
	CArrayList<bayoDatFile_t *> expfile;

	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(madWorldMDBHeader_t))
	{
		return;
	}
	madWorldMDBHeader<big> hdr((madWorldMDBHeader_t*)data);

	if (givenTextures.Num() == 0) {
		Model_Bayo_GetTextureBundle<game>(texFiles, dfiles, df, rapi);
		if (texFiles.Num() > 0)
		{
			for (int i = 0; i < texFiles.Num(); i++) {
				DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
			}
			Model_Bayo_LoadTextures<big, game>(textures, texFiles, rapi);
		}
	}
	else {
		for (int i = 0; i < givenTextures.Num(); i++) {
			textures.Append(givenTextures[i]);
		}
	}

	Model_MadWorld_LoadMaterials<big>(hdr, textures, matList, data, rapi);
	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetOption(RPGOPT_BIGENDIAN, false); //data endianness will bea decoded by the plugin.
	rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_MadWorld_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

	Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
	if (bones) {
		Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT, data + hdr.boneRelativePositionOffset);
		Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT, data + hdr.boneRelativePositionOffset);
	}

	int numMeshes = Model_MadWorld_NumMeshes(hdr, data);
	DBGLOG("Found %d meshes\n", numMeshes);
	madWorldMDBMesh_t * pMesh = (madWorldMDBMesh_t *)(data + hdr.meshesOffset);
	for (int i = 0; i < numMeshes; i++) {
		char batch_name[256];
		madWorldMDBMesh<big> mesh(pMesh);
		DBGLOG("\t%d - %s:\n", i, (BYTE*)pMesh + sizeof(madWorldMDBMesh_t));
		sprintf_s(batch_name, 256, "%02d(%s)", i, (BYTE*)pMesh + sizeof(madWorldMDBMesh_t));

		uint32_t numVertexes;
		uint32_t numTriangles;
		uint8_t  vertexSize;
		Model_MadWorld_NumTriangleIndices<big>(hdr, mesh, (BYTE*)pMesh, data, dataSize, numVertexes, numTriangles); //TriStrips will be converted to triangles
		vertexSize = Model_MadWorld_VertexSize<big>(hdr, mesh);
		DBGLOG("\t\t%u vertices, %u triangles, vertexSize: %u\n", numVertexes, numTriangles, vertexSize);
		BYTE *pVertexBuffer = (BYTE*)(rapi->Noesis_PooledAlloc(numVertexes*vertexSize));
		uint32_t *pIndexBuffer  = (uint32_t *)(rapi->Noesis_PooledAlloc(numTriangles*3*sizeof(int)));
		if (Model_MadWorld_DecodeTriangles<big>(hdr, mesh, pVertexBuffer, pIndexBuffer, vertexSize, (BYTE*)pMesh, data, dataSize, pretransform)) {
			continue; //Wrong IndexBuffer data found;
		}
		DBGLOG("\t\tSetting buffers\n");
		rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
		char *matName;
		if (hdr.numMaterials && mesh.materialID < matList.Num())
			matName = matList[mesh.materialID]->name;
		else
			matName = NULL;
		rapi->rpgSetMaterial(matName);
		//bind positions
		int offset = 0;
		rapi->rpgBindPositionBuffer(pVertexBuffer + offset, RPGEODATA_FLOAT, vertexSize);
		offset += 3 * sizeof(float);
		if (hdr.numBonePalette) {
			rapi->rpgBindBoneIndexBuffer(pVertexBuffer + offset, RPGEODATA_BYTE, vertexSize, 4);
			offset += 4;
			rapi->rpgBindBoneWeightBuffer(pVertexBuffer + offset, RPGEODATA_BYTE, vertexSize, 4);
			offset += 4;
		}
		else {
			rapi->rpgBindBoneIndexBuffer(NULL, RPGEODATA_BYTE, 0, 0);
			rapi->rpgBindBoneWeightBuffer(NULL, RPGEODATA_BYTE, 0, 0);
		}
		//bind normals
		if (hdr.numNormals && !(mesh.flags & 0x4)) {
			rapi->rpgBindNormalBuffer(pVertexBuffer + offset, RPGEODATA_FLOAT, vertexSize);
			offset += 3 * sizeof(float);
		}
		if (hdr.numColors && mesh.flags & 0x1) {
			// Don't bind color as they mess up the rendering.
			//rapi->rpgBindColorBuffer(pVertexBuffer + offset, RPGEODATA_BYTE, vertexSize, 4);
			offset += 4;
		}
		else {
			rapi->rpgBindColorBuffer(NULL, RPGEODATA_BYTE, 0, 0);
		}
		if (hdr.numUVs && !(mesh.flags & 0x8)) {
			rapi->rpgBindUV1Buffer(pVertexBuffer + offset, RPGEODATA_FLOAT, vertexSize);
			offset += 2 * sizeof(float);
		}
		else {
			rapi->rpgBindUV1Buffer(NULL, RPGEODATA_BYTE, 0);
		}
		rapi->rpgCommitTriangles(pIndexBuffer, RPGEODATA_UINT, numTriangles*3, RPGEO_TRIANGLE, true);
		pMesh = (madWorldMDBMesh_t *)((BYTE*)pMesh + mesh.nextMeshOffset);
	}

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(matList, textures);
	rapi->rpgSetExData_Materials(md);
	if (bones) {
		rapi->rpgSetExData_Bones(bones, numBones + 1);
	}
	int anims_num = animList.Num();
	noesisAnim_t *anims = rapi->Noesis_AnimFromAnimsList(animList, anims_num);
	//for(int i = 0; i < anims_num; i++) {
	//	DBGLOG("anim: %s, size: %d, flag: %d\n", animList[i]->filename, animList[i]->dataLen, animList[i]->flags & NANIMFLAG_FILENAMETOSEQ);
	//	DBGLOG("seq: %p, size: %d\n", (anims+i)->aseq, (anims+i)->dataLen );
	//}
	rapi->rpgSetExData_AnimsNum(anims, 1);
	DBGLOG("Found %d anims\n", anims_num);
	noesisModel_t *mdl = rapi->rpgConstructModel();
	if (mdl) {
		models.Append(mdl);
	}
	rapi->rpgDestroyContext(pgctx);
	matList.Clear();
	texFiles.Clear();
	textures.Clear();
	motfiles.Clear();
	animList.Clear();
	expfile.Clear();
}

template <>
static void Model_Bayo_LoadScenery<true, MADWORLD>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	const bool big = true;
	const game_t game = MADWORLD;
	DBGLOG("Loading %s\n", df.name);
	if (df.dataSize < sizeof(madWorldSCRHdr_t)) {
		DBGLOG("Empty SCR file\n");
		return;
	}
	madWorldSCRHdr<big> hdr((madWorldSCRHdr_t *)df.data);
	if (memcmp(hdr.id, "SCR\0", 4))
	{ //invalid header
		DBGLOG("Invalid SCR file\n");
		return;
	}

	bayoDatFile_t textureFile;
	textureFile.name = rapi->Noesis_PooledString("dummy.wtb");
	textureFile.data = df.data + hdr.texturesOffset;
	textureFile.dataSize = df.dataSize - hdr.texturesOffset;
	CArrayList<bayoDatFile_t> dfiles;
	CArrayList<bayoDatFile_t *> texfiles;
	texfiles.Append(&textureFile);
	CArrayList<noesisTex_t *> textures;
	Model_Bayo_LoadTextures<big, game>(textures, texfiles, rapi);
	int sharedtexturesoffset = -1;
	sharedtexturesoffset = textures.Num();
	DBGLOG("found %d models in %s\n", hdr.numModels, df.name);
	for (int i = 0; i < hdr.numModels; i++) {
		bayoDatFile_t modelFile;
		int dscrOffset = sizeof(madWorldSCRHdr_t) + i * sizeof(madWorldSCRModelDscr_t);
		DBGLOG("offset: %x\n", dscrOffset);
		madWorldSCRModelDscr<big> modelDscr((madWorldSCRModelDscr_t *)(df.data + dscrOffset));
		char modelName[0x31];
		char fileName[0x35];
		memset(modelName, 0, 21);
		for (int j = 0; j < 0x30; j++) {
			modelName[j] = modelDscr.name[j];
		}
		modelName[0x30] = 0;
		snprintf(fileName, 21, "%s.wmb", modelName);
		DBGLOG("%d - %d: model name: %s, ", i, models.Num(), fileName);
		modelFile.name = rapi->Noesis_PooledString(fileName);
		modelFile.data = df.data + dscrOffset + modelDscr.offset;
		int j = i;
		size_t size = 0;
		while (size == 0) {
			if (j < (hdr.numModels - 1)) {
				int nextDscrOffset = sizeof(madWorldSCRHdr_t) + (j + 1) * sizeof(madWorldSCRModelDscr_t);
				madWorldSCRModelDscr<big> nextModelDscr((madWorldSCRModelDscr_t *)(df.data + nextDscrOffset));
				size = (nextDscrOffset + nextModelDscr.offset) - (dscrOffset + modelDscr.offset);
			}
			else {
				size = hdr.texturesOffset - (dscrOffset + modelDscr.offset);
			}
			j++;
		}
		modelFile.dataSize = size;
		DBGLOG("start: %d, size: %d\n", dscrOffset + modelDscr.offset, modelFile.dataSize);
		modelMatrix_t m;
		Model_Bayo_CreatePreTransformMatrix(modelDscr.transform, m);
		Model_Bayo_LoadModel<big, game>(dfiles, modelFile, rapi, models, textures, &m, sharedtexturesoffset);
	}
	rapi->SetPreviewOption("drawAllModels", "1");
}