#pragma once
#include "main.h"
struct FireBulletData
{
	FireBulletData( const Vector &eye_pos ) : src( eye_pos )
	{
	}

	Vector						src;
	trace_t						enter_trace;
	Vector						direction;
	CTraceFilter				filter;
	float						trace_length;
	float						trace_length_remaining;
	float						current_damage;
	int							penetrate_count;
};
class C_AutoWall
{
public:
	bool IsBreakableEntity(C_MyEntity* pBaseEntity);
	bool HandleBulletPenetration( FireBulletData& BulletData );
	bool PenetrateWall( C_MyEntity* pBaseEntity, C_MyWeapon* pWeapon, const Vector& vecPoint, float& flDamage );
	bool SimulateFireBullet( C_MyEntity* pBaseEntity, C_MyWeapon* pWeapon, FireBulletData& BulletData );
	bool TraceDidHitWorld( trace_t* pTrace );
	bool TraceDidHitNonWorldEntity( trace_t* pTrace );
	bool TraceToExit( Vector& vecEnd, trace_t* pEnterTrace, Vector vecStart, Vector vecDir, trace_t* pExitTrace );
	void UTIL_TraceLine( const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, C_MyEntity* pCSIgnore, trace_t* pTrace );
	void ScaleDamage( int iHitgroup, C_MyEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage );
};

extern C_AutoWall AutoWall;