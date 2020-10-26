//this is kind of a poor example for plugins, since the format's not totally known and the code is WIP.
//but it does showcase some interesting usages.

#include "stdafx.h"
#undef max
#undef min
#include "half.hpp"
using half_float::half;
#include <map>
#include <stack>
#include <stdint.h>
#include <winreg.h>

#ifdef NOESIS_RELEASE
const char *g_pPluginName = "bayonetta";
const char *g_pPluginDesc = "Bayonetta model handler, by Dick, Kerilk.";
#else
const char *g_pPluginName = "bayonetta_pc";
const char *g_pPluginDesc = "Bayonetta PC model handler, by Dick, Kerilk.";
#endif

FILE *bayo_log;
#if defined(_DEBUG) && !defined(NOESIS_RELEASE)
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


struct SPGOptions {
	bool bAnimPrompt;
	bool bTexturePrompt;
	bool bEnableMultipass;
	bool bDisableLightmaps;
	bool bHideShadowMeshes;
	bool bDisplayLODs;
	bool bEnableExternalTools;
};
SPGOptions *gpPGOptions = NULL;
SPGOptions persistentPGOptions;

static void bayonetta_default_options(SPGOptions &opts) {
#ifdef NOESIS_RELEASE
	LPWSTR reg_key = L"Software\\Noesis\\Plugins\\Bayonetta";
	opts = { false, false, false, false, false, false, false };
#else
	LPWSTR reg_key = L"Software\\Noesis\\Plugins\\Bayonetta PC";
	opts = { true, true, true, false, false, false, true };
#endif
}

#ifdef NOESIS_RELEASE
LPWSTR reg_key = L"Software\\Noesis\\Plugins\\Bayonetta";
#else
LPWSTR reg_key = L"Software\\Noesis\\Plugins\\Bayonetta PC";
#endif

static void bayonetta_load_options() {
	HKEY key;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, reg_key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &key, NULL) == ERROR_SUCCESS) {
		DWORD type;
		DWORD sz = sizeof(SPGOptions);
		if (RegQueryValueEx(key, L"config", NULL, &type, (LPBYTE)&persistentPGOptions, &sz) != ERROR_SUCCESS) {
			DBGLOG("Could not read registry key\n");
			bayonetta_default_options(persistentPGOptions);
		}
		else {
			if (type != REG_BINARY) {
				bayonetta_default_options(persistentPGOptions);
			}
		}
		RegCloseKey(key);
	}
	else {
		DBGLOG("Could not open registry key\n");
	}
}

static void bayonetta_save_options() {
	HKEY key;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, reg_key, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, NULL) == ERROR_SUCCESS) {
		DWORD sz = sizeof(SPGOptions);
		if (RegSetValueEx(key, L"config", 0, REG_BINARY, (LPBYTE)&persistentPGOptions, sz) != ERROR_SUCCESS) {
			DBGLOG("Could not write registry key");
		}
		RegCloseKey(key);
	}
	else {
		DBGLOG("Could not open registry key\n");
	}
}

enum EPGOption
{
	kPGO_DoAnimPrompt = 0,
	kPGO_NoAnimPrompt,
	kPGO_DoTexPrompt,
	kPGO_NoTexPrompt,
	kPGO_DoMultipass,
	kPGO_NoMultipass,
	kPGO_DoLightmaps,
	kPGO_NoLightmaps,
	kPGO_DoShadows,
	kPGO_NoShadows,
	kPGO_DoLODs,
	kPGO_NoLODs,
	kPGO_DoExternal,
	kPGO_NoExternal
};


#include "FloatDecompressor.h"

typedef enum game_e {
	BAYONETTA,
	BAYONETTA2,
	VANQUISH,
	NIER_AUTOMATA,
	MGRR,
	ASTRAL_CHAIN,
	TD,
	ANARCHY_REIGNS,
	MADWORLD
} game_t;

#include "tpl.h"
#include "Bayo.h"
#include "Vanquish.h"
#include "Bayo2.h"
#include "Nier.h"
#include "AstralChain.h"
#include "TD.h"
#include "MGRR.h"
#include "AnarchyReigns.h"
#include "MadWorld.h"

#include "MotionBayo.h"
#include "MotionBayo2.h"




#include "bayonetta_materials.h"

