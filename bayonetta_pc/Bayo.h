#pragma once
typedef struct bayoV4F_s
{
	float x;
	float y;
	float z;
	float w;
} bayoV4F_t;
template <bool big>
struct bayoV4F : public bayoV4F_s {
	bayoV4F(bayoV4F_t * ptr) : bayoV4F_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(x);
			LITTLE_BIG_SWAP(y);
			LITTLE_BIG_SWAP(z);
			LITTLE_BIG_SWAP(w);
		}
	}
};
typedef struct bayoDat_s
{
	BYTE			id[4];
	int				numRes;
	int				ofsRes;
	int				ofsType;
	int				ofsNames;
	int				ofsSizes;
} bayoDat_t;

template <bool big>
struct bayoDat : public bayoDat_s {
	bayoDat(bayoDat_t * ptr) : bayoDat_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numRes);
			LITTLE_BIG_SWAP(ofsRes);
			LITTLE_BIG_SWAP(ofsType);
			LITTLE_BIG_SWAP(ofsNames);
			LITTLE_BIG_SWAP(ofsSizes);
		}
	}
};
typedef struct bayoDatFile_s
{
	char				*name;
	BYTE				*data;
	int					dataSize;
} bayoDatFile_t;
typedef struct bayoWTBHdr_s
{
	BYTE				id[4];
	int					unknown;
	int					numTex;
	int					ofsTexOfs;
	int					ofsTexSizes;
	int					ofsTexFlags;
	int					texIdxOffset;
	int					texInfoOffset;
} bayoWTBHdr_t;
template <bool big>
struct bayoWTBHdr : public bayoWTBHdr_s {
	bayoWTBHdr(bayoWTBHdr_t *ptr) : bayoWTBHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(unknown);
			LITTLE_BIG_SWAP(numTex);
			LITTLE_BIG_SWAP(ofsTexOfs);
			LITTLE_BIG_SWAP(ofsTexSizes);
			LITTLE_BIG_SWAP(ofsTexFlags);
			LITTLE_BIG_SWAP(texIdxOffset);
			LITTLE_BIG_SWAP(texInfoOffset);
		}
	}
};
typedef struct bayoWTAHdr_s
{
	BYTE				id[4];
	int					unknown;
	int					numTex;
	int					ofsTexOfs;
	int					ofsTexSizes;
	int					ofsTexFlags;
	int					texIdxOffset;
	int					texInfoOffset;
	int					ofsMipmapOfs;
} bayoWTAHdr_t;
template <bool big>
struct bayoWTAHdr : public bayoWTAHdr_s {
	bayoWTAHdr(bayoWTAHdr_t *ptr) : bayoWTAHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(unknown);
			LITTLE_BIG_SWAP(numTex);
			LITTLE_BIG_SWAP(ofsTexOfs);
			LITTLE_BIG_SWAP(ofsTexSizes);
			LITTLE_BIG_SWAP(ofsTexFlags);
			LITTLE_BIG_SWAP(texIdxOffset);
			LITTLE_BIG_SWAP(texInfoOffset);
			LITTLE_BIG_SWAP(ofsMipmapOfs);
		}
	}
};
// Texture is now DDS
typedef struct ddsPixelFormat_s
{
	int					size;
	int					flags;
	int					id;
	int					rgbBitCount;
	int					rBitMask;
	int					gBitMask;
	int					bBitMask;
	int					aBitMask;
} ddsPixelFormat_t;
typedef struct ddsTexHdr_s
{
	BYTE				id[4];
	int					hSize;
	int					flags;
	int					height;
	int					width;
	int					pitchOrLinearSize;
	int					depth;
	int					mipMapCount;
	int					reserved1[11];
	ddsPixelFormat_t	pixelFormat;
	int					caps;
	int					caps2;
	int					caps3;
	int					caps4;
	int					reserved2;
} ddsTexHdr_t;
typedef struct wtbTexHdr_s
{
	int					unknownA;
	int					unknownB;
	int					unknownC;
	int					unknownD;
	int					unknownE;
	short				unknownF;
	short				unknownG;
	short				unknownH;
	short				unknownI;
	short				unknownJ;
	short				unknownK;
	int					texFmt;
	WORD				heightBits;
	WORD				widthBits;
	int					unknownO;
	int					unknownP;
	int					unknownQ;
} wtbTexHdr_t;
typedef struct GX2Hdr_s {
	DWORD dimension;
	DWORD width;
	DWORD height;
	DWORD depth;
	DWORD numMipmaps;
	DWORD format;
	DWORD AAMode;
	DWORD usage;
	DWORD dataLength;
	DWORD dataPointer;
	DWORD mipmapsDataLength;
	DWORD mimapsPointer;
	DWORD tileMode;
	DWORD swizzleValue;
	DWORD alignment;
	DWORD pitch;
	DWORD mimapOffsets[13];
	DWORD firstMipmap;
	DWORD numMipmaps2;
	DWORD firstSlice;
	DWORD numSlices;
	BYTE component[4];
	DWORD textureRegisters[5];
} GX2Hdr_t;
template <bool big>
struct GX2Hdr : public GX2Hdr_s {
	GX2Hdr(GX2Hdr_t *ptr) : GX2Hdr_s(*ptr) {
		LITTLE_BIG_SWAP(dimension);
		LITTLE_BIG_SWAP(width);
		LITTLE_BIG_SWAP(height);
		LITTLE_BIG_SWAP(depth);
		LITTLE_BIG_SWAP(numMipmaps);
		LITTLE_BIG_SWAP(format);
		LITTLE_BIG_SWAP(AAMode);
		LITTLE_BIG_SWAP(usage);
		LITTLE_BIG_SWAP(dataLength);
		LITTLE_BIG_SWAP(dataPointer);
		LITTLE_BIG_SWAP(mipmapsDataLength);
		LITTLE_BIG_SWAP(mimapsPointer);
		LITTLE_BIG_SWAP(tileMode);
		LITTLE_BIG_SWAP(swizzleValue);
		LITTLE_BIG_SWAP(alignment);
		LITTLE_BIG_SWAP(pitch);
		for (int i = 0; i < 13; i++) LITTLE_BIG_SWAP(mimapOffsets);
		LITTLE_BIG_SWAP(firstMipmap);
		LITTLE_BIG_SWAP(numMipmaps2);
		LITTLE_BIG_SWAP(firstSlice);
		LITTLE_BIG_SWAP(numSlices);
		for (int i = 0; i < 5; i++) LITTLE_BIG_SWAP(textureRegisters[i]);
	}
};
typedef struct bayoSCRHdr_s
{
	BYTE				id[4];
	int					numModels;
	unsigned int		ofsTextures;
	BYTE				unknown[4];
} bayoSCRHdr_t;
template <bool big>
struct bayoSCRHdr : public bayoSCRHdr_s {
	bayoSCRHdr(bayoSCRHdr_t * ptr) : bayoSCRHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(numModels);
			LITTLE_BIG_SWAP(ofsTextures);
		}
	}
};
typedef struct bayoVector_s {
	float x;
	float y;
	float z;
	void swap(void) {
		LITTLE_BIG_SWAP(x);
		LITTLE_BIG_SWAP(y);
		LITTLE_BIG_SWAP(z);
	}
} bayoVector_t;

#define BAYO_VERTEX_FMT_PRESENT		0x40000000
#define BAYO_VERTEX_FMT_UNKNOWNA	0x20000000
#define BAYO_VERTEX_FMT_UNKNOWNB	0x10000000
#define BAYO_VERTEX_FMT_COMPRESSED	0x08000000
#define BAYO_VERTEX_FMT_POSITION2	0x00000020
#define BAYO_VERTEX_FMT_BONEINFOS	0x00000010
#define BAYO_VERTEX_FMT_NORMAL		0x00000008
#define BAYO_VERTEX_FMT_MAPPING		0x00000004
#define BAYO_VERTEX_FMT_COLOR		0x00000002
#define BAYO_VERTEX_FMT_TANGENTS	0x00000001

