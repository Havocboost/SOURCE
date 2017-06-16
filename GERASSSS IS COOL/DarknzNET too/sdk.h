#pragma once


#include "main.h"


#ifndef CLIENT_DLL
#define CLIENT_DLL
#endif

// Public
#include "public\\tier0\\wchartypes.h"
#include "public\\cdll_int.h"
#include "public\\iprediction.h"
#include "public\\bone_setup.h"
#include "public\\icliententitylist.h"
#include "public\\ienginevgui.h"
#include "public\\IGameUIFuncs.h"
#include "public\\igameevents.h"
#include "public\\view_shared.h"
#include "public\\inetchannelinfo.h"
#include "public\\iachievementmgr.h"
#include "public\\steam\\steam_api.h"
#include "public\\steam\\isteamuserstats.h"
#include "public\\model_types.h"
#include "public\\inputsystem\\iinputstacksystem.h"
// Client
#include "game\\client\\cbase.h"
#include "game\\client\\imessagechars.h"
#include "game\\client\\iclientmode.h"
#include "game\\client\\cliententitylist.h"
#include "game\\client\\cdll_client_int.h"
#include "game\\client\\c_baseanimating.h"
#include "game\\client\\c_basecombatweapon.h"
#include "game\\client\\c_baseplayer.h"
#include "game\\client\\enginesprite.h"
#include "game\\client\\input.h"
#include "game\\client\\c_playerresource.h"
#include "game\\client\\iviewrender.h"
#include "game\\client\\viewrender.h"
#include "game\\client\\game_controls\\commandmenu.h"
#include "game\\client\\hudelement.h"
#include "game\\shared\\gamemovement.h"
#include "game\\client\\clientmode_shared.h"
#include "game\\client\\glow_outline_effect.h"

// Engine
#include "engine\\client.h"
#include "public\\engine\\ivmodelrender.h"
#include "public\\engine\\ivdebugoverlay.h"
#include "public\\engine\\ivmodelinfo.h"
#include "public\\engine\\IEngineTrace.h"
#include "public\\engine\\IEngineSound.h"

// Material System
#include "public\\materialsystem\\imaterialsystemstub.h"
#include "public\\materialsystem\\itexture.h"
#include "public\\materialsystem\\imaterialvar.h"
#include "public\\tier1\\checksum_md5.h"

// VGUI
#include "public\\matsys_controls\\matsyscontrols.h"
#include "public\\vgui\\IClientPanel.h"
#include "public\\vgui\\IPanel.h"
#include "public\\vgui\\ISurface.h"
#include "public\\vgui\\ILocalize.h"
#include "public\\collisionutils.h"
#include "public\\vstdlib\\random.h"

// Server
#include "game\\server\\playerinfomanager.h"

// VGUI Controls
#include "public\\vgui_controls\\Panel.h"

// VGUI Material Surface
#include "public\\VGuiMatSurface\\IMatSystemSurface.h"
#include "public\\mathlib\\vector.h"

// Shared
#include "game\\shared\\usermessages.h"
#include "game\\shared\\basecombatweapon_shared.h"
#include "game\\shared\\takedamageinfo.h"
#include "game\\shared\\igamemovement.h"
#include "game\\shared\\in_buttons.h"
#include "game\\shared\\props_shared.h"
// Utils
#include "public\\tier1\\utlvector.h"

#include "public\\bspfile.h"
#include "public\\gamebspfile.h"
#pragma comment(lib, "public\\tier0.lib")
#pragma comment(lib, "public\\tier1.lib")
#pragma comment(lib, "public\\tier2.lib")
#pragma comment(lib, "public\\tier3.lib")
#pragma comment(lib, "public\\mathlib.lib")
#pragma comment(lib, "public\\vstdlib.lib")


#pragma optimize("gsy",on)
#pragma warning( disable : 4244 )



enum WeaponId
{
	WEAPON_NULL = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_P228 = 5,
	WEAPON_USP = 6,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 12,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M3 = 15,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_MP5NAVY = 18,
	WEAPON_P90 = 19,
	WEAPON_SCOUT = 20,
	WEAPON_SG550 = 21,
	WEAPON_SG552 = 22,
	WEAPON_TMP = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR17 = 37,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFE_GG = 41,
	WEAPON_KNIFE_T = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HE_GRENADE = 44,
	WEAPON_SMOKE_GRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC_GRENADE = 48,
	WEAPON_C4 = 49,
	ITEM_KEVLAR = 50,
	ITEM_ASSAULTSUIT = 51,
	ITEM_NVG = 52,
	ITEM_DEFUSER = 53,
	ITEM_CUTTERS = 54,
	WEAPON_KNIFE_CT = 59,
	WEAPON_CZ75 = 63,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_R8REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9BAYONET = 508,
	WEAPON_KNIFE_HUNTSMAN = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY= 515,
	WEAPON_KNIFE_SHADOWDAGGER = 516,
};

class ICustomTraceFilter
{
public:
	virtual bool ShouldHitEntity(PVOID pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};
class CTraceSkipEntity : public ICustomTraceFilter
{
public:
	CTraceSkipEntity(PVOID pEntToSkip = NULL)
	{
		pSkip = pEntToSkip;
	}
	bool ShouldHitEntity(PVOID pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

/*enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC			= 0x001,
	FONTFLAG_UNDERLINE		= 0x002,
	FONTFLAG_STRIKEOUT		= 0x004,
	FONTFLAG_SYMBOL			= 0x008,
	FONTFLAG_ANTIALIAS		= 0x010,
	FONTFLAG_GAUSSIANBLUR	= 0x020,
	FONTFLAG_ROTARY			= 0x040,
	FONTFLAG_DROPSHADOW		= 0x080,
	FONTFLAG_ADDITIVE		= 0x100,
	FONTFLAG_OUTLINE		= 0x200,
	FONTFLAG_CUSTOM			= 0x400,		// custom generated font - never fall back to asian compatibility mode
	FONTFLAG_BITMAP			= 0x800,		// compiled bitmap font - no fallbacks
};
*/

template <typename T>
__forceinline T Member( void *base, DWORD offset = 0 )
{
	return (T)( (DWORD)base + offset );
}


template <typename T>
__forceinline T Member( DWORD base, DWORD offset = 0 )
{
	return (T)( base + offset );
}


typedef void ( __thiscall *void_t )( void *thisptr );
typedef int ( __thiscall *GetInt_t )( void *thisptr );
typedef float ( __thiscall *GetFloat_t )( void *thisptr );


#define TIME2TICKS( time ) ( (int)( .5f + ( (float)time / Globals()->interval_per_tick ) ) )
#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif