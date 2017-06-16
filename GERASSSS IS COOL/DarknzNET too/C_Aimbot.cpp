#include "C_Aimbot.h"
#include "Conversion.h"



C_IWAimbot IWAimbot;

//=================================================
bool C_IWAimbot::GetHiboxPosition( C_MyEntity* pPlayer, Vector &vPos, int iHitBox )
{
	Vector vMax;
	Vector vMin;

	matrix3x4_t m_mMatrix[ 128 ];

	*( float* ) ( ( DWORD ) ( pPlayer ) +0x2914 ) = 0.0f;
	*( unsigned int* ) ( ( DWORD ) ( pPlayer ) +0x2680 ) = 0;

	if ( !pPlayer->SetupBones( m_mMatrix, 128, 0x00000100, 0.0f ) )
		return false;

	studiohdr_t* hdr = Interface->ModelInfo()->GetVTable<IVModelInfo>()->GetStudioModel( pPlayer->GetModel() );

	if ( !hdr )
		return false;

	mstudiobbox_t* Box = hdr->pHitboxSet( 0 )->pHitbox( iHitBox );

	if ( !Box )
		return false;

	float scalecenter;


	scalecenter = 0;


	VectorTransform( Box->bbmin, m_mMatrix[ Box->bone ], vMin );
	VectorTransform( Box->bbmax, m_mMatrix[ Box->bone ], vMax );

	vPos = ( vMin + vMax ) * 0.5;
	vPos += ( *( Vector* ) ( ( DWORD ) ( pPlayer ) +0x134 ) - pPlayer->GetAbsOrigin( ) );
	/*
	if (iHitBox == 12)
	{
	float flPitch = pPlayer->GetEyeAngles().x;
	if ((flPitch > 0.0f) && (flPitch <= 89.99f))
	{
	float flHeight = fabsf((vMin.z - vMax.z)) / 2.7f;

	vPos.z += ((flHeight * (flPitch / 89.99f)));
	}
	}*/

	if ( iHitBox == 0 )
	{
		vPos.x += Aimbot::Adjust_X;
		vPos.y += Aimbot::Adjust_Y;
		vPos.z += Aimbot::Adjust_Z;
	}

	/*float flAimHeight = 0.f;

	for (;m_iCurrentHitbox == 0;)
	{
	SDK::CTrace::trace_t tempTrace;
	SDK::CTrace::Ray_t tempRay;
	SDK::CTrace::CTraceFilter tempFilter;
	tempFilter.pSkip = pLocal;

	tempRay.Init(gEngine.GetEyePosition(pLocal), vHitbox);

	g_pTrace->TraceRay(tempRay, 0x4600400B, &tempFilter, &tempTrace);

	if (tempTrace.m_pEnt == pEntity)
	{
	if (tempTrace.hitgroup == 1)
	break;
	}
	else
	{
	vHitbox.z -= flAimHeight;
	break;
	}

	flAimHeight += 0.10f;
	vHitbox.z += flAimHeight;
	}*/

	/*Vector m_vecCorners[Corners2] = { ((Box->bbmin + Box->bbmax) * 0.5f), // center
	Vector(Box->bbmin.x + scalecenter, Box->bbmin.y + scalecenter, Box->bbmin.z + scalecenter), // left bottom front corner
	Vector(Box->bbmin.x + scalecenter, Box->bbmax.y - scalecenter, Box->bbmin.z + scalecenter), // left bottom back corner
	Vector(Box->bbmax.x - scalecenter, Box->bbmax.y - scalecenter, Box->bbmin.z + scalecenter), // left top back corner
	Vector(Box->bbmax.x - scalecenter, Box->bbmin.y + scalecenter, Box->bbmin.z + scalecenter), // left top front corner
	Vector(Box->bbmax.x - scalecenter, Box->bbmax.y - scalecenter, Box->bbmax.z - scalecenter), // right top back corner
	Vector(Box->bbmin.x + scalecenter, Box->bbmax.y - scalecenter, Box->bbmax.z - scalecenter), // right bottom back corner
	Vector(Box->bbmin.x + scalecenter, Box->bbmin.y + scalecenter, Box->bbmax.z - scalecenter), // right bottom front corner
	Vector(Box->bbmax.x - scalecenter, Box->bbmin.y + scalecenter, Box->bbmax.z - scalecenter), // right top front corner
	((m_vecCorners[3] + m_vecCorners[5]) * .5f)
	};

	VectorTransform(m_vecCorners[0], m_mMatrix[Box->bone], m_vecTargetPos[0]);
	VectorTransform(m_vecCorners[1], m_mMatrix[Box->bone], m_vecTargetPos[1]);
	VectorTransform(m_vecCorners[2], m_mMatrix[Box->bone], m_vecTargetPos[2]);
	VectorTransform(m_vecCorners[3], m_mMatrix[Box->bone], m_vecTargetPos[3]);
	VectorTransform(m_vecCorners[4], m_mMatrix[Box->bone], m_vecTargetPos[4]);
	VectorTransform(m_vecCorners[5], m_mMatrix[Box->bone], m_vecTargetPos[5]);
	VectorTransform(m_vecCorners[6], m_mMatrix[Box->bone], m_vecTargetPos[6]);
	VectorTransform(m_vecCorners[7], m_mMatrix[Box->bone], m_vecTargetPos[7]);
	VectorTransform(m_vecCorners[8], m_mMatrix[Box->bone], m_vecTargetPos[8]);
	VectorTransform(m_vecCorners[9], m_mMatrix[Box->bone], m_vecTargetPos[9]);*/


	return true;
}
bool C_IWAimbot::IsVisible( C_MyEntity *TargetEntity, C_MyEntity *LocalPlayer, const Vector &TargetPosition, const Vector &EyePos )
{
	trace_t Trace;
	Ray_t Ray;

	Ray.Init( EyePos, TargetPosition );
	CTraceFilterSkipTwoEnts filter;

	filter.pSkip = LocalPlayer;
	filter.pSkip2 = TargetEntity;


	Interface->EngineTrace()->GetVTable<IEngineTrace>()->TraceRay( Ray, CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_HITBOX, &filter, &Trace );

	return ( Trace.fraction > 0.97f );
}






bool C_IWAimbot::TraceTargetHitpoint( C_MyEntity* pLocalEntity, C_MyWeapon* pLocalWeapon, C_MyEntity* pBaseEntity, Vector& vecHitPoint )
{
	int Choose[] ={ ( Aimbot::Hitbox ), 11, 5, 12, 1, 9, 10, 13, 14, 16, 17, 18, 8, 7, 6, 4, 3, 2, 15 };

	Choose[ 0 ] = ( Aimbot::Hitbox );

	for ( int i = 18; i >= 0; i-- )
	{
		if ( Choose[ i ] == ( Aimbot::Hitbox ) )
		{
			Choose[ i ] = 0;
		}
	}


	auto flMinDamage = Aimbot::AutowallDmg;
	auto vecCurPos = pLocalEntity->GetEyePosition();

	Vector vecHit;
	auto bDefaultHitbox = GetHiboxPosition( pBaseEntity, vecHit, Aimbot::Hitbox );
	if ( bDefaultHitbox )
	{
		auto bIsVisible = IsVisible( pBaseEntity, pLocalEntity, vecHit, vecCurPos );
		if ( bIsVisible )
		{
			vecHitPoint = vecHit;
			return true;
		}

		auto flDamage = 0.f;
		auto bPenetrate = ( Aimbot::Autowall && AutoWall.PenetrateWall( pLocalEntity, pLocalWeapon, vecHit, flDamage ) );

		if ( bPenetrate && flDamage >= flMinDamage )
		{
			vecHitPoint = vecHit;
			return true;
		}
	}
	if ( Aimbot::Hitscans )
	{
		if ( Aimbot::Hitscans <= 2 )
		{
			static int increase = 0;
			if ( increase >= 18 )
			{
				increase = 0;
			}
			else
			{
				increase++;
			}
			GetHiboxPosition( pBaseEntity, vecHit, increase );
		}
		else if ( Aimbot::Hitscans == 3 )
		{
			auto flDamage = 0.f;
			for ( int m_iHitbox = 18; m_iHitbox >= 0; m_iHitbox-- )
			{
				GetHiboxPosition( pBaseEntity, vecHit, Choose[ m_iHitbox ] );
				if ( Aimbot::Autowall && AutoWall.PenetrateWall( pLocalEntity, pLocalWeapon, vecHit, flDamage ) && flDamage >= flMinDamage && pLocalWeapon->GetID() != WEAPON_AWP )
				{
					vecHitPoint = vecHit;
					return true;
				}
			}
		}

		auto flDamage = 0.f;
		if ( IsVisible( pBaseEntity, pLocalEntity, vecHit, vecCurPos ) /*&& pLocalWeapon->GetID() != WEAPON_AWP*/ )
		{
			vecHitPoint = vecHit;
			return true;
		}
		else if ( Aimbot::Hitscans == 2 && Aimbot::Autowall && AutoWall.PenetrateWall( pLocalEntity, pLocalWeapon, vecHit, flDamage ) && flDamage >= flMinDamage /*&& pLocalWeapon->GetID() != WEAPON_AWP*/ )
		{
			vecHitPoint = vecHit;
			return true;
		}
	}

	return false;
}




