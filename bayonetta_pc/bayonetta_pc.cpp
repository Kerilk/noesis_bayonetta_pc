//this is kind of a poor example for plugins, since the format's not totally known and the code is WIP.
//but it does showcase some interesting usages.

#include "stdafx.h"

const char *g_pPluginName = "bayonetta_pc";
const char *g_pPluginDesc = "Bayonetta PC model handler, by Dick, Kerilk.";

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
	int					ofsUnknowns;
	int					resva;
	int					resvb;
} bayoWTBHdr_t;
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
	BYTE				id[4];
	int					unknownA;
	WORD				unknownB;
	WORD				unknownC;
	int					numVerts;
	WORD				unknownD;
	WORD				unknownE;
	int					unknownF;
	int					ofsVerts;
	int					ofsVertExData;
	int					unknownG[4];
	int					numBones;
	int					ofsBoneHie;
	int					ofsBoneDataA;
	int					ofsBoneDataB;
	int					ofsBoneHieB;
	int					numMaterials;
	int					ofsMaterialsOfs;
	int					ofsMaterials;
	int					numMeshes;
	int					ofsMeshOfs;
	int					ofsMeshes;
	int					unknownK;
	int					unknownL;
	int					ofsUnknownJ;
	int					ofsUnknownK;
	int					ofsUnknownL;
	int					exMatInfo[4];
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
typedef struct wmbMat_s
{
	WORD				matFlags;
	WORD				unknownB;
	WORD				texFlagsA;
	WORD				texIdxA;
	WORD				texFlagsB;
	WORD				texIdxB;
	WORD				texFlagsC;
	WORD				texIdxC;
	WORD				texFlagsD;
	WORD				texIdxD;
	WORD				texFlagsE;
	WORD				texIdxE;
} wmbMat_t;

