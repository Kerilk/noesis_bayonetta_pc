//this is kind of a poor example for plugins, since the format's not totally known and the code is WIP.
//but it does showcase some interesting usages.


#include "stdafx.h"
#undef max
#undef min
#include "half.hpp"
using half_float::half;

const char *g_pPluginName = "bayonetta_pc";
const char *g_pPluginDesc = "Bayonetta PC model handler, by Dick, Kerilk.";

FILE *bayo_log;
#ifdef _DEBUG
#define DBGLOG(fmt, ...) fprintf(bayo_log, fmt, __VA_ARGS__)
#define OPENLOG() (bayo_log = fopen("bayo.log", "w"))
#define CLOSELOG() fclose(bayo_log)
#define DBGFLUSH() fflush(bayo_log)
#else
#define DBGLOG(fmt, ...) do { if (0) fprintf(bayo_log, fmt, __VA_ARGS__); } while (0)
#define OPENLOG() do { if (0) bayo_log = fopen("bayo.log", "w+"); } while (0)
#define CLOSELOG() do { if (0) fclose(bayo_log); } while (0)
#define DBGFLUSH() do { if (0) fflush(bayo_log); } while (0)
#endif

#define DBG_ANIM_DATA 0
#if DBG_ANIM_DATA
#define DBGALOG(fmt, ...) DBGLOG(fmt, __VA_ARGS__)
#else
#define DBGALOG(fmt, ...) do { if (0) DBGLOG(fmt, __VA_ARGS__); } while (0)
#endif

typedef struct bayoDat_s
{
	BYTE			id[4];
	int				numRes;
	int				ofsRes;
	int				ofsType;
	int				ofsNames;
	int				ofsSizes;
} bayoDat_t;
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
	int					resva;
	int					resvb;
} bayoWTBHdr_t;

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
typedef struct bayoWMBHdr_s
{
	BYTE				id[4];				// 0
	int					unknownA;			// 4
	WORD				unknownB;			// 8
	WORD				unknownC;			// A
	int					numVerts;			// C
	WORD				unknownD;			//10
	WORD				unknownE;			//12
	int					unknownF;			//14
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
	int					ofsUnknownK;		//68
	int					ofsUnknownL;		//6C
	int					exMatInfo[4];		//70
} bayoWMBHdr_t;
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
typedef struct wmbBatch_s
{
	int					id;
	WORD				unknownB;
	WORD				unknownC;
	BYTE				texID;
	BYTE				unknownDB;
	WORD				unknownE;
	int					vertStart;
	int					vertEnd;
	int					primType;
	int					ofsIndices;
	int					numIndices;
	int					vertOfs;
	int					unknownI[7];
} wmbBatch_t;
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
typedef struct bayoMOTHdr_s
{
	BYTE				id[4];
	short int			unknownA;
	short int			frameCount;
	int					ofsMotion;
	int					numEntries;
} bayoMOTHdr_t;
typedef union bayoMotField_u
{
	float flt;
	int offset;
} bayoMotField_t;
typedef struct bayoMotItem_s
{
	short int			boneIndex;
	char				index;
	BYTE				flag;
	short int			elem_number;
	short int			unknown;
	bayoMotField_t		value;
} bayoMotItem_t;
typedef struct bayoInterpolHeader4_s {
	float values[6];
} bayoInterpolHeader4_t;
typedef struct bayoInterpolKeyframe4_s {
	unsigned short int index;
	unsigned short int coeffs[3];
} bayoInterpolKeyframe4_t;
typedef short unsigned int pghalf;
typedef struct bayoInterpolHeader6_s {
	pghalf values[6];
} bayoInterpolHeader6_t;
typedef struct bayoInterpolKeyframe6_s {
	BYTE index;
	BYTE coeffs[3];
} bayoInterpolKeyframe6_t;
typedef struct bayoInterpolHeader7_s {
	pghalf values[6];
} bayoInterpolHeader7_t;
typedef struct bayoInterpolKeyframe7_s {
	unsigned short int index;
	BYTE dummy;
	BYTE coeffs[3];
} bayoInterpolKeyframe7_t;
typedef struct bayoVertexData_s {
	float position[3];			//00
	short uv[2];				//0C //half float really
	char normals[4];			//0F
	int unknwownA;				//14
	unsigned char boneIndex[4];	//18
	unsigned char boneWeight[4];//1C
} bayoVertexData_t;
typedef struct bayoMatType_s {
	bool known;
	short size;
	char texture_number;
	char lightmap_index;
	char normalmap_index;
	char texture2_index;
	char reflection_index;
} bayoMatType_t;

bayoMatType_t bayoMatTypes[256];

//thanks Phernost (stackoverflow)
class FloatDecompressor
{
	union Bits
	{
		float f;
		int si;
		unsigned int ui;
	};

	static int const significandFBits = 23;
	static int const exponentFBits = 8;
	static int const biasF = 127;
	static int const exponentF    = 0x7F800000;
	static int const significandF = 0x007fffff;
	static int const signF        = 0x80000000;

	int const significandHBits;
	int const exponentHBits;
	int const biasH;
    int exponentH;
	int significandH;
    static int const signH        = 0x8000;

	int shiftSign;
	int shiftBits;

public:

	FloatDecompressor(int eHBits, int sHBits, int bH): exponentHBits(eHBits), significandHBits(sHBits), biasH(bH) {
		int tmp = 0;
		for(int i = 0; i < eHBits; i++) {
			tmp <<= 1;
			tmp += 1;
		}
		tmp <<= sHBits;
		exponentH = tmp;

		tmp = 0;
		for(int i = 0; i < sHBits; i++) {
			tmp <<= 1;
			tmp += 1;
		}
		significandH = tmp;
		shiftSign = significandFBits + exponentFBits - significandHBits - exponentHBits;
		shiftBits = significandFBits - significandHBits;
	}

	float decompress(short unsigned int value)
	{
		Bits v;
		v.ui = value;
		int sign = v.si & signH;
		v.si ^= sign;

		sign <<=  shiftSign;
		int exponent = v.si & exponentH;
		int significand = v.si ^ exponent;
		significand <<= shiftBits;

        v.si = sign | significand;
		if( exponent == exponentH ) {
			v.si |= exponentF;
		} else if ( exponent != 0 ) {
			exponent >>= significandHBits;
			exponent += biasF - biasH;
			exponent <<= significandFBits;
			v.si |= exponent;
		}
		return v.f;
	}
};


