#pragma once

//Aalways big endian
typedef struct bayo2BXMHdr_s
{
	BYTE				id[4];
	UINT32				unknown;
	UINT16				numNodes;
	UINT16				numData;
	UINT32				sizeData;
} bayo2BXMHdr_t;
template<bool big>
struct bayo2BXMHdr : bayo2BXMHdr_s
{
	bayo2BXMHdr(bayo2BXMHdr_t * ptr) : bayo2BXMHdr_s(*ptr) {
		LITTLE_BIG_SWAP(unknown);
		LITTLE_BIG_SWAP(numNodes);
		LITTLE_BIG_SWAP(numData);
		LITTLE_BIG_SWAP(sizeData);
	}
};
typedef struct bayo2BXMOffsets_s
{
	INT16				ofsName;
	INT16				ofsData;
} bayo2BXMOffsets_t;
template<bool big>
struct bayo2BXMOffsets : bayo2BXMOffsets_s
{
	bayo2BXMOffsets(bayo2BXMOffsets_t *ptr) : bayo2BXMOffsets_s(*ptr) {
		LITTLE_BIG_SWAP(ofsName);
		LITTLE_BIG_SWAP(ofsData);
	}
};
typedef struct bayo2BXMNode_s {
	UINT16				numChildren;
	UINT16				indexFisrtChild;
	UINT16				numAttributes;
	UINT16				indexData;
} bayo2BXMNode_t;
template<bool big>
struct bayo2BXMNode : bayo2BXMNode_s
{
	bayo2BXMNode(bayo2BXMNode_t *ptr) : bayo2BXMNode_s(*ptr) {
		LITTLE_BIG_SWAP(numChildren);
		LITTLE_BIG_SWAP(indexFisrtChild);
		LITTLE_BIG_SWAP(numAttributes);
		LITTLE_BIG_SWAP(indexData);
	}
};
typedef struct bayo2SCRHdr_s
{
	BYTE				id[4];
	unsigned short		unknownA;
	unsigned short		numModels;
	unsigned int		ofsOffsetsModels;
} bayo2SCRHdr_t;
template <bool big>
struct bayo2SCRHdr : public bayo2SCRHdr_s {
	bayo2SCRHdr(bayo2SCRHdr_t * ptr) : bayo2SCRHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(numModels);
			LITTLE_BIG_SWAP(ofsOffsetsModels);
		}
	}
};
typedef struct bayoSCRModelDscr_s
{
	BYTE				name[16];
	unsigned int		offset;
	float				transform[9];
	short				unknownA[42];
}bayoSCRModelDscr_t;
template <bool big>
struct bayoSCRModelDscr : public bayoSCRModelDscr_s {
	bayoSCRModelDscr(bayoSCRModelDscr_t * ptr) : bayoSCRModelDscr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offset);
			for (int i = 0; i < 9; i++) {
				LITTLE_BIG_SWAP(transform[i]);
			}
			for (int i = 0; i < 42; i++) {
				LITTLE_BIG_SWAP(unknownA[i]);
			}
		}
	}
};
typedef struct bayo2SCRModelDscr_s
{
	unsigned int		offset;
	BYTE				name[64];
	float				transform[9];
	short				unknownA[18]; //Speculations
}bayo2SCRModelDscr_t;
template <bool big>
struct bayo2SCRModelDscr : public bayo2SCRModelDscr_s {
	bayo2SCRModelDscr(bayo2SCRModelDscr_t * ptr) : bayo2SCRModelDscr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(offset);
			for (int i = 0; i < 9; i++) {
				LITTLE_BIG_SWAP(transform[i]);
			}
			for (int i = 0; i < 18; i++) {
				LITTLE_BIG_SWAP(unknownA[i]);
			}
		}
	}
};

template <>
static void Model_Bayo_GetTextureBundle<BAYONETTA2>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	char texName2[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, ".wta");
	rapi->Noesis_GetExtensionlessName(texName2, df.name);
	strcat_s(texName2, MAX_NOESIS_PATH, ".wtp");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName2))
		{
			texFiles.Append(&dft);
		}
	}
	if (texFiles.Num() < 2) {
		texFiles.Clear();
	}
}

static void Model_Bayo2_GetSCRTextureBundle(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	char texName2[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, "scr.wta");
	rapi->Noesis_GetExtensionlessName(texName2, df.name);
	strcat_s(texName2, MAX_NOESIS_PATH, "scr.wtp");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName2))
		{
			texFiles.Append(&dft);
		}
	}
	if (texFiles.Num() < 2) {
		texFiles.Clear();
	}
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, "shared.wta");
	rapi->Noesis_GetExtensionlessName(texName2, df.name);
	strcat_s(texName2, MAX_NOESIS_PATH, "shared.wtp");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName2))
		{
			texFiles.Append(&dft);
		}
	}
	if (texFiles.Num() == 3 || texFiles.Num() == 1) {
		texFiles.Pop();
	}
}

template <>
static void Model_Bayo_LoadTextures<false, BAYONETTA2>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	const bool big = false;
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
	{ //not a valid texture bundle
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}
	DBGLOG("found valid texture header file, containing %d textures, headers offset: %x\n", hdr.numTex, hdr.texInfoOffset);
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

		noesisTex_t	*nt = rapi->Noesis_LoadTexByHandler(data2 + tofs[i], tsizes[i], ".bntx");
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
static void Model_Bayo_LoadTextures<true, BAYONETTA2>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
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
	bayoWTAHdr<true> hdr((bayoWTAHdr_t *)data);
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
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *mofs = (int *)(data + hdr.ofsMipmapOfs);
	for (int i = 0; i < hdr.numTex; i++)
	{
		int globalIdx;
		char fname[8192];
		char fnamegtx[8192];
		char fnamedds[8192];
		char cmd[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%s%s%03i", rapi->Noesis_GetOption("texpre"), texName, i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);
		sprintf_s(fnamegtx, MAX_NOESIS_PATH, "%s.gtx", fname);
		sprintf_s(fnamedds, MAX_NOESIS_PATH, "%s.dds", fname);

		GX2Hdr<big> texHdr((GX2Hdr_t *)(data + hdr.texInfoOffset + i * 0xc0));
		//DBGLOG("%d: dim: %d, width %d, height %d, depth %d, numMimap: %d, format: %x\n", i, texHdr.dimension, texHdr.width, texHdr.height, texHdr.depth, texHdr.numMipmaps, texHdr.format);
		//DBGLOG("\tusage: %x, length: %d, mipmapDataLength: %d, tileMode: %x\n", texHdr.usage, texHdr.dataLength, texHdr.mipmapsDataLength, texHdr.tileMode);
		//DBGLOG("\tswizzle: %x, alignment %d, pitch %d, first mipmap: %d\n", texHdr.swizzleValue, texHdr.alignment, texHdr.pitch, texHdr.firstMipmap);
		//DBGLOG("\tcomponents: %d, %d, %d, %d\n", texHdr.component[0], texHdr.component[1], texHdr.component[2], texHdr.component[3]);

		if (hdr.texIdxOffset)
		{
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
			LITTLE_BIG_SWAP(globalIdx);
		}
		DBGLOG("%s: 0x%0x\n", fname, globalIdx);
		//GX2_SURFACE_FORMAT_T_BC1_UNORM = 0x31
		//GX2_SURFACE_FORMAT_T_BC3_UNORM = 0x33
		FILE  * fgtx = fopen(fnamegtx, "wb");
		// gtx header (http://mk8.tockdom.com/wiki/GTX%5CGSH_(File_Format))
		fwrite("\x47\x66\x78\x32\x00\x00\x00\x20\x00\x00\x00\x07\x00\x00\x00\x01\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x20, fgtx);
		// block header (GX2 surface)
		fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x0B\x00\x00\x00\x9C\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x20, fgtx);
		// write GX2 surface
		fwrite(data + hdr.texInfoOffset + i * 0xc0, 1, 0x9c, fgtx);
		// block header (data)
		fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x0C", 1, 0x14, fgtx);
		DWORD size = texHdr.dataLength;
		if (big) LITTLE_BIG_SWAP(size);
		fwrite(&size, 4, 1, fgtx);
		fwrite("\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x8, fgtx);
		// write pixel data
		int tof = tofs[i];
		LITTLE_BIG_SWAP(tof);
		fwrite(data2 + tof, 1, texHdr.dataLength, fgtx);
		if (texHdr.numMipmaps > 1) {
			// block header (mipmap data)
			fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x0D", 1, 0x14, fgtx);
			size = texHdr.mipmapsDataLength;
			if (big) LITTLE_BIG_SWAP(size);
			fwrite(&size, 4, 1, fgtx);
			fwrite("\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x8, fgtx);
			// write mipmap data
			int mof = mofs[i];
			LITTLE_BIG_SWAP(mof);
			fwrite(data2 + mof, 1, texHdr.mipmapsDataLength, fgtx);
		}
		// write ending header
		fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x20, fgtx);

		fclose(fgtx);
		sprintf_s(cmd, 8192, "TexConv2.exe -i \"%s\" -o \"%s\"", fnamegtx, fnamedds);

		STARTUPINFOW si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		wchar_t wcmd[8192];
		mbstowcs(wcmd, cmd, strlen(cmd) + 1);

		if (CreateProcess(L"Texconv2.exe", wcmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		//system(cmd);
		noesisTex_t	*nt = rapi->Noesis_LoadExternalTex(fnamedds);
		if (nt) {
			nt->filename = rapi->Noesis_PooledString(fname);
			textures.Append(nt);
		}
		else {
			DBGLOG("Could not load texture %s using TexConv2.exe\n", fnamedds);
			sprintf_s(cmd, 8192, "gtx_extract_no5.exe \"%s\"", fnamegtx);
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));
			mbstowcs(wcmd, cmd, strlen(cmd) + 1);
			if (CreateProcess(L"gtx_extract_no5.exe", wcmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			nt = rapi->Noesis_LoadExternalTex(fnamedds);
			if (nt) {
				nt->filename = rapi->Noesis_PooledString(fname);
				textures.Append(nt);
			}
			else {
				DBGLOG("Could not load texture %s using gtx_extract_no5.exe\n", fnamedds);
				nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
				textures.Append(nt);
			}
		}
		remove(fnamedds);
		remove(fnamegtx);
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
static void Model_Bayo_CreateNormal<true, BAYONETTA2>(char *src, float *dst) {
	DWORD r;
	memcpy(&r, src, sizeof(r));
	LITTLE_BIG_SWAP(r);
	int xBits = 10;
	int yBits = 10;
	int zBits = 10;
	int x = ((r >> 0) & ((1 << xBits) - 1));
	int y = ((r >> xBits) & ((1 << yBits) - 1));
	int z = ((r >> (xBits + yBits)) & ((1 << zBits) - 1));
	dst[0] = (float)SignedBits(x, xBits) / (float)((1 << (xBits - 1)) - 1);
	dst[1] = (float)SignedBits(y, yBits) / (float)((1 << (yBits - 1)) - 1);
	dst[2] = (float)SignedBits(z, zBits) / (float)((1 << (zBits - 1)) - 1);
}

template <>
static void Model_Bayo_CreateNormal<false, BAYONETTA2>(char *src, float *dst) {
	DWORD r;
	memcpy(&r, src, sizeof(r));
	int xBits = 10;
	int yBits = 10;
	int zBits = 10;
	int x = ((r >> 0) & ((1 << xBits) - 1));
	int y = ((r >> xBits) & ((1 << yBits) - 1));
	int z = ((r >> (xBits + yBits)) & ((1 << zBits) - 1));
	dst[0] = (float)SignedBits(x, xBits) / (float)((1 << (xBits - 1)) - 1);
	dst[1] = (float)SignedBits(y, yBits) / (float)((1 << (yBits - 1)) - 1);
	dst[2] = (float)SignedBits(z, zBits) / (float)((1 << (zBits - 1)) - 1);
}

template <>
static void Model_Bayo_CreateTangents<true, BAYONETTA2>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
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
		for (int j = 0; j < 4; j++) {
			LITTLE_BIG_SWAP(dst[j]);
		}
	}
}

template <>
static void Model_Bayo_CreateTangents<false, BAYONETTA2>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m) {
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

template<bool big>
static void Model_Bayo2_LoadScenery(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
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
		Model_Bayo_LoadTextures<big, BAYONETTA2>(textures, texFiles, rapi);
	}
	char scrName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(scrName, df.name);
	Model_Bayo_LoadSharedTextures<big, BAYONETTA2>(textures, scrName, rapi);

	CArrayList<bayoDatFile_t> dfiles;

	unsigned int * ofsOffsetsModels = (unsigned int *)(df.data + hdr.ofsOffsetsModels);

	DBGLOG("found %d models in %s\n", hdr.numModels, df.name);
	for (int i = 0; i < hdr.numModels; i++) {
		bayoDatFile_t modelFile;
		int dscrOffset = ofsOffsetsModels[i];
		if (big) {
			LITTLE_BIG_SWAP(dscrOffset);
		}
		bayo2SCRModelDscr<big> modelDscr((bayo2SCRModelDscr_t *)(df.data + dscrOffset));
		char modelName[69];
		char fileName[69];
		memset(modelName, 0, 69);
		for (int j = 0; j < 64; j++) {
			modelName[j] = modelDscr.name[j];
		}
		snprintf(fileName, 69, "%s.wmb", modelName);
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
		Model_Bayo_LoadModel<big, BAYONETTA2>(dfiles, modelFile, rapi, models, textures, &m);
	}
	rapi->SetPreviewOption("drawAllModels", "1");
}

template <>
static void Model_Bayo_LoadScenery<true, BAYONETTA2>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	Model_Bayo2_LoadScenery<true>(olddfiles, df, rapi, models);
}
template <>
static void Model_Bayo_LoadScenery<false, BAYONETTA2>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	Model_Bayo2_LoadScenery<false>(olddfiles, df, rapi, models);
}