#define WMB_TAG  0x00424d57
#define WMB3_TAG 0x33424d57
#define WMB4_TAG 0x34424d57
#define XT1_TAG  0x00315458

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
	case MADWORLD:
		gameName = "MadWorld";
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
	const uint64_t offsetToEndOfNames = dat.ofsNames + sizeof(int) + ((uint64_t)strSize * dat.numRes);
	if (strSize <= 0 || strSize >= bufferLen || offsetToEndOfNames > bufferLen)
	{
		return false;
	}
	int numWMB = 0;
	int numMOT = 0;
	int numSCR = 0;
	int numWTB = 0;
	int numWTA = 0;
	int numMDB = 0;
	int numTPL = 0;
	int numHKX = 0;
	DBGLOG("Found %d resources\n", dat.numRes);
	for (int i = 0; i < dat.numRes; i++)
	{
		char *name = (char *)namesp;
		if (name[strSize-1])
		{ //incorrectly terminated string
			return false;
		}
		DBGLOG("\t%s\n", name);
		if (rapi->Noesis_CheckFileExt(name, ".wtb"))
			numWTB++;
		if (rapi->Noesis_CheckFileExt(name, ".wta"))
			numWTA++;
		if (rapi->Noesis_CheckFileExt(name, ".hkx"))
			numHKX++;
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
			DBGLOG("Found Vanquish or Anarchy Reigns File or MadWorld File!\n");
			return false;
		}
		else if (game == ASTRAL_CHAIN && rapi->Noesis_CheckFileExt(name, ".scr"))
		{
			DBGLOG("Found Bayonetta or Bayonetta 2 or MGRR or MadWorld File or TD!\n");
			return false;
		}
		else if (rapi->Noesis_CheckFileExt(name, ".scr"))
		{
			numSCR++;
		}
		else if (rapi->Noesis_CheckFileExt(name, ".mdb"))
		{
			numMDB++;
			if (game != MADWORLD)
			{
				DBGLOG("Found MadWorld file!\n");
				return false;
			}
		}
		else if (rapi->Noesis_CheckFileExt(name, ".tpl"))
		{
			numTPL++;
			if (game != MADWORLD)
			{
				DBGLOG("Found MadWorld file!\n");
				return false;
			}
		}

		namesp += strSize;
	}
	if (numWMB <= 0 && numMOT <= 0 && numSCR <= 0 && numMDB <= 0)
	{ //nothing of interest in here
		return false;
	}
	if (game == MADWORLD) {
		if (numMDB == 0 && numSCR == 0) {
			DBGLOG("Found 0 MadWorld model or level!\n");
			return false;
		}
		if (numSCR && !numHKX) {
			DBGLOG("Found Bayonetta or Bayonetta2 level");
			return false;
		}
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
	if ((game == BAYONETTA2 || game == MGRR || game == TD) && numSCR > 0) {
		CArrayList<bayoDatFile_t> dfiles;
		Model_Bayo_GetDATEntries<big>(dfiles, fileBuffer, bufferLen);
		for (int i = 0; i < dfiles.Num(); i++) {
			//DBGLOG("name: %s", name);
			bayoDatFile_t &df = dfiles[i];
			if (rapi->Noesis_CheckFileExt(df.name, ".scr")) {
				bayo2SCRHdr<big> hdr((bayo2SCRHdr_t *)df.data);
				if (memcmp(hdr.id, "SCR\0", 4))
				{ //invalid header
					DBGLOG("Invalid SCR file\n");
					return false;
				}
				if (hdr.numModels == 0) {
					DBGLOG("Empty SCR file\n");
					return false;
				}
				unsigned int * ofsOffsetsModels = (unsigned int *)(df.data + hdr.ofsOffsetsModels);
				int dscrOffset = ofsOffsetsModels[0];
				if (big) {
					LITTLE_BIG_SWAP(dscrOffset);
				}
				bayo2SCRModelDscr<big> modelDscr((bayo2SCRModelDscr_t *)(df.data + dscrOffset));
				BYTE * model_data = df.data + modelDscr.offset;
				unsigned int tag = ((unsigned int*)model_data)[0];
				if (big)
					LITTLE_BIG_SWAP(tag);
				if (game == BAYONETTA2 && tag != WMB_TAG)
					return false;
				if (game == MGRR && tag != WMB4_TAG)
					return false;
				if (game == TD && tag != WMB3_TAG)
					return false;
			}
		}
	}
	if (game == BAYONETTA2 && numWMB > 0 && numWTA == 0) {
		DBGLOG("Found TW101 File (VANQUISH loader)!\n");
		return false;
	}
	DBGLOG("Found %d mdb files\n", numMDB);
	DBGLOG("Found %d mot files\n", numMOT);
	DBGLOG("Found %d wmb files\n", numWMB);
	DBGLOG("Found %d scr files\n", numSCR);
	return true;
}