static void bayoSetMatType(bayoMatType_t &mat,
						   short size,
						   char texture_number,
						   char lightmap_index,
						   char normalmap_index,
						   char texture2_index,
						   char reflection_index) {
	mat.known = true;
	mat.size = size;
	mat.texture_number = texture_number;
	mat.lightmap_index = lightmap_index;
	mat.normalmap_index = normalmap_index;
	mat.texture2_index = texture2_index;
	mat.reflection_index = reflection_index;
}
static void bayoUnsetMatType(bayoMatType_t &mat) {
	mat.known = false;
	mat.size = 0;
	mat.texture_number = 1;
	mat.lightmap_index = -1;
	mat.normalmap_index = -1;
	mat.texture2_index = -1;
	mat.reflection_index = -1;
}
static void bayoSetMatTypes(void) {
	for(int i=0; i<256; i++) {
		bayoUnsetMatType(bayoMatTypes[i]);
	}
	bayoSetMatType(bayoMatTypes[0x31], 0xC0, 3,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x32], 0xE4, 4,  1, -1, -1,  3);
	bayoSetMatType(bayoMatTypes[0x33], 0xD4, 4,  2, -1,  1, -1);
	bayoSetMatType(bayoMatTypes[0x34], 0xF8, 5,  2, -1,  1,  4);
	bayoSetMatType(bayoMatTypes[0x38], 0xD4, 4, -1,  2, -1, -1);
	bayoSetMatType(bayoMatTypes[0x3A], 0xD4, 4,  1,  2, -1, -1);
	bayoSetMatType(bayoMatTypes[0x3C], 0xD4, 4, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x40], 0xC4, 4, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x42], 0xAC, 2, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x44], 0xE4, 4,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x47], 0x68, 1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x48], 0xC0, 3,  1, -1,  2, -1);
	bayoSetMatType(bayoMatTypes[0x4A], 0xD4, 4,  2, -1,  1, -1);
	bayoSetMatType(bayoMatTypes[0x4B], 0xD4, 4, -1,  2, -1, -1);
	bayoSetMatType(bayoMatTypes[0x4C], 0xAC, 2, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x53], 0x68, 1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x54], 0xD4, 4,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x59], 0xD4, 4,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x60], 0x68, 1, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x68], 0xAC, 2, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x6B], 0xD0, 3, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x6D], 0xD0, 3, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x6E], 0xD4, 4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x71], 0xE4, 4,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x72], 0xD4, 4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x75], 0xAC, 2, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x7C], 0xEA, 4,  1, -1, -1,  3);
	bayoSetMatType(bayoMatTypes[0x7F], 0x124,4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x81], 0x120,3, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x83], 0xAC, 2, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x87], 0xD4, 4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0x89], 0xC0, 3,  1, -1, -1,  2);
	bayoSetMatType(bayoMatTypes[0x8F], 0xD4, 4,  1, -1,  2,  3);
	bayoSetMatType(bayoMatTypes[0x97], 0x114,4, -1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xA1], 0xB0, 3,  1, -1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xA3], 0xE4, 4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xB2], 0xD4, 4, -1,  1, -1, -1);
	bayoSetMatType(bayoMatTypes[0xB3], 0x124,4, -1,  1, -1, -1);

}


//see if something is a valid bayonetta .dat
bool Model_Bayo_Check(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi)
{
	DBGLOG("----------------------\n");
	if (bufferLen < sizeof(bayoDat_t))
	{
		return false;
	}
	bayoDat_t dat = *((bayoDat_t *)fileBuffer);
	if (memcmp(dat.id, "DAT\0", 4))
	{
		return false;
	}
	if (dat.numRes <= 0 ||
		dat.ofsRes <= 0 || dat.ofsRes >= bufferLen ||
		dat.ofsType <= 0 || dat.ofsType >= bufferLen ||
		dat.ofsNames <= 0 || dat.ofsNames >= (bufferLen-4) ||
		dat.ofsSizes <= 0 || dat.ofsSizes >= bufferLen)
	{
		return false;
	}

	BYTE *namesp = fileBuffer+dat.ofsNames;
	int strSize = *((int *)namesp);
	namesp += sizeof(int);
	if (strSize <= 0 || strSize >= bufferLen || dat.ofsNames+(int)sizeof(int)+(strSize*dat.numRes) > bufferLen)
	{
		return false;
	}
	int numWMB = 0;
	int numMOT = 0;
	DBGLOG("Found %d resources\n", dat.numRes);
	for (int i = 0; i < dat.numRes; i++)
	{
		char *name = (char *)namesp;
		if (name[strSize-1])
		{ //incorrectly terminated string
			return false;
		}
		DBGLOG("\t%s\n", name);
		if (rapi->Noesis_CheckFileExt(name, ".wmb"))
		{
			numWMB++;
		}
		//todo - figure out and add support for animation data
		/*
		else if (rapi->Noesis_CheckFileExt(name, ".mot"))
		{
			numMOT++;
		}
		*/
		namesp += strSize;
	}
	if (numWMB <= 0 && numMOT <= 0)
	{ //nothing of interest in here
		return false;
	}
	DBGLOG("Found %d wmb files\n", numWMB);
	return true;
}

