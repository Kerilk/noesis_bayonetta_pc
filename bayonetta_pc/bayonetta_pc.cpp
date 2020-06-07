//this is kind of a poor example for plugins, since the format's not totally known and the code is WIP.
//but it does showcase some interesting usages.

#include "stdafx.h"
#undef max
#undef min
#include "half.hpp"
using half_float::half;
#include <map>
#include <stack>

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

#include "FloatDecompressor.h"

typedef enum game_e {
	BAYONETTA,
	BAYONETTA2,
	VANQUISH,
	NIER_AUTOMATA,
	MGRR,
	ASTRAL_CHAIN,
	TD,
	ANARCHY_REIGNS
} game_t;

#include "Bayo.h"
#include "Vanquish.h"
#include "Bayo2.h"
#include "Nier.h"
#include "AstralChain.h"
#include "TD.h"
#include "MGRR.h"
#include "AnarchyReigns.h"

#include "MotionBayo.h"
#include "MotionBayo2.h"




#include "bayonetta_materials.h"

#define WMB_TAG  0x00424d57
#define WMB3_TAG 0x33424d57
#define WMB4_TAG 0x34424d57
#define XT1_TAG 0x00315458

//see if something is a valid bayonetta .dat
template <bool big, game_e game>
bool Model_Bayo_Check(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi)
{
	char * gameName;
	switch (game) {
	case BAYONETTA:
		gameName = "Bayonetta";
		break;
	case BAYONETTA2:
		gameName = "Bayonnetta 2";
		break;
	case VANQUISH:
		gameName = "Vanquish";
		break;
	case NIER_AUTOMATA:
		gameName = "Nier Automata";
		break;
	case MGRR:
		gameName = "MGRR";
		break;
	case ASTRAL_CHAIN:
		gameName = "Astral Chain";
		break;
	case TD:
		gameName = "Transformer Devastation";
		break;
	case ANARCHY_REIGNS:
		gameName = "Anarchy Reigns";
		break;
	default:
		gameName = "Unknown";
	}
	DBGLOG("Checking %s %s\n", big? "big" : "little", gameName);
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
	int numSCR = 0;
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
			//Try to rule out non bayonetta file.
			int sizeWmb = ((int*)(fileBuffer + dat.ofsSizes))[i];
			if (big) {
				LITTLE_BIG_SWAP(sizeWmb);
			}
			if ( sizeWmb > 12) {
				int offWmb = ((int*)(fileBuffer + dat.ofsRes))[i];
				if (big) {
					LITTLE_BIG_SWAP(offWmb);
				}
				unsigned int tag = ((unsigned int*)(fileBuffer + offWmb))[0];
				unsigned int version = ((int*)(fileBuffer + offWmb))[1];

				if (big) {
					LITTLE_BIG_SWAP(tag);
					LITTLE_BIG_SWAP(version);
				}
				if (game == MGRR && tag != WMB4_TAG) {
					DBGLOG("Found non MGRR File!\n");
					return false;
				}
				if (game != MGRR && tag == WMB4_TAG) {
					DBGLOG("Found MGRR File!\n");
					return false;
				}
				if ((game == NIER_AUTOMATA || game == ASTRAL_CHAIN || game == TD) && tag != WMB3_TAG) {
					DBGLOG("Found non Nier Automata, Astral Chain File or Transformer Devastation File!\n");
					return false;
				}
				if ((game != NIER_AUTOMATA && game != ASTRAL_CHAIN && game != TD) && tag == WMB3_TAG) {
					DBGLOG("Found Nier Automata, Astral Chain File or Transformer Devastation File!\n");
					return false;
				}
				if ((game != NIER_AUTOMATA && game != ASTRAL_CHAIN) && tag == WMB3_TAG && version == 0x20160116) {
					DBGLOG("Found Nier Automata or Astral Chain File!\n");
					return false;
				}
				if ((game == NIER_AUTOMATA || game == ASTRAL_CHAIN) && tag == WMB3_TAG && version != 0x20160116) {
					DBGLOG("Found Transformer Devastation File!\n");
					return false;
				}
				unsigned int vertex_type = ((int*)(fileBuffer + offWmb))[2];
				if (big) {
					LITTLE_BIG_SWAP(vertex_type);
				}
				if( game == BAYONETTA && vertex_type & 0x400000) {
					DBGLOG("Found Bayonetta 2 or Vanquish File!\n");
					return false;
				}

				unsigned int vertexOffset = ((unsigned int*)(fileBuffer + offWmb))[6];
				if (big) LITTLE_BIG_SWAP(vertexOffset);
				if (big && game != ANARCHY_REIGNS && vertexOffset == 0xa0) {
					DBGLOG("Found Anarchy Reigns File!\n");
					return false;
				}

				if (!big && game == BAYONETTA2 && vertexOffset == 0xa0) {
					DBGLOG("Found Vanquish File!\n");
					return false;
				}
			}
		}
		else if ((game == ASTRAL_CHAIN || game == NIER_AUTOMATA) && rapi->Noesis_CheckFileExt(name, ".wta"))
		{
			int sizeWta = ((int*)(fileBuffer + dat.ofsSizes))[i];
			if (big) {
				LITTLE_BIG_SWAP(sizeWta);
			}
			if (sizeWta > 0x20) {
				unsigned int offWta = ((unsigned int*)(fileBuffer + dat.ofsRes))[i];
				if (big) {
					LITTLE_BIG_SWAP(offWta);
				}
				unsigned int offsetTextureInfo = ((unsigned int*)(fileBuffer + offWta))[7];
				if (game == ASTRAL_CHAIN && !offsetTextureInfo) {
					DBGLOG("Not an Astral Chain file (no texture infos)!\n");
					return false;
				}
				unsigned int tag = ((unsigned int*)(fileBuffer + offWta + offsetTextureInfo))[0];
				if (game == ASTRAL_CHAIN && tag != XT1_TAG) { //XT1 texture
					DBGLOG("Not an Astral Chain file wrong tag (%x)!\n", tag);
					return false;
				} else if (game == NIER_AUTOMATA && tag == XT1_TAG) {
					DBGLOG("Found Astral Chain File");
					return false;
				}
			}
		}
		else if (game == BAYONETTA2 && rapi->Noesis_CheckFileExt(name, ".wtb"))
		{
			DBGLOG("Found Bayonetta, Vanquish or Anarchy Reigns File!\n");
			return false;
		}
		else if (game == BAYONETTA && (rapi->Noesis_CheckFileExt(name, ".wta") || rapi->Noesis_CheckFileExt(name, ".wtp") || rapi->Noesis_CheckFileExt(name, ".bxm")))
		{
			DBGLOG("Found Bayonetta 2 File!\n");
			return false;
		}
		else if ((game == VANQUISH || game == ANARCHY_REIGNS) && (rapi->Noesis_CheckFileExt(name, ".wta") || rapi->Noesis_CheckFileExt(name, ".wtp") || rapi->Noesis_CheckFileExt(name, ".scr")))
		{
			DBGLOG("Found Bayonetta 2 or MGRR File!\n");
			return false;
		}
		else if ((game == BAYONETTA || game == BAYONETTA2) && rapi->Noesis_CheckFileExt(name, ".hkx"))
		{
			DBGLOG("Found Vanquish or Anarchy Reigns File!\n");
			return false;
		}
		else if (game == ASTRAL_CHAIN && rapi->Noesis_CheckFileExt(name, ".scr"))
		{
			DBGLOG("Found Bayonetta or Bayonetta 2 or MGRR File!\n");
			return false;
		}
		else if (rapi->Noesis_CheckFileExt(name, ".scr"))
		{
			numSCR++;
		}

		namesp += strSize;
	}
	if (numWMB <= 0 && numMOT <= 0 && numSCR <= 0)
	{ //nothing of interest in here
		return false;
	}
	if (game == BAYONETTA2 && numSCR > 0) {
		namesp = fileBuffer + dat.ofsNames + sizeof(int);
		bool found = false;
		for (int i = 0; i < dat.numRes; i++) {
			char *name = (char *)namesp;
			//DBGLOG("name: %s", name);
			if (rapi->Noesis_CheckFileExt(name, ".wta")) {
				found = true;
			}
			namesp += strSize;
		}
		if (!found) {
			return false;
		}
	}
	DBGLOG("Found %d wmb files\n", numWMB);
	DBGLOG("Found %d scr files\n", numSCR);
	return true;
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
	int fh_2 = g_nfn->NPAPI_Register("Bayonetta 2 Switch Model", ".dat");
	if (fh_2 < 0)
	{
		return false;
	}
	int fh_b = g_nfn->NPAPI_Register("Bayonetta Big Endian Model (WiiU)", ".dat");
	if (fh_b < 0)
	{
		return false;
	}
	int fh_v = g_nfn->NPAPI_Register("Vanquish PC Model", ".dat");
	if (fh_v < 0)
	{
		return false;
	}
	int fh_n = g_nfn->NPAPI_Register("Nier Automata PC Model", ".dtt");
	if (fh_n < 0)
	{
		return false;
	}
	int fh_a = g_nfn->NPAPI_Register("Astral Chain Switch Model", ".dat");
	if (fh_a < 0)
	{
		return false;
	}
	int fh_m = g_nfn->NPAPI_Register("MGRR PC Model", ".dat");
	if (fh_m < 0)
	{
		return false;
	}
	int fh_td = g_nfn->NPAPI_Register("Transformer Devastation PC Model", ".dat");
	if (fh_td < 0)
	{
		return false;
	}
	int fh_ar = g_nfn->NPAPI_Register("Anarchy Reigns X360 Model", ".dat");
	if (fh_ar < 0)
	{
		return false;
	}
	OPENLOG();
	bayoSetMatTypes();
	//set the data handlers for this format
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh, Model_Bayo_Check<false, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh, Model_Bayo_Load<false, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_b, Model_Bayo_Check<true, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_b, Model_Bayo_Load<true, BAYONETTA>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_b2, Model_Bayo_Check<true, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_b2, Model_Bayo_Load<true, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_2, Model_Bayo_Check<false, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_2, Model_Bayo_Load<false, BAYONETTA2>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_v, Model_Bayo_Check<false, VANQUISH>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_v, Model_Bayo_Load<false, VANQUISH>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_n, Model_Bayo_Check<false, NIER_AUTOMATA>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_n, Model_Bayo_Load<false, NIER_AUTOMATA>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_a, Model_Bayo_Check<false, ASTRAL_CHAIN>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_a, Model_Bayo_Load<false, ASTRAL_CHAIN>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_m, Model_Bayo_Check<false, MGRR>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_m, Model_Bayo_Load<false, MGRR>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_td, Model_Bayo_Check<false, TD>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_td, Model_Bayo_Load<false, TD>);
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh_ar, Model_Bayo_Check<true, ANARCHY_REIGNS>);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh_ar, Model_Bayo_Load<true, ANARCHY_REIGNS>);
	//g_nfn->NPAPI_PopupDebugLog(0);
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