#define bayonetta_option_prompt(member, prompt, title) \
{ \
	noeUserPromptParam_t params; \
	memset(&params, 0, sizeof(params)); \
	params.defaultValue = gpPGOptions->member ? "1" : "0"; \
	params.promptStr = prompt; \
	params.titleStr = title; \
	params.valType = NOEUSERVAL_BOOL; \
	if (g_nfn->NPAPI_UserPrompt(&params)) { \
		gpPGOptions->member = *(bool *)params.valBuf; \
		persistentPGOptions.member = *(bool *)params.valBuf; \
		bayonetta_save_options(); \
	} \
	return 0; \
}

int bayonetta_anim_prompt(int handle, void *user_data) {
	bayonetta_option_prompt(bAnimPrompt, "Prompt for Animation?", "Animation Prompt");
}

int bayonetta_texture_prompt(int handle, void *user_data) {
	bayonetta_option_prompt(bTexturePrompt, "Prompt for Texture?", "Texture Prompt");
}

int bayonetta_multipass(int handle, void *user_data) {
	bayonetta_option_prompt(bEnableMultipass, "Enable Multipass Rendering?", "Enable Multipass");
}

int bayonetta_lightmaps(int handle, void *user_data) {
	bayonetta_option_prompt(bDisableLightmaps, "Disable Lightmaps Rendering?", "Disable Lightmaps");
}

int bayonetta_hide_shadow_meshes(int handle, void *user_data) {
	bayonetta_option_prompt(bHideShadowMeshes, "Hide Shadow Meshes?", "Hide Shadow Meshes");
}

int bayonetta_display_lods(int handle, void *user_data) {
	bayonetta_option_prompt(bDisplayLODs, "Enable LODs?", "Enable LODs");
}

int bayonetta_external_tools(int handle, void *user_data) {
	bayonetta_option_prompt(bEnableExternalTools, "Enable External Tools?", "Enable External Tools");
}

struct SPGamesPair
{
	SPGamesPair(bool(*pCheck)(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi), noesisModel_t *(*pLoad)(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi))
		: mpCheck(pCheck)
		, mpLoad(pLoad)
	{
	}
	bool(*mpCheck)(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi);
	noesisModel_t * (*mpLoad)(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi);
};

static const SPGamesPair sPGamesPairs[] =
{
	SPGamesPair(Model_Bayo_Check<false, BAYONETTA>, Model_Bayo_Load<false, BAYONETTA>),
	SPGamesPair(Model_Bayo_Check<true, BAYONETTA>, Model_Bayo_Load<true, BAYONETTA>),
	SPGamesPair(Model_Bayo_Check<true, BAYONETTA2>, Model_Bayo_Load<true, BAYONETTA2>),
	SPGamesPair(Model_Bayo_Check<false, BAYONETTA2>, Model_Bayo_Load<false, BAYONETTA2>),
	SPGamesPair(Model_Bayo_Check<false, VANQUISH>, Model_Bayo_Load<false, VANQUISH>),
	SPGamesPair(Model_Bayo_Check<false, NIER_AUTOMATA>, Model_Bayo_Load<false, NIER_AUTOMATA>),
	SPGamesPair(Model_Bayo_Check<false, ASTRAL_CHAIN>, Model_Bayo_Load<false, ASTRAL_CHAIN>),
	SPGamesPair(Model_Bayo_Check<false, MGRR>, Model_Bayo_Load<false, MGRR>),
	SPGamesPair(Model_Bayo_Check<false, TD>, Model_Bayo_Load<false, TD>),
	SPGamesPair(Model_Bayo_Check<true, ANARCHY_REIGNS>, Model_Bayo_Load<true, ANARCHY_REIGNS>),
	SPGamesPair(Model_Bayo_Check<true, MADWORLD>, Model_Bayo_Load<true, MADWORLD>)
};
static const int sPgpCount = sizeof(sPGamesPairs) / sizeof(sPGamesPairs[0]);

static const char sPluginSig[] = "BAYOPGPLUGIN_V0"; //size includes terminator
struct SVerifiedPassthroughData
{
	char mId[16];
	int mHandlerIndex;
};
static_assert(sizeof(sPluginSig) == sizeof(((SVerifiedPassthroughData *)NULL)->mId), "Signature size should match passthrough struct id size");