//get a texture bundle file for a specific model
static bayoDatFile_t *Model_Bayo_GetTextureBundle(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, ".wtb");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			return &dft;
		}
	}
	return NULL;
}
// get motion files
static void Model_Bayo_GetMotionFiles(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<bayoDatFile_t *> &motfiles)
{
	char motName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(motName, df.name);
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
//load texture bundle
static void Model_Bayo_LoadTextures(CArrayList<noesisTex_t *> &textures, BYTE *data, int dataSize, noeRAPI_t *rapi)
{
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr_t hdr = *((bayoWTBHdr_t *)data);
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
	int *tofs = (int *)(data+hdr.ofsTexOfs);
	int *tsizes = (int *)(data+hdr.ofsTexSizes);
	int *tflags = (int *)(data+hdr.ofsTexFlags);
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
		BYTE *texData = data+ofs;
		BYTE *pix;
		int globalIdx = -1;
		ddsTexHdr_t tex;
		if (hdr.resva)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data+hdr.resva+sizeof(int)*i);
			globalIdx = *ip;
		}
		if (hdr.resvb)
		{ //texture info is contiguous in its own section
			ddsTexHdr_t *thdr = (ddsTexHdr_t  *)(data+hdr.resvb+sizeof(ddsTexHdr_t)*i);
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
		DBGLOG("\t%03d (idx %d, flags %x): ", i, globalIdx, tflags[i]);
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
		} else if (tex.pixelFormat.flags & 0x41) {
			DBGLOG("RGBA\n");
			dxtFmt = NOESISTEX_RGBA32;
			uncompressed = true;
			channelSwiz = true;
		} else {
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
				for (int i = 0; i < mipSize-swapCount; i += swapCount)
				{
					LittleBigSwap(untiledMip+i, swapCount);
				}
			}
			if (channelSwiz)
			{
				int swapCount = 4;
				for (int i = 0; i < mipSize-swapCount; i += swapCount)
				{
					BYTE *p = untiledMip+i;
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
			mipSize = (dxtFmt == NOESISTEX_DXT1) ? (width*height)/2 : (width*height);
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
				for (int j = 0; j < mipSize-swapCount; j += swapCount)
				{
					LittleBigSwap(untiledMip+j, swapCount);
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

//decode motion index (simpler thanks to Alquazar(zenhax))
static inline short int Model_Bayo_DecodeMotionIndex(const short int *table, const short int boneIndex) {
	short int index = table[(boneIndex >> 8) & 0xf];
	if ( index != -1 ) {
		index = table[((boneIndex >> 4) & 0xf) + index];
		if ( index != -1 ) {
			index = table[(boneIndex & 0xf) + index];
			return index;
		}
	}
	return 0x0fff;
}
//initialize motion matrix
static void Model_Bayo_InitMotions(modelMatrix_t * &matrixes, float * &tmpValues, modelBone_t *bones, const int boneNumber, const int maxCoeffs, const short int frameCount, noeRAPI_t *rapi) {

	matrixes = (modelMatrix_t *)rapi->Noesis_UnpooledAlloc(sizeof(modelMatrix_t) * boneNumber * frameCount);
	tmpValues = (float *)rapi->Noesis_UnpooledAlloc(sizeof(float) * boneNumber * frameCount * maxCoeffs);
    memset(tmpValues, 0, sizeof(float) * boneNumber * frameCount * maxCoeffs);

	for(int i = 0; i < boneNumber; i++) {
		float translate[3] = {0.0,0.0,0.0};
		if(bones[i].eData.parent) {

			g_mfn->Math_VecSub(bones[i].mat.o, bones[i].eData.parent->mat.o, translate);
			//g_mfn->Math_TranslateMatrix(&matrixes[i + j*bone_number], translate);
		}
		for( int j = 0; j < frameCount; j++) {
			matrixes[i + j*boneNumber] = g_identityMatrix;
			for( int k = 0; k < 3; k++) {
				tmpValues[j + k * frameCount + i *  frameCount * maxCoeffs] = translate[k];
			}
			//g_mfn->Math_TranslateMatrix(&matrixes[i + j*bone_number], bones[i].mat.o);
			//float zero[3] = {0.0f, 0.0f, 0.0f};
			//g_mfn->Math_RotationMatrix(0.0, 0, &matrixes[i + j*bone_number]);
		}
	}
}
//apply rotate/translate to model matrix
static void Model_Bayo_ApplyMotions(modelMatrix_t * matrixes, float * tmpValues, modelBone_t *bones, const int boneNumber, const int maxCoeffs, const short int frameCount) {
	DBGALOG("-------------------------------\n");
	for(int bi = 0; bi < boneNumber; bi++) {
		DBGALOG("bone %d (%d)", bi, bones[bi].index);
		DBGALOG(" parent %d\n", bones[bi].eData.parent ? bones[bi].eData.parent->index : -1);
		//DBGLOG("\ttranslate: %f, %f, %f\n", bones[bi].mat.o[0], bones[bi].mat.o[1], bones[bi].mat.o[2]);
		DBGALOG("\trelative: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));
	}
	DBGALOG("-------------------------------\n");
	for(int bi = 0; bi < boneNumber; bi++) {
		DBGALOG("bone %d\n", bi);

		for( int fi = 0; fi < frameCount; fi++) {
			DBGALOG("\tframe %d\n", fi);
			modelMatrix_t tmp_mat;
			modelMatrix_t tmp_mat2;
			float translate[3] = {0.0, 0.0, 0.0};
			float rotate[3] = {0.0, 0.0, 0.0};
			int rotate_order[3] = {1,2,0};
			float rotate_coeff[3] = {1.0, -1.0, 1.0};
			float translate_coeff[3] = {1.0, 1.0, 1.0};

			for( int i = 0; i < 3; i++) {
				translate[i] = translate_coeff[i] * tmpValues[fi + i * frameCount + bi *  frameCount * maxCoeffs];
			}
			for( int i = 0; i < 3; i++) {
				rotate[i] = rotate_coeff[i] * tmpValues[fi + (3 + i) * frameCount + bi *  frameCount * maxCoeffs];
			}
			DBGALOG("\t\ttranslate: %f, %f, %f\n", translate[0], translate[1], translate[2]);
			DBGALOG("\t\tref relative: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));
			DBGALOG("\t\trotate: %f, %f, %f\n", rotate[0], rotate[1], rotate[2]);

			g_mfn->Math_TranslateMatrix(&matrixes[bi + boneNumber * fi], translate);

			for( int i = 0; i < 3; i++) {
				g_mfn->Math_RotationMatrix(rotate[rotate_order[i]], rotate_order[i], &tmp_mat);
				g_mfn->Math_MatrixMultiply(&matrixes[bi + boneNumber * fi], &tmp_mat, &tmp_mat2);
				matrixes[bi + boneNumber * fi] = tmp_mat2;
			}
		}
	}
}
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader4_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = h->values[j];
	}
}
static FloatDecompressor C(6, 9, 47);
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader6_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j]);
	}
}
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader7_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j]);
	}
}
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe4_t *p_v, bayoInterpolKeyframe4_t *v) {
	firstFrame = p_v->index;
    lastFrame = v->index;
}
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int frameCount, bayoInterpolKeyframe6_t *p_v, bayoInterpolKeyframe6_t *v) {
	firstFrame = frameCount - 1;
	lastFrame = frameCount - 1 + v->index;
}
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe7_t *p_v, bayoInterpolKeyframe7_t *v) {
	firstFrame = p_v->index;
    lastFrame = v->index;
}
template <class T>
static void Model_Bayo_HermitInterpolate(float * tmpValues, float *fvals, const T *p_v, const T *v, short int &frameCount, const short int first_frame, const short int last_frame) {
	float p0, p1, m0, m1;
	p0 = fvals[0] + fvals[1] * p_v->coeffs[0];
	p1 = fvals[0] + fvals[1] * v->coeffs[0];
	m0 = fvals[4] + fvals[5] * p_v->coeffs[2];
	m1 = fvals[2] + fvals[3] * v->coeffs[1];

	for(; frameCount <= last_frame; frameCount++) {
		float t;
		t = (float)(frameCount - first_frame)/(last_frame - first_frame);
		tmpValues[frameCount] = (2*t*t*t - 3*t*t + 1)*p0 + (t*t*t - 2*t*t + t)*m0 + (-2*t*t*t + 3*t*t)*p1 + (t*t*t - t*t)*m1;
		DBGALOG("%f, %d, %f\n\t", t, frameCount, tmpValues[frameCount]);
	}
	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", v->index, v->coeffs[0], v->coeffs[1], v->coeffs[2],
			fvals[0] + fvals[1] * v->coeffs[0],
			fvals[2] + fvals[3] * v->coeffs[1],
			fvals[4] + fvals[5] * v->coeffs[2]);
}
//interpolate motion
template <class T1, class T2>
static void Model_Bayo_Interpolate(float * tmpValues, BYTE * data, const short int elemNumber) {
	short int frameCount = 0;
	T1 *h = (T1 *)(data);
	T2 *v = (T2 *)(h+1);
	T2 *p_v;

	float fvals[6];
	Model_Bayo_DecodeInterpolateHeader(fvals, h);
	DBGALOG("\t");
	for(int j = 0; j < 6; j++)
	{
		DBGALOG("%#g ", fvals[j]);
	}
	DBGALOG("\n\t(");
	for(int j = 0; j < sizeof(*h); j++)
	{
		DBGALOG("%02x ", ((BYTE *)h)[j]);
	}
	DBGALOG(")\n\t");

	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", v->index, v->coeffs[0], v->coeffs[1], v->coeffs[2],
			fvals[0] + fvals[1] * v->coeffs[0],
			fvals[2] + fvals[3] * v->coeffs[1],
			fvals[4] + fvals[5] * v->coeffs[2]);

	p_v = v;
	tmpValues[frameCount] = fvals[0] + fvals[1] * v->coeffs[0];
	v++;
	DBGALOG("%f, %d, %f\n\t", 0.0, frameCount, tmpValues[frameCount]);
	frameCount++;

	for(int j = 1; j < elemNumber; j++)
	{
		short int first_frame, last_frame;
		Model_Bayo_DecodeFrameIndex(first_frame, last_frame, frameCount, p_v, v);
		Model_Bayo_HermitInterpolate(tmpValues, fvals, p_v, v, frameCount, first_frame, last_frame);

		p_v = v;
		v++;
	}
	DBGALOG("\n");
}
//loat motion file
static void Model_Bayo_LoadMotions(CArrayList<noesisAnim_t *> &animList, CArrayList<bayoDatFile_t *> &motfiles, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT)
{
  FloatDecompressor C(6, 9, 47);
  for(int mi=0; mi < motfiles.Num(); mi++)
  {
	DBGLOG("Loading %s\n", motfiles[mi]->name);

	BYTE * data     = motfiles[mi]->data;
	size_t dataSize = motfiles[mi]->dataSize;
	if (dataSize < sizeof(bayoMOTHdr_t))
	{
		continue;
	}
	bayoMOTHdr_t hdr = *((bayoMOTHdr_t *)data);
	if (memcmp(hdr.id, "mot\0", 4))
	{ //not a valid motion file
		continue;
	}

	char fname[MAX_NOESIS_PATH];
	sprintf_s(fname, MAX_NOESIS_PATH, "%s", motfiles[mi]->name);

    const int max_coeffs = 10;

	modelMatrix_t * matrixes;
	float * tmp_values;
	Model_Bayo_InitMotions(matrixes, tmp_values, bones, bone_number, max_coeffs, hdr.frameCount, rapi);

	bayoMotItem_t * items = (bayoMotItem_t*)(data + hdr.ofsMotion);
	DBGALOG("unknown flag: 0x%04x, frame count: %d, data offset: 0x%04x, record number: %d\n", hdr.unknownA, hdr.frameCount, hdr.ofsMotion, hdr.numEntries);
	for(int i=0; i < hdr.numEntries; i++) {
		bayoMotItem_t *it = &items[i];
		if( it->boneIndex == 0x7fff || it->boneIndex == -1) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x)\n",it->boneIndex, it->index, it->flag, it->elem_number, it->unknown, it->value.flt, it->value.offset);
			continue;
		} else if ( it->boneIndex >= 0xf60 ) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) special flag 0x2 index\n", it->boneIndex, it->index, it->flag, it->elem_number, it->unknown, it->value.flt, it->value.offset);
		    continue;
		}
		short int boneIndex = Model_Bayo_DecodeMotionIndex(animBoneTT, it->boneIndex);
		if( boneIndex == 0x0fff ) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) cannot translate bone\n", it->boneIndex, it->index, it->flag, it->elem_number, it->unknown, it->value.flt, it->value.offset);
			continue;
		}

		//float tmp_values[65536];
		DBGALOG("%5d (%5d) %3d 0x%02x %3d %3d", boneIndex, it->boneIndex, it->index, it->flag, it->elem_number, it->unknown);
		if ( boneIndex >= bone_number ) {
			DBGALOG(" out of bone bounds\n");
			continue;
		}
		if( it->flag == 1 ) {
			DBGALOG(" 0x%08x\n", it->value.offset);
			float *fdata = (float *)(data + it->value.offset);
			for(int frame_count=0; frame_count < it->elem_number; frame_count++) {
				tmp_values[frame_count + it->index * hdr.frameCount + boneIndex *  hdr.frameCount * max_coeffs] = fdata[frame_count];
				DBGALOG("\t%3d %+f\n", frame_count, fdata[frame_count]);
			}
		} else if( it->flag == 4 ) {
			DBGALOG(" 0x%08x\n", it->value.offset);

			Model_Bayo_Interpolate<bayoInterpolHeader4_t,bayoInterpolKeyframe4_t>(tmp_values + it->index * hdr.frameCount + boneIndex *  hdr.frameCount * max_coeffs,
									data + it->value.offset,
									it->elem_number);

		} else if( it->flag == 6 ) {
			DBGALOG(" 0x%08x\n", it->value.offset);

			Model_Bayo_Interpolate<bayoInterpolHeader6_t,bayoInterpolKeyframe6_t>(tmp_values + it->index * hdr.frameCount + boneIndex *  hdr.frameCount * max_coeffs,
									data + it->value.offset,
									it->elem_number);

		} else if( it->flag == 7 ) { //diff from 6 because frame delta would be > 255
			DBGALOG(" 0x%08x\n", it->value.offset);

			Model_Bayo_Interpolate<bayoInterpolHeader7_t,bayoInterpolKeyframe7_t>(tmp_values + it->index * hdr.frameCount + boneIndex *  hdr.frameCount * max_coeffs,
									data + it->value.offset,
									it->elem_number);

		} else if( it->flag ==  0xff ) {
			DBGALOG(" %+f (0x%08x)\n", it->value.flt, it->value.offset);
			continue;
		} else if ( it->flag != 0 ) {
			DBGALOG(" %+f (0x%08x)\n", it->value.flt, it->value.offset);
			assert(0);
			rapi->LogOutput("WARNING: Unknown motion flag %0x02x.\n", it->flag);
		} else {
			DBGALOG(" %+f\n", it->value.flt);
			for(int j = 0; j < hdr.frameCount; j++) {
				tmp_values[j + it->index * hdr.frameCount + boneIndex *  hdr.frameCount * max_coeffs] = it->value.flt;
			}
		}

	}

	Model_Bayo_ApplyMotions(matrixes, tmp_values, bones, bone_number, max_coeffs, hdr.frameCount);

	noesisAnim_t *anim = rapi->rpgAnimFromBonesAndMatsFinish(bones, bone_number, matrixes, hdr.frameCount, 60);
	anim->filename = rapi->Noesis_PooledString(fname);
	anim->flags |= NANIMFLAG_FILENAMETOSEQ;
	anim->aseq = rapi->Noesis_AnimSequencesAlloc(1, hdr.frameCount);
	anim->aseq->s->startFrame = 0;
	anim->aseq->s->endFrame = hdr.frameCount - 1;
	anim->aseq->s->frameRate = 60;
	anim->aseq->s->name = rapi->Noesis_PooledString(fname);
	if (anim)
	{
		animList.Append(anim);
	}
	rapi->Noesis_UnpooledFree(matrixes);
	rapi->Noesis_UnpooledFree(tmp_values);
  }

}
//decode bayonetta x10y10z10 normals
static void Model_Bayo_CreateNormals(BYTE *data, float *dsts, int numVerts, int stride, bool eet)
{
	for (int i = 0; i < numVerts; i++)
	{
		/*
		BYTE *src = (BYTE *)(data + stride*i);
		float *dst = dsts+i*3;
		DWORD r;
		memcpy(&r, src, sizeof(r));
		int xBits = (eet) ? 11 : 10;
		int yBits = (eet) ? 11 : 10;
		int zBits = 10;
		int x = ((r>>0) & ((1<<xBits)-1));
		int y = ((r>>xBits) & ((1<<yBits)-1));
		int z = ((r>>(xBits+yBits)) & ((1<<zBits)-1));
		dst[0] = (float)SignedBits(x, xBits) / (float)((1<<(xBits-1))-1);
		dst[1] = (float)SignedBits(y, yBits) / (float)((1<<(yBits-1))-1);
		dst[2] = (float)SignedBits(z, zBits) / (float)((1<<(zBits-1))-1);
		g_mfn->Math_VecNorm(dst);*/
		char *src = (char *)(data + stride*i + 1);
		float *dst = dsts+i*3;
		for (int j = 0; j < 3;  j++) {
		  dst[j] = (float)src[2-j]/(float)127;
		}
		g_mfn->Math_VecNorm(dst);
	}
}

