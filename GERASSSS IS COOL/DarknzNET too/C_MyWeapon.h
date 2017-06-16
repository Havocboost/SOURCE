#pragma once
#include "main.h"

enum
{
	OFFSETINDEX_GLOCK,
	OFFSETINDEX_FAMAS,
	OFFSETINDEX_M4A1,
	OFFSETINDEX_USP,
	OFFSETINDECES_MAX
};


class C_MyWeapon
{
public:

	WORD GetHandle(void);

	int &GetID(void);

	float GetInaccuracy(void);

	float GetSpread(void);

	void UpdateAccuracyPenalty(void);

	const char * GetWeaponName(void);
	
	float &GetNextPrimaryAttack(void);

	float GetNextSecondaryAttack(void);

	int GetClip1(void);

	int GetZoomLevel(void);

	int & GetPaintKit(void);

	int & GetSkinSeed(void);

	int & GetItemIDHigh(void);

	float & GetSkinWear(void);

	int & GetEntityQuality(void);

	bool IsInReload(void);

	float &GetAccuracyPenalty(void);

	C_MyEntity * GetOwner(void);
	
	int GetBurstShotsRemaining(int offsetIndex);

	bool HasBurstShotsRemaining(int offsetIndex);

	float &GetNextBurstShootTime(int offsetIndex);

	bool IsSpecialMode(int offsetIndex);
	
	bool IsFirearm(void);

	static int GetIDToOffsetIndex(int id);
	bool HitChance(float flChance);
	void SetWeaponViewModel(const char * name, C_MyWeapon * weapon);
};