static void bayonetta_reset_options(unsigned char *store, int storeSize) {
	bayonetta_load_options();
	memcpy(store, &persistentPGOptions, storeSize);
}

static void *option_handler_add(int fmtHandle, addOptParms_t &optParms, char *optName, char *optDescr, bool wantArg, bool(*handler)(const char *arg, unsigned char *store, int storeSize))
{
	optParms.optName = optName;
	optParms.optDescr = optDescr;
	if (wantArg)
	{
		optParms.flags |= OPTFLAG_WANTARG;
	}
	else
	{
		optParms.flags &= ~OPTFLAG_WANTARG;
	}
	optParms.handler = handler;
	return g_nfn->NPAPI_AddTypeOption(fmtHandle, &optParms);
}

template<typename T>
T * option_handler_init(int fmtHandle, addOptParms_t &optParms, char *optName, char *optDescr, bool wantArg, bool(*handler)(const char *arg, unsigned char *store, int storeSize))
{
	memset(&optParms, 0, sizeof(optParms));
	optParms.storeSize = sizeof(T);
	optParms.storeReset = bayonetta_reset_options;
	T * pRet = (T *)option_handler_add(fmtHandle, optParms, optName, optDescr, wantArg, handler);
	NoeAssert(pRet);
	optParms.shareStore = (unsigned char *)pRet;
	return pRet;
}

bool Model_Bayo_Check_All(BYTE *fileBuffer, int bufferLen, noeRAPI_t *rapi)
{
	for (int pgpIndex = 0; pgpIndex < sPgpCount; ++pgpIndex)
	{
		const SPGamesPair &pgp = sPGamesPairs[pgpIndex];
		if (pgp.mpCheck(fileBuffer, bufferLen, rapi))
		{
			SVerifiedPassthroughData * pPd = (SVerifiedPassthroughData *)rapi->Noesis_PooledAlloc(sizeof(SVerifiedPassthroughData));

			memcpy(pPd->mId, sPluginSig, sizeof(sPluginSig));
			pPd->mHandlerIndex = pgpIndex;
	
			//since we succeeded, we'll get a call to load under the same module instance before any other plugin code is allowed to run with that instance. we could potentially just use a global right
			//here in the plugin, but the architecture is designed to allow these calls interleaved with different module instances providing the underlying memory. plenty of plugins would explode if
			//that ever happened, but we might as well pretend there's still hope!
			rapi->Noesis_SetPluginUserPtr(pPd);
			return true;
		}
	}
	return false;
}

static bool sDidSetMatTypes = false;

noesisModel_t * Model_Bayo_Load_All(BYTE *fileBuffer, int bufferLen, int &numMdl, noeRAPI_t *rapi)
{
	if (!sDidSetMatTypes)
	{
		//we don't want to add the overhead of this to plugin load time, so we only do it on demand when we're about to load a file
		bayoSetMatTypes();
		sDidSetMatTypes = true;
	}

	SVerifiedPassthroughData * pPd = (SVerifiedPassthroughData *)rapi->Noesis_GetPluginUserPtr();
	if (pPd && !memcmp(pPd->mId, sPluginSig, sizeof(sPluginSig)) && pPd->mHandlerIndex >= 0 && pPd->mHandlerIndex < sPgpCount)
	{
		return sPGamesPairs[pPd->mHandlerIndex].mpLoad(fileBuffer, bufferLen, numMdl, rapi);
	}

	//well, something got fucked up. this code shouldn't ever run. but who knows!
	NoeAssert(0);

	for (auto &pgp : sPGamesPairs)
		{
		if (pgp.mpCheck(fileBuffer, bufferLen, rapi))
		{
			return pgp.mpLoad(fileBuffer, bufferLen, numMdl, rapi);
		}
	}
	return NULL;
}