//convert the bones
modelBone_t *Model_Bayo_CreateBones(bayoWMBHdr_t &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones, short int * &animBoneTT)
{
	numBones = 0;
	if (hdr.numBones <= 0 || hdr.ofsBoneHie <= 0 || hdr.ofsBoneDataA <= 0 || hdr.ofsBoneDataB <= 0)
	{
		return NULL;
	}
	short *parentList = (short *)(data+hdr.ofsBoneHie);
	float *posList = (float *)(data+hdr.ofsBoneDataB);
	float *relPosList = (float *)(data+hdr.ofsBoneDataA); //actually relative positions
	animBoneTT = (short int *)(data+hdr.ofsBoneHieB);

	numBones = hdr.numBones;
	DBGLOG("Found %d bones\n", numBones);
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones);
	for (int i = 0; i < numBones; i++)
	{
		modelBone_t *bone = bones + i;
		float *ppos = posList + i*3;
		short parent = parentList[i];
		assert(parent < numBones);
		bone->index = i;
		bone->eData.parent = (parent >= 0) ? bones+parent : NULL;
		sprintf_s(bone->name, 30, "bone%03i", i);
		bone->mat = g_identityMatrix;
		float pos[3];
		memcpy(pos, ppos, sizeof(pos));
		/*
		modelMatrix_t mat1, mat2, mat3;
		g_mfn->Math_RotationMatrix(rot[0], 0, &mat1);
		g_mfn->Math_RotationMatrix(-rot[1], 1, &mat2);
		g_mfn->Math_MatrixMultiply(&mat2, &mat1, &mat3);
		g_mfn->Math_RotationMatrix(rot[2], 2, &mat1);
		g_mfn->Math_MatrixMultiply(&mat3, &mat1, &bone->mat);
		*/
		g_mfn->Math_VecCopy(pos, bone->mat.o);

	}
	DBGALOG("-------------------------------\n");
	for(int bi = 0; bi < numBones; bi++) {
		DBGALOG("bone %d (%d)\n", bi, bones[bi].index);
		DBGALOG("parent %d\n", bones[bi].eData.parent ? bones[bi].eData.parent->index : -1);
		DBGALOG("\ttranslate: %f, %f, %f\n", bones[bi].mat.o[0], bones[bi].mat.o[1], bones[bi].mat.o[2]);
		DBGALOG("\trelative_c: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));
		DBGALOG("\trelative_g: %f, %f, %f\n", relPosList[3 * bi], relPosList[3 * bi + 1], relPosList[3 * bi + 2]);
	}
	//bones come pre-transformed
	//rapi->rpgMultiplyBones(bones, numBones);
	return bones;
}

//load Bayonetta Material
static void Model_Bayo_LoadMaterials(bayoWMBHdr_t &hdr,
									 CArrayList<noesisTex_t *> &textures,
									 bool &hasExMatInfo,
									 CArrayList<noesisMaterial_t *> &matList,
									 CArrayList<noesisMaterial_t *> &matListLightMap,
									 CArrayList<noesisMaterial_t *> &totMatList,
									 BYTE *data,
									 noeRAPI_t *rapi) {
	int *matOfsList = (int *)(data + hdr.ofsMaterialsOfs);
	hasExMatInfo = (hdr.exMatInfo[0] && hdr.exMatInfo[1] && hdr.exMatInfo[2] && hdr.exMatInfo[3]);
	int *matIDs = (hasExMatInfo) ? (int *)(data + hdr.exMatInfo[1]) : NULL;
	int numMatIDs = 0;
	if (matIDs)
	{ //got a global reference list (this seems redundant since it's also provided in the texture bundle)
		numMatIDs = *matIDs;
		matIDs++;
	}
	DBGLOG("Found %d materials\n", hdr.numMaterials);
	for (int i = 0; i < hdr.numMaterials; i++)
	{
		DBGLOG("\t%03d:", i);
		int matOfs = matOfsList[i];
		BYTE *matData = data + hdr.ofsMaterials + matOfs;
		//create a noesis material entry
		char matName[128];
		sprintf_s(matName, 128, "bayomat%i", i);
		DBGLOG(" name: %s,", matName);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		nmat->name = rapi->Noesis_PooledString(matName);
		//nmat->flags |= NMATFLAG_TWOSIDED;

		if (hasExMatInfo && numMatIDs > 0)
		{ //search by global index values
			DBGLOG("vanquish style\n");
			nmat->normalTexIdx = (textures.Num() > 0) ? textures.Num()-1 : -1; //default to flat normal

			char *shaderName = (char *)(data + hdr.exMatInfo[0] + 16*i);
			if (_strnicmp(shaderName, "har", 3) == 0)
			{ //blend hair
				nmat->noDefaultBlend = false;
			}
			bool isSkin = (_strnicmp(shaderName, "skn00", 5) == 0);
			bool isPHG = (_strnicmp(shaderName, "phg05", 5) == 0);
			bool isLBT = (_strnicmp(shaderName, "lbt00", 5) == 0);
			bool raSwap = (_strnicmp(shaderName, "max32", 5) == 0); //hacky way to see if the normal needs red and alpha swapped, probably not reliable
			int difTexId = *((int *)(matData + 4));
			int nrmOfs = (isSkin || isPHG || isLBT) ? 8 : 16;
			int nrmTexId = *((int *)(matData + nrmOfs)); //this is kinda happenstance, i think the only right way to know what to do is to check the pixel shader
			for (int j = 0; j < textures.Num(); j++)
			{
				noesisTex_t *tex = textures[j];
				if (tex && tex->globalIdx == difTexId)
				{
					nmat->texIdx = j;
				}
				if (tex && tex->globalIdx == nrmTexId)
				{
					nmat->normalTexIdx = j;
					if (raSwap)
					{
						nmat->flags |= NMATFLAG_NMAPSWAPRA;
					}
				}
			}
		}
		else
		{ //bayonetta-style
			wmbMat_t mat = *((wmbMat_t *)matData);

			if( !bayoMatTypes[mat.matFlags].known ) {
				DBGLOG(" unknown material id: %4x, %4x", mat.matFlags, mat.unknownB);
				for( int j=0; j<5; j++) {
					DBGLOG(", tex%d: %d, %2x, %4x", j,  mat.texs[j].tex_idx, mat.texs[j].tex_flagA, mat.texs[j].tex_flagB);
				}
				DBGLOG("\n");
				DBGFLUSH();
			} else {
				DBGLOG(" material id: %2x, offset: %x, tex: %d(%2x, %x)",
					   mat.matFlags, hdr.ofsMaterials + matOfs, mat.texs[0].tex_idx, mat.texs[0].tex_flagA, mat.texs[0].tex_flagB);
			}

			nmat->texIdx = mat.texs[0].tex_idx;
			char normalmap_index = bayoMatTypes[mat.matFlags].normalmap_index;

			if( normalmap_index != -1 && !mat.texs[normalmap_index].tex_flagB ) {
				DBGLOG(", normal: %d(%2x, %x)", mat.texs[normalmap_index].tex_idx, mat.texs[normalmap_index].tex_flagA, mat.texs[normalmap_index].tex_flagB);
				nmat->normalTexIdx = mat.texs[normalmap_index].tex_idx;
			} else {
				nmat->normalTexIdx = (textures.Num() > 0) ? textures.Num()-1 : -1;
			}
			//todo - some materials also do a scale+bias+rotation on the uv's at runtime to transform the texture coordinates into a
			//specific region of the normal page. i would think the uv transform data is buried in the giant chunk of floats that
			//follows the material data, but i don't see it in there. maybe it's related to some texture bundle flags.
/*				if (nrmIdx == 6 || nrmIdx == 2 || nrmIdx == 13) {
					char matNameLightMap[128];
					sprintf_s(matNameLightMap, 128, "bayomat_light%i", i);
					noesisMaterial_t *nmatLightMap = rapi->Noesis_GetMaterialList(1, true);
					nmatLightMap->name = rapi->Noesis_PooledString(matNameLightMap);
					nmatLightMap->texIdx = nrmIdx;
					nmatLightMap->normalTexIdx = -1;
					matListLightMap.Append(nmatLightMap);
					totMatList.Append(nmatLightMap);
				} */
			DBGLOG("\n");
			float *scaleBias = (float *)rapi->Noesis_PooledAlloc(4*sizeof(float));
			scaleBias[0] = 1.0f;
			scaleBias[1] = 1.0f;
			scaleBias[2] = 0.0f;
			scaleBias[3] = 0.0f;
			nmat->ex->pUvScaleBias = scaleBias;

/*			if( bayoMatTypes[mat.matFlags].known ) { //Doesn't work everywhere unfortunately (bayonetta's eyes seem wrong with this) but works for sapientia's leg
				float *scale_p = ((float *)matData) + 1 + bayoMatTypes[mat.matFlags].texture_number;
				scaleBias[0] = scale_p[0];
				scaleBias[1] = scale_p[1];
			}*/
			DBGLOG("scale: %f %f\n", nmat->ex->pUvScaleBias[0], nmat->ex->pUvScaleBias[1] );

		}
		matListLightMap.Append(NULL);
		matList.Append(nmat);
		totMatList.Append(nmat);
	}
}
//load a single model from a dat set
static void Model_Bayo_LoadModel(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models)
{
	DBGLOG("Loading %s\n", df.name);
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(bayoWMBHdr_t))
	{
		return;
	}
	bayoWMBHdr_t hdr = *((bayoWMBHdr_t *)data);
	if (memcmp(hdr.id, "WMB\0", 4))
	{ //invalid header
		return;
	}
	bool isVanqModel = (hdr.unknownA < 0);
	DBGLOG("Vanquish: %s\n", isVanqModel ? "true" : "false");

	CArrayList<bayoDatFile_t *> motfiles;
	CArrayList<noesisTex_t *> textures;
	CArrayList<noesisMaterial_t *> matList;
	CArrayList<noesisMaterial_t *> matListLightMap;
	CArrayList<noesisMaterial_t *> totMatList;
	CArrayList<noesisAnim_t *> animList;

	bool hasExMatInfo;

	bayoDatFile_t *texBundle = Model_Bayo_GetTextureBundle(dfiles, df, rapi);
	if (texBundle)
	{
		DBGLOG("Found texture bundle %s\n", texBundle->name);
		Model_Bayo_LoadTextures(textures, texBundle->data, texBundle->dataSize, rapi);
	}

	Model_Bayo_LoadMaterials(hdr, textures, hasExMatInfo, matList, matListLightMap, totMatList, data, rapi);

	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetEndian(false);
	BYTE *vertData = data + hdr.ofsVerts;
	const int bayoVertSize = 32;//(hdr.ofsVerts > 128) ? 48 : 32;

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_Bayo_CreateBones(hdr, data, rapi, numBones, animBoneTT);

	Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);

	//decode normals
	float *normals = (float *)rapi->Noesis_PooledAlloc(sizeof(float)*3*hdr.numVerts);
	Model_Bayo_CreateNormals(vertData+16, normals, hdr.numVerts, bayoVertSize, isVanqModel);

	BYTE *meshStart = data + hdr.ofsMeshes;
	int *meshOfsList = (int *)(data + hdr.ofsMeshOfs);
	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	for (int i = 0; i < hdr.numMeshes; i++)
	{
		//if (i != 0) continue;
		int meshOfs = meshOfsList[i];
		wmbMesh_t mesh = *((wmbMesh_t *)(meshStart+meshOfs));
		DBGLOG("\t%3d: id: %d, offset: %x, name: %s\n", i, mesh.id , hdr.ofsMeshes+meshOfs, mesh.name);
		int *batchOfsList = (int *)(meshStart+meshOfs+mesh.batchOfs);
		for (int j = 0; j < mesh.numBatch; j++)
		{
			DBGLOG("\t\t%3d: ", j);
			int batchOfs = batchOfsList[j];
			BYTE *batchData = (BYTE *)batchOfsList + batchOfs;
			wmbBatch_t batch = *((wmbBatch_t *)batchData);
			DBGLOG("%d, %x, %x, %x, %x,", batch.id, batch.unknownB, batch.unknownC, batch.unknownDB, batch.unknownE);
			if (batch.unknownE == 0xf20) {
				DBGLOG("skipped (shadow model)\n");
				continue; // shadow meshes
			}
			/*if (batch.unknownB != 0x8001) {
				DBGLOG("skipped\n");
				continue;
			}*/
			int numBoneRefs = *((int *)(batchData+sizeof(wmbBatch_t)));
			int *boneRefDst = NULL;
			if (numBoneRefs > 0 && bones)
			{ //set up reference map
				BYTE *boneRefs = batchData+sizeof(wmbBatch_t)+sizeof(int);
				boneRefDst = (int *)rapi->Noesis_UnpooledAlloc(sizeof(int)*numBoneRefs);
				for (int k = 0; k < numBoneRefs; k++)
				{
					boneRefDst[k] = boneRefs[k];
				}
			}
			rapi->rpgSetBoneMap(boneRefDst);
			int vertOfs = batch.vertOfs;
			DBGLOG("vertAddr: %x, ", hdr.ofsVerts + vertOfs*bayoVertSize);
			//bind positions
			rapi->rpgBindPositionBuffer(vertData + vertOfs*bayoVertSize, RPGEODATA_FLOAT, bayoVertSize);
			//bind normals
			rapi->rpgBindNormalBuffer(normals + vertOfs*3, RPGEODATA_FLOAT, sizeof(float)*3);
			//bind uv's
			rapi->rpgBindUV1Buffer(vertData+12 + vertOfs*bayoVertSize, RPGEODATA_HALFFLOAT, bayoVertSize);
			if (bones)
			{ //bind weight data
				rapi->rpgBindBoneIndexBuffer(vertData+24 + vertOfs*bayoVertSize, RPGEODATA_UBYTE, bayoVertSize, 4);
				rapi->rpgBindBoneWeightBuffer(vertData+28 + vertOfs*bayoVertSize, RPGEODATA_UBYTE, bayoVertSize, 4);
			}

			int texID = (hasExMatInfo) ? batch.unknownC : batch.texID;
			char *matName = (texID < matList.Num()) ? matList[texID]->name : NULL;
			DBGLOG("matName: %s\n", matName);
			rapi->rpgSetMaterial(matName);
			if(texID < matList.Num() && matList[texID]->ex->pUvScaleBias) {
				rapi->rpgSetUVScaleBias(matList[texID]->ex->pUvScaleBias, matList[texID]->ex->pUvScaleBias + 2);
			} else {
				rapi->rpgSetUVScaleBias(NULL, NULL);
			}
/*			if(matListLightMap[texID]) {
				rapi->rpgSetLightmap(matListLightMap[texID]->name);
				rapi->rpgBindUV2Buffer(vertData+20 + vertOfs*bayoVertSize, RPGEODATA_HALFFLOAT, bayoVertSize);
			} else {
				rapi->rpgSetLightmap(NULL);
				rapi->rpgBindUV2Buffer(NULL, RPGEODATA_HALFFLOAT, 0);
			}*/

			rpgeoPrimType_e primType = (batch.primType == 4) ? RPGEO_TRIANGLE : RPGEO_TRIANGLE_STRIP;
			rapi->rpgCommitTriangles(batchData+batch.ofsIndices, RPGEODATA_USHORT, batch.numIndices, primType, true);
			if (boneRefDst)
			{ //reference map is no longer needed once triangles have been committed
				rapi->rpgSetBoneMap(NULL);
				rapi->Noesis_UnpooledFree(boneRefDst);
			}
		}
	}

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(totMatList, textures);
	rapi->rpgSetExData_Materials(md);
	rapi->rpgSetExData_Bones(bones, numBones);

