#include "main.h"


WORD C_MyWeapon::GetHandle(void)
{
	return *Member<WORD*>(this, 0x9A6 + 0xC);
}
//=================================================
int &C_MyWeapon::GetID(void)
{
	static int offset = Netvars->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");
	return *(int*)((DWORD)this + offset);
}
//=================================================
float C_MyWeapon::GetInaccuracy(void)
{
	DWORD dwInaccuracyVMT = (*reinterpret_cast< PDWORD_PTR* >(this))[484];
	return ((float(__thiscall*)(C_MyWeapon*)) dwInaccuracyVMT)(this);
}
//=================================================
float C_MyWeapon::GetSpread(void)
{
	DWORD dwSpreadVMT = (*reinterpret_cast< PDWORD_PTR* >(this))[485];
	return ((float(__thiscall*)(C_MyWeapon*)) dwSpreadVMT)(this);
}
//=================================================
void C_MyWeapon::UpdateAccuracyPenalty(void)
{
	DWORD dwUpdateVMT = (*reinterpret_cast< PDWORD_PTR* >(this))[486];
	return ((void(__thiscall*)(C_MyWeapon*)) dwUpdateVMT)(this);
}
//=================================================
const char* C_MyWeapon::GetWeaponName(void)
{
	DWORD dwGetNameVMT = (*reinterpret_cast< PDWORD_PTR* >(this))[378];
	return ((const char*(__thiscall*)(C_MyWeapon*)) dwGetNameVMT)(this);
}
//=================================================
float &C_MyWeapon::GetNextPrimaryAttack(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
	return *Member<float*>(this, offset);
}
//=================================================
float C_MyWeapon::GetNextSecondaryAttack(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_flNextSecondaryAttack");
	return *Member<float*>(this, offset);
}
//=================================================
int C_MyWeapon::GetClip1(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
	return *Member<int*>(this, offset);
}
//=================================================
int C_MyWeapon::GetZoomLevel(void)
{
	static int offset = Netvars->GetOffset("DT_WeaponCSBaseGun", "m_zoomLevel");
	return *Member<int*>(this, offset);
}
//=================================================
int &C_MyWeapon::GetPaintKit(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
	return *Member<int*>(this, offset);
}
//=================================================
int &C_MyWeapon::GetSkinSeed(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_nFallbackSeed");
	return *Member<int*>(this, offset);
}
//=================================================
int &C_MyWeapon::GetItemIDHigh(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_iItemIDHigh");
	return *Member<int*>(this, offset);
}
//=================================================
float &C_MyWeapon::GetSkinWear(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_flFallbackWear");
	return *Member<float*>(this, offset);
}
//=================================================
int &C_MyWeapon::GetEntityQuality(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_iEntityQuality");
	return *Member<int*>(this, offset);
}
//=================================================
bool C_MyWeapon::IsInReload(void)
{
	static int offset = Netvars->GetOffset("DT_WeaponCSBase", "m_bReloadVisuallyComplete") - 0x93;
	return *Member<bool*>(this, offset);
}
//=================================================
float &C_MyWeapon::GetAccuracyPenalty(void)
{
	static int offset = Netvars->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
	return *Member<float*>(this, offset);
}
//=================================================
C_MyEntity *C_MyWeapon::GetOwner(void)
{
	static int offset = Netvars->GetOffset("DT_BaseCombatWeapon", "m_hOwner");
	return (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntityFromHandle(*Member<int*>(this, offset));
}
//=================================================
int C_MyWeapon::GetBurstShotsRemaining(int offsetIndex)
{
	static int offsets[OFFSETINDECES_MAX] = { 0, 0 };

	if (!offsets[OFFSETINDEX_GLOCK]
		|| !offsets[OFFSETINDEX_FAMAS])
	{
		offsets[OFFSETINDEX_GLOCK] = Netvars->GetOffset("DT_WeaponGlock", "m_iBurstShotsRemaining");
		offsets[OFFSETINDEX_FAMAS] = Netvars->GetOffset("DT_WeaponFamas", "m_iBurstShotsRemaining");
	}


	return *Member<int*>(this, offsets[offsetIndex]);
}
//=================================================
bool C_MyWeapon::HasBurstShotsRemaining(int offsetIndex)
{
	return (GetBurstShotsRemaining(offsetIndex) > 0);
}
//=================================================
float &C_MyWeapon::GetNextBurstShootTime(int offsetIndex)
{
	static int offsets[OFFSETINDECES_MAX] = { 0, 0 };

	if (!offsets[OFFSETINDEX_GLOCK]
		|| !offsets[OFFSETINDEX_FAMAS])
	{
		offsets[OFFSETINDEX_GLOCK] = (Netvars->GetOffset("DT_WeaponGlock", "m_iBurstShotsRemaining") + 4);
		offsets[OFFSETINDEX_FAMAS] = (Netvars->GetOffset("DT_WeaponFamas", "m_iBurstShotsRemaining") + 4);
	}


	return *Member<float*>(this, offsets[offsetIndex]);
}
//=================================================
bool C_MyWeapon::IsSpecialMode(int offsetIndex)
{
	static int offsets[OFFSETINDECES_MAX] = { 0, 0 };

	if (!offsets[OFFSETINDEX_GLOCK]
		|| !offsets[OFFSETINDEX_FAMAS]
		|| !offsets[OFFSETINDEX_M4A1]
		|| !offsets[OFFSETINDEX_USP])
	{
		offsets[OFFSETINDEX_GLOCK] = Netvars->GetOffset("DT_WeaponGlock", "m_bBurstMode");
		offsets[OFFSETINDEX_FAMAS] = Netvars->GetOffset("DT_WeaponFamas", "m_bBurstMode");
		offsets[OFFSETINDEX_M4A1] = Netvars->GetOffset("DT_WeaponM4A1", "m_bSilencerOn");
		offsets[OFFSETINDEX_USP] = Netvars->GetOffset("DT_WeaponUSP", "m_bSilencerOn");
	}


	return *Member<bool*>(this, offsets[offsetIndex]);
}
//=================================================
bool C_MyWeapon::IsFirearm(void)
{
	int id = GetID();

	bool isbadweapon = ((id == WEAPON_NULL)
		|| (id == WEAPON_KNIFE_T)
		|| (id == WEAPON_KNIFE_CT)
		|| (id == WEAPON_KNIFE_GG)
		|| (id == WEAPON_KNIFE_KARAMBIT)
		|| (id == WEAPON_KNIFE_M9BAYONET)
		|| (id == WEAPON_KNIFE_FALCHION)
		|| (id == WEAPON_KNIFE_SHADOWDAGGER)
		|| (id == WEAPON_KNIFE_BAYONET)
		|| (id == WEAPON_KNIFE_BUTTERFLY)
		|| (id == WEAPON_KNIFE_FLIP)
		|| (id == WEAPON_KNIFE_GUT)
		|| (id == WEAPON_KNIFE_BOWIE)
		|| (id == WEAPON_FLASHBANG)
		|| (id == WEAPON_HE_GRENADE)
		|| (id == WEAPON_SMOKE_GRENADE)
		|| (id == WEAPON_INC_GRENADE)
		|| (id == WEAPON_MOLOTOV)
		|| (id == WEAPON_DECOY)
		|| (id == WEAPON_C4));

	return !isbadweapon;
}
//=================================================
int C_MyWeapon::GetIDToOffsetIndex(int id)
{
	switch (id)
	{
	case WEAPON_GLOCK:

		return OFFSETINDEX_GLOCK;
		break;

	case OFFSETINDEX_FAMAS:

		return OFFSETINDEX_FAMAS;
		break;

	case WEAPON_M4A1:

		return OFFSETINDEX_M4A1;
		break;

	case WEAPON_USP:

		return OFFSETINDEX_USP;
		break;

	default:

		break;
	}

	return -1;
}
//=================================================
bool C_MyWeapon::HitChance(float flChance)
{
	return(flChance >= GetInaccuracy());
}