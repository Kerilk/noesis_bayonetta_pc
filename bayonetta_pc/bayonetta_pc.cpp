//this is kind of a poor example for plugins, since the format's not totally known and the code is WIP.
//but it does showcase some interesting usages.

#include "stdafx.h"
#undef max
#undef min
#include "half.hpp"
using half_float::half;
#include <map>

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

typedef enum game_e {
	BAYONETTA,
	BAYONETTA2,
	VANQUISH
} game_t;

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
	bayoDat( bayoDat_t * ptr ): bayoDat_s(*ptr){
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
	bayoWTBHdr( bayoWTBHdr_t *ptr ): bayoWTBHdr_s(*ptr) {
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
	bayoWTAHdr( bayoWTAHdr_t *ptr ): bayoWTAHdr_s(*ptr) {
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
	GX2Hdr( GX2Hdr_t *ptr ): GX2Hdr_s(*ptr) {
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
template <bool big>
struct bayoWMBHdr : public bayoWMBHdr_s {
	bayoWMBHdr( bayoWMBHdr_t * ptr ): bayoWMBHdr_s(*ptr){
		if (big) {
			LITTLE_BIG_SWAP(*((int *)id));
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(unknownC);
			LITTLE_BIG_SWAP(numVerts);
			LITTLE_BIG_SWAP(unknownD);
			LITTLE_BIG_SWAP(unknownE);
			LITTLE_BIG_SWAP(unknownF);
			LITTLE_BIG_SWAP(ofsVerts);
			LITTLE_BIG_SWAP(ofsVertExData);
			for(int i=0; i<4; i++) LITTLE_BIG_SWAP(unknownG[i]);
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
			LITTLE_BIG_SWAP(ofsUnknownK);
			LITTLE_BIG_SWAP(ofsUnknownL);
			for(int i=0; i<4; i++) LITTLE_BIG_SWAP(exMatInfo[i]);
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
	wmbMesh( wmbMesh_t * ptr ): wmbMesh_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(id);
			LITTLE_BIG_SWAP(numBatch);
			LITTLE_BIG_SWAP(unknownB);
			LITTLE_BIG_SWAP(batchOfs);
			LITTLE_BIG_SWAP(unknownD);
			for(int i=0; i<4; i++) LITTLE_BIG_SWAP(unknownE[i]);
			for(int i=0; i<12; i++) LITTLE_BIG_SWAP(mat[i]);
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
	wmbBatch( wmbBatch_t * ptr ): wmbBatch_s(*ptr) {
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
			for(int i=0; i<7; i++) LITTLE_BIG_SWAP(unknownI[i]);
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
	wmbMat( wmbMat_t *ptr ): wmbMat_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(matFlags);
			LITTLE_BIG_SWAP(unknownB);
			for( int i = 0; i < 5; i++ ) {
				LITTLE_BIG_SWAP(texs[i]);
			}
		}
	}
};
typedef struct bayo2EXPHdr_s
{
	BYTE				id[4];
	int					version;
	unsigned int		offsetRecords;
	int					numRecords;
	unsigned int		offsetInterpolationData;
	int					numtInterpolationData;
} bayo2EXPHdr_t;
template <bool big>
struct bayo2EXPHdr : public bayo2EXPHdr_s
{
	bayo2EXPHdr(bayo2EXPHdr_t *ptr) : bayo2EXPHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(version);
			LITTLE_BIG_SWAP(offsetRecords);
			LITTLE_BIG_SWAP(numRecords);
			LITTLE_BIG_SWAP(offsetInterpolationData);
			LITTLE_BIG_SWAP(numtInterpolationData);
		}
	}
};
typedef struct bayoEXPHdr_s
{
	BYTE				id[4];
	int					unknownA;
	unsigned int		offsetRecords;
	unsigned int		numRecords;
} bayoEXPHdr_t;
template <bool big>
struct bayoEXPHdr : public bayoEXPHdr_s
{
	bayoEXPHdr(bayoEXPHdr_t *ptr) : bayoEXPHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(offsetRecords);
			LITTLE_BIG_SWAP(numRecords);
		}
	}
};
typedef struct bayo2EXPRecord_s
{
	short int			boneIndex;
	char				animationTrack;
	char				unknownA;
	short int			valueCount;
	short int			unknwonB;
	unsigned int		offset;
} bayo2EXPRecord_t;
template <bool big>
struct bayo2EXPRecord : public bayo2EXPRecord_s
{
	bayo2EXPRecord(bayo2EXPRecord_t *ptr) : bayo2EXPRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(valueCount);
			LITTLE_BIG_SWAP(unknwonB);
			LITTLE_BIG_SWAP(offset);
		}
	}
};