#include "Conversion.h"

void C_IWAimbot::CalcAngle( Vector &vSource, Vector &vDestination, QAngle &qAngle )
{
	Vector vDelta = vSource - vDestination;

	float fHyp = ( vDelta.x * vDelta.x ) + ( vDelta.y * vDelta.y );

	float fRoot;

	__asm
	{
		sqrtss xmm0, fHyp
		movss fRoot, xmm0
	}

	qAngle.x = RAD2DEG( atan( vDelta.z / fRoot ) );
	qAngle.y = RAD2DEG( atan( vDelta.y / vDelta.x ) );

	if ( vDelta.x >= 0.0f )
		qAngle.y += 180.0f;

	qAngle.x = AngleNormalize( qAngle.x );
	qAngle.y = AngleNormalize( qAngle.y );
}


float GetFov( Vector vLocalOrigin, Vector vPosition, Vector vForward )
{
	Vector vLocal;

	VectorSubtract( vPosition, vLocalOrigin, vLocal );

	vLocal.NormalizeInPlace();

	float fValue = vForward.Dot( vLocal );

	//np for kolo's math skills
	if ( fValue < -1.0f )
		fValue = -1.0f;

	if ( fValue > 1.0f )
		fValue = 1.0f;

	return RAD2DEG( acos( fValue ) );
}