template<int whichOption>
static bool set_option(const char *arg, unsigned char *store, int storeSize) {
	NoeAssert(store && storeSize == sizeof(SPGOptions));
	SPGOptions * pOpts = (SPGOptions *)store;
	switch (whichOption)
	{
	case kPGO_DoAnimPrompt:
		pOpts->bAnimPrompt = true;
		break;
	case kPGO_NoAnimPrompt:
		pOpts->bAnimPrompt = false;
		break;
	case kPGO_DoTexPrompt:
		pOpts->bTexturePrompt = true;
		break;
	case kPGO_NoTexPrompt:
		pOpts->bTexturePrompt = false;
		break;
	case kPGO_DoMultipass:
		pOpts->bEnableMultipass = true;
		break;
	case kPGO_NoMultipass:
		pOpts->bEnableMultipass = false;
		break;
	case kPGO_NoLightmaps:
		pOpts->bDisableLightmaps = true;
		break;
	case kPGO_DoLightmaps:
		pOpts->bDisableLightmaps = false;
		break;
	case kPGO_NoShadows:
		pOpts->bHideShadowMeshes = true;
		break;
	case kPGO_DoShadows:
		pOpts->bHideShadowMeshes = false;
		break;
	case kPGO_DoLODs:
		pOpts->bDisplayLODs = true;
		break;
	case kPGO_NoLODs:
		pOpts->bDisplayLODs = false;
		break;
	case kPGO_DoExternal:
		pOpts->bEnableExternalTools = true;
		break;
	case kPGO_NoExternal:
		pOpts->bEnableExternalTools = false;
		break;
	}
	return true;
}

//called by Noesis to init the plugin
bool NPAPI_InitLocal(void)
{
	int fh = g_nfn->NPAPI_Register("Bayonetta/PG Model", ".dat;.dtt");
	if (fh < 0)
	{
		return false;
	}
	OPENLOG();
	g_nfn->NPAPI_SetTypeHandler_TypeCheck(fh, Model_Bayo_Check_All);
	g_nfn->NPAPI_SetTypeHandler_LoadModel(fh, Model_Bayo_Load_All);
	addOptParms_t optParms;
	gpPGOptions = option_handler_init<SPGOptions>(fh, optParms, "-bayopganimprompt", "enable prompt for external animation.", false, set_option<kPGO_DoAnimPrompt>);
	option_handler_add(fh, optParms, "-bayopgnoanimprompt", "disable prompt for external animation.", false, set_option<kPGO_NoTexPrompt>);
	option_handler_add(fh, optParms, "-bayopgtexprompt", "enable prommpt for external/shared textures.", false, set_option<kPGO_DoTexPrompt>);
	option_handler_add(fh, optParms, "-bayopgnotexprompt", "disable prommpt for external/shared textures.", false, set_option<kPGO_NoTexPrompt>);
	option_handler_add(fh, optParms, "-bayopgmultipass", "enable bayonetta multi-pass materials.", false, set_option<kPGO_DoMultipass>);
	option_handler_add(fh, optParms, "-bayopgnomultipass", "disable bayonetta multi-pass materials.", false, set_option<kPGO_NoMultipass>);
	option_handler_add(fh, optParms, "-bayopglightmaps", "enable lightmaps.", false, set_option<kPGO_DoLightmaps>);
	option_handler_add(fh, optParms, "-bayopgnolightmaps", "disable lightmaps.", false, set_option<kPGO_NoLightmaps>);
	option_handler_add(fh, optParms, "-bayopgshadows", "enable shadow meshes.", false, set_option<kPGO_DoShadows>);
	option_handler_add(fh, optParms, "-bayopgnoshadows", "disable shadow meshes.", false, set_option<kPGO_NoShadows>);
	option_handler_add(fh, optParms, "-bayopglods", "enable LODs.", false, set_option<kPGO_DoLODs>);
	option_handler_add(fh, optParms, "-bayopgnolods", "disable LODs.", false, set_option<kPGO_NoLODs>);
	option_handler_add(fh, optParms, "-bayopgexternal", "enable external processing tools.", false, set_option<kPGO_DoExternal>);
	option_handler_add(fh, optParms, "-bayopgnoexternal", "disable external processing tools.", false, set_option<kPGO_NoExternal>);

	bayonetta_default_options(persistentPGOptions);
#ifdef NOESIS_RELEASE
	const char *menu = "Bayonetta";
#else
	const char *menu = "Bayonetta PC";
#endif

	int handle = g_nfn->NPAPI_RegisterTool("Animation Prompt", bayonetta_anim_prompt, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Texture Prompt", bayonetta_texture_prompt, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Enable Multipass", bayonetta_multipass, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Enable Lightmaps", bayonetta_multipass, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Hide Shadow Meshes", bayonetta_hide_shadow_meshes, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Enable LODs", bayonetta_display_lods, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);
	handle = g_nfn->NPAPI_RegisterTool("Enable External Tools", bayonetta_external_tools, NULL);
	g_nfn->NPAPI_SetToolSubMenuName(handle, menu);

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