#if 0 //create a procedural anim where bayonetta turns her upper torso and hips
	if (bones)
	{
		sharedPAnimParm_t aparms[2];
		memset(aparms, 0, sizeof(aparms)); //it's a good idea to do this, in case future noesis versions add more meaningful fields.
		aparms[0].angAmt = 25.0f;
		aparms[0].axis = 1; //rotate left and right
		aparms[0].boneIdx = 2; //upper torso bone
		aparms[0].timeScale = 0.1f; //acts as a framestep
		aparms[1].angAmt = 25.0f;
		aparms[1].axis = 0; //rotate back and forth
		aparms[1].boneIdx = 19; //hips
		aparms[1].timeScale = 0.1f; //acts as a framestep
		noesisAnim_t *anim = rapi->rpgCreateProceduralAnim(bones, numBones, aparms, 2, 500);
		if (anim)
		{
			rapi->rpgSetExData_AnimsNum(anim, 1);
		}
	}
#endif
	Model_Bayo_LoadMotions(animList, motfiles, bones, numBones, rapi, animBoneTT);
/*    int anims_num = 0;
	if( animList.Num() > 0 ) {
		rapi->rpgSetExData_AnimsNum(animList[0], 1);
	}*/
	int anims_num = animList.Num();
    //noesisAnim_t *anims = rapi->Noesis_AnimFromAnimsList(animList, anims_num);
	//for(int i = 0; i < anims_num; i++) {
	//	DBGLOG("anim: %s, size: %d, flag: %d\n", animList[i]->filename, animList[i]->dataLen, animList[i]->flags & NANIMFLAG_FILENAMETOSEQ);
	//	DBGLOG("seq: %p, size: %d\n", (anims+i)->aseq, (anims+i)->dataLen );
	//}
    //rapi->rpgSetExData_AnimsNum(anims, anims_num);
	//rapi->rpgMultiplyBones(bones, numBones);
	DBGLOG("Found %d anims\n", anims_num);
	rapi->rpgSetTriWinding(true); //bayonetta uses reverse face windings
	noesisModel_t *mdl = rapi->rpgConstructModel();
	if( mdl ) {
		models.Append(mdl);
	}
	for(int i = 0; i < anims_num; i++) {
		noesisModel_t *mdl = rapi->rpgConstructModel();
		if( mdl ) {
			models.Append(mdl);
			rapi->Noesis_SetModelAnims(mdl, animList[i], 1);
		}
	}
	
	rapi->rpgDestroyContext(pgctx);

	animList.Clear();
	matList.Clear();
	motfiles.Clear();
	textures.Clear();
	matListLightMap.Clear();
	totMatList.Clear();
}