void C_IWAimbot::Main( CUserCmd* pUserCmd, C_MyEntity* pLocal, C_MyWeapon *pWeapon )
{

	int iMyTeam = pLocal->GetTeamNum();

	if ( !pWeapon ) return;

	if ( !pWeapon->IsFirearm() ) return;

	static int wait = 0;

	int tickold = pUserCmd->tick_count;


	vEyePos = pLocal->GetEyePosition();

	static QAngle vClientViewAngles;
	Interface->Engine()->GetVTable<IVEngineClient>()->GetViewAngles( vClientViewAngles );

	static Vector vAngle;
	AngleVectors( vClientViewAngles, &vAngle );

	Reset();

	for ( INT ax = 1; ax <= Interface->Engine()->GetVTable<IVEngineClient>()->GetMaxClients(); ax++ )
	{
		C_MyEntity* pBaseEntity = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( ax );
		if ( !pBaseEntity
			|| pBaseEntity == pLocal
			|| !pLocal->IsAlive()
			|| ( pBaseEntity->GetTeamNum() == iMyTeam )
			|| pBaseEntity->IsDormant()
			|| !pBaseEntity->IsAlive()
			|| pBaseEntity->IsProtected()
			|| PlayerList[ pBaseEntity->GetIndex() ].flWhitelist
			|| !TraceTargetHitpoint( pLocal, pWeapon, pBaseEntity, vTarget ) )
			continue;



		float fCurrFOV = GetFov( vEyePos, vTarget, vAngle );

		if ( fCurrFOV > 360.0f )	//aimfov
			continue;

		//	if(g_CVARS.CvarList[TargetSelection] == 1)//targetselection
		fCurrFOV = ( Vector( vTarget - vEyePos ).Length() );

		if ( fBestTarget < fCurrFOV )
			continue;

		fBestTarget = fCurrFOV;

		vFinal = vTarget;

		//this is our target which is closest to crosshair
		iTarget = ax;
		m_flTime = pBaseEntity->GetSimulationTime();

	}

	if ( HasTarget() )
	{
		CalcAngle( vEyePos, vFinal, pUserCmd->viewangles );

		if ( !Aimbot::Silent )
			Interface->Engine()->GetVTable<IVEngineClient>()->SetViewAngles( pUserCmd->viewangles );
		C_MyEntity *pEntity;
		pUserCmd->ProcessSimulation( m_flTime );
		if ( Misc::AutoMM )
		{
			if ( pWeapon->GetClip1() > 0 )
			{
				if ( !pWeapon->IsInReload() && pLocal->GetFlags() & FL_ONGROUND )
				{

					if ( !( pUserCmd->buttons & IN_DUCK ) )
					{
						pUserCmd->buttons |= IN_DUCK;
						/*pUserCmd->forwardmove = 0.0f;
						pUserCmd->sidemove = 0.0f;*/
					}
					if ( !pLocal->IsScoped() && ( pWeapon->GetID() == WEAPON_AWP || pWeapon->GetID() == WEAPON_G3SG1 || pWeapon->GetID() == WEAPON_SCAR20 ) )
					{
						pUserCmd->buttons |= IN_ATTACK2;
					}
					if ( Aimbot::Autoshoot && ( /*pWeapon->GetID() == WEAPON_AWP*/ /*||*/ pWeapon->GetID() == WEAPON_G3SG1 || pWeapon->GetID() == WEAPON_SCAR20 ) )
					{
						if ( pLocal->IsScoped() && pLocal->GetVelocity().Length() < 60.0f )
						{
							/*if ( Aimbot::Hitchance )
							{
								if ( pWeapon->HitChance( 0.005f ) )
								{
									pUserCmd->buttons |= IN_ATTACK;
								}
							}
							else
							{
								pUserCmd->buttons |= IN_ATTACK;
							}*/
						}
					}
					else if ( Aimbot::Autoshoot )
					{
						if ( pWeapon->HitChance( 0.010f ) )
						{
							pUserCmd->buttons |= IN_ATTACK;
						}
					}
				}
			}
			else
			{
				pUserCmd->buttons |= IN_RELOAD;
			}
		}
		else if ( Aimbot::Autoshoot )
		{
			if ( pWeapon->GetClip1() == 0 )
			{
				pUserCmd->buttons |= IN_RELOAD;
			}
			else
			{
				if ( Aimbot::Hitchance )
				{
					if ( pWeapon->HitChance( 0.005f ) )
					{
						pUserCmd->buttons |= IN_ATTACK;
					}
				}
				else
				{
					pUserCmd->buttons |= IN_ATTACK;
				}
			}
		}
	}
	else
	{
		if ( Misc::AutoMM )
		{
			static bool isUserSetZoom = false;
			if ( pUserCmd->buttons & IN_ATTACK2 )
			{
				isUserSetZoom = true;
			}
			if ( !pLocal->IsScoped() && isUserSetZoom )
			{
				isUserSetZoom = false;
			}
			if ( !isUserSetZoom && pLocal->IsScoped() && !pWeapon->IsInReload() && pWeapon->GetClip1() > 0 &&
				( pWeapon->GetID() == WEAPON_AWP || pWeapon->GetID() == WEAPON_G3SG1 || pWeapon->GetID() == WEAPON_SCAR20 ) )
			{
				pUserCmd->buttons |= IN_ATTACK2;
			}
		}
	}

}