typedef struct bayoEXPRecord_s
{
	short int			unknownA;
	short int			boneIndex;
	char				animationTrack;
	char				entryType;
	char				unknownB;
	char				unknwonC;
	int					unknownD;
	unsigned int		offset;
	int					unknownE;
} bayoEXPRecord_t;
template <bool big>
struct bayoEXPRecord : public bayoEXPRecord_s
{
	bayoEXPRecord(bayoEXPRecord_t * ptr) : bayoEXPRecord_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(unknownD);
			LITTLE_BIG_SWAP(offset);
			LITTLE_BIG_SWAP(unknownE);
		}
	}
};
typedef struct bayo2EXPValue_s
{
	char			type;
	char			animationTrack;
	short int		boneIndex;
	float			value;
} bayo2EXPValue_t;
template <bool big>
struct bayo2EXPValue : public bayo2EXPValue_s
{
	bayo2EXPValue(bayo2EXPValue_t * ptr) : bayo2EXPValue_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(value);
		}
	}
};
typedef struct bayo2EXPInterpolationData_s
{
	int				numPoints;
	int				unknownA;
	unsigned int	offset;
} bayo2EXPInterpolationData_t;
template <bool big>
struct bayo2EXPInterpolationData : public bayo2EXPInterpolationData_s
{
	bayo2EXPInterpolationData(bayo2EXPInterpolationData_t * ptr) : bayo2EXPInterpolationData_s(*ptr) {
		LITTLE_BIG_SWAP(numPoints);
		LITTLE_BIG_SWAP(unknownA);
		LITTLE_BIG_SWAP(offset);
	}
};
typedef struct bayo2EXPInterpolationPoints_s
{
	float v;
	float p;
	float m0;
	float m1;
} bayo2EXPInterpolationPoints_t;
template <bool big>
struct bayo2EXPInterpolationPoints : public bayo2EXPInterpolationPoints_s
{
	bayo2EXPInterpolationPoints(bayo2EXPInterpolationPoints_t *ptr) : bayo2EXPInterpolationPoints_s(*ptr) {
		LITTLE_BIG_SWAP(v);
		LITTLE_BIG_SWAP(p);
		LITTLE_BIG_SWAP(m0);
		LITTLE_BIG_SWAP(m1);
	}
};
typedef struct bayoEXPCoef_s
{
	unsigned int		flag;
	float				value;
} bayoEXPCoef_t;
typedef struct bayoEXPEntry1_s
{
	unsigned int		flag;
	short int			boneIndex;
	char				animationTrack;
	char				padding;
} bayoEXPEntry1_t;
template <bool big>
struct bayoEXPEntry1 : public bayoEXPEntry1_s
{
	bayoEXPEntry1(bayoEXPEntry1_t*ptr) : bayoEXPEntry1_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flag);
			LITTLE_BIG_SWAP(boneIndex);
		}
	}
};
typedef struct bayoEXPEntry2_s
{
	unsigned int		flag;
	short int			boneIndex;
	char				animationTrack;
	char				padding;
	bayoEXPCoef_t		coefficient;
} bayoEXPEntry2_t;
template <bool big>
struct bayoEXPEntry2 : public bayoEXPEntry2_s
{
	bayoEXPEntry2(bayoEXPEntry2_t*ptr) : bayoEXPEntry2_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flag);
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(coefficient.flag);
			LITTLE_BIG_SWAP(coefficient.value);
		}
	}
};
typedef struct bayoEXPEntry3_s
{
	unsigned int		flag;
	short int			boneIndex;
	char				animationTrack;
	char				padding;
	bayoEXPCoef_t		coefficients[2];
} bayoEXPEntry3_t;
template <bool big>
struct bayoEXPEntry3 : public bayoEXPEntry3_s
{
	bayoEXPEntry3(bayoEXPEntry3_t*ptr) : bayoEXPEntry3_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(flag);
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(coefficients[0].flag);
			LITTLE_BIG_SWAP(coefficients[0].value);
			LITTLE_BIG_SWAP(coefficients[1].flag);
			LITTLE_BIG_SWAP(coefficients[1].value);
		}
	}
};
typedef struct bayoMOTHdr_s
{
	BYTE				id[4];
	short int			unknownA;
	short int			frameCount;
	int					ofsMotion;
	int					numEntries;
} bayoMOTHdr_t;
template <bool big>
struct bayoMOTHdr : public bayoMOTHdr_s {
	bayoMOTHdr( bayoMOTHdr_t *ptr ): bayoMOTHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(frameCount);
			LITTLE_BIG_SWAP(ofsMotion);
			LITTLE_BIG_SWAP(numEntries);
		}
	}
};
typedef struct bayo2MOTHdr_s
{
	BYTE				id[4];
	int					hash;
	short int			unknownA;
	short int			frameCount;
	int					ofsMotion;
	int					numEntries;
} bayo2MOTHdr_t;
template <bool big>
struct bayo2MOTHdr : public bayo2MOTHdr_s {
	bayo2MOTHdr( bayo2MOTHdr_t *ptr ): bayo2MOTHdr_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(hash);
			LITTLE_BIG_SWAP(unknownA);
			LITTLE_BIG_SWAP(frameCount);
			LITTLE_BIG_SWAP(ofsMotion);
			LITTLE_BIG_SWAP(numEntries);
		}
	}
};
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
template <bool big>
struct bayoMotItem : public bayoMotItem_s {
	bayoMotItem( bayoMotItem_t *ptr ): bayoMotItem_s(*ptr) {
		if(big) {
			LITTLE_BIG_SWAP(boneIndex);
			LITTLE_BIG_SWAP(index);
			LITTLE_BIG_SWAP(flag);
			LITTLE_BIG_SWAP(elem_number);
			LITTLE_BIG_SWAP(unknown);
			LITTLE_BIG_SWAP(value);
		}
	}
};
typedef struct bayo2InterpolKeyframe4_s {
	unsigned short int index;
	unsigned short int dummy;
	float p;
	float m0;
	float m1;
} bayo2InterpolKeyframe4_t;
template <bool big>
struct bayo2InterpolKeyframe4 : public bayo2InterpolKeyframe4_s {
	bayo2InterpolKeyframe4( bayo2InterpolKeyframe4_t *ptr ): bayo2InterpolKeyframe4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
			LITTLE_BIG_SWAP(dummy);
			LITTLE_BIG_SWAP(p);
			LITTLE_BIG_SWAP(m0);
			LITTLE_BIG_SWAP(m1);
		}
	}
};
typedef struct bayoInterpolHeader4_s {
	float values[6];
} bayoInterpolHeader4_t;
typedef struct bayoInterpolKeyframe4_s {
	unsigned short int index;
	unsigned short int coeffs[3];
} bayoInterpolKeyframe4_t;
template <bool big>
struct bayoInterpolKeyframe4 : public bayoInterpolKeyframe4_s {
	bayoInterpolKeyframe4( bayoInterpolKeyframe4_t *ptr): bayoInterpolKeyframe4_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
			for(int i = 0; i < 3; i++) LITTLE_BIG_SWAP(coeffs[i]);
		}
	}
};
typedef short unsigned int pghalf;
typedef struct bayoInterpolHeader6_s {
	pghalf values[6];
} bayoInterpolHeader6_t;
typedef struct bayoInterpolKeyframe6_s {
	BYTE index;
	BYTE coeffs[3];
} bayoInterpolKeyframe6_t;
template <bool big>
struct bayoInterpolKeyframe6 : public bayoInterpolKeyframe6_s {
	bayoInterpolKeyframe6( bayoInterpolKeyframe6_t *ptr): bayoInterpolKeyframe6_s(*ptr) {
	}
};
typedef struct bayoInterpolHeader7_s {
	pghalf values[6];
} bayoInterpolHeader7_t;
typedef struct bayoInterpolKeyframe7_s {
	unsigned short int index;
	BYTE dummy;
	BYTE coeffs[3];
} bayoInterpolKeyframe7_t;
template <bool big>
struct bayoInterpolKeyframe7 : public bayoInterpolKeyframe7_s {
	bayoInterpolKeyframe7( bayoInterpolKeyframe7_t *ptr): bayoInterpolKeyframe7_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
		}
	}
};
typedef struct bayoInterpolHeader8_s {
	pghalf values[6];
} bayoInterpolHeader8_t;
typedef struct bayoInterpolKeyframe8_s {
	unsigned short int index;
	BYTE coeffs[3];
} bayoInterpolKeyframe8_t;
template <bool big>
struct bayoInterpolKeyframe8 : public bayoInterpolKeyframe8_s {
	bayoInterpolKeyframe8( bayoInterpolKeyframe8_t *ptr): bayoInterpolKeyframe8_s(*ptr) {
		if (big) {
			LITTLE_BIG_SWAP(index);
		}
	}
};
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
		} else if ( significand ) { //denorm
			Bits magic;
			magic.ui = (biasF - biasH + biasF) << significandFBits;
			v.f *= magic.f;
		}
		return v.f;
	}
	float decompress(short unsigned int value, bool big) {
		short unsigned int v2 = value;
		if (big) LITTLE_BIG_SWAP(v2);
		return decompress(v2);
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
template <bool big, game_e game>
bool Model_Bayo_Check(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi)
{
	DBGLOG("----------------------\n");
	if (bufferLen < sizeof(bayoDat_t))
	{
		return false;
	}
	bayoDat<big> dat((bayoDat_t *)fileBuffer);
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
	if (big) LITTLE_BIG_SWAP(strSize);

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
		if (game == BAYONETTA2 && rapi->Noesis_CheckFileExt(name, ".wtb"))
		{
			DBGLOG("Found Bayonetta File!");
			return false;
		}
		if (game == BAYONETTA && (rapi->Noesis_CheckFileExt(name, ".wta") || rapi->Noesis_CheckFileExt(name, ".wtp")))
		{
			DBGLOG("Found Bayonetta 2 File!");
			return false;
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
template <game_t game>
static void Model_Bayo_GetTextureBundle(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi);
template <>
static void Model_Bayo_GetTextureBundle<BAYONETTA>(CArrayList<bayoDatFile_t *> &texFiles, CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	char texName[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(texName, df.name);
	strcat_s(texName, MAX_NOESIS_PATH, ".wtb");
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &dft = dfiles[i];
		if (!_stricmp(dft.name, texName))
		{
			texFiles.Append(&dft);
		}
	}
}
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
static void Model_Bayo_LoadTextures<true, BAYONETTA2>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	const bool big = true;
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	int dataSize2 = texFiles[1]->dataSize;
	BYTE * data2 = texFiles[1]->data;

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
	int *tofs = (int *)(data+hdr.ofsTexOfs);
	int *tsizes = (int *)(data+hdr.ofsTexSizes);
	int *mofs = (int *)(data+hdr.ofsMipmapOfs);
	for (int i = 0; i < hdr.numTex; i++)
	{
		int globalIdx;
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

		GX2Hdr<big> texHdr((GX2Hdr_t *)(data + hdr.texInfoOffset + i*0xc0));
		//DBGLOG("%d: dim: %d, width %d, height %d, depth %d, numMimap: %d, format: %x\n", i, texHdr.dimension, texHdr.width, texHdr.height, texHdr.depth, texHdr.numMipmaps, texHdr.format);
		//DBGLOG("\tusage: %x, length: %d, mipmapDataLength: %d, tileMode: %x\n", texHdr.usage, texHdr.dataLength, texHdr.mipmapsDataLength, texHdr.tileMode);
		//DBGLOG("\tswizzle: %x, alignment %d, pitch %d, first mipmap: %d\n", texHdr.swizzleValue, texHdr.alignment, texHdr.pitch, texHdr.firstMipmap);
		//DBGLOG("\tcomponents: %d, %d, %d, %d\n", texHdr.component[0], texHdr.component[1], texHdr.component[2], texHdr.component[3]);

		if (hdr.texIdxOffset)
		{
			int *ip = (int  *)(data+hdr.texIdxOffset+sizeof(int)*i);
			globalIdx = *ip;
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
		fwrite(data + hdr.texInfoOffset + i*0xc0, 1, 0x9c, fgtx);
		// block header (data)
		fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x0C", 1, 0x14, fgtx);
		DWORD size = texHdr.dataLength;
		if (big) LITTLE_BIG_SWAP(size);
		fwrite(&size, 4, 1,  fgtx);
		fwrite("\x00\x00\x00\x00\x00\x00\x00\x00", 1, 0x8, fgtx);
		// write pixel data
		int tof = tofs[i];
		LITTLE_BIG_SWAP(tof);
		fwrite(data2 + tof, 1, texHdr.dataLength, fgtx);
		if ( texHdr.numMipmaps > 1 ) {
			// block header (mipmap data)
			fwrite("\x42\x4C\x4B\x7B\x00\x00\x00\x20\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x0D", 1, 0x14, fgtx);
			size = texHdr.mipmapsDataLength;
			if (big) LITTLE_BIG_SWAP(size);
			fwrite(&size, 4, 1,  fgtx);
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
		mbstowcs(wcmd, cmd, strlen(cmd)+1);

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
		} else {
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
	int *tofs = (int *)(data+hdr.ofsTexOfs);
	int *tsizes = (int *)(data+hdr.ofsTexSizes);
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
			int *ip = (int  *)(data+hdr.texIdxOffset+sizeof(int)*i);
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
		mbstowcs(wcmd, cmd, strlen(cmd)+1);

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
		} else {
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
/*
template <>
static void Model_Bayo_LoadTextures<true, BAYONETTA>(CArrayList<noesisTex_t *> &textures, CArrayList<bayoDatFile_t *> &texFiles, noeRAPI_t *rapi)
{
	int dataSize = texFiles[0]->dataSize;
	BYTE * data = texFiles[0]->data;
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr<true> hdr((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "\0BTW", 4))
	{ //not a valid texture bundle
		return;
	}
	if (hdr.numTex <= 0 || hdr.ofsTexOfs <= 0 || hdr.ofsTexOfs >= dataSize ||
		hdr.ofsTexSizes <= 0 || hdr.ofsTexSizes >= dataSize)
	{
		return;
	}

	int *tofs = (int *)(data+hdr.ofsTexOfs);
	int *tsizes = (int *)(data+hdr.ofsTexSizes);
	for (int i = 0; i < hdr.numTex; i++)
	{
		char fname[8192];
		rapi->Noesis_GetDirForFilePath(fname, rapi->Noesis_GetOutputName());
		char nameStr[MAX_NOESIS_PATH];
		sprintf_s(nameStr, MAX_NOESIS_PATH, ".\\%sbayotex%03i", rapi->Noesis_GetOption("texpre"), i);
		strcat_s(fname, MAX_NOESIS_PATH, nameStr);

		int ofs = tofs[i];
		int size = tsizes[i];
		LITTLE_BIG_SWAP(ofs);
		LITTLE_BIG_SWAP(size);
		if (ofs < 0 || ofs > dataSize)
		{
			continue;
		}
		BYTE *texData = data+ofs;
		BYTE *pix;
		int globalIdx = -1;
		wtbTexHdr_t tex;
		if (hdr.texIdxOffset)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data+hdr.texIdxOffset+sizeof(int)*i);
			globalIdx = *ip;
			LITTLE_BIG_SWAP(globalIdx);
		}
		if (hdr.texInfoOffset)
		{ //texture info is contiguous in its own section
			wtbTexHdr_t *thdr = (wtbTexHdr_t  *)(data+hdr.texInfoOffset+sizeof(wtbTexHdr_t)*i);
			tex = *thdr;
			pix = texData;
		}
		else
		{
			tex = *((wtbTexHdr_t *)texData);
			pix = texData + sizeof(wtbTexHdr_t);
		}
		LITTLE_BIG_SWAP(tex.unknownJ);
		LITTLE_BIG_SWAP(tex.unknownO);
		LITTLE_BIG_SWAP(tex.unknownP);
		LITTLE_BIG_SWAP(tex.unknownQ);
		LITTLE_BIG_SWAP(tex.texFmt);
		LITTLE_BIG_SWAP(tex.heightBits);
		LITTLE_BIG_SWAP(tex.widthBits);
		if (tex.texFmt == 0)
		{
			noesisTex_t *nt = rapi->Noesis_AllocPlaceholderTex(fname, 32, 32, false);
			textures.Append(nt);
			continue;
		}
		int width = (((tex.widthBits>>5) & 127)+1)<<5;
		int height = ((tex.heightBits & 1023)+1) << 3;

		bool endianSwap = true;
		bool untile = !!(tex.unknownJ & 32768);
		bool uncompressed = false;
		bool channelSwiz = false;
		int dxtFmt = NOESISTEX_RGBA32;
		int texFlags = 0;
		if (tex.unknownJ > 0)
		{ //just a guess
			texFlags |= NTEXFLAG_SEGMENTED;
		}
		switch (tex.texFmt)
		{
		case 82:
			dxtFmt = NOESISTEX_DXT1;
			break;
		case 83:
			dxtFmt = NOESISTEX_DXT3;
			break;
		case 84:
			dxtFmt = NOESISTEX_DXT5;
			break;
		case 134:
			dxtFmt = NOESISTEX_RGBA32;
			uncompressed = true;
			channelSwiz = true;
			break;
		default:
			assert(0);
			rapi->LogOutput("WARNING: Unknown texture format %i.\n", tex.texFmt);
			dxtFmt = NOESISTEX_DXT1;
			break;
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
}*/
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
		if (hdr.texIdxOffset)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data+hdr.texIdxOffset+sizeof(int)*i);
			globalIdx = *ip;
		}
		if (hdr.texInfoOffset)
		{ //texture info is contiguous in its own section
			ddsTexHdr_t *thdr = (ddsTexHdr_t  *)(data+hdr.texInfoOffset+sizeof(ddsTexHdr_t)*i);
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
template <bool big>
static inline short int Model_Bayo_DecodeMotionIndex(const short int *table, const short int boneIndex) {
	short int index = table[(boneIndex >> 8) & 0xf];
	if (big) LITTLE_BIG_SWAP(index);
	if ( index != -1 ) {
		index = table[((boneIndex >> 4) & 0xf) + index];
		if (big) LITTLE_BIG_SWAP(index);
		if ( index != -1 ) {
			index = table[(boneIndex & 0xf) + index];
			if (big) LITTLE_BIG_SWAP(index);
			return index;
		}
	}
	return 0x0fff;
}
//initialize motion matrix
static void Model_Bayo_InitMotions(modelMatrix_t * &matrixes, float * &tmpValues, modelBone_t *bones, const int boneNumber, const short int frameCount, noeRAPI_t *rapi) {
	const int maxCoeffs = 10;
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
			for( int k = 7; k < 10; k++) {
				tmpValues[j + k * frameCount + i *  frameCount * maxCoeffs] = 1.0f;
			}
			//g_mfn->Math_TranslateMatrix(&matrixes[i + j*bone_number], bones[i].mat.o);
			//float zero[3] = {0.0f, 0.0f, 0.0f};
			//g_mfn->Math_RotationMatrix(0.0, 0, &matrixes[i + j*bone_number]);
		}
	}
}
//apply constrained bone motions
template <bool big>
static void Model_Bayo1_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	static int maxCoeffs = 10;
	if (expfile.Num() > 0) {
		DBGLOG("\tapplying: %s\n", expfile[0]->name);
		BYTE *data = expfile[0]->data;
		size_t dataSize = expfile[0]->dataSize;
		if (dataSize < sizeof(bayoEXPHdr_t))
		{
			return;
		}
		bayoEXPHdr<big> hdr((bayoEXPHdr_t *)data);
		for (unsigned int i = 0; i < hdr.numRecords; i++) {
			bayoEXPRecord<big> record((bayoEXPRecord_t *)(data + hdr.offsetRecords + i * sizeof(bayoEXPRecord_t)));
			short int targetBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, record.boneIndex);
			char targetTrack = record.animationTrack;
			short int sourceBone;
			char sourceTrack;
			DBGLOG("\t\trecord type: %d\n", record.entryType);
			if (record.entryType == 1) {
				bayoEXPEntry1<big> entry1((bayoEXPEntry1_t *)(data + record.offset));
				sourceBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, entry1.boneIndex);
				sourceTrack = entry1.animationTrack;
				DBGLOG("\t\ttrgtBone: %d, trgtTrack: %d, srcBone: %d, srcTrack: %d\n", targetBone, targetTrack, sourceBone, sourceTrack);
				for (int fi = 0; fi < frameCount; fi++) {
					tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
				}
			}
			else if (record.entryType == 2) {
				bayoEXPEntry2<big> entry2((bayoEXPEntry2_t *)(data + record.offset));
				sourceBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, entry2.boneIndex);
				sourceTrack = entry2.animationTrack;
				DBGLOG("\t\ttrgtBone: %d, trgtTrack: %d, srcBone: %d, srcTrack: %d, flag: %x, value: %f\n", targetBone, targetTrack, sourceBone, sourceTrack, entry2.coefficient.flag, entry2.coefficient.value);
				for (int fi = 0; fi < frameCount; fi++) {
					if (entry2.coefficient.flag == 0x4) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = entry2.coefficient.value * tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
					}
					else if (entry2.coefficient.flag == 0x1) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = entry2.coefficient.value + tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
					}
				}
			}
			else if (record.entryType == 3) {
				bayoEXPEntry3<big> entry3((bayoEXPEntry3_t *)(data + record.offset));
				sourceBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, entry3.boneIndex);
				sourceTrack = entry3.animationTrack;
				DBGLOG("\t\ttrgtBone: %d, trgtTrack: %d, srcBone: %d, srcTrack: %d, flag1: %x, value1: %f, flag2: %x, value2: %f\n", targetBone, targetTrack, sourceBone, sourceTrack, entry3.coefficients[0].flag, entry3.coefficients[0].value, entry3.coefficients[1].flag, entry3.coefficients[1].value);
				for (int fi = 0; fi < frameCount; fi++) {
					if (entry3.coefficients[0].flag == 0x4) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = entry3.coefficients[0].value * tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
					}
					else if (entry3.coefficients[0].flag == 0x20004) { //dubious
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = abs(entry3.coefficients[0].value) * tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
					}
					else if (entry3.coefficients[0].flag == 0x1) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = entry3.coefficients[0].value + tmpValues[fi + sourceTrack * frameCount + sourceBone * frameCount * maxCoeffs];
					}
					if (entry3.coefficients[1].flag == 0x4) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] *= entry3.coefficients[1].value;
					}
					else if (entry3.coefficients[1].flag == 0x1) {
						tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] += entry3.coefficients[1].value;
					}
				}
			}
		}
	}
}
template <bool big>
static float Model_Bayo2_DecodeEXP_Value( float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT, BYTE *interpol, BYTE *&values, int &valueCount, int frame) {
	DBGLOG("\t\tDecoding, remaining: %d\n", valueCount);
	static int maxCoeffs = 10;
	std::stack<float> s;
	char o = -1;
	while( valueCount > 0 ) {
		if (o != -1 && s.size() >= 2) {
			float v2 = s.top();
			s.pop();
			float v1 = s.top();
			s.pop();
			if (o == '+') {
				v1 += v2;
			}
			else if (o == '*') {
				v1 *= v2;
			}
			s.push(v1);
			o = -1;
		}
		bayo2EXPValue<big> v((bayo2EXPValue_t *) values);
		values += sizeof(bayo2EXPValue_t);
		valueCount -= 1;
		switch (v.type) {
		case 0: //terminator
			DBGLOG("\t\t\tTerminator\n");
			return s.top();
			break;
		case 1: //Parenthesis
			DBGLOG("\t\t\tOpening Paren\n");
			s.push( Model_Bayo2_DecodeEXP_Value<big>(tmpValues, bone_number, frameCount, animBoneTT, interpol, values, valueCount, frame) );
			break;
		case 2: //Closing Parenthesis
			DBGLOG("\t\t\tClosing Paren\n");
			return s.top();
			break;
		case 3: //Animation track
			DBGLOG("\t\t\tAnimation, bone: %d, track: %d", Model_Bayo_DecodeMotionIndex<big>(animBoneTT, v.boneIndex), v.animationTrack);
			s.push(tmpValues[frame + v.animationTrack * frameCount + Model_Bayo_DecodeMotionIndex<big>(animBoneTT, v.boneIndex) * frameCount * maxCoeffs]);
			DBGLOG(", val: %f\n", s.top());
			break;
		case 4: //Immediate
			DBGLOG("\t\t\tImmediate: %f\n", v.value);
			s.push(v.value);
			break;
		case 5: // Arithmetic
			if (v.boneIndex == 0) {
				o = '+';
			}
			else if (v.boneIndex == 2) {
				o = '*';
			}
			DBGLOG("\t\t\tArithmetic: %c\n", o);
			break;
		case 6: // Function call
			DBGLOG("\t\t\tFunction: abs\n");
			s.push( abs( Model_Bayo2_DecodeEXP_Value<big>(tmpValues, bone_number, frameCount, animBoneTT, interpol, values, valueCount, frame) ) );
			break;
		case 7: // End function call
			DBGLOG("\t\t\tEnd Function\n");
			return s.top();
			break;
		case 8: // interpolate
			DBGLOG("Interpolate\n");
			s.push(0.0);
			break;
		}

	}
	return s.top();
}
template <bool big>
static void Model_Bayo2_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	static int maxCoeffs = 10;
	if (expfile.Num() > 0) {
		DBGLOG("\tapplying: %s\n", expfile[0]->name);
		BYTE *data = expfile[0]->data;
		size_t dataSize = expfile[0]->dataSize;
		if (dataSize < sizeof(bayo2EXPHdr_t))
		{
			return;
		}
		bayo2EXPHdr<big> hdr((bayo2EXPHdr_t *)data);
		BYTE *interpol = data + hdr.offsetInterpolationData;
		for (int i = 0; i < hdr.numRecords; i++) {
			bayo2EXPRecord<big> record((bayo2EXPRecord_t *)(data + hdr.offsetRecords + i * sizeof(bayo2EXPRecord_t)));
			short int targetBone = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, record.boneIndex);
			char targetTrack = record.animationTrack;
			DBGLOG("\t\tfound bone: %d, track: %d, numValues: %d\n", targetBone, targetTrack, record.valueCount);
			for (int fi = 0; fi < frameCount; fi++) {
				BYTE *vals = data + hdr.offsetRecords + i * sizeof(bayo2EXPRecord_t) + record.offset;
				int count = record.valueCount;
				float value = Model_Bayo2_DecodeEXP_Value<big>(
					tmpValues,
					bone_number,
					frameCount,
					animBoneTT,
					interpol,
					vals,
					count,
					fi);
				DBGLOG("\t\t%f\n", value);
				tmpValues[fi + targetTrack * frameCount + targetBone * frameCount * maxCoeffs] = value;
			}
		}
	}
}
template <bool big, game_t game>
inline static void Model_Bayo_ApplyEXP(CArrayList<bayoDatFile_t *> & expfile, float * tmpValues, const int bone_number, const short int frameCount, short int * animBoneTT) {
	if (game == BAYONETTA) {
		Model_Bayo1_ApplyEXP<big>(expfile, tmpValues, bone_number, frameCount, animBoneTT);
	}
	else if (game == BAYONETTA2) {
		Model_Bayo2_ApplyEXP<big>(expfile, tmpValues, bone_number, frameCount, animBoneTT);
	}
}
//apply rotate/translate to model matrix
static void Model_Bayo_ApplyMotions(modelMatrix_t * matrixes, float * tmpValues, modelBone_t *bones, const int boneNumber, const short int frameCount) {
	const int maxCoeffs = 10;
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
			float translate[3];
			float rotate[3];
			float scale[3];
			//int rotate_order[3] = {2,1,0};
			float rotate_coeff[3] = {-1.0, 1.0, -1.0};
			float translate_coeff[3] = {1.0, 1.0, 1.0};
			float scale_coeff[3] = {1.0, 1.0, 1.0};

			for ( int i = 0; i < 3; i++) {
				translate[i] = translate_coeff[i] * tmpValues[fi + i * frameCount + bi *  frameCount * maxCoeffs];
			}
			for ( int i = 3, j = 0; i < 6; i++, j++) {
				rotate[j] = rotate_coeff[j] * tmpValues[fi + i * frameCount + bi *  frameCount * maxCoeffs];
			}
			for ( int i = 7, j = 0; i < 10; i++, j++) {
				scale[j] = scale_coeff[j] * tmpValues[fi + i * frameCount + bi *  frameCount * maxCoeffs];
			}
			DBGALOG("\t\ttranslate: %f, %f, %f\n", translate[0], translate[1], translate[2]);
			DBGALOG("\t\tref relative: %f, %f, %f\n",
			bones[bi].mat.o[0] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[0] : 0.0),
			bones[bi].mat.o[1] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[1] : 0.0),
			bones[bi].mat.o[2] - (bones[bi].eData.parent ? bones[bi].eData.parent->mat.o[2] : 0.0));

			g_mfn->Math_TranslateMatrix(&matrixes[bi + boneNumber * fi], translate);

			DBGALOG("\t\trotate: %f, %f, %f\n", rotate[0], rotate[1], rotate[2]);

			g_mfn->Math_RotateMatrix(&matrixes[bi + boneNumber * fi], rotate[2], 0.0f, 0.0f, 1.0f);
			g_mfn->Math_RotateMatrix(&matrixes[bi + boneNumber * fi], rotate[1], 0.0f, 1.0f, 0.0f);
			g_mfn->Math_RotateMatrix(&matrixes[bi + boneNumber * fi], rotate[0], 1.0f, 0.0f, 0.0f);

			DBGALOG("\t\tscale: %f, %f, %f\n", scale[0], scale[1], scale[2]);
			for ( int i = 0; i < 3; i++ ) {
				matrixes[bi + boneNumber * fi].x1[i] *= scale[i];
				matrixes[bi + boneNumber * fi].x2[i] *= scale[i];
				matrixes[bi + boneNumber * fi].x3[i] *= scale[i];
			}
		}
	}
}
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader4_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = h->values[j];
		if (big) LITTLE_BIG_SWAP(fvals[j]);
	}
}
static FloatDecompressor C(6, 9, 47);
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader6_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader7_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big>
static inline void Model_Bayo_DecodeInterpolateHeader(float * fvals, bayoInterpolHeader8_t *h) {
	for(int j = 0; j < 6; j++) {
		fvals[j] = C.decompress(h->values[j], big);
	}
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe4<big> &p_v, bayoInterpolKeyframe4<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int frameCount, bayoInterpolKeyframe6<big> &p_v, bayoInterpolKeyframe6<big> &v) {
	if (game == BAYONETTA2) {
		firstFrame = p_v.index;
		lastFrame = v.index;
	}else {
		firstFrame = frameCount - 1;
		lastFrame = frameCount - 1 + v.index;
	}
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe7<big> &p_v, bayoInterpolKeyframe7<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <bool big, game_e game>
static inline void Model_Bayo_DecodeFrameIndex(short int &firstFrame, short int &lastFrame, short int, bayoInterpolKeyframe8<big> &p_v, bayoInterpolKeyframe8<big> &v) {
	firstFrame = p_v.index;
	lastFrame = v.index;
}
template <class T>
static void Model_Bayo_HermitInterpolate(float * tmpValues, float *fvals, const T &p_v, const T &v, short int &frameCount, const short int first_frame, const short int last_frame) {
	float p0, p1, m0, m1;
	p0 = fvals[0] + fvals[1] * p_v.coeffs[0];
	p1 = fvals[0] + fvals[1] * v.coeffs[0];
	m0 = fvals[4] + fvals[5] * p_v.coeffs[2];
	m1 = fvals[2] + fvals[3] * v.coeffs[1];

	for(; frameCount <= last_frame; frameCount++) {
		float t;
		t = (float)(frameCount - first_frame)/(last_frame - first_frame);
		tmpValues[frameCount] = (2*t*t*t - 3*t*t + 1)*p0 + (t*t*t - 2*t*t + t)*m0 + (-2*t*t*t + 3*t*t)*p1 + (t*t*t - t*t)*m1;
		DBGALOG("%f, %d, %f\n\t", t, frameCount, tmpValues[frameCount]);
	}
	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", v.index, v.coeffs[0], v.coeffs[1], v.coeffs[2],
			fvals[0] + fvals[1] * v.coeffs[0],
			fvals[2] + fvals[3] * v.coeffs[1],
			fvals[4] + fvals[5] * v.coeffs[2]);
}
//interpolate motion
template <bool big, game_e game, class T1, class T2, class T3>
static void Model_Bayo_Interpolate(float * tmpValues, BYTE * data, const short int elemNumber, short int length) {
	short int frameCount;
	T1 *h = (T1 *)(data);
	T2 *v_p = (T2 *)(h+1);
	T2 *p_v_p;

	float fvals[6];
	Model_Bayo_DecodeInterpolateHeader<big>(fvals, h);
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

	T3 t_v(v_p);
	DBGALOG("%3d %5d %5d %5d (%+f %+f %+f)\n\t", t_v.index, t_v.coeffs[0], t_v.coeffs[1], t_v.coeffs[2],
			fvals[0] + fvals[1] * t_v.coeffs[0],
			fvals[2] + fvals[3] * t_v.coeffs[1],
			fvals[4] + fvals[5] * t_v.coeffs[2]);
	frameCount = t_v.index;
	float f = fvals[0] + fvals[1] * t_v.coeffs[0];
	for (int j = 0; j < frameCount; j++) {
		tmpValues[j] = f;
		DBGALOG("%d, %f\n\t", j, f);
	}
	tmpValues[frameCount] = f;
	DBGALOG("%f, %d, %f\n\t", 0.0, frameCount, f);

	p_v_p = v_p;
	v_p++;
	frameCount++;

	for (int j = 1; j < elemNumber; j++, p_v_p++, v_p++)
	{
		T3 p_v(p_v_p);
		T3 v(v_p);
		short int first_frame, last_frame;
		Model_Bayo_DecodeFrameIndex<big, game>(first_frame, last_frame, frameCount, p_v, v);
		Model_Bayo_HermitInterpolate(tmpValues, fvals, p_v, v, frameCount, first_frame, last_frame);
	}
	for (int j = frameCount; j < length; j++) {
		tmpValues[j] = tmpValues[frameCount-1];
		DBGALOG("%d, %f\n\t", j, tmpValues[j]);
	}

	DBGALOG("\n");
}
//loat motion file
template <bool big, game_t game>
static void Model_Bayo_LoadMotions(CArrayList<noesisAnim_t *> &animList, CArrayList<bayoDatFile_t *> &motfiles, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT)
{
  const int maxCoeffs = 10;
  for(int mi=0; mi < motfiles.Num(); mi++)
  {
	DBGLOG("Loading %s\n", motfiles[mi]->name);

	BYTE * data     = motfiles[mi]->data;
	size_t dataSize = motfiles[mi]->dataSize;
	int unknownA;
	int frameCount;
	int ofsMotion;
	int numEntries;
	if (game == BAYONETTA2) {
		if (dataSize < sizeof(bayo2MOTHdr_t))
		{
			continue;
		}
		bayo2MOTHdr<big> hdr((bayo2MOTHdr_t *)data);
		if (memcmp(hdr.id, "mot\0", 4))
		{ //not a valid motion file
			continue;
		}
		unknownA = hdr.unknownA;
		frameCount = hdr.frameCount;
		ofsMotion = hdr.ofsMotion;
		numEntries = hdr.numEntries;
	} else {
		if (dataSize < sizeof(bayoMOTHdr_t))
		{
			continue;
		}
		bayoMOTHdr<big> hdr((bayoMOTHdr_t *)data);
		if (memcmp(hdr.id, "mot\0", 4))
		{ //not a valid motion file
			continue;
		}
		unknownA = hdr.unknownA;
		frameCount = hdr.frameCount;
		ofsMotion = hdr.ofsMotion;
		numEntries = hdr.numEntries;
	}

	char fname[MAX_NOESIS_PATH];
	sprintf_s(fname, MAX_NOESIS_PATH, "%s", motfiles[mi]->name);

	modelMatrix_t * matrixes;
	float * tmp_values;
	Model_Bayo_InitMotions(matrixes, tmp_values, bones, bone_number, frameCount, rapi);

	bayoMotItem_t * items = (bayoMotItem_t*)(data + ofsMotion);
	DBGALOG("unknown flag: 0x%04x, frame count: %d, data offset: 0x%04x, record number: %d\n", unknownA, frameCount, ofsMotion, numEntries);
	for(int i=0; i < numEntries; i++) {
		bayoMotItem<big> it(&items[i]);
		if (game == BAYONETTA2) data = (BYTE *)&items[i];
		if( it.boneIndex == 0x7fff || it.boneIndex == -1) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x)\n",it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
			continue;
		} else if ( it.boneIndex >= 0xf60 ) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) special flag 0x2 index\n", it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
		    continue;
		}
		short int boneIndex = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, it.boneIndex);
		if( boneIndex == 0x0fff ) {
			DBGALOG("%5d %3d 0x%02x %3d %3d %+f (0x%08x) cannot translate bone\n", it.boneIndex, it.index, it.flag, it.elem_number, it.unknown, it.value.flt, it.value.offset);
			continue;
		}

		//float tmp_values[65536];
		DBGALOG("%5d (%5d) %3d 0x%02x %3d %3d", boneIndex, it.boneIndex, it.index, it.flag, it.elem_number, it.unknown);
		DBGALOG(" %+f (0x%08x)\n", it.value.flt, it.value.offset);
		if ( boneIndex >= bone_number ) {
			DBGALOG(" out of bone bounds\n");
			continue;
		}
		if ( it.flag == 1 ) {
			float *fdata = (float *)(data + it.value.offset);
			for(int frame_count=0; frame_count < it.elem_number; frame_count++) {
				float f = fdata[frame_count];
				if (big) LITTLE_BIG_SWAP(f);
				tmp_values[frame_count + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = f;
				DBGALOG("\t%3d %+f\n", frame_count, f);
			}
			float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex *  frameCount * maxCoeffs];
			for (int j = it.elem_number; j < frameCount; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = v;
				DBGALOG("\t%d, %f\n", j, v);
			}
		} else if ( it.flag == 2 ) {
			float *fData = (float *)(data + it.value.offset);
			short unsigned int *suiData = (short unsigned int *)&fData[2];
			float fbase = fData[0];
			float fdelta = fData[1];
			if (big) LITTLE_BIG_SWAP(fbase);
			if (big) LITTLE_BIG_SWAP(fdelta);
			DBGALOG("\t%f %f\n", fbase, fdelta);
			for(int frame_count=0; frame_count < it.elem_number; frame_count++) {
				short unsigned int val;
				float f;
				val = suiData[frame_count];
				if (big) LITTLE_BIG_SWAP(val);
				f = fbase + fdelta*val;
				DBGALOG("\t%d %d %f\n", frame_count, val, f);
				tmp_values[frame_count + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = f;
			}
			float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex *  frameCount * maxCoeffs];
			for (int j = it.elem_number; j < frameCount; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = v;
				DBGALOG("\t%d, %f\n", j, v);
			}
		} else if ( it.flag == 3 ) {
			short unsigned int *suiData = (short unsigned int *)(data + it.value.offset);
			BYTE * bData = (BYTE *)&suiData[2];
			float fbase = C.decompress(suiData[0], big);
			float fdelta = C.decompress(suiData[1], big);
			DBGALOG("\t%f %f\n", fbase, fdelta);
			for(int frame_count=0; frame_count < it.elem_number; frame_count++) {
				BYTE val = bData[frame_count];
				float f = fbase + fdelta*val;
				DBGALOG("\t%d %d %f\n", frame_count, val, f);
				tmp_values[frame_count + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = f;
			}
			float v = tmp_values[it.elem_number - 1 + it.index * frameCount + boneIndex *  frameCount * maxCoeffs];
			for (int j = it.elem_number; j < frameCount; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = v;
				DBGALOG("\t%d, %f\n", j, v);
			}
		} else if ( game == BAYONETTA2 && it.flag == 4 ) {
			bayo2InterpolKeyframe4_t *v_p = (bayo2InterpolKeyframe4_t *)(data + it.value.offset);
			bayo2InterpolKeyframe4_t *p_v_p;
			bayo2InterpolKeyframe4<big> t_v(v_p);
			int frame_count = t_v.index;

			DBGALOG("\t%d %f (%f %f)\n", t_v.index, t_v.p, t_v.m0, t_v.m1);
			for (int j = 0; j < frame_count; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = t_v.p;
				DBGALOG("\t%d, %f\n", j, t_v.p);
			}
			tmp_values[frame_count + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = t_v.p;
			DBGALOG("\t%f, %d, %f\n", 0.0, frame_count, t_v.p);
			frame_count++;
			p_v_p = v_p;
			v_p++;
			for(int j = 1; j < it.elem_number; j++, p_v_p++, v_p++)	{
				bayo2InterpolKeyframe4<big> v(v_p);
				bayo2InterpolKeyframe4<big> p_v(p_v_p);
				float p0, p1, m0, m1;
				p0 = p_v.p;
				m0 = p_v.m1;
				p1 = v.p;
				m1 = v.m0;
				for(; frame_count <= v.index; frame_count++) {
					float t;
					float f;
					t = (float)(frame_count - p_v.index)/(v.index - p_v.index);
		            f = (2*t*t*t - 3*t*t + 1)*p0 + (t*t*t - 2*t*t + t)*m0 + (-2*t*t*t + 3*t*t)*p1 + (t*t*t - t*t)*m1;
					tmp_values[frame_count + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = f;
					DBGALOG("\t%f, %d, %f\n", 0.0, frame_count, f);
				}
				DBGALOG("\t%d %f (%f %f)\n", v.index, v.p, v.m0, v.m1);
			}
			float v = tmp_values[frame_count - 1 + it.index * frameCount + boneIndex *  frameCount * maxCoeffs];
			for (int j = frame_count; j < frameCount; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = v;
				DBGALOG("\t%d, %f\n", j, v);
			}
			DBGALOG("\n");
		} else if ( it.flag == 4 || (game == BAYONETTA2 && it.flag == 5) ) {

			Model_Bayo_Interpolate<big, game, bayoInterpolHeader4_t, bayoInterpolKeyframe4_t, bayoInterpolKeyframe4<big>>(tmp_values + it.index * frameCount + boneIndex *  frameCount * maxCoeffs,
									data + it.value.offset,
									it.elem_number, frameCount);
		} else if ( game == BAYONETTA2 && it.flag == 6 ) {

			Model_Bayo_Interpolate<big, BAYONETTA2, bayoInterpolHeader6_t, bayoInterpolKeyframe6_t, bayoInterpolKeyframe6<big>>(tmp_values + it.index * frameCount + boneIndex *  frameCount * maxCoeffs,
									data + it.value.offset,
									it.elem_number, frameCount);

		} else if ( it.flag == 6 || (game == BAYONETTA2 && it.flag == 7) ) {

			Model_Bayo_Interpolate<big, BAYONETTA, bayoInterpolHeader6_t, bayoInterpolKeyframe6_t, bayoInterpolKeyframe6<big>>(tmp_values + it.index * frameCount + boneIndex *  frameCount * maxCoeffs,
									data + it.value.offset,
									it.elem_number, frameCount);

		} else if ( it.flag == 7 ) { //diff from 6 because frame delta would be > 255

			Model_Bayo_Interpolate<big, game, bayoInterpolHeader7_t, bayoInterpolKeyframe7_t, bayoInterpolKeyframe7<big>>(tmp_values + it.index * frameCount + boneIndex *  frameCount * maxCoeffs,
									data + it.value.offset,
									it.elem_number, frameCount);

		} else if ( it.flag == 8 ) {

			Model_Bayo_Interpolate<big, game, bayoInterpolHeader8_t, bayoInterpolKeyframe8_t, bayoInterpolKeyframe8<big>>(tmp_values + it.index * frameCount + boneIndex *  frameCount * maxCoeffs,
									data + it.value.offset,
									it.elem_number, frameCount);

		} else if ( it.flag ==  0xff ) {
			continue;
		} else if ( it.flag != 0 ) {
			DBGLOG("WARNING: Unknown motion flag %02x.\n", it.flag);
			assert(0);
			continue;
			rapi->LogOutput("WARNING: Unknown motion flag %02x.\n", it.flag);
		} else {
			for (int j = 0; j < frameCount; j++) {
				tmp_values[j + it.index * frameCount + boneIndex *  frameCount * maxCoeffs] = it.value.flt;
			}
		}

	}

	for (int bi = 0; bi < bone_number; bi++) {
		for (int fi = 0; fi < frameCount; fi++) {
			tmp_values[fi + 3 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
			tmp_values[fi + 4 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
			tmp_values[fi + 5 * frameCount + bi * frameCount * maxCoeffs] *= g_flRadToDeg;
		}
	}


	Model_Bayo_ApplyEXP<big, game>(expfile, tmp_values, bone_number, frameCount, animBoneTT);

	Model_Bayo_ApplyMotions(matrixes, tmp_values, bones, bone_number, frameCount);

	noesisAnim_t *anim = rapi->rpgAnimFromBonesAndMatsFinish(bones, bone_number, matrixes, frameCount, 60);

	anim->filename = rapi->Noesis_PooledString(fname);
	anim->flags |= NANIMFLAG_FILENAMETOSEQ;
	anim->aseq = rapi->Noesis_AnimSequencesAlloc(1, frameCount);
	anim->aseq->s->startFrame = 0;
	anim->aseq->s->endFrame = frameCount - 1;
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
//gather entries from a dat file
template <bool big>
static void Model_Bayo_GetDATEntries(CArrayList<bayoDatFile_t> &dfiles, BYTE *fileBuffer, int bufferLen)
{
	bayoDat<big> dat((bayoDat_t *)fileBuffer);

	BYTE *namesp = fileBuffer+dat.ofsNames;
	int strSize = *((int *)namesp);
	if (big) LITTLE_BIG_SWAP(strSize);
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
		if (big) LITTLE_BIG_SWAP(df.dataSize);
		sizep++;

		int ofs = *ofsp;
		if (big) LITTLE_BIG_SWAP(ofs);
		df.data = fileBuffer+ofs;
		ofsp++;

		dfiles.Append(df);
	}
}
template <bool big, game_t game>
static void Model_Bayo_LoadExternalMotions(CArrayList<noesisAnim_t *> &animList, bayoDatFile_t &df, CArrayList<bayoDatFile_t *> &expfile, modelBone_t *bones, int bone_number, noeRAPI_t *rapi, short int * animBoneTT){
	noeUserPromptParam_t promptParams;
	char wmbName[MAX_NOESIS_PATH];
	char motionPrompt[MAX_NOESIS_PATH];
	rapi->Noesis_GetExtensionlessName(wmbName, df.name);
	sprintf_s(motionPrompt, MAX_NOESIS_PATH, "Load motions for %s in other files?", wmbName);
	promptParams.titleStr = "Load motions?";
	promptParams.promptStr = motionPrompt;
	promptParams.defaultValue = "Just click!";
	promptParams.valType = NOEUSERVAL_NONE;
	promptParams.valHandler = NULL;
	wchar_t noepath[MAX_NOESIS_PATH];
	GetCurrentDirectory(MAX_NOESIS_PATH, noepath);

	while( g_nfn->NPAPI_UserPrompt(&promptParams) ) {
		int dataLength;
		BYTE* data = rapi->Noesis_LoadPairedFile("Bayonetta PC Model", ".dat", dataLength, NULL);
		if (data) {
			CArrayList<bayoDatFile_t> datfiles;
			Model_Bayo_GetDATEntries<big>(datfiles, data, dataLength);
			if(datfiles.Num() > 0) {
				CArrayList<bayoDatFile_t *> motfiles;
				Model_Bayo_GetMotionFiles(datfiles, df, rapi, motfiles);
				if(motfiles.Num() > 0) {
					Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, bone_number, rapi, animBoneTT);
				}
				motfiles.Clear();
			}
			datfiles.Clear();
		}
		rapi->Noesis_UnpooledFree(data);
	}
	SetCurrentDirectory(noepath);
}
//decode bayonetta x10y10z10 normals
template <bool big, game_t game>
static void Model_Bayo_CreateNormal(char *src, float *dst);
template <>
static void Model_Bayo_CreateNormal<true, BAYONETTA2>(char *src, float *dst) {
	DWORD r;
	memcpy(&r, src, sizeof(r));
	LITTLE_BIG_SWAP(r);
	int xBits = 10;
	int yBits = 10;
	int zBits = 10;
	int x = ((r>>0) & ((1<<xBits)-1));
	int y = ((r>>xBits) & ((1<<yBits)-1));
	int z = ((r>>(xBits+yBits)) & ((1<<zBits)-1));
	dst[0] = (float)SignedBits(x, xBits) / (float)((1<<(xBits-1))-1);
	dst[1] = (float)SignedBits(y, yBits) / (float)((1<<(yBits-1))-1);
	dst[2] = (float)SignedBits(z, zBits) / (float)((1<<(zBits-1))-1);
}
template <>
static void Model_Bayo_CreateNormal<true, BAYONETTA>(char *src, float *dst) {
	return Model_Bayo_CreateNormal<true, BAYONETTA2>(src, dst);
}
template <>
static void Model_Bayo_CreateNormal<false, BAYONETTA>(char *src, float *dst) {
	for (int j = 0; j < 3;  j++) {
		dst[j] = (float)src[3-j]/(float)127;
	}
}
template <bool big, game_t game>
static void Model_Bayo_CreateNormals(BYTE *data, float *dsts, int numVerts, int stride)
{
	for (int i = 0; i < numVerts; i++)
	{
		char *src = (char *)(data + stride*i);
		float *dst = dsts+i*3;
		Model_Bayo_CreateNormal<big, game>(src, dst);
		g_mfn->Math_VecNorm(dst);
		if(big) {
			LITTLE_BIG_SWAP(dst[0]);
			LITTLE_BIG_SWAP(dst[1]);
			LITTLE_BIG_SWAP(dst[2]);
		}
	}
}

template <bool big, game_t game>
static void Model_Bayo_CreateTangents(BYTE *data, float *dsts, int numVerts, int stride)
{
	for (int i = 0; i < numVerts; i++)
	{
		uint32_t src = *((uint32_t *)(data + stride * i));
		float *dst = dsts + i * 4;
		for (int j = 0; j < 4; j++) {
			dst[j] = ((float)((src >> (8*i)) & 0xff) - (float)127) / (float)127;
		}
		g_mfn->Math_VecNorm(dst);
		if (big) {
			for (int j = 0; j < 4; j++) {
				LITTLE_BIG_SWAP(dst[j]);
			}
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
	short *parentList = (short *)(data+hdr.ofsBoneHie);
	float *posList = (float *)(data+hdr.ofsBoneDataB);
	float *relPosList = (float *)(data+hdr.ofsBoneDataA); //actually relative positions
	animBoneTT = (short int *)(data+hdr.ofsBoneHieB);
	std::map<short int, short int> boneMap;
	for (short int i = 0; i < 0x1000; i++) {
		short int decoded_index = Model_Bayo_DecodeMotionIndex<big>(animBoneTT, i);
		if (decoded_index != 0x0fff) {
			boneMap.insert(std::pair <short int, short int>(decoded_index, i));
		}
	}

	numBones = hdr.numBones;
	DBGLOG("Found %d bones\n", numBones);
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones);
	for (int i = 0; i < numBones; i++)
	{
		modelBone_t *bone = bones + i;
		float *ppos = posList + i*3;
		short parent = parentList[i];
		if (big) LITTLE_BIG_SWAP(parent);
		assert(parent < numBones);
		bone->index = i;
		bone->eData.parent = (parent >= 0) ? bones+parent : NULL;
		sprintf_s(bone->name, 30, "bone%03i", boneMap.at((short int)i));
		bone->mat = g_identityMatrix;
		float pos[3];

		memcpy(pos, ppos, sizeof(pos));
		if (big)  {
			LITTLE_BIG_SWAP(pos[0]);
			LITTLE_BIG_SWAP(pos[1]);
			LITTLE_BIG_SWAP(pos[2]);
		}
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
		float relPos[3];
		memcpy(relPos, relPosList + 3*bi, sizeof(relPos));
		if (big)  {
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

//load Bayonetta Material
template <bool big>
static void Model_Bayo_LoadMaterials(bayoWMBHdr<big> &hdr,
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
		if (big) LITTLE_BIG_SWAP(numMatIDs);
		matIDs++;
	}
	DBGLOG("Found %d materials\n", hdr.numMaterials);
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
		nmat->name = rapi->Noesis_PooledString(matName);
		//nmat->flags |= NMATFLAG_TWOSIDED;

		if (hasExMatInfo && numMatIDs > 0)
		{ //search by global index values
			DBGLOG("vanquish style\n");
			nmat->noDefaultBlend = true;
			nmat->normalTexIdx = (textures.Num() > 0) ? textures.Num()-1 : -1; //default to flat normal
			char *shaderName = (char *)(data + hdr.exMatInfo[0] + 16*i);
			if (_strnicmp(shaderName, "har", 3) == 0 || _strnicmp(shaderName, "gla", 3) == 0 || _strnicmp(shaderName, "cnm", 3) == 0 || _strnicmp(shaderName, "alp", 3) == 0)
			{ //blend hair
				nmat->noDefaultBlend = false;
			}
			bool isSkin = (_strnicmp(shaderName, "skn0", 4) == 0);
			bool isPHG = (_strnicmp(shaderName, "phg05", 5) == 0);
			bool isLBT = (_strnicmp(shaderName, "lbt00", 5) == 0);
			bool raSwap = (_strnicmp(shaderName, "max32", 5) == 0); //hacky way to see if the normal needs red and alpha swapped, probably not reliable
			int difTexId = *((int *)(matData + 4));
			int nrmOfs = (isPHG || isLBT) ? 8 : 16;
			int nrmTexId = *((int *)(matData + nrmOfs)); //this is kinda happenstance, i think the only right way to know what to do is to check the pixel shader
			DBGLOG("\t\tshader: %s, diff: 0x%0x, nrm: 0x%0x\n", shaderName, difTexId, nrmTexId);
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
			wmbMat<big> mat((wmbMat_t *)matData);

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
template <bool big, game_t game>
static void Model_Bayo_LoadModel(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi, CArrayList<noesisModel_t *> &models)
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

	bool hasExMatInfo;

	Model_Bayo_GetTextureBundle<game>(texFiles, dfiles, df, rapi);
	if (texFiles.Num() > 0)
	{
		for( int i = 0; i < texFiles.Num(); i++) {
			DBGLOG("Found texture bundle %s\n", texFiles[i]->name);
		}
		Model_Bayo_LoadTextures<big,game>(textures, texFiles, rapi);
	}

	Model_Bayo_LoadMaterials<big>(hdr, textures, hasExMatInfo, matList, matListLightMap, totMatList, data, rapi);
	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetEndian(big);
	BYTE *vertData = data + hdr.ofsVerts;
	const int bayoVertSize = 32;//(hdr.ofsVerts > 128) ? 48 : 32;

	int numBones;
	short int * animBoneTT;
	modelBone_t *bones = Model_Bayo_CreateBones<big>(hdr, data, rapi, numBones, animBoneTT);

	Model_Bayo_GetMotionFiles(dfiles, df, rapi, motfiles);
	Model_Bayo_GetEXPFile(dfiles, df, rapi, expfile);
	Model_Bayo_LoadMotions<big, game>(animList, motfiles, expfile, bones, numBones, rapi, animBoneTT);

	Model_Bayo_LoadExternalMotions<big, game>(animList, df, expfile, bones, numBones, rapi, animBoneTT);

	//decode normals
	float *normals = (float *)rapi->Noesis_PooledAlloc(sizeof(float) * 3 * hdr.numVerts);
	Model_Bayo_CreateNormals<big, game>(vertData + 16, normals, hdr.numVerts, bayoVertSize);
	float *tangents = (float *)rapi->Noesis_PooledAlloc(sizeof(float) * 4 * hdr.numVerts);
	Model_Bayo_CreateTangents<big, game>(vertData + 20, tangents, hdr.numVerts, bayoVertSize);

	BYTE *meshStart = data + hdr.ofsMeshes;
	int *meshOfsList = (int *)(data + hdr.ofsMeshOfs);
	DBGLOG("Found %d meshes\n", hdr.numMeshes);
	for (int i = 0; i < hdr.numMeshes; i++)
	{
		//if (i != 0) continue;
		int meshOfs = meshOfsList[i];
		if (big) LITTLE_BIG_SWAP(meshOfs);
		wmbMesh<big> mesh((wmbMesh_t *)(meshStart+meshOfs));
		DBGLOG("\t%3d: id: %d, offset: %x, name: %s\n", i, mesh.id , hdr.ofsMeshes+meshOfs, mesh.name);
		int *batchOfsList = (int *)(meshStart+meshOfs+mesh.batchOfs);
		for (int j = 0; j < mesh.numBatch; j++)
		{
			char batch_name[256];
			DBGLOG("\t\t%3d: ", j);
			int batchOfs = batchOfsList[j];
			if (big) LITTLE_BIG_SWAP(batchOfs);
			BYTE *batchData = (BYTE *)batchOfsList + batchOfs;
			wmbBatch<big> batch((wmbBatch_t *)batchData);
			DBGLOG("%d, %x, %x, %x, %x, %x, ", batch.id, batch.unknownB, batch.unknownC, batch.unknownDB, batch.unknownE1, batch.unknownE2);
			if ((game == BAYONETTA && batch.unknownE1 == 0x20 && batch.unknownE2 == 0x0f) || (game == BAYONETTA2 && batch.unknownE1 == 0x30)) {
				sprintf_s(batch_name, 256, "%02d(%s)_%02d_s", i, mesh.name, j);
			}
			else {
				sprintf_s(batch_name, 256, "%02d(%s)_%02d", i, mesh.name, j);
			}
			rapi->rpgSetName(rapi->Noesis_PooledString(batch_name));
			/*if (batch.unknownE == 0xf20) {
				DBGLOG("skipped (shadow model)\n");
				continue; // shadow meshes
			}*/
			int numBoneRefs = *((int *)(batchData+sizeof(wmbBatch_t)));
			if (big) LITTLE_BIG_SWAP(numBoneRefs);
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
			//bind tangents
			rapi->rpgBindTangentBuffer(tangents + vertOfs * 4, RPGEODATA_FLOAT, sizeof(float) * 4);
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
/*			if(texID < matList.Num() && matList[texID]->ex->pUvScaleBias) {
				rapi->rpgSetUVScaleBias(matList[texID]->ex->pUvScaleBias, matList[texID]->ex->pUvScaleBias + 2);
			} else {
				rapi->rpgSetUVScaleBias(NULL, NULL);
			}*/
/*			if(matListLightMap[texID]) {
				rapi->rpgSetLightmap(matListLightMap[texID]->name);
				rapi->rpgBindUV2Buffer(vertData+20 + vertOfs*bayoVertSize, RPGEODATA_HALFFLOAT, bayoVertSize);
			} else {
				rapi->rpgSetLightmap(NULL);
				rapi->rpgBindUV2Buffer(NULL, RPGEODATA_HALFFLOAT, 0);
			}*/
			DBGLOG("primType: %d, numIndices: %d\n", batch.primType, batch.numIndices);
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
/*    int anims_num = 0;
	if( animList.Num() > 0 ) {
		rapi->rpgSetExData_AnimsNum(animList[0], 1);
	}*/
	int anims_num = animList.Num();
    noesisAnim_t *anims = rapi->Noesis_AnimFromAnimsList(animList, anims_num);
	//for(int i = 0; i < anims_num; i++) {
	//	DBGLOG("anim: %s, size: %d, flag: %d\n", animList[i]->filename, animList[i]->dataLen, animList[i]->flags & NANIMFLAG_FILENAMETOSEQ);
	//	DBGLOG("seq: %p, size: %d\n", (anims+i)->aseq, (anims+i)->dataLen );
	//}
    rapi->rpgSetExData_AnimsNum(anims, 1);
	//rapi->rpgMultiplyBones(bones, numBones);
	DBGLOG("Found %d anims\n", anims_num);
	rapi->rpgSetTriWinding(true); //bayonetta uses reverse face windings
	//rapi->rpgSetName(rapi->Noesis_PooledString(df.name));
	noesisModel_t *mdl = rapi->rpgConstructModel();
	if( mdl ) {
		models.Append(mdl);
	}
/*	for(int i = 0; i < anims_num; i++) {
		noesisModel_t *mdl = rapi->rpgConstructModel();
		if( mdl ) {
			models.Append(mdl);
			rapi->Noesis_SetModelAnims(mdl, animList[i], 1);
		}
	}*/
	
	rapi->rpgDestroyContext(pgctx);

	animList.Clear();
	matList.Clear();
	motfiles.Clear();
	texFiles.Clear();
	textures.Clear();
	matListLightMap.Clear();
	totMatList.Clear();
}


//load it
template <bool big, game_t game>
noesisModel_t *Model_Bayo_Load(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	CArrayList<bayoDatFile_t> dfiles;
	DBGLOG("Loading model\n");
	//create a list of resources
	Model_Bayo_GetDATEntries<big>(dfiles, fileBuffer, bufferLen);
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
			Model_Bayo_LoadModel<big, game>(dfiles, df, rapi, models);
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
	int fh_b2 = g_nfn->NPAPI_Register("Bayonetta 2 Big Endian Model", ".dat");
	if (fh_b2 < 0)
	{
		return false;
	}
	int fh_b = g_nfn->NPAPI_Register("Bayonetta Big Endian Model (WiiU)", ".dat");
	if (fh_b < 0)
	{
		return false;
	}
	OPENLOG();
	bayoSetMatTypes();
	//set the data handlers for this format
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh, Model_Bayo_Check<false, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh, Model_Bayo_Load<false, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_b2, Model_Bayo_Check<true, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_b2, Model_Bayo_Load<true, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_b, Model_Bayo_Check<true, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_b, Model_Bayo_Load<true, BAYONETTA>);

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