//gather entries from a dat file
static void Model_Bayo_GetDATEntries(CArrayList<bayoDatFile_t> &dfiles, BYTE *fileBuffer, int bufferLen)
{
	bayoDat_t dat = *((bayoDat_t *)fileBuffer);

	BYTE *namesp = fileBuffer+dat.ofsNames;
	int strSize = *((int *)namesp);
	namesp += sizeof(int);
	int *ofsp = (int *)(fileBuffer+dat.ofsRes);
	int *sizep = (int *)(fileBuffer+dat.ofsSizes);
	DBGLOG("Found %d entries\n", dat.numRes);
	for (int i = 0; i < dat.numRes; i++)
	{
		bayoDatFile_t df;
		memset(&df, 0, sizeof(df));
		df.name = (char *)namesp;
		DBGLOG("\t%s\n", df.name);
		namesp += strSize;

		df.dataSize = *sizep;
		sizep++;

		int ofs = *ofsp;
		df.data = fileBuffer+ofs;
		ofsp++;

		dfiles.Append(df);
	}
}

//load it
noesisModel_t *Model_Bayo_Load(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	CArrayList<bayoDatFile_t> dfiles;

	DBGLOG("Loading model\n");
	//create a list of resources
	Model_Bayo_GetDATEntries(dfiles, fileBuffer, bufferLen);
	//for vanquish, append any matching dtt files (they're just paired dat files)
	char *inFile = rapi->Noesis_GetInputName();
	BYTE *dttFile = NULL;
	if (inFile && inFile[0])
	{
		char fn[MAX_NOESIS_PATH];
		rapi->Noesis_GetExtensionlessName(fn, inFile);
		strcat_s(fn, MAX_NOESIS_PATH, ".dtt");
		int dttLen = 0;
		dttFile = (BYTE *)rapi->Noesis_ReadFile(fn, &dttLen);
		if (dttFile && dttLen > 0)
		{
			Model_Bayo_GetDATEntries(dfiles, dttFile, dttLen);
		}
	}

	CArrayList<noesisModel_t *> models;
	DBGLOG("Have %d files\n", dfiles.Num());
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &df = dfiles[i];
		if (rapi->Noesis_CheckFileExt(df.name, ".wmb"))
		{ //it's a model
			Model_Bayo_LoadModel(dfiles, df, rapi, models);
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

//called by Noesis to init the plugin
bool NPAPI_InitLocal(void)
{
	int fh = g_nfn->NPAPI_Register("Bayonetta PC Model", ".dat");
	if (fh < 0)
	{
		return false;
	}
	OPENLOG();
	bayoSetMatTypes();
	//set the data handlers for this format
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh, Model_Bayo_Check);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh, Model_Bayo_Load);

	return true;
}

//called by Noesis before the plugin is freed
void NPAPI_ShutdownLocal(void)
{
	CLOSELOG();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	return TRUE;
}