typedef struct bayoWMBHdr_s
{
	BYTE				id[4];				// 0
	int					unknownA;			// 4
	int					vertexFormat;			// 8
	int					numVerts;			// C
	BYTE				numMapping;			//10
	BYTE				unknownD;			//11
	WORD				unknownE;			//12
	int					ofsPositions;		//14
	int					ofsVerts;			//18
	int					ofsVertExData;		//1C
	int					unknownG[4];		//20
	int					numBones;			//30
	int					ofsBoneHie;			//34
	int					ofsBoneDataA;		//38
	int					ofsBoneDataB;		//3C
	int					ofsBoneHieB;		//40
	int					numMaterials;		//44
	int					ofsMaterialsOfs;	//48
	int					ofsMaterials;		//4C
	int					numMeshes;			//50
	int					ofsMeshOfs;			//54
	int					ofsMeshes;			//58
	int					unknownK;			//5C
	int					unknownL;			//60
	int					ofsUnknownJ;		//64
	int					ofsBoneSymmetries;	//68
	int					ofsBoneFlags;		//6C
	int					exMatInfo[4];		//70
} bayoWMBHdr_t;
template <bool big>
struct bayoWMBHdr : public bayoWMBHdr_s {
	bayoWMBHdr(bayoWMBHdr_t * ptr) : bayoWMBHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(vertexFormat);
			LITTLE_BIG_SWAP(numVerts);
			LITTLE_BIG_SWAP(unknownE);
			LITTLE_BIG_SWAP(ofsPositions);
			LITTLE_BIG_SWAP(ofsVerts);
			LITTLE_BIG_SWAP(ofsVertExData);
			for (int i = 0; i < 4; i++) LITTLE_BIG_SWAP(unknownG[i]);
			LITTLE_BIG_SWAP(numBones);
			LITTLE_BIG_SWAP(ofsBoneHie);
			LITTLE_BIG_SWAP(ofsBoneDataA);
			LITTLE_BIG_SWAP(ofsBoneDataB);
			LITTLE_BIG_SWAP(ofsBoneHieB);
			LITTLE_BIG_SWAP(numMaterials);
			LITTLE_BIG_SWAP(ofsMaterialsOfs);
			LITTLE_BIG_SWAP(ofsMaterials);
			LITTLE_BIG_SWAP(numMeshes);
			LITTLE_BIG_SWAP(ofsMeshOfs);
			LITTLE_BIG_SWAP(ofsMeshes);
			LITTLE_BIG_SWAP(unknownK);
			LITTLE_BIG_SWAP(unknownL);
			LITTLE_BIG_SWAP(ofsUnknownJ);
			LITTLE_BIG_SWAP(ofsBoneSymmetries);
			LITTLE_BIG_SWAP(ofsBoneFlags);
			for (int i = 0; i < 4; i++) LITTLE_BIG_SWAP(exMatInfo[i]);
		}
	}
};
typedef struct wmbMesh_s
{
	WORD				id;
	WORD				numBatch;
	int					unknownB;
	int					batchOfs;
	int					unknownD;
	int					unknownE[4];
	char				name[32];
	float				mat[12];
} wmbMesh_t;
template <bool big>
struct wmbMesh : public wmbMesh_s {
	wmbMesh(wmbMesh_t * ptr) : wmbMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(id);
			LITTLE_BIG_SWAP(numBatch);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(batchOfs);
			LITTLE_BIG_SWAP(unknownD);
			for (int i = 0; i < 4; i++) LITTLE_BIG_SWAP(unknownE[i]);
			for (int i = 0; i < 12; i++) LITTLE_BIG_SWAP(mat[i]);
		}
	}
};
typedef struct wmbBatch_s
{
	WORD				unknownA;
	WORD				id;
	WORD				unknownB;
	WORD				unknownC;
	BYTE				texID;
	BYTE				unknownDB;
	BYTE				unknownE1;
	BYTE				unknownE2;
	int					vertStart;
	int					vertEnd;
	int					primType;
	int					ofsIndices;
	int					numIndices;
	int					vertOfs;
	int					unknownI[7];
} wmbBatch_t;
template <bool big>
struct wmbBatch : public wmbBatch_s {
	wmbBatch(wmbBatch_t * ptr) : wmbBatch_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(id);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(unknownC);
			LITTLE_BIG_SWAP(texID);
			LITTLE_BIG_SWAP(unknownDB);
			LITTLE_BIG_SWAP(unknownE1);
			LITTLE_BIG_SWAP(unknownE2);
			LITTLE_BIG_SWAP(vertStart);
			LITTLE_BIG_SWAP(vertEnd);
			LITTLE_BIG_SWAP(primType);
			LITTLE_BIG_SWAP(ofsIndices);
			LITTLE_BIG_SWAP(numIndices);
			LITTLE_BIG_SWAP(vertOfs);
			for (int i = 0; i < 7; i++) LITTLE_BIG_SWAP(unknownI[i]);
		}
	}
};
typedef struct bayoTex_s
{
	BYTE				tex_idx;
	BYTE				tex_flagA;
	WORD				tex_flagB;
} bayoTex_t;
typedef struct wmbMat_s
{
	WORD				matFlags;
	WORD				unknownB;
	bayoTex_t			texs[5];
} wmbMat_t;
template <bool big>
struct wmbMat : public wmbMat_s {
	wmbMat(wmbMat_t *ptr) : wmbMat_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(matFlags);
			LITTLE_BIG_SWAP(unknownB);
			for (int i = 0; i < 5; i++) {
				LITTLE_BIG_SWAP(texs[i]);
			}
		}
	}
};

//get a texture bundle file for a specific model
template <game_t game>
static void Model_Bayo_GetTextureBundle(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi);
template <>
static void Model_Bayo_GetTextureBundle<BAYONETTA>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, ".wtb");
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

// get motion files
static void Model_Bayo_GetMotionFiles(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<bayoDatFile_t *> &motfiles, const char *prefix = NULL)
{
	char motName[MAX_NOESIS_PATH];
	if (prefix)
	{
		sprintf_s(motName, MAX_NOESIS_PATH, "%s", prefix);
	}
	else
	{
		rapi->Noesis_GetExtensionlessName(motName, df.name);
	}
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (rapi->Noesis_CheckFileExt(dft.name, ".mot") && !_strnicoll(dft.name, motName, strlen(motName)))
		{
			DBGLOG("Found motion file: %s\n", dft.name);
			motfiles.Append(&dft);
		}
	}
}
// get exp file
static void Model_Bayo_GetEXPFile(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<bayoDatFile_t *> &expfile)
{
	char expName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(expName, df.name);
	strcat_s(expName, MAX_NOESIS_PATH, ".exp");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, expName))
		{
			expfile.Append(&dft);
		}
	}
}
//load texture bundle
template <bool big, game_t game>
static void Model_Bayo_LoadTextures(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi);

template <>
static void Model_Bayo_LoadTextures<true, BAYONETTA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	const bool big = true;
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;

	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr<true> hdr((bayoWTBHdr_t *)data);
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
	for (int i = 0; i < hdr.numTex; i++)
	{
		int globalIdx = 0;
		char fname[8192];
		char fnamegtx[8192];
		char fnamedds[8192];
		char cmd[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());

		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayotex%03i", rapi->Noesis_GetOption("texpre"), i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);
		sprintf_s(fnamegtx, MAX_NOESIS_PATH, "%s.gtx", fname);
		sprintf_s(fnamedds, MAX_NOESIS_PATH, "%s.dds", fname);

		if (hdr.texIdxOffset)
		{
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
		}
		DBGLOG("%s: 0x%0x\n", fname, globalIdx);
		//GX2_SURFACE_FORMAT_T_BC1_UNORM = 0x31
		//GX2_SURFACE_FORMAT_T_BC3_UNORM = 0x33
		FILE  * fgtx = fopen(fnamegtx, "wb");
		int tof = tofs[i];
		int tsize = tsizes[i];
		LITTLE_BIG_SWAP(tof);
		LITTLE_BIG_SWAP(tsize);
		fwrite(data + tof, 1, tsize, fgtx);
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
			DBGLOG("Could not load texture %s\n", fnamedds);
			nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
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
static void Model_Bayo_LoadTextures<false, BAYONETTA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTBHdr_t))
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
	DBGLOG("Found %d textures\n", hdr.numTex);
	int *tofs = (int *)(data + hdr.ofsTexOfs);
	int *tsizes = (int *)(data + hdr.ofsTexSizes);
	int *tflags = (int *)(data + hdr.ofsTexFlags);
	for (int i = 0; i < hdr.numTex; i++)
	{
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayotex%03i", rapi->Noesis_GetOption("texpre"), i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		int ofs = tofs[i];
		int size = tsizes[i];
		if (ofs < 0 || ofs > dataSize)
		{
			continue;
		}
		BYTE *texData = data + ofs;
		BYTE *pix;
		int globalIdx = -1;
		ddsTexHdr_t tex;
		if (hdr.texIdxOffset)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data + hdr.texIdxOffset + sizeof(int)*i);
			globalIdx = *ip;
		}
		if (hdr.texInfoOffset)
		{ //texture info is contiguous in its own section
			ddsTexHdr_t *thdr = (ddsTexHdr_t  *)(data + hdr.texInfoOffset + sizeof(ddsTexHdr_t)*i);
			tex = *thdr;
			pix = texData;
		}
		else
		{
			tex = *((ddsTexHdr_t *)texData);
			pix = texData + sizeof(ddsTexHdr_t);
		}
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

//gather entries from a dat file
template <bool big>
static void Model_Bayo_GetDATEntries(CArrayList<bayoDatFile_t> &dfiles, BYTE *fileBuffer, int bufferLen)
{
	bayoDat<big> dat((bayoDat_t *)fileBuffer);

	BYTE *namesp = fileBuffer + dat.ofsNames;
	int strSize = *((int *)namesp);
	if (big) LITTLE_BIG_SWAP(strSize);
	namesp += sizeof(int);

	int *ofsp = (int *)(fileBuffer + dat.ofsRes);
	int *sizep = (int *)(fileBuffer + dat.ofsSizes);
	DBGLOG("Found %d entries\n", dat.numRes);
	for (int i = 0; i < dat.numRes; i++)
	{
		bayoDatFile_t df;
		memset(&df, 0, sizeof(df));
		df.name = (char *)namesp;
		DBGLOG("\t%s\n", df.name);
		namesp += strSize;

		df.dataSize = *sizep;
		if (big) LITTLE_BIG_SWAP(df.dataSize);
		sizep++;

		int ofs = *ofsp;
		if (big) LITTLE_BIG_SWAP(ofs);
		df.data = fileBuffer + ofs;
		ofsp++;

		dfiles.Append(df);
	}
}
template <bool big, game_t game>
static void Model_Bayo_LoadSharedTextures(CArrayList<noesisTex_t *> &textures, char* name, noeRAPI_t *rapi) {
	noeUserPromptParam_t promptParams;
	char texturePrompt[MAX_NOESIS_PATH];
	char defaultValue[MAX_NOESIS_PATH];
	sprintf_s(texturePrompt, MAX_NOESIS_PATH, "Load shared textures (%s) in other files? (specify prefix if different)", name);
	sprintf_s(defaultValue, MAX_NOESIS_PATH, "%s", "Just click!");
	promptParams.titleStr = "Load shared textures?";
	promptParams.promptStr = texturePrompt;
	promptParams.defaultValue = defaultValue;
	promptParams.valType = NOEUSERVAL_NONE;
	promptParams.valHandler = NULL;
	wchar_t noepath[MAX_NOESIS_PATH];
	GetCurrentDirectory(MAX_NOESIS_PATH, noepath);

	while (g_nfn->NPAPI_UserPrompt(&promptParams)) {
		int dataLength;
		BYTE* data = rapi->Noesis_LoadPairedFile("Scenery Model", ".dat", dataLength, NULL);
		SetCurrentDirectory(noepath);
		if (data) {
			CArrayList<bayoDatFile_t> datfiles;
			Model_Bayo_GetDATEntries<big>(datfiles, data, dataLength);
			if (datfiles.Num() > 0) {
				CArrayList<bayoDatFile_t *> texfiles;
				if (game == BAYONETTA2) {
					for (int i = 0; i < datfiles.Num(); i++) {
						if (strstr(datfiles[i].name, "shared.wta")) {
							DBGLOG("Found shared texture bundle %s\n", datfiles[i].name);
							texfiles.Append(&datfiles[i]);
						}
					}
					for (int i = 0; i < datfiles.Num(); i++) {
						if (strstr(datfiles[i].name, "shared.wtp")) {
							DBGLOG("Found shared texture bundle %s\n", datfiles[i].name);
							texfiles.Append(&datfiles[i]);
						}
					}
					if (texfiles.Num() == 2) {
						Model_Bayo_LoadTextures<big, game>(textures, texfiles, rapi);
					}
				}
				else {
					for (int i = 0; i < datfiles.Num(); i++) {
						if (strstr(datfiles[i].name, "cmn.wtb")) {
							DBGLOG("Found shared texture bundle %s\n", datfiles[i].name);
							texfiles.Append(&datfiles[i]);
						}
					}
					if (texfiles.Num() > 0) {
						Model_Bayo_LoadTextures<big, game>(textures, texfiles, rapi);
					}
				}
				texfiles.Clear();
			}
			datfiles.Clear();
		}
		rapi->Noesis_UnpooledFree(data);
	}
	SetCurrentDirectory(noepath);
}

