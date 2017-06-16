#include "main.h"

S_WeaponInfo C_MyWeaponInfo::m_current;

void S_WeaponInfo::Clear(void)
{
	m_owner = 0;
	m_weapon = 0;
	m_id = 0;
	m_penetration = 0;
	m_damage = 0;
	m_maxRange = 0.f;
	m_rangeModifier = 0.f;
	m_bulletsPerShot = 0;
	m_bulletType = 0;
	m_penetrationRange = 0.f;
	m_penetrationPower = 0.f;
	m_weaponArmorRatio = 0.f;
	m_alias = "";
}
//=================================================
bool C_MyWeaponInfo::Init(C_MyEntity *localPlayer)
{
	C_MyWeapon *weapon = localPlayer->GetWeapon();

	if (!weapon)
	{
		return false;
	}


	GetWeaponInfo(localPlayer, weapon);

	return true;
}
//=================================================
void C_MyWeaponInfo::Clear(void)
{
	Get()->Clear();
}
//=================================================
S_WeaponInfo *C_MyWeaponInfo::Get(void)
{
	return &m_current;
}
//=================================================
DWORD C_MyWeaponInfo::GetCSWpnData(C_MyWeapon *weapon)
{
	DWORD dwWeaponDataVMT = (*reinterpret_cast< PDWORD_PTR* >(weapon))[456];
	return ((DWORD(__thiscall*)(C_MyWeapon*)) dwWeaponDataVMT)(weapon);
}

//=================================================
void C_MyWeaponInfo::GetWeaponInfo( C_MyEntity *localPlayer, C_MyWeapon *weapon )
{
	DWORD infotable = GetCSWpnData( weapon );

	m_current.m_owner = localPlayer;
	m_current.m_weapon = weapon;

	m_current.m_penetration = *( float* ) ( infotable + 0x864 );
	m_current.m_damage = *( int* ) ( infotable + 0x868 );
	m_current.m_maxRange = *( float* ) ( infotable + 0x86C );
	m_current.m_rangeModifier = *( float* ) ( infotable + 0x870 );
	m_current.m_bulletsPerShot = *( int* ) ( infotable + 0x874 );
	m_current.m_cycleTime = *( float* ) ( infotable + 0x828 );
	m_current.m_bulletType = *( int* ) ( infotable + 0x7B0 );
	m_current.m_weaponArmorRatio = *( float* ) ( infotable + 0x850 );
	m_current.m_id = weapon->GetID();
}
