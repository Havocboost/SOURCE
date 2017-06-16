#pragma once
#include "main.h"

class C_Utils
{
public:
	void Log(const char* Message, ...);
	void Log(DWORD Color, const char* Message, ...);
	int GetPlayerModifiedDamage(const float &constdamage, bool isHeadshot, bool isFriendly, C_MyWeapon*Weapon, C_MyEntity *targetEntity);
	void ClipTraceToPlayers(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, void *filter, trace_t *tr);
	void TraceFilterSkipTwoEntities(DWORD* thisptr, const C_MyEntity *PassEntity, const C_MyEntity *PassEntity2, int CollisionGroup);
	void UTIL_TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);
	float GetHitgroupModifiedDamage(float dmg, int hitgroup);
	bool IsVisible(C_MyEntity *TargetEntity, C_MyEntity *LocalPlayer, const Vector &TargetPosition, const Vector &EyePos);
};

extern C_Utils Utils;