//see if something is a valid bayonetta .dat
bool Model_Bayo_Check(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi)
{
	if (bufferLen < sizeof(bayoDat_t))
	{
		return false;
	}
	bayoDat_t dat = *((bayoDat_t *)fileBuffer);
	if (memcmp(dat.id, "DAT\0", 4))
	{
		return false;
	}
	LITTLE_BIG_SWAP(dat.numRes);
	LITTLE_BIG_SWAP(dat.ofsRes);
	LITTLE_BIG_SWAP(dat.ofsType);
	LITTLE_BIG_SWAP(dat.ofsNames);
	LITTLE_BIG_SWAP(dat.ofsSizes);
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
	LITTLE_BIG_SWAP(strSize);
	namesp += sizeof(int);
	if (strSize <= 0 || strSize >= bufferLen || dat.ofsNames+(int)sizeof(int)+(strSize*dat.numRes) > bufferLen)
	{
		return false;
	}
	int numWMB = 0;
	int numMOT = 0;
	for (int i = 0; i < dat.numRes; i++)
	{
		char *name = (char *)namesp;
		if (name[strSize-1])
		{ //incorrectly terminated string
			return false;
		}
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

//load texture bundle
static void Model_Bayo_LoadTextures(CArrayList<noesisTex_t *> &textures, BYTE *data, int dataSize, noeRAPI_t *rapi)
{
	if (dataSize < sizeof(bayoWTBHdr_t))
	{
		return;
	}
	bayoWTBHdr_t hdr = *((bayoWTBHdr_t *)data);
	if (memcmp(hdr.id, "\0BTW", 4))
	{ //not a valid texture bundle
		return;
	}
	LITTLE_BIG_SWAP(hdr.numTex);
	LITTLE_BIG_SWAP(hdr.ofsTexOfs);
	LITTLE_BIG_SWAP(hdr.ofsTexSizes);
	LITTLE_BIG_SWAP(hdr.ofsUnknowns);
	LITTLE_BIG_SWAP(hdr.resva);
	LITTLE_BIG_SWAP(hdr.resvb);
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
		if (hdr.resva)
		{ //global id's (probably generated as checksums)
			int *ip = (int  *)(data+hdr.resva+sizeof(int)*i);
			globalIdx = *ip;
		}
		if (hdr.resvb)
		{ //texture info is contiguous in its own section
			wtbTexHdr_t *thdr = (wtbTexHdr_t  *)(data+hdr.resvb+sizeof(wtbTexHdr_t)*i);
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
}

//decode bayonetta x10y10z10 normals
static void Model_Bayo_CreateNormals(BYTE *data, float *dsts, int numVerts, int stride, bool eet)
{
	for (int i = 0; i < numVerts; i++)
	{
		BYTE *src = (BYTE *)(data + stride*i);
		float *dst = dsts+i*3;
		DWORD r;
		memcpy(&r, src, sizeof(r));
		LITTLE_BIG_SWAP(r);
		int xBits = (eet) ? 11 : 10;
		int yBits = (eet) ? 11 : 10;
		int zBits = 10;
		int x = ((r>>0) & ((1<<xBits)-1));
		int y = ((r>>xBits) & ((1<<yBits)-1));
		int z = ((r>>(xBits+yBits)) & ((1<<zBits)-1));
		dst[0] = (float)SignedBits(x, xBits) / (float)((1<<(xBits-1))-1);
		dst[1] = (float)SignedBits(y, yBits) / (float)((1<<(yBits-1))-1);
		dst[2] = (float)SignedBits(z, zBits) / (float)((1<<(zBits-1))-1);
		g_mfn->Math_VecNorm(dst);
		LITTLE_BIG_SWAP(dst[0]);
		LITTLE_BIG_SWAP(dst[1]);
		LITTLE_BIG_SWAP(dst[2]);
	}
}

//convert the bones
modelBone_t *Model_Bayo_CreateBones(bayoWMBHdr_t &hdr, BYTE *data, noeRAPI_t *rapi, int &numBones)
{
	numBones = 0;
	if (hdr.numBones <= 0 || hdr.ofsBoneHie <= 0 || hdr.ofsBoneDataA <= 0 || hdr.ofsBoneDataB <= 0)
	{
		return NULL;
	}
	short *parentList = (short *)(data+hdr.ofsBoneHie);
	float *posList = (float *)(data+hdr.ofsBoneDataB);
	//float *rotList = (float *)(data+hdr.ofsBoneDataA); //actually relative positions
	numBones = hdr.numBones;
	modelBone_t *bones = rapi->Noesis_AllocBones(numBones);
	for (int i = 0; i < numBones; i++)
	{
		modelBone_t *bone = bones + i;
		float *ppos = posList + i*3;
		short parent = parentList[i];
		LITTLE_BIG_SWAP(parent);
		assert(parent < numBones);
		bone->index = i;
		bone->eData.parent = (parent >= 0) ? bones+parent : NULL;
		sprintf_s(bone->name, 30, "bone%03i", i);
		bone->mat = g_identityMatrix;
		float pos[3];
		memcpy(pos, ppos, sizeof(pos));
		LITTLE_BIG_SWAP(pos[0]);
		LITTLE_BIG_SWAP(pos[1]);
		LITTLE_BIG_SWAP(pos[2]);
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
	//bones come pre-transformed
	//rapi->rpgMultiplyBones(bones, numBones);
	return bones;
}

//load a single model from a dat set
static noesisModel_t *Model_Bayo_LoadModel(CArrayList<bayoDatFile_t> &dfiles, bayoDatFile_t &df, noeRAPI_t *rapi)
{
	BYTE *data = df.data;
	int dataSize = df.dataSize;
	if (dataSize < sizeof(bayoWMBHdr_t))
	{
		return NULL;
	}
	bayoWMBHdr_t hdr = *((bayoWMBHdr_t *)data);
	if (memcmp(hdr.id, "\0BMW", 4))
	{ //invalid header
		return NULL;
	}
	LITTLE_BIG_SWAP(hdr.unknownA);
	LITTLE_BIG_SWAP(hdr.unknownB);
	LITTLE_BIG_SWAP(hdr.unknownC);
	LITTLE_BIG_SWAP(hdr.numVerts);
	LITTLE_BIG_SWAP(hdr.unknownD);
	LITTLE_BIG_SWAP(hdr.unknownE);
	LITTLE_BIG_SWAP(hdr.unknownF);
	LITTLE_BIG_SWAP(hdr.ofsVerts);
	LITTLE_BIG_SWAP(hdr.ofsVertExData);
	LITTLE_BIG_SWAP(hdr.numBones);
	LITTLE_BIG_SWAP(hdr.ofsBoneHie);
	LITTLE_BIG_SWAP(hdr.ofsBoneDataA);
	LITTLE_BIG_SWAP(hdr.ofsBoneDataB);
	LITTLE_BIG_SWAP(hdr.ofsBoneHieB);
	LITTLE_BIG_SWAP(hdr.numMaterials);
	LITTLE_BIG_SWAP(hdr.ofsMaterialsOfs);
	LITTLE_BIG_SWAP(hdr.ofsMaterials);
	LITTLE_BIG_SWAP(hdr.numMeshes);
	LITTLE_BIG_SWAP(hdr.ofsMeshOfs);
	LITTLE_BIG_SWAP(hdr.ofsMeshes);
	LITTLE_BIG_SWAP(hdr.unknownK);
	LITTLE_BIG_SWAP(hdr.unknownL);
	LITTLE_BIG_SWAP(hdr.ofsUnknownJ);
	LITTLE_BIG_SWAP(hdr.ofsUnknownK);
	LITTLE_BIG_SWAP(hdr.ofsUnknownL);
	LITTLE_BIG_SWAP(hdr.exMatInfo[0]);
	LITTLE_BIG_SWAP(hdr.exMatInfo[1]);
	LITTLE_BIG_SWAP(hdr.exMatInfo[2]);
	LITTLE_BIG_SWAP(hdr.exMatInfo[3]);
	bool isVanqModel = (hdr.unknownA < 0);

	CArrayList<noesisTex_t *> textures;
	CArrayList<noesisMaterial_t *> matList;
	bayoDatFile_t *texBundle = Model_Bayo_GetTextureBundle(dfiles, df, rapi);
	if (texBundle)
	{
		Model_Bayo_LoadTextures(textures, texBundle->data, texBundle->dataSize, rapi);
	}
	int *matOfsList = (int *)(data + hdr.ofsMaterialsOfs);
	bool hasExMatInfo = (hdr.exMatInfo[0] && hdr.exMatInfo[1] && hdr.exMatInfo[2] && hdr.exMatInfo[3]);
	int *matIDs = (hasExMatInfo) ? (int *)(data + hdr.exMatInfo[1]) : NULL;
	int numMatIDs = 0;
	if (matIDs)
	{ //got a global reference list (this seems redundant since it's also provided in the texture bundle)
		numMatIDs = *matIDs;
		LITTLE_BIG_SWAP(numMatIDs);
		matIDs++;
	}

	for (int i = 0; i < hdr.numMaterials; i++)
	{
		int matOfs = matOfsList[i];
		LITTLE_BIG_SWAP(matOfs);
		BYTE *matData = data + hdr.ofsMaterials + matOfs;
		//create a noesis material entry
		char matName[128];
		sprintf_s(matName, 128, "bayomat%i", i);
		noesisMaterial_t *nmat = rapi->Noesis_GetMaterialList(1, true);
		nmat->name = rapi->Noesis_PooledString(matName);
		nmat->noDefaultBlend = true;
		if (hasExMatInfo && numMatIDs > 0)
		{ //search by global index values
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
			LITTLE_BIG_SWAP(mat.matFlags);
			LITTLE_BIG_SWAP(mat.unknownB);
			LITTLE_BIG_SWAP(mat.texFlagsA);
			LITTLE_BIG_SWAP(mat.texIdxA);
			LITTLE_BIG_SWAP(mat.texFlagsB);
			LITTLE_BIG_SWAP(mat.texIdxB);
			LITTLE_BIG_SWAP(mat.texFlagsC);
			LITTLE_BIG_SWAP(mat.texIdxC);
			LITTLE_BIG_SWAP(mat.texFlagsD);
			LITTLE_BIG_SWAP(mat.texIdxD);
			LITTLE_BIG_SWAP(mat.texFlagsE);
			LITTLE_BIG_SWAP(mat.texIdxE);
			nmat->texIdx = mat.texIdxA;
			int blendVal = ((mat.matFlags>>4) & 15); //no idea if this is correct. it probably isn't. but it generally happens to work out.
			int blendValB = (mat.matFlags & 15);
			if (blendVal <= 7)
			{ //blended
				if (blendVal == 7)
				{
					nmat->alphaTest = 0.1f;
				}
				else
				{
					nmat->noDefaultBlend = false;
				}
			}

			nmat->normalTexIdx = (textures.Num() > 0) ? textures.Num()-1 : -1;
			//todo - some materials also do a scale+bias+rotation on the uv's at runtime to transform the texture coordinates into a
			//specific region of the normal page. i would think the uv transform data is buried in the giant chunk of floats that
			//follows the material data, but i don't see it in there. maybe it's related to some texture bundle flags.
			if (!mat.texFlagsB && blendVal >= 7 && blendValB >= 2)
			{
				int nrmIdx = mat.texIdxB;
				if (nrmIdx < textures.Num())
				{
					noesisTex_t *tex = textures[nrmIdx];
					if (tex && !(tex->flags & NTEXFLAG_SEGMENTED))
					{
						nmat->normalTexIdx = nrmIdx;
					}
				}
			}
		}

		matList.Append(nmat);
	}

	void *pgctx = rapi->rpgCreateContext();
	rapi->rpgSetEndian(true);
	BYTE *vertData = data + hdr.ofsVerts;
	const int bayoVertSize = 32;//(hdr.ofsVerts > 128) ? 48 : 32;

	int numBones;
	modelBone_t *bones = Model_Bayo_CreateBones(hdr, data, rapi, numBones);

	//decode normals
	float *normals = (float *)rapi->Noesis_PooledAlloc(sizeof(float)*3*hdr.numVerts);
	Model_Bayo_CreateNormals(vertData+16, normals, hdr.numVerts, bayoVertSize, isVanqModel);

	BYTE *meshStart = data + hdr.ofsMeshes;
	int *meshOfsList = (int *)(data + hdr.ofsMeshOfs);
	for (int i = 0; i < hdr.numMeshes; i++)
	{
		int meshOfs = meshOfsList[i];
		LITTLE_BIG_SWAP(meshOfs);
		wmbMesh_t mesh = *((wmbMesh_t *)(meshStart+meshOfs));
		LITTLE_BIG_SWAP(mesh.id);
		LITTLE_BIG_SWAP(mesh.numBatch);
		LITTLE_BIG_SWAP(mesh.unknownB);
		LITTLE_BIG_SWAP(mesh.batchOfs);
		LITTLE_BIG_SWAP(mesh.unknownD);
		for (int j = 0; j < 12; j++)
		{
			LITTLE_BIG_SWAP(mesh.mat[j]);
		}

		int *batchOfsList = (int *)(meshStart+meshOfs+mesh.batchOfs);
		for (int j = 0; j < mesh.numBatch; j++)
		{
			int batchOfs = batchOfsList[j];
			LITTLE_BIG_SWAP(batchOfs);
			BYTE *batchData = (BYTE *)batchOfsList + batchOfs;
			wmbBatch_t batch = *((wmbBatch_t *)batchData);
			LITTLE_BIG_SWAP(batch.id);
			LITTLE_BIG_SWAP(batch.unknownB);
			LITTLE_BIG_SWAP(batch.unknownC);
			LITTLE_BIG_SWAP(batch.unknownE);
			LITTLE_BIG_SWAP(batch.vertStart);
			LITTLE_BIG_SWAP(batch.vertEnd);
			LITTLE_BIG_SWAP(batch.primType);
			LITTLE_BIG_SWAP(batch.ofsIndices);
			LITTLE_BIG_SWAP(batch.numIndices);
			LITTLE_BIG_SWAP(batch.vertOfs);
			int numBoneRefs = *((int *)(batchData+sizeof(wmbBatch_t)));
			LITTLE_BIG_SWAP(numBoneRefs);
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
			rapi->rpgSetMaterial(matName);

			rpgeoPrimType_e primType = (batch.primType == 4) ? RPGEO_TRIANGLE : RPGEO_TRIANGLE_STRIP;
			rapi->rpgCommitTriangles(batchData+batch.ofsIndices, RPGEODATA_USHORT, batch.numIndices, primType, true);
			if (boneRefDst)
			{ //reference map is no longer needed once triangles have been committed
				rapi->rpgSetBoneMap(NULL);
				rapi->Noesis_UnpooledFree(boneRefDst);
			}
		}
	}

	noesisMatData_t *md = rapi->Noesis_GetMatDataFromLists(matList, textures);
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

	rapi->rpgSetTriWinding(true); //bayonetta uses reverse face windings
	noesisModel_t *mdl = rapi->rpgConstructModel();
	rapi->rpgDestroyContext(pgctx);
	matList.Clear();
	return mdl;
}

//gather entries from a dat file
static void Model_Bayo_GetDATEntries(CArrayList<bayoDatFile_t> &dfiles, BYTE *fileBuffer, int bufferLen)
{
	bayoDat_t dat = *((bayoDat_t *)fileBuffer);
	LITTLE_BIG_SWAP(dat.numRes);
	LITTLE_BIG_SWAP(dat.ofsRes);
	LITTLE_BIG_SWAP(dat.ofsType);
	LITTLE_BIG_SWAP(dat.ofsNames);
	LITTLE_BIG_SWAP(dat.ofsSizes);

	BYTE *namesp = fileBuffer+dat.ofsNames;
	int strSize = *((int *)namesp);
	LITTLE_BIG_SWAP(strSize);
	namesp += sizeof(int);
	int *ofsp = (int *)(fileBuffer+dat.ofsRes);
	int *sizep = (int *)(fileBuffer+dat.ofsSizes);
	for (int i = 0; i < dat.numRes; i++)
	{
		bayoDatFile_t df;
		memset(&df, 0, sizeof(df));
		df.name = (char *)namesp;
		namesp += strSize;

		df.dataSize = *sizep;
		LITTLE_BIG_SWAP(df.dataSize);
		sizep++;

		int ofs = *ofsp;
		LITTLE_BIG_SWAP(ofs);
		df.data = fileBuffer+ofs;
		ofsp++;

		dfiles.Append(df);
	}
}

//load it
noesisModel_t *Model_Bayo_Load(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	CArrayList<bayoDatFile_t> dfiles;

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
	for (int i = 0; i < dfiles.Num(); i++)
	{
		bayoDatFile_t &df = dfiles[i];
		if (rapi->Noesis_CheckFileExt(df.name, ".wmb"))
		{ //it's a model
			noesisModel_t *mdl = Model_Bayo_LoadModel(dfiles, df, rapi);
			if (mdl)
			{
				models.Append(mdl);
			}
		}
	}

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

	//set the data handlers for this format
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh, Model_Bayo_Check);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh, Model_Bayo_Load);

	return true;
}

//called by Noesis before the plugin is freed
void NPAPI_ShutdownLocal(void)
{
	//nothing to do here
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
