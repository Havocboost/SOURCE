#pragma once
#include "sdk.h"
#include "windows.h"
enum class ResolveMode : int {
	OFF = 0,
	FORCE,
	DELTA,
	STEADY,
	TICKMODULO,
	ALL
};

class CResolveInfo 
{
	friend class CResolver;
protected:
	//std::deque<CTickRecord> m_sRecords;
	bool	m_bEnemyShot; //priority
	bool	m_bLowerBodyYawChanged;
	bool	m_bBacktrackThisTick;
};

#define Resolver CResolver::GetInstance()

class CResolver {
	friend class CLagcompensation;
	friend class CBacktracking;

	//IMPLEMENT_SINGLETON( CResolver );

public:
	void StoreVars( CBaseEntity* Entity );
	void StoreVars( CBaseEntity* Entity, QAngle ang, float lby, float simtime, float tick );

	void Resolve( CBaseEntity* ent );

	bool& LowerBodyYawChanged( CBaseEntity* ent );
	bool& BacktrackThisTick( CBaseEntity* ent );

private:
	CTickRecord GetShotRecord( CBaseEntity* );
	bool HasStaticRealAngle( int index, float tolerance = 15.f );
	bool IsEntityMoving( CBaseEntity* ent );
};



const inline float GetDelta( float a, float b ) {
	return;
}

const inline float LBYDelta( const CTickRecord& v ) {
	return v.m_angEyeAngles.y - v.m_flLowerBodyYawTarget;
}

const inline bool IsDifferent( float a, float b, float tolerance = 10.f ) {
	return ( GetDelta( a, b ) > tolerance );
}