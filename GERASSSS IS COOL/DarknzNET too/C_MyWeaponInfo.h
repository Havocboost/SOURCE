#pragma once


#include "main.h"


struct S_WeaponInfo
{
	void Clear(void);

	C_MyEntity*	m_owner;
	C_MyWeapon*	m_weapon;
	int			m_id;
	float		m_penetration;
	int			m_damage;
	float		m_maxRange;
	float		m_rangeModifier;
	int			m_bulletsPerShot;
	int			m_bulletType;
	float		m_penetrationRange;
	float		m_penetrationPower;
	float		m_weaponArmorRatio;
	float		m_cycleTime;
	char		*m_alias;
};


class C_MyWeaponInfo
{
public:

	static bool Init(C_MyEntity *localPlayer);

	static void Clear(void);

	static S_WeaponInfo *Get(void);

	static S_WeaponInfo m_current;
	
	static const char *GetWeaponAlias(int id);
	
	static DWORD GetCSWpnData(C_MyWeapon *weapon);

	static void GetBulletTypeParameters(int iBulletType, float &iPenetrationPower, float &flPenetrationDistance);
	
	static void GetWeaponInfo(C_MyEntity *localPlayer, C_MyWeapon *weapon);
};