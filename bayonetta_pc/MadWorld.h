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
	uint16_t	ua;
	uint16_t	ub;
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
			LITTLE_BIG_SWAP(ua);
			LITTLE_BIG_SWAP(ub);
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
		nmat->noDefaultBlend = true;
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
	DBGLOG("%x\n", hdr.meshesOffset);
	while (*pMesh) {
		uint32_t off = *pMesh;
		if (big)
			LITTLE_BIG_SWAP(off);
		DBGLOG("%x\n", off);
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
		//if (hdr.numNormals)
		indexSize += 2;
		if (hdr.numColors && mesh.flags & 0x1)
			indexSize += 2;
		if (hdr.numUVs && !(mesh.flags & 0x8))
			indexSize += 2;
		pIndexBuffers += indexSize * numIndexes;
	}
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
	rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
	rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);

	int numMeshes = Model_MadWorld_NumMeshes(hdr, data);
	DBGLOG("Found %d meshes\n", numMeshes);
	madWorldMDBMesh_t * pMesh = (madWorldMDBMesh_t *)(data + hdr.meshesOffset);
	for (int i = 0; i < numMeshes; i++) {
		madWorldMDBMesh<big> mesh(pMesh);
		DBGLOG("\t%d - %s:\n", i, (BYTE*)pMesh + sizeof(madWorldMDBMesh_t));
		uint32_t numVertexes;
		uint32_t numTriangles;
		Model_MadWorld_NumTriangleIndices<big>(hdr, mesh, (BYTE*)pMesh, data, dataSize, numVertexes, numTriangles); //TriStrips will be converted to triangles
		DBGLOG("\t\t%u vertices, %u triangles\n", numVertexes, numTriangles);
		pMesh = (madWorldMDBMesh_t *)((BYTE*)pMesh + mesh.nextMeshOffset);
	}

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_MadWorld_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(matList, textures);
	rapi->rpgSetExData_Materials(md);
	if (bones) {
		rapi->rpgSetExData_Bones(bones, numBones + 1);
	}
	noesisModel_t *mdl = rapi->rpgConstructModel();
	if (mdl) {
		models.Append(mdl);
	}
	rapi->rpgDestroyContext(pgctx);
	matList.Clear();
	texFiles.Clear();
	textures.Clear();
}

template <>
static void Model_Bayo_LoadScenery<true, MADWORLD>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	return;
}