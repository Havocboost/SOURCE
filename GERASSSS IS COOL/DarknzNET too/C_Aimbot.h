#pragma once
#include "main.h"

#define	CHAR_TEX_CONCRETE		'C'
#define CHAR_TEX_DIRT			'D'
#define CHAR_TEX_GRATE			'G'
#define CHAR_TEX_METAL			'M'
#define CHAR_TEX_COMPUTER		'P'
#define CHAR_TEX_TILE			'T'
#define CHAR_TEX_VENT			'V'
#define CHAR_TEX_WOOD			'W'
#define CHAR_TEX_GLASS			'Y'


#define TICK_INTERVAL			( Globals()->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )



class C_IWAimbot
{
public:
	float Rate(C_MyEntity* me, C_MyEntity* pl);

	void Main(CUserCmd* pUserCmd, C_MyEntity* pLocal, C_MyWeapon *pWeapon);

	bool MultiPoints(CUserCmd*, C_MyEntity* pLocal, C_MyEntity* pPlayer, Vector &vPos, int iHitBox, C_MyWeapon* Weapon);

	bool IsVisible(C_MyEntity *TargetEntity, C_MyEntity *LocalPlayer, const Vector &TargetPosition, const Vector &EyePos);

	int GetTotalDamage(C_MyEntity *LocalPlayer, C_MyWeapon* Weapon);

	bool KiroScans(CUserCmd* cmd, C_MyEntity* pLocal, C_MyEntity* pPlayer, Vector &vPos, int iHitBox, C_MyWeapon* pWeapon);

	bool GetHiboxPosition(C_MyEntity* pPlayer, Vector &vPos, int iHitBox);

	void CalcAngle(Vector &vSource, Vector &vDestination, QAngle &qAngle);

	bool TraceTargetHitpoint(C_MyEntity* pLocalEntity, C_MyWeapon* pLocalWeapon, C_MyEntity* pBaseEntity, Vector& vecHitPoint);

	void Reset()
	{
		m_flTime = 0.0f;
		iTarget = -1;
		fBestTarget = 99999.9f;
		vTarget.Init(0.0f, 0.0f, 0.0f);
		vFinal.Init(0.0f, 0.0f, 0.0f);
		m_vecDirection.Init();
		//	vEyePos.Init();

		m_vecDirection.Init();
		for (int i = 10; i >= 0; i--)
			m_vecTargetPos[i].Init();
		for (int i = 10; i >= 0; i--)
			m_vecCorners[i].Init();
	}

	
	bool HasTarget()
	{
		return (iTarget != -1);
	}
	ITraceFilter *tfNoPlayers;

	int iTarget;
	int iRCSTarget;

	float fBestTarget;
	float fBestRCSTarget;

	Vector vPoints[55];

	Vector vTarget;
	Vector vRCSTarget;

	Vector vFinal;
	Vector vRCSFinal;

	Vector vEyePos;
	Vector m_vecDirection;
	Vector m_vecTargetPos[10], m_vecCorners[10];
	//playerlist specifics
	float fIsSelected[66];
	float fYawMod[66];
	float fPitchMod[66];
	float fWhiteList[66];
	float fSpecialAimspot[66];

	float m_flTime;
};

extern C_IWAimbot IWAimbot;