template <bool big, game_t game>
static void Model_Bayo_LoadExternalMotions(CArrayList<noesisAnim_t *> &animList, bayoDatFile_t &df, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT, void* extraBoneInfo);

//decode bayonetta normals
template <bool big, game_t game>
static void Model_Bayo_CreateNormal(char *src, float *dst);

template <>
static void Model_Bayo_CreateNormal<true, BAYONETTA2>(char *src, float *dst);

template <>
static void Model_Bayo_CreateNormal<true, BAYONETTA>(char *src, float *dst) {
	return Model_Bayo_CreateNormal<true, BAYONETTA2>(src, dst);
}

template <>
static void Model_Bayo_CreateNormal<false, BAYONETTA>(char *src, float *dst) {
	for (int j = 0; j < 3; j++) {
		dst[j] = (float)src[3 - j] / (float)127;
	}
}

template <bool big, game_t game>
static void Model_Bayo_CreateNormals(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m)
{
	for (int i = 0; i < numVerts; i++)
	{
		char *src = (char *)(data + stride * i);
		float *dst = dsts + i * 3;
		float tmp[3];
		Model_Bayo_CreateNormal<big, game>(src, dst);
		if (m) {
			g_mfn->Math_TransformPointByMatrixNoTrans(m, dst, tmp);
			g_mfn->Math_VecCopy(tmp, dst);
		}
		g_mfn->Math_VecNorm(dst);
		if (big) {
			LITTLE_BIG_SWAP(dst[0]);
			LITTLE_BIG_SWAP(dst[1]);
			LITTLE_BIG_SWAP(dst[2]);
		}
	}
}

template <bool big>
static void Model_Bayo_PretransformPositions(BYTE *data, int numVerts, int stride, modelMatrix_t *m)
{
	for (int i = 0; i < numVerts; i++)
	{
		float * src = (float *)(data + stride * i);
		float tmp[3];
		if (big) {
			LITTLE_BIG_SWAP(src[0]);
			LITTLE_BIG_SWAP(src[1]);
			LITTLE_BIG_SWAP(src[2]);
		}
		g_mfn->Math_TransformPointByMatrix(m, src, tmp);
		g_mfn->Math_VecCopy(tmp, src);
		if (big) {
			LITTLE_BIG_SWAP(src[0]);
			LITTLE_BIG_SWAP(src[1]);
			LITTLE_BIG_SWAP(src[2]);
		}
	}
}
template <bool big>
static void Model_Bayo_PretransformNormals(BYTE *data, int numVerts, int stride, modelMatrix_t *m)
{
	for (int i = 0; i < numVerts; i++)
	{
		float * src = (float *)(data + stride * i);
		float tmp[3];
		if (big) {
			LITTLE_BIG_SWAP(src[0]);
			LITTLE_BIG_SWAP(src[1]);
			LITTLE_BIG_SWAP(src[2]);
		}
		g_mfn->Math_TransformPointByMatrixNoTrans(m, src, tmp);
		g_mfn->Math_VecCopy(tmp, src);
		if (big) {
			LITTLE_BIG_SWAP(src[0]);
			LITTLE_BIG_SWAP(src[1]);
			LITTLE_BIG_SWAP(src[2]);
		}
	}
}

template <bool big, game_t game>
static void Model_Bayo_CreateTangents(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m);

template <>
static void Model_Bayo_CreateTangents<false, BAYONETTA>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m)
{
	for (int i = 0; i < numVerts; i++)
	{
		BYTE *src = data + stride * i;
		float tmp[3];
		float *dst = dsts + i * 4;
		for (int j = 0; j < 4; j++) {
			dst[j] = (src[j] - (float)127) / (float)127;
		}
		if (m) {
			g_mfn->Math_TransformPointByMatrixNoTrans(m, dst, tmp);
			g_mfn->Math_VecCopy(tmp, dst);
		}
	}
}

template <>
static void Model_Bayo_CreateTangents<true, BAYONETTA>(BYTE *data, float *dsts, int numVerts, int stride, modelMatrix_t *m)
{
	for (int i = 0; i < numVerts; i++)
	{
		BYTE *src = data + stride * i;
		float tmp[3];
		float *dst = dsts + i * 4;
		for (int j = 0; j < 4; j++) {
			dst[j] = (src[3 - j] - (float)127) / (float)127;
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

//convert the bones
template <bool big>
modelBone_t *Model_Bayo_CreateBones(bayoWMBHdr<big> &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT)
{
	numBones = 0;
	if (hdr.numBones <= 0 || hdr.ofsBoneHie <= 0 || hdr.ofsBoneDataA <= 0 || hdr.ofsBoneDataB <= 0)
	{
		return NULL;
	}
	short *parentList = (short *)(data + hdr.ofsBoneHie);
	float *posList = (float *)(data + hdr.ofsBoneDataB);
	float *relPosList = (float *)(data + hdr.ofsBoneDataA); //actually relative positions
	char *boneFlags = nullptr;
	if (hdr.ofsBoneFlags)
		boneFlags = (char *)(data + hdr.ofsBoneFlags);
	animBoneTT = (short int *)(data + hdr.ofsBoneHieB);
	std::map<short int, short int> boneMap;
	for (short int i = 0; i < 0x1000; i++) {
		short int decoded_index = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, i);
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
		float *ppos = posList + i * 3;
		short parent = parentList[i];
		if (big) LITTLE_BIG_SWAP(parent);
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
		sprintf_s(bone->name, 30, "bone%03i", boneMap.at((short int)i));
		bone->mat = g_identityMatrix;
		float pos[3];

		memcpy(pos, ppos, sizeof(pos));
		if (big) {
			LITTLE_BIG_SWAP(pos[0]);
			LITTLE_BIG_SWAP(pos[1]);
			LITTLE_BIG_SWAP(pos[2]);
		}
		g_mfn->Math_VecCopy(pos, bone->mat.o);
		if (boneFlags)
			bone->userIndex = boneFlags[i];
		else
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
	//bones come pre-transformed
	//rapi->rpgMultiplyBones(bones, numBones);
	return bones;
}

template<bool big>
static void Model_Bayo_SetTile(BYTE * matData, int tileOffset, noesisMaterial_t * mat, noeRAPI_t *rapi) {
	if (tileOffset != -1) {
		bayoV4F<big> tile((bayoV4F_t *)(matData + tileOffset));
		char myexpr[128];
		if (tile.x != 1.0f) {
			snprintf(myexpr, 128, "vert_uv_u * %f", tile.x);
			mat->expr->v_uvExpr[0] = rapi->Express_Parse(myexpr);
		}
		if (tile.y != 1.0f) {
			snprintf(myexpr, 128, "vert_uv_v * %f", tile.y);
			mat->expr->v_uvExpr[1] = rapi->Express_Parse(myexpr);
		}
	}
}
template<bool big>
static int Model_Bayo_ReadTextureIndex(wmbMat<big> &mat, CArrayList<noesisTex_t *> &textures, int textureOffset, int &sharedtextureoffset, bool default0, noeRAPI_t * rapi) {
	//DBGLOG("texture offset %d ", textureOffset);
	if (textureOffset != -1 || default0) {
		int offset;
		if (textureOffset != -1) {
			offset = textureOffset / 4 - 1;
		}
		else {
			offset = 0;
		}
		//DBGLOG(" offset %d ", offset);
		if ((mat.texs[offset].tex_flagB & 0xff00) == 0xa000) {
			if (sharedtextureoffset == -1) {
				sharedtextureoffset = textures.Num();
				char scrName[10];
				snprintf(scrName, 10, "r%2x0", mat.texs[offset].tex_flagB & 0xff);
				Model_Bayo_LoadSharedTextures<big, BAYONETTA>(textures, scrName, rapi);
				if (textures.Num() == sharedtextureoffset) {
					sharedtextureoffset = -2;
				}
			}
			if (sharedtextureoffset >= 0) {
				return mat.texs[offset].tex_idx + sharedtextureoffset;
			}
			else {
				return -1;
			}
		}
		else if (!mat.texs[offset].tex_flagB || (mat.texs[offset].tex_flagB & 0xff00) == 0x9000) {
			return mat.texs[offset].tex_idx;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}
//load Bayonetta Material
#define BAYONETTA_MULTIPASS (1<<0)
template <bool big, game_t game>
static void Model_Bayo_LoadMaterials(bayoWMBHdr<big> &hdr,
	CArrayList<noesisTex_t *> &textures,
	bool &hasExMatInfo,
	CArrayList<noesisMaterial_t *> &matList,
	CArrayList<noesisMaterial_t *> &matListLightMap,
	CArrayList<noesisMaterial_t *> &totMatList,
	BYTE *data,
	noeRAPI_t *rapi,
	int sharedtextureoffset = -1) {
	char *inFile = rapi->Noesis_GetInputName();
	char texDir[MAX_NOESIS_PATH] = "";
	if (game == VANQUISH || game == ANARCHY_REIGNS) {
		rapi->Noesis_GetDirForFilePath(texDir, inFile);
		strcat_s(texDir, MAX_NOESIS_PATH, "\\..\\HTextures\\");
	}
	int *matOfsList = (int *)(data + hdr.ofsMaterialsOfs);
	hasExMatInfo = (hdr.exMatInfo[0] && hdr.exMatInfo[1] && hdr.exMatInfo[3]);
	int *matIDs = (hasExMatInfo) ? (int *)(data + hdr.exMatInfo[1]) : NULL;
	int numMatIDs = 0;
	if (matIDs)
	{ //got a global reference list (this seems redundant since it's also provided in the texture bundle)
		numMatIDs = *matIDs;
		if (big) LITTLE_BIG_SWAP(numMatIDs);
		matIDs++;
	}
	DBGLOG("Found %d materials, shared textures offset: %d\n", hdr.numMaterials, sharedtextureoffset);
	if ((game == VANQUISH || game == ANARCHY_REIGNS) && numMatIDs > 0) {
		for (int j = 0; j < numMatIDs; j++) {
			int texId = *(matIDs + j * 2);
			if (big) LITTLE_BIG_SWAP(texId);
			Model_Vanquish_LoadExtraTex<big, game>(texDir, texId, rapi, textures);
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
	for (int i = 0; i < hdr.numMaterials; i++)
	{
		DBGLOG("\t%03d:", i);
		int matOfs = matOfsList[i];
		if (big) LITTLE_BIG_SWAP(matOfs);
		BYTE *matData = data + hdr.ofsMaterials + matOfs;
		//create a noesis material entry
		char matName[128];
		sprintf_s(matName, 128, "bayomat%i", i);
		DBGLOG(" name: %s,", matName);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		noesisMaterial_t *nmatLightMap = NULL;
		nmat->name = rapi->Noesis_PooledString(matName);
		//nmat->flags |= NMATFLAG_TWOSIDED;

		if (hasExMatInfo && numMatIDs > 0)
		{ //search by global index values
			DBGLOG("vanquish style\n");
			nmat->noDefaultBlend = true;
			nmat->texIdx = -1;
			nmat->normalTexIdx = -1; //default to flat normal
			char *shaderName = (char *)(data + hdr.exMatInfo[0] + 16 * i);
			if (_strnicmp(shaderName, "har", 3) == 0 || _strnicmp(shaderName, "gla", 3) == 0 || _strnicmp(shaderName, "cnm", 3) == 0 || _strnicmp(shaderName, "alp", 3) == 0)
			{ //blend hair
				nmat->noDefaultBlend = false;
			}
			bool isSkin = (_strnicmp(shaderName, "skn0", 4) == 0);
			bool isPHG = (_strnicmp(shaderName, "phg05", 5) == 0);
			bool isLBT = (_strnicmp(shaderName, "lbt00", 5) == 0);
			bool raSwap = (_strnicmp(shaderName, "max32", 5) == 0); //hacky way to see if the normal needs red and alpha swapped, probably not reliable
			int difTexId = *((int *)(matData + 4));
			if (big) { LITTLE_BIG_SWAP(difTexId); }
			int nrmOfs = (isPHG || isLBT) ? 8 : 16;
			int nrmTexId = *((int *)(matData + nrmOfs)); //this is kinda happenstance, i think the only right way to know what to do is to check the pixel shader
			if (big) { LITTLE_BIG_SWAP(nrmTexId); }
			DBGLOG("\t\tshader: %s, diff: 0x%0x, nrm: 0x%0x\n", shaderName, difTexId, nrmTexId);
			for (int j = 0; j < textures.Num(); j++)
			{
				noesisTex_t *tex = textures[j];
				if (tex && tex->globalIdx == difTexId)
				{
					nmat->texIdx = j;
				}
			}
			for (int j = 0; j < textures.Num(); j++)
			{
				noesisTex_t *tex = textures[j];
				if (tex && tex->globalIdx == nrmTexId)
				{
					nmat->normalTexIdx = j;
					if (raSwap)
					{
						nmat->flags |= NMATFLAG_NMAPSWAPRA;
					}
				}
			}
			if (nmat->normalTexIdx == -1) {
				nmat->normalTexIdx = textures.Num() - 1;
			}
		}
		else
		{ //bayonetta-style
			wmbMat<big> mat((wmbMat_t *)matData);

			if (!bayoMatTypes[mat.matFlags].known) {
				DBGLOG(" unknown material id: %2x, %4x", mat.matFlags, mat.unknownB);
				for (int j = 0; j < 5; j++) {
					DBGLOG(", tex%d: %d, %2x, %4x", j, mat.texs[j].tex_idx, mat.texs[j].tex_flagA, mat.texs[j].tex_flagB);
				}
				DBGLOG("\n");
				DBGFLUSH();
			}
			else {
				DBGLOG(" material id: %2x, %4x, offset: %x",
					mat.matFlags, mat.unknownB, hdr.ofsMaterials + matOfs);
			}

			nmat->normalTexIdx = -1;
			int color1 = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].color_1_sampler, sharedtextureoffset, true, rapi);
			int color2 = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].color_2_sampler, sharedtextureoffset, false, rapi);
			int color3 = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].color_3_sampler, sharedtextureoffset, false, rapi);
			DBGLOG(", color1: %d", color1);
			if (color2 != -1) {
				DBGLOG(", color2: %d", color2);
			}
			if (color3 != -1) {
				DBGLOG(", color3: %d", color3);
			}
			if (color3 != -1 && color2 != -1) {
				// r: 1 - ratio of color1 and (color2 + color3)
				// g: 1 - ratio of color2 and color 3
				// (1 - r) * (g*color3 + (1-g)*color2) +  r * color1
				//(1-r) * g * color3 + (1-r)*(1-g)*color2 + r * color1
				nmat->ex->userTag[0] = BAYONETTA_MULTIPASS;
				nmat->texIdx = color3;
				nmat->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				nmat->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[3] = rapi->Express_Parse("1.0");

				char matName2[128];
				sprintf_s(matName2, 128, "bayomat2p%i", i);
				DBGLOG(" name: %s,", matName2);
				noesisMaterial_t *nmat2 = rapi->Noesis_GetMaterialList(1, true);
				nmat2->name = rapi->Noesis_PooledString(matName2);
				totMatList.Append(nmat2);
				nmat2->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				nmat2->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[3] = rapi->Express_Parse("vert_clr_g");
				nmat2->texIdx = color2;
				nmat->nextPass = nmat2;
				nmat2->blendSrc = NOEBLEND_ONE_MINUS_SRC_ALPHA;
				nmat2->blendDst = NOEBLEND_SRC_ALPHA;

				char matName3[128];
				sprintf_s(matName3, 128, "bayomat3p%i", i);
				DBGLOG(" name: %s,", matName3);
				noesisMaterial_t *nmat3 = rapi->Noesis_GetMaterialList(1, true);
				nmat3->name = rapi->Noesis_PooledString(matName3);
				totMatList.Append(nmat3);
				nmat3->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				nmat3->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat3->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat3->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat3->expr->v_clrExpr[3] = rapi->Express_Parse("vert_clr_r");
				nmat3->texIdx = color1;
				nmat2->nextPass = nmat3;
				nmat3->blendSrc = NOEBLEND_ONE_MINUS_SRC_ALPHA;
				nmat3->blendDst = NOEBLEND_SRC_ALPHA;

				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_1_tile, nmat3, rapi);
				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_2_tile, nmat2, rapi);
				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_3_tile, nmat, rapi);
			}
			else if (color2 != -1) {
				nmat->ex->userTag[0] = BAYONETTA_MULTIPASS;
				nmat->texIdx = color1;
				nmat->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				nmat->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[3] = rapi->Express_Parse("1.0");
				//nmat->alphaTest = 0.0f;
				//nmat->noDefaultBlend = true ;
				//DBGLOG(", blendSrc: %d", nmat->blendSrc);
				//DBGLOG(", blendDst: %d", nmat->blendDst);
				char matName2[128];
				sprintf_s(matName2, 128, "bayomat2p%i", i);
				DBGLOG(" name: %s,", matName2);
				noesisMaterial_t *nmat2 = rapi->Noesis_GetMaterialList(1, true);
				nmat2->name = rapi->Noesis_PooledString(matName2);
				totMatList.Append(nmat2);

				nmat2->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				nmat2->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat2->expr->v_clrExpr[3] = rapi->Express_Parse("vert_clr_r");
				nmat2->texIdx = color2;
				nmat->nextPass = nmat2;

				nmat2->blendSrc = NOEBLEND_SRC_ALPHA;
				nmat2->blendDst = NOEBLEND_ONE_MINUS_SRC_ALPHA;

				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_1_tile, nmat, rapi);
				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_2_tile, nmat2, rapi);
			}
			else {
				nmat->texIdx = color1;
				//avoid using material expressions for simple materials.

				/*if (bayoMatTypes[mat.matFlags].color_1_tile != -1) {
					bayoV4F<big> tile((bayoV4F_t *)(matData + bayoMatTypes[mat.matFlags].color_1_tile));

					if (tile.x != 1.0f || tile.y != 1.0f) {
						float *scaleBias = (float *)rapi->Noesis_PooledAlloc(4 * sizeof(float));
						scaleBias[0] = tile.x;
						scaleBias[1] = tile.y;
						scaleBias[2] = 0.0f;
						scaleBias[3] = 0.0f;
						nmat->ex->pUvScaleBias = scaleBias;
					}
				}*/
				nmat->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
				/*nmat->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
				nmat->expr->v_clrExpr[3] = rapi->Express_Parse("1.0");*/
				Model_Bayo_SetTile<big>(matData, bayoMatTypes[mat.matFlags].color_1_tile, nmat, rapi);
			}
			if (mat.matFlags == 0x87 || mat.matFlags == 0x6b) { //"modelshaderpls06_bxnxx" || "modelshaderobs07_bxnxx"
				nmat->flags |= NMATFLAG_NORMAL_UV1;
				//nmat->ex->flags2 |= NMATFLAG2_PREFERPPL;
				DBGLOG(", normal use UV2");
			}
			if (mat.matFlags == 0x6b) { //"modelshaderobs07_bxnxx"
				//nmat->flags |= NMATFLAG_PBR_SPEC | NMATFLAG_PBR_ROUGHNESS_NRMALPHA;
				//nmat->ex->roughnessScale = -1.0;
				//nmat->ex->roughnessBias = 1.0;
			}
			if (mat.matFlags == 0x69) { //"modelshaderbil04_xxxxx"
				//nmat->flags |= NMATFLAG_SPRITE_FACINGXY; //no effect
			}
			if (bayoMatTypes[mat.matFlags].shader_name && strstr(bayoMatTypes[mat.matFlags].shader_name, "modelshaderbgs")) {
				nmat->bumpTexIdx = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].reliefmap_sampler, sharedtextureoffset, false, rapi);
				DBGLOG(", bump: %d", nmat->bumpTexIdx);
			}
			else {
				nmat->normalTexIdx = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].reliefmap_sampler, sharedtextureoffset, false, rapi);
				DBGLOG(", normal: %d", nmat->normalTexIdx);
			}
			if (nmat->normalTexIdx == -1 && textures.Num() > 0) {
				nmat->normalTexIdx = textures.Num() - 1;
			}

			nmat->specularTexIdx = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].spec_mask_sampler, sharedtextureoffset, false, rapi);

			if (bayoMatTypes[mat.matFlags].specular != -1) {
				bayoV4F<big> spec((bayoV4F_t *)(matData + bayoMatTypes[mat.matFlags].specular));
				nmat->specular[0] = spec.x;
				nmat->specular[1] = spec.y;
				nmat->specular[2] = spec.z;
			}

			if (bayoMatTypes[mat.matFlags].diffuse != -1) {
				bayoV4F<big> diff((bayoV4F_t *)(matData + bayoMatTypes[mat.matFlags].diffuse));
				nmat->diffuse[0] = diff.x;
				nmat->diffuse[1] = diff.y;
				nmat->diffuse[2] = diff.z;
			}

			nmat->envTexIdx = Model_Bayo_ReadTextureIndex(mat, textures, bayoMatTypes[mat.matFlags].envmap_sampler, sharedtextureoffset, false, rapi);
			/*			if (nmat->envTexIdx != -1 && nmat->specularTexIdx == -1) {
							nmat->specularTexIdx = nmat->texIdx;
							nmat->flags |= NMATFLAG_PBR_SPEC;
							nmat->specular[0] = 1.0;
							nmat->specular[1] = 1.0;
							nmat->specular[2] = 1.0;
							nmat->specular[3] = 1.0;
							nmat->noDefaultBlend = true;
						}*/
						//todo - some materials also do a scale+bias+rotation on the uv's at runtime to transform the texture coordinates into a
						//specific region of the normal page. i would think the uv transform data is buried in the giant chunk of floats that
						//follows the material data, but i don't see it in there. maybe it's related to some texture bundle flags.
			short lightmap_offset = bayoMatTypes[mat.matFlags].lightmap_sampler;
			if (lightmap_offset != -1 && !mat.texs[lightmap_offset / 4 - 1].tex_flagB) {
				char matNameLightMap[128];
				sprintf_s(matNameLightMap, 128, "bayomat_light%i", i);
				nmatLightMap = rapi->Noesis_GetMaterialList(1, true);
				nmatLightMap->name = rapi->Noesis_PooledString(matNameLightMap);
				nmatLightMap->texIdx = mat.texs[lightmap_offset / 4 - 1].tex_idx;
				nmatLightMap->normalTexIdx = nmat->normalTexIdx;
				//nmatLightMap->noLighting = true;
				nmatLightMap->flags |= NMATFLAG_USELMUVS;
				nmatLightMap->blendDst = NOEBLEND_ZERO;
				nmatLightMap->blendSrc = NOEBLEND_DST_COLOR;
				//nmatLightMap->noDefaultBlend = true;
				//nmatLightMap->alphaTest = 0.5;

				if (nmat->ex->userTag[0] & BAYONETTA_MULTIPASS) {
					nmatLightMap->expr = rapi->Noesis_AllocMaterialExpressions(NULL);
					nmatLightMap->expr->v_clrExpr[0] = rapi->Express_Parse("1.0");
					nmatLightMap->expr->v_clrExpr[1] = rapi->Express_Parse("1.0");
					nmatLightMap->expr->v_clrExpr[2] = rapi->Express_Parse("1.0");
					nmatLightMap->expr->v_clrExpr[3] = rapi->Express_Parse("1.0");
				}

				totMatList.Append(nmatLightMap);
				//nmat->noLighting = true;
				if (color3 != -1 && color2 != -1) {
					nmat->nextPass->nextPass->nextPass = nmatLightMap;
				}
				else if (color2 != -1) {
					nmat->nextPass->nextPass = nmatLightMap;
				}
				else {
					nmat->nextPass = nmatLightMap;
				}
			}
			/*copy properties to next passes*/
			if (color3 != -1 && color2 != -1) {
				nmat->nextPass->nextPass->normalTexIdx = nmat->normalTexIdx;
				nmat->nextPass->nextPass->noLighting = nmat->noLighting;
				g_mfn->Math_VecCopy(nmat->diffuse, nmat->nextPass->nextPass->diffuse);
				g_mfn->Math_VecCopy(nmat->specular, nmat->nextPass->nextPass->specular);
				nmat->nextPass->normalTexIdx = nmat->normalTexIdx;
				nmat->nextPass->noLighting = nmat->noLighting;
				g_mfn->Math_VecCopy(nmat->diffuse, nmat->nextPass->diffuse);
				g_mfn->Math_VecCopy(nmat->specular, nmat->nextPass->specular);
			}
			else if (color2 != -1) {
				nmat->nextPass->normalTexIdx = nmat->normalTexIdx;
				nmat->nextPass->noLighting = nmat->noLighting;
				g_mfn->Math_VecCopy(nmat->diffuse, nmat->nextPass->diffuse);
				g_mfn->Math_VecCopy(nmat->specular, nmat->nextPass->specular);
			}
			DBGLOG("\n");



		}
		matListLightMap.Append(nmatLightMap);
		matList.Append(nmat);
		totMatList.Append(nmat);
	}
}

typedef struct buffer_s {
	BYTE				*address = NULL;
	unsigned int		stride = 0;
	rpgeoDataType_e		type = RPGEODATA_FLOAT;
} buffer_t;

typedef struct buffers_s {
	buffer_t position;
	buffer_t mapping;
	buffer_t tangents;
	buffer_t normal;
	buffer_t bone_indexes;
	buffer_t bone_weights;
	buffer_t color;
	buffer_t mapping2;
	buffer_t position2;
} buffers_t;

template <bool big, game_t game>
static void __set_position(buffer_t &position, BYTE *address, unsigned int stride, unsigned int count, modelMatrix_t * pretransform = NULL) {
	position.address = address;
	position.stride = stride;
	position.type = RPGEODATA_FLOAT;
	if (pretransform)
	{
		Model_Bayo_PretransformPositions<big>(position.address, count, stride, pretransform);
	}
}
template <bool big, game_t game>
static void __set_fnormal(buffer_t &normal, BYTE *address, unsigned int stride, unsigned int count, modelMatrix_t * pretransform = NULL) {
	normal.address = address;
	normal.stride = stride;
	normal.type = RPGEODATA_FLOAT;
	if (pretransform)
	{
		Model_Bayo_PretransformNormals<big>(normal.address, count, stride, pretransform);
	}
}
template <bool big, game_t game>
static void __set_hnormal(buffer_t &normal, BYTE *address, unsigned int stride, unsigned int count, noeRAPI_t *rapi, modelMatrix_t * pretransform = NULL) {
	normal.address = (BYTE *)rapi->Noesis_PooledAlloc(sizeof(float) * 3 * count);
	float *dst = (float *)normal.address;
	for (unsigned int i = 0; i < count; i++) {
		dst[3 * i] = H.decompress(*(unsigned short *)(address + i * stride), big);
		dst[3 * i + 1] = H.decompress(*(unsigned short *)(address + i * stride + 2), big);
		dst[3 * i + 2] = H.decompress(*(unsigned short *)(address + i * stride + 4), big);
	}
	normal.stride = 12;
	normal.type = RPGEODATA_FLOAT;
	if (pretransform)
	{
		Model_Bayo_PretransformNormals<big>(normal.address, count, stride, pretransform);
	}
}
template <bool big, game_t game>
static void __set_mapping(buffer_t &mapping, BYTE *address, unsigned int stride) {
	mapping.address = address;
	mapping.stride = stride;
	mapping.type = RPGEODATA_HALFFLOAT;
}
template <bool big, game_t game>
static void __set_fmapping(buffer_t &mapping, BYTE *address, unsigned int stride) {
	mapping.address = address;
	mapping.stride = stride;
	mapping.type = RPGEODATA_FLOAT;
}
template <bool big, game_t game>
static void __set_normal(buffer_t &normal, BYTE *address, unsigned int stride, unsigned int count, noeRAPI_t *rapi, modelMatrix_t * pretransform = NULL) {
	normal.address = (BYTE *)rapi->Noesis_PooledAlloc(sizeof(float) * 3 * count);
	Model_Bayo_CreateNormals<big, game>(address, (float *)normal.address, count, stride, pretransform);
	normal.stride = 12;
	normal.type = RPGEODATA_FLOAT;
}
template <typename T>
static void __set_static_info_helper(buffer_t &info, unsigned int count, unsigned int stride, void * data, noeRAPI_t *rapi) {
	info.address = (BYTE *)rapi->Noesis_PooledAlloc(sizeof(T) * stride * count);
	for (unsigned int i = 0; i < count; i++)
		memcpy(info.address + sizeof(T) * stride * i, data, sizeof(T) * stride);
	info.stride = sizeof(T) * stride;
}
template <bool big, game_t game, rpgeoDataType_e type>
static void __set_static_info(buffer_t &info, unsigned int count, unsigned int stride, void * data, noeRAPI_t *rapi) {
	switch (type) {
	case RPGEODATA_FLOAT:
		__set_static_info_helper<float>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_INT:
		__set_static_info_helper<int>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_UINT:
		__set_static_info_helper<unsigned int>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_SHORT:
		__set_static_info_helper<short>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_USHORT:
		__set_static_info_helper<unsigned short>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_HALFFLOAT:
		__set_static_info_helper<unsigned short>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_DOUBLE:
		__set_static_info_helper<double>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_BYTE:
		__set_static_info_helper<char>(info, count, stride, data, rapi);
		break;
	case RPGEODATA_UBYTE:
		__set_static_info_helper<unsigned char>(info, count, stride, data, rapi);
		break;
	}
	info.type = type;
}
template <bool big, game_t game>
static void __set_tangents(buffer_t &tangents, BYTE *address, unsigned int stride, unsigned int count, noeRAPI_t *rapi, modelMatrix_t * pretransform = NULL) {
	tangents.address = (BYTE *)rapi->Noesis_PooledAlloc(sizeof(float) * 4 * count);
	Model_Bayo_CreateTangents<big, game>(address, (float *)tangents.address, count, stride, pretransform);
	tangents.stride = 16;
	tangents.type = RPGEODATA_FLOAT;
}
template <bool big, game_t game>
static void __set_bone_infos(buffer_t &bone_indexes, BYTE *address, unsigned int stride) {
	bone_indexes.address = address;
	bone_indexes.stride = stride;
	bone_indexes.type = RPGEODATA_UBYTE;
}
template <bool big, game_t game>
static void __set_color(buffer_t &color, BYTE *address, unsigned int stride) {
	color.address = address;
	color.stride = stride;
	color.type = RPGEODATA_UBYTE;
}
template <bool big, game_t game>
static void __set_indices(buffer_t &indices, BYTE *address, unsigned int stride) {
	indices.address = address;
	indices.type = RPGEODATA_UINT;
	indices.stride = stride;
}
template <bool big, game_t game>
static void __set_sindices(buffer_t &indices, BYTE *address, unsigned int stride) {
	indices.address = address;
	indices.type = RPGEODATA_USHORT;
	indices.stride = stride;
}
template <bool big, game_t game>
static void Model_Bayo_SetBuffers(bayoDatFile_t &df, noeRAPI_t *rapi, bayoWMBHdr<big> &hdr, buffers_t &buffers, modelMatrix_t * pretransform = NULL) {
	BYTE *data = df.data;
	unsigned int bayoVertSize;
	unsigned int bayoVertExSize;
	unsigned int numVerts = hdr.numVerts;
	BYTE *pos = data + hdr.ofsPositions;
	BYTE *verts = data + hdr.ofsVerts;
	BYTE *vertsEx = data + hdr.ofsVertExData;
	DBGLOG("Vertex format: <%0x, %d, %d>!!!\n", hdr.vertexFormat, hdr.numMapping, hdr.unknownD);
	// Bayonetta
	if (hdr.vertexFormat == 0x6800001f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x6800001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 4;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4800000f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
		__set_mapping<big, game>(buffers.mapping2, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4800000f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 28;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x6800003f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 16;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_position<big, game>(buffers.position2, vertsEx + 4, bayoVertExSize, numVerts, pretransform);
	}
	else if (hdr.vertexFormat == 0x6000001f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 44;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, pos, 12, numVerts, pretransform);
		__set_fnormal<big, game>(buffers.normal, verts, bayoVertSize, numVerts, pretransform);
		__set_color<big, game>(buffers.color, verts + 12, bayoVertSize);
		__set_tangents<big, game>(buffers.tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 20, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 24, bayoVertSize);
		__set_fmapping<big, game>(buffers.mapping, verts + 28, bayoVertSize);
		__set_fmapping<big, game>(buffers.mapping2, verts + 36, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4800001f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4800001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 4;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4000001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 36;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, pos, 12, numVerts, pretransform);
		__set_fnormal<big, game>(buffers.normal, verts, bayoVertSize, numVerts, pretransform);
		__set_color<big, game>(buffers.color, verts + 12, bayoVertSize);
		__set_tangents<big, game>(buffers.tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 20, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 24, bayoVertSize);
		__set_fmapping<big, game>(buffers.mapping, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x6000001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 36;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, pos, 12, numVerts, pretransform);
		__set_fnormal<big, game>(buffers.normal, verts, bayoVertSize, numVerts, pretransform);
		__set_color<big, game>(buffers.color, verts + 12, bayoVertSize);
		__set_tangents<big, game>(buffers.tangents, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 20, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 24, bayoVertSize);
		__set_fmapping<big, game>(buffers.mapping, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x5800000f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
		__set_mapping<big, game>(buffers.mapping2, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x5800000f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 28;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x5800002f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 40;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
		__set_position<big, game>(buffers.position2, verts + 28, bayoVertSize, numVerts, pretransform);
	}
	else if (hdr.vertexFormat == 0x4800000b && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
	}
	else if (hdr.vertexFormat == 0x4800002f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 40;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
		__set_position<big, game>(buffers.position2, verts + 28, bayoVertSize, numVerts, pretransform);
	}
	//Bayonetta 2
	else if (hdr.vertexFormat == 0x6b40001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 4;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4b40000f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 28;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x6b40001f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4b40000f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_color<big, game>(buffers.color, verts + 24, bayoVertSize);
		__set_mapping<big, game>(buffers.mapping2, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4b40001f && hdr.numMapping == 0x2 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x6b40001d && hdr.numMapping == 0x1 && hdr.unknownD == 0x0) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4b40001d && hdr.numMapping == 0x1 && hdr.unknownD == 0x0) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4b40001f && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 4;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4b40001d && hdr.numMapping == 0x2 && hdr.unknownD == 0x0) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	else if (hdr.vertexFormat == 0x4b40000d && hdr.numMapping == 0x1 && hdr.unknownD == 0x0) {
		bayoVertSize = 24;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
	}
	else if (hdr.vertexFormat == 0x6b40001d && hdr.numMapping == 0x2 && hdr.unknownD == 0x0) {
		bayoVertSize = 32;
		bayoVertExSize = 8;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
		__set_color<big, game>(buffers.color, vertsEx, bayoVertExSize);
		__set_mapping<big, game>(buffers.mapping2, vertsEx + 4, bayoVertExSize);
	}
	//Vanquish
	else if (hdr.vertexFormat == 0x4b40001d && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x6b40001d && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 32;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
		__set_bone_infos<big, game>(buffers.bone_indexes, verts + 24, bayoVertSize);
		__set_bone_infos<big, game>(buffers.bone_weights, verts + 28, bayoVertSize);
	}
	else if (hdr.vertexFormat == 0x4b40000d && hdr.numMapping == 0x1 && hdr.unknownD == 0x1) {
		bayoVertSize = 24;
		bayoVertExSize = 0;
		__set_position<big, game>(buffers.position, verts, bayoVertSize, numVerts, pretransform);
		__set_mapping<big, game>(buffers.mapping, verts + 12, bayoVertSize);
		__set_normal<big, game>(buffers.normal, verts + 16, bayoVertSize, numVerts, rapi, pretransform);
		__set_tangents<big, game>(buffers.tangents, verts + 20, bayoVertSize, numVerts, rapi, pretransform);
	}
	else {
		DBGLOG("Unknown vertex format: <%0x, %d, %d>!!!\n", hdr.vertexFormat, hdr.numMapping, hdr.unknownD);
	}
}

template <bool big, game_t game>
static void Model_Bayo_LoadModel(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models, CArrayList<noesisTex_t *> &givenTextures, modelMatrix_t * pretransform, int sharedtextureoffset = -1)
{
	DBGLOG("Loading %s\n", df.name);
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(bayoWMBHdr_t))
	{
		return;
	}
	bayoWMBHdr<big> hdr((bayoWMBHdr_t *)data);
	if (memcmp(hdr.id, "WMB\0", 4))
	{ //invalid header
		return;
	}
	bool isVanqModel = (hdr.unknownA < 0);
	DBGLOG("Vanquish: %s\n", isVanqModel ? "true" : "false");

	CArrayList<bayoDatFile_t *> motfiles;
	CArrayList<bayoDatFile_t *> texFiles;
	CArrayList<bayoDatFile_t *> expfile;
	CArrayList<noesisTex_t *> textures;
	CArrayList<noesisMaterial_t *> matList;
	CArrayList<noesisMaterial_t *> matListLightMap;
	CArrayList<noesisMaterial_t *> totMatList;
	CArrayList<noesisAnim_t *> animList;

	buffers_t buffers;

	bool hasExMatInfo;

	if (givenTextures.Num() == 0) {
		Model_Bayo_GetTextureBundle<game>(texFiles, dfiles, df, rapi);
		if (texFiles.Num() > 0)
		{
			for (int i = 0; i < texFiles.Num(); i++) {
				DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
			}
			if (game == BAYONETTA2) {
				CArrayList<bayoDatFile_t *> newTexFiles;
				for (int i = 0; i < texFiles.Num(); i += 2) {
					CArrayList<bayoDatFile_t *> newTexFiles;
					newTexFiles.Append(texFiles[i]);
					newTexFiles.Append(texFiles[i + 1]);
					Model_Bayo_LoadTextures<big, game>(textures, newTexFiles, rapi);
				}
			}
			else {
				Model_Bayo_LoadTextures<big, game>(textures, texFiles, rapi);
			}
		}
	}
	else {
		for (int i = 0; i < givenTextures.Num(); i++) {
			textures.Append(givenTextures[i]);
		}
	}


	Model_Bayo_LoadMaterials<big, game>(hdr, textures, hasExMatInfo, matList, matListLightMap, totMatList, data, rapi, sharedtextureoffset);
	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetOption(RPGOPT_BIGENDIAN, big);
	rapi->rpgSetOption(RPGOPT_TRIWINDBACKWARD, true);

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_Bayo_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

	Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
	Model_Bayo_GetEXPFile(dfiles, df, rapi, expfile);
	if (bones) {
		Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBoneDataA);
		Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT, data + hdr.ofsBoneDataA);
	}

	Model_Bayo_SetBuffers<big, game>(df, rapi, hdr, buffers, pretransform);

	BYTE *meshStart = data + hdr.ofsMeshes;
	int *meshOfsList = (int *)(data + hdr.ofsMeshOfs);
	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	for (int i = 0; i < hdr.numMeshes; i++)
	{
		//if (i != 0) continue;
		int meshOfs = meshOfsList[i];
		if (big) LITTLE_BIG_SWAP(meshOfs);
		wmbMesh<big> mesh((wmbMesh_t *)(meshStart + meshOfs));
		DBGLOG("\t%3d: id: %d, offset: %x, name: %s\n", i, mesh.id, hdr.ofsMeshes + meshOfs, mesh.name);
		int *batchOfsList = (int *)(meshStart + meshOfs + mesh.batchOfs);
		for (int j = 0; j < mesh.numBatch; j++)
		{
			char batch_name[256];
			DBGLOG("\t\t%3d: ", j);
			int batchOfs = batchOfsList[j];
			if (big) LITTLE_BIG_SWAP(batchOfs);
			BYTE *batchData = (BYTE *)batchOfsList + batchOfs;
			wmbBatch<big> batch((wmbBatch_t *)batchData);
			DBGLOG("%d, %x, %x, %x, %x, %x, ", batch.id, batch.unknownB, batch.unknownC, batch.unknownDB, batch.unknownE1, batch.unknownE2);
			bool bShadow;
			if ((game == BAYONETTA && batch.unknownE1 == 0x20 && batch.unknownE2 == 0x0f) || (game == BAYONETTA2 && batch.unknownE1 == 0x30)) {
				sprintf_s(batch_name, 256, "%02d(%s)_%02d_s", i, mesh.name, j);
				bShadow = true;
			}
			else {
				sprintf_s(batch_name, 256, "%02d(%s)_%02d", i, mesh.name, j);
				bShadow = false;
			}
			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			/*if (batch.unknownE == 0xf20) {
				DBGLOG("skipped (shadow model)\n");
				continue; // shadow meshes
			}*/
			int numBoneRefs = *((int *)(batchData + sizeof(wmbBatch_t)));
			if (big) LITTLE_BIG_SWAP(numBoneRefs);
			int *boneRefDst = NULL;
			if (numBoneRefs > 0 && bones && buffers.bone_indexes.address)
			{ //set up reference map
				BYTE *boneRefs = batchData + sizeof(wmbBatch_t) + sizeof(int);
				boneRefDst = (int *)rapi->Noesis_UnpooledAlloc(sizeof(int)*numBoneRefs);
				for (int k = 0; k < numBoneRefs; k++)
				{
					boneRefDst[k] = boneRefs[k];
				}
			}
			rapi->rpgSetBoneMap(boneRefDst);
			int vertOfs = batch.vertOfs;
			DBGLOG("vertAddr: %p, ", buffers.position.address + vertOfs * buffers.position.stride);
			//bind positions
			rapi->rpgBindPositionBuffer(buffers.position.address + vertOfs * buffers.position.stride, buffers.position.type, buffers.position.stride);
			//bind normals
			rapi->rpgBindNormalBuffer(buffers.normal.address + vertOfs * buffers.normal.stride, buffers.normal.type, buffers.normal.stride);
			//bind tangents
			if (false && batch.primType == 4) {
				DBGLOG("\n");
				modelTan4_t	*tangents = rapi->rpgCalcTangents(batch.vertEnd - vertOfs, batch.numIndices, batchData + batch.ofsIndices,
					RPGEODATA_USHORT, sizeof(unsigned short) * (batch.primType == 4 ? 3 : 1),
					buffers.position.address + vertOfs * buffers.position.stride, buffers.position.type, buffers.position.stride,
					buffers.normal.address + vertOfs * buffers.normal.stride, buffers.normal.type, buffers.normal.stride,
					buffers.mapping.address + vertOfs * buffers.mapping.stride, buffers.mapping.type, buffers.mapping.stride,
					NULL, true);
				rapi->rpgBindTangentBuffer(tangents, RPGEODATA_FLOAT, 16);
				for (int k = batch.vertStart - batch.vertOfs; k < batch.vertEnd - batch.vertOfs; k++) {
					modelTan4_t * ta = (modelTan4_t *)(buffers.tangents.address + vertOfs * buffers.tangents.stride);
					modelVert_t * n = (modelVert_t *)(buffers.normal.address + vertOfs * buffers.normal.stride);
					DBGLOG("%d no: %f %f %f\n", k, n[k].x, n[k].y, n[k].z);
					DBGLOG("%d gt: %f %f %f %f\n", k, ta[k].v[0], ta[k].v[1], ta[k].v[2], ta[k].v[3]);
					DBGLOG("%d nt: %f %f %f %f\n", k, tangents[k].v[0], tangents[k].v[1], tangents[k].v[2], tangents[k].v[3]);
					DBGLOG("%d  d: %f %f %f %f\n", k, abs(ta[k].v[0] - tangents[k].v[0]), abs(ta[k].v[1] - tangents[k].v[1]), abs(ta[k].v[2] - tangents[k].v[2]), abs(ta[k].v[3] - tangents[k].v[3]));
					modelVert_t bt;
					g_mfn->Math_CrossProduct((float*)&n[k], ta[k].v, (float *)&bt);
					g_mfn->Math_VecScale((float *)&bt, ta[k].v[3]);
					DBGLOG("%d gb: %f %f %f\n", k, bt.x, bt.y, bt.z);
					g_mfn->Math_CrossProduct((float*)&n[k], tangents[k].v, (float *)&bt);
					g_mfn->Math_VecScale((float *)&bt, tangents[k].v[3]);
					DBGLOG("%d nb: %f %f %f\n", k, bt.x, bt.y, bt.z);
				}
			}
			//rapi->rpgBindTangentBuffer(buffers.tangents.address + vertOfs * buffers.tangents.stride, buffers.tangents.type, buffers.tangents.stride);
			//bind uv's
			rapi->rpgBindUV1Buffer(buffers.mapping.address + vertOfs * buffers.mapping.stride, buffers.mapping.type, buffers.mapping.stride);
			if (buffers.mapping2.address) {
				rapi->rpgBindUV2Buffer(buffers.mapping2.address + vertOfs * buffers.mapping2.stride, buffers.mapping2.type, buffers.mapping2.stride);
				DBGLOG("binding UV2, ");
			}
			else {
				rapi->rpgBindUV2Buffer(NULL, RPGEODATA_HALFFLOAT, 0);
			}
			if (bones && buffers.bone_indexes.address)
			{ //bind weight data
				rapi->rpgBindBoneIndexBuffer(buffers.bone_indexes.address + vertOfs * buffers.bone_indexes.stride, buffers.bone_indexes.type, buffers.bone_indexes.stride, 4);
				rapi->rpgBindBoneWeightBuffer(buffers.bone_weights.address + vertOfs * buffers.bone_weights.stride, buffers.bone_weights.type, buffers.bone_weights.stride, 4);
			}

			int texID = (hasExMatInfo) ? batch.unknownC : batch.texID;
			char *matName = (texID < matList.Num()) ? matList[texID]->name : NULL;
			//bind color if needed for multipass materials for now
			if (matName && buffers.color.address && (matList[texID]->ex->userTag[0] & BAYONETTA_MULTIPASS)) {
				rapi->rpgBindColorBuffer(buffers.color.address + vertOfs * buffers.color.stride, buffers.color.type, buffers.color.stride, 4);
			}
			else {
				rapi->rpgBindColorBuffer(NULL, RPGEODATA_BYTE, 0, 0);
			}
			DBGLOG("matName: %s\n", matName);
			rapi->rpgSetMaterial(matName);
			if (texID < matList.Num() && matList[texID]->ex->pUvScaleBias) {
				rapi->rpgSetUVScaleBias(matList[texID]->ex->pUvScaleBias, matList[texID]->ex->pUvScaleBias + 2);
			}
			else {
				rapi->rpgSetUVScaleBias(NULL, NULL);
			}
			DBGLOG("primType: %d, numIndices: %d\n", batch.primType, batch.numIndices);
			rpgeoPrimType_e primType = (batch.primType == 4) ? RPGEO_TRIANGLE : RPGEO_TRIANGLE_STRIP;
			rapi->rpgCommitTriangles(batchData + batch.ofsIndices, RPGEODATA_USHORT, batch.numIndices, primType, true);
			//rapi->rpgSmoothTangents(NULL);
			if (boneRefDst)
			{ //reference map is no longer needed once triangles have been committed
				rapi->rpgSetBoneMap(NULL);
				rapi->Noesis_UnpooledFree(boneRefDst);
			}
		}
	}

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(totMatList, textures);
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
	//sharedModel_t *shMdl = rapi->rpgGetSharedModel(mdl, 0);
	//for (int i = 0; i < shMdl->numMeshes; i++) {
	//	shMdl->meshes[i].
	//}

	rapi->rpgDestroyContext(pgctx);

	animList.Clear();
	matList.Clear();
	motfiles.Clear();
	texFiles.Clear();
	textures.Clear();
	matListLightMap.Clear();
	totMatList.Clear();
}

static void Model_Bayo_CreatePreTransformMatrix(float * transform, modelMatrix_t &m) {
	float translate[3];
	float rotate[3];
	float scale[3];
	//int rotate_order[3] = {2,1,0};
	float rotate_coeff[3] = { -1.0, 1.0, -1.0 };
	float translate_coeff[3] = { 1.0, 1.0, 1.0 };
	float scale_coeff[3] = { 1.0, 1.0, 1.0 };

	m = g_identityMatrix;

	for (int i = 0; i < 3; i++) {
		translate[i] = translate_coeff[i] * transform[i];
	}
	for (int i = 3, j = 0; i < 6; i++, j++) {
		rotate[j] = rotate_coeff[j] * transform[i] * g_flRadToDeg;
	}
	for (int i = 6, j = 0; i < 9; i++, j++) {
		scale[j] = scale_coeff[j] * transform[i];
	}

	DBGALOG("\tpre translate: %f, %f, %f\n", translate[0], translate[1], translate[2]);
	g_mfn->Math_TranslateMatrix(&m, translate);

	DBGALOG("\tpre rotate: %f, %f, %f\n", rotate[0], rotate[1], rotate[2]);

	g_mfn->Math_RotateMatrix(&m, rotate[2], 0.0f, 0.0f, 1.0f);
	g_mfn->Math_RotateMatrix(&m, rotate[1], 0.0f, 1.0f, 0.0f);
	g_mfn->Math_RotateMatrix(&m, rotate[0], 1.0f, 0.0f, 0.0f);

	DBGALOG("\tpre scale: %f, %f, %f\n", scale[0], scale[1], scale[2]);
	for (int i = 0; i < 3; i++) {
		m.x1[i] *= scale[i];
		m.x2[i] *= scale[i];
		m.x3[i] *= scale[i];
	}
}

template <bool big, game_t game>
static void Model_Bayo_LoadScenery(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models);

template <bool big, game_t game>
static void Model_Bayo_LoadMotions(CArrayList<noesisAnim_t *> &animList, CArrayList<bayoDatFile_t *> &motfiles, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT, void * extraBoneInfo);

template <bool big>
static void Model_Bayo_LoadSceneryBayo1(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	DBGLOG("Loading %s\n", df.name);
	bayoSCRHdr<big> hdr((bayoSCRHdr_t *)df.data);
	if (memcmp(hdr.id, "SCR\0", 4))
	{ //invalid header
		DBGLOG("Invalid SCR file\n");
		return;
	}
	bayoDatFile_t textureFile;
	textureFile.name = rapi->Noesis_PooledString("dummy.wtb");
	textureFile.data = df.data + hdr.ofsTextures;
	textureFile.dataSize = df.dataSize - hdr.ofsTextures;
	CArrayList<bayoDatFile_t> dfiles;
	CArrayList<bayoDatFile_t *> texfiles;
	texfiles.Append(&textureFile);
	CArrayList<noesisTex_t *> textures;
	int sharedtexturesoffset = -1;
	Model_Bayo_LoadTextures<big, BAYONETTA>(textures, texfiles, rapi);
	sharedtexturesoffset = textures.Num();
	char scrName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(scrName, df.name);
	Model_Bayo_LoadSharedTextures<big, BAYONETTA>(textures, scrName, rapi);
	DBGLOG("found %d models in %s\n", hdr.numModels, df.name);
	for (int i = 0; i < hdr.numModels; i++) {
		bayoDatFile_t modelFile;
		int dscrOffset = sizeof(bayoSCRHdr_t) + i * sizeof(bayoSCRModelDscr_t);
		DBGLOG("offset: %x\n", dscrOffset);
		bayoSCRModelDscr<big> modelDscr((bayoSCRModelDscr_t *)(df.data + dscrOffset));
		char modelName[21];
		char fileName[21];
		memset(modelName, 0, 21);
		for (int j = 0; j < 16; j++) {
			modelName[j] = modelDscr.name[j];
		}
		snprintf(fileName, 21, "%s.wmb", modelName);
		DBGLOG("%d - %d: model name: %s, ", i, models.Num(), fileName);
		modelFile.name = rapi->Noesis_PooledString(fileName);
		modelFile.data = df.data + dscrOffset + modelDscr.offset;
		if (i < (hdr.numModels - 1)) {
			int nextDscrOffset = sizeof(bayoSCRHdr_t) + (i + 1) * sizeof(bayoSCRModelDscr_t);
			bayoSCRModelDscr<big> nextModelDscr((bayoSCRModelDscr_t *)(df.data + nextDscrOffset));
			modelFile.dataSize = (nextDscrOffset + nextModelDscr.offset) - (dscrOffset + modelDscr.offset);
		}
		else {
			modelFile.dataSize = hdr.ofsTextures - (dscrOffset + modelDscr.offset);
		}
		DBGLOG("start: %d, size: %d\n", dscrOffset + modelDscr.offset, modelFile.dataSize);
		modelMatrix_t m;
		Model_Bayo_CreatePreTransformMatrix(modelDscr.transform, m);
		Model_Bayo_LoadModel<big, BAYONETTA>(dfiles, modelFile, rapi, models, textures, &m, sharedtexturesoffset);
	}
	rapi->SetPreviewOption("drawAllModels", "1");
}
template <>
static void Model_Bayo_LoadScenery<false, BAYONETTA>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	Model_Bayo_LoadSceneryBayo1<false>(olddfiles, df, rapi, models);
}
template <>
static void Model_Bayo_LoadScenery<true, BAYONETTA>(CArrayList<bayoDatFile_t> &olddfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models) {
	Model_Bayo_LoadSceneryBayo1<true>(olddfiles, df, rapi, models);
}

//load it
template <bool big, game_t game>
noesisModel_t *Model_Bayo_Load(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	CArrayList<bayoDatFile_t> dfiles;

	int version = g_nfn->NPAPI_GetAPIVersion();
	if (version < 74) {
		DBGLOG("Outdated Noesis\n");
		g_nfn->NPAPI_MessagePrompt(L"Please update Noesis!");
		return NULL;
	}
	DBGLOG("Loading model\n");
	//create a list of resources
	Model_Bayo_GetDATEntries<big>(dfiles, fileBuffer, bufferLen);
	//for Vanquish, Transformer Devastation or Astral Chain, append any matching dtt files (they're just paired dat files)
	char *inFile = rapi->Noesis_GetInputName();
	BYTE *dttFile = NULL;
	if (inFile && inFile[0] && game != NIER_AUTOMATA)
	{
		char fn[MAX_NOESIS_PATH];
		rapi->Noesis_GetExtensionlessName(fn, inFile);
		strcat_s(fn, MAX_NOESIS_PATH, ".dtt");
		int dttLen = 0;
		dttFile = (BYTE *)rapi->Noesis_ReadFile(fn, &dttLen);
		if (dttFile && dttLen > 0)
		{
			Model_Bayo_GetDATEntries<big>(dfiles, dttFile, dttLen);
		}
	}
	//for Nier, append any matching dat files (they're just paired dtt files) :)
	if (inFile && inFile[0] && game == NIER_AUTOMATA)
	{
		char fn[MAX_NOESIS_PATH];
		rapi->Noesis_GetExtensionlessName(fn, inFile);
		strcat_s(fn, MAX_NOESIS_PATH, ".dat");
		int dttLen = 0;
		dttFile = (BYTE *)rapi->Noesis_ReadFile(fn, &dttLen);
		if (dttFile && dttLen > 0)
		{
			Model_Bayo_GetDATEntries<big>(dfiles, dttFile, dttLen);
		}
	}
	CArrayList<noesisModel_t *> models;
	DBGLOG("Have %d files\n", dfiles.Num());
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &df = dfiles[i];
		if (rapi->Noesis_CheckFileExt(df.name, ".wmb"))
		{ //it's a model
			CArrayList<noesisTex_t *> textures;
			Model_Bayo_LoadModel<big, game>(dfiles, df, rapi, models, textures, NULL);
		}
		else if (rapi->Noesis_CheckFileExt(df.name, ".scr"))
		{ //it's a scenery
			Model_Bayo_LoadScenery<big, game>(dfiles, df, rapi, models);
		}
	}
	DBGFLUSH();
	if (models.Num() <= 0)
	{
		return NULL;
	}
	noesisModel_t *mdlList = rapi->Noesis_ModelsFromList(models, numMdl);
	models.Clear();
	if (dttFile)
	{ //free the dtt file memory
		rapi->Noesis_UnpooledFree(dttFile);
	}
	return mdlList;
}