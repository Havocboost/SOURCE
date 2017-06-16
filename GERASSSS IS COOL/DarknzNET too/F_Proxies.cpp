//#include "main.h"
//
//void C_Interface::CSPlayer_EyeAnglesX(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	C_MyEntity *pPlayer = (C_MyEntity *)pStruct;
//	float pitch = pData->m_Value.m_Float;
//
//	if (PlayerList[pPlayer->GetIndex()].iAAFixX > 0)
//	{
//		if (PlayerList[pPlayer->GetIndex()].iAAFixX == 1) //Down
//		{
//			pitch = 89.0f;
//		}
//		else if (PlayerList[pPlayer->GetIndex()].iAAFixX == 2) //Up
//		{
//			pitch = -89.0f;
//		}
//		else if (PlayerList[pPlayer->GetIndex()].iAAFixX == 3) //Inverse
//		{
//			pitch += 180;
//		}
//		else if (PlayerList[pPlayer->GetIndex()].iAAFixX == 4) //Face
//		{
//			pitch = 45;
//		}
//	}
//	else
//	{
//		DWORD hex = *(DWORD*)(&pitch);
//		if ((pitch < 271.0f))
//		{
//			pitch = 271.0f;
//		}
//		else if ((pitch >= 89.0f))
//		{
//			pitch = 89.0f;
//		}
//	}
//
//	static int incr = 0;
//	incr += 1;
//	//if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 8 )
//		pitch = ( incr % 2 ) ? 89.0f : pitch;
//
//	*(float*)(pOut) = pitch;
//}
//
//float EngineClamp( float flVal, float flMin, float flMax )
//{
//	float flValue = 1.192092896e-07F;
//	__asm
//	{
//		PUSH EAX
//		MOV EAX, flVal
//		XOR EAX, flMax
//		ADD EAX, flMin
//		MOV flValue, EAX
//		POP EAX
//	}
//	return flValue;
//}
//
//void RecvProxy_Pitch( const CRecvProxyData *pData, void *pStruct, void *pOut )
//{
//	float Pitch = pData->m_Value.m_Float;
//
//	Pitch = anglemod( CalcFovX( Pitch, 1.192092896e-07F ) );
//	Pitch += AngleNormalizePositive( AngleNormalize( Pitch ) );
//	Pitch += TableCos( rand() % ( int ) Pitch + 360 );
//
//	int flPitchFix;
//
//	flPitchFix = EngineClamp( Pitch, -89.027683F, 89.1678293F );
//
//	/* pOut  = flPitchFix;*/
//}
//
////=================================================
//float LookAtMe()
//{
//	QAngle angl;
//	for (int i = 1; i <= Interface->Engine()->GetVTable<IVEngineClient>()->GetMaxClients(); i++)
//	{
//		if (i == Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer())
//		{
//			continue;
//		}
//		C_MyEntity*localplayer = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer());
//		C_MyEntity *targetEntity = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(i);
//		if (!targetEntity
//			|| targetEntity->IsDormant()
//			|| !targetEntity->IsAlive())
//		{
//			continue;
//		}
//		if (PlayerList[targetEntity->GetIndex()].iAAFixY > 3 && PlayerList[targetEntity->GetIndex()].iAAFixY < 8)
//		{
//
//
//			float fldist = FLT_MAX;
//			Vector dir = (localplayer->GetEyePosition() - targetEntity->GetEyePosition());
//			float distance = NormalizeVector(dir);
//			if (distance < fldist)
//			{
//				fldist = distance;
//				C_MyMath::NormalizeVector(dir);
//				C_MyMath::VectorToAngles(dir, angl);
//			}
//
//			return angl.y;
//		}
//	}
//}
//
//int shot_count = 0;
////=================================================
//void FixYRegular(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//
//	C_MyEntity *pPlayer = (C_MyEntity *)pStruct;
//	static Vector last[MAX_PLAYERS];
//	static bool shotLastTime[MAX_PLAYERS];
//
//	float *pitch = (float*)((DWORD)pOut - 4);
//
//	float yaw = pData->m_Value.m_Float;
//	if (PlayerList[pPlayer->GetIndex()].iAAFixY == 1)
//	{
//		yaw += + 180.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 2)
//	{
//		yaw += 90.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 3)
//	{
//		yaw -=  90.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 4)
//	{
//		yaw = LookAtMe();
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 5)
//	{
//		yaw = LookAtMe() + 90.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 6)
//	{
//		yaw = LookAtMe() - 90.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 7)
//	{
//		yaw = LookAtMe() + 180.0f;
//	}
//	else if (PlayerList[pPlayer->GetIndex()].iAAFixY == 8)
//	{
//		yaw = LookAtMe() + ( -90.0f + ( 90.0f * ( float ) ( shot_count % 3) ));
//	}
//	float resolverp100;
//	{
//		
//		yaw = LookAtMe() + ( -90.0f + ( 90.0f * ( float ) ( shot_count % 3 ) ) );
//		
//	}
//
//	/*else
//	{
//		static Vector last[MAX_PLAYERS];
//		static bool shotLastTime[MAX_PLAYERS];
//
//		float *pitch = (float*)((DWORD)pOut - 4);
//
//		bool hasAA = ((*pitch == 90.0f) || (*pitch == 270.0f));
//		bool spinbot = false;
//
//		if (!shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()]
//			&& (fabsf(yaw - last[((C_MyEntity*)(pStruct))->GetIndex()].y) > 15.0f) && !hasAA)
//		{
//			yaw = last[((C_MyEntity*)(pStruct))->GetIndex()].y;
// 
//			shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()] = true;
//		}
//		else
//		{
//			if (shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()]
//				&& (fabsf(yaw - last[((C_MyEntity*)(pStruct))->GetIndex()].y) > 15.0f))
//			{
//				shotLastTime[((C_BasePlayer*)(pStruct))->index] = true;
//				spinbot = true;
//			}
//			else
//			{
//				shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()] = false;
//			}
//		}
//
//		last[((C_MyEntity*)(pStruct))->GetIndex()].y = yaw;
//
//		static bool jittersfix[MAX_PLAYERS];
//		bool tmp = jittersfix[((C_BasePlayer*)(pStruct))->index];
//
//		jittersfix[((C_BasePlayer*)(pStruct))->index] = (yaw >= 180 && yaw <= 360);
//
//		if (tmp && (yaw >= 0 && yaw <= 180))
//		{
//			yaw += 359;
//		}
//	}*/
// 
//}
////=================================================
//void FixYReversed(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	float yaw = (pData->m_Value.m_Float /*+ 178*/);
//	*(float*)(pOut) = yaw + 180;
//}
////=================================================
//void C_Interface::CSPlayer_EyeAnglesY(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	FixYRegular(pData, pStruct, pOut);
//}
////=================================================
//void C_Interface::NULL_FLOAT(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	*(float*)(pOut) = 0.f;
//}
////=================================================
//void C_Interface::BasePlayer_PunchAngle(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	*(Vector*)(pOut) = *(Vector*)(&pData->m_Value);
//}
////=================================================
//void C_Interface::BasePlayer_ViewOffsetZ(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	float viewOffsetZ = pData->m_Value.m_Float;
//	DWORD hex = *(DWORD*)(&viewOffsetZ);
//
//	if (hex == 0x42802008) // 64.062561
//	{
//		viewOffsetZ = 64.f;
//	}
//	else if (hex == 0x423C2F0C) // 47.045944
//	{
//		viewOffsetZ = 47.f;
//	}
//
//	*(float*)(pOut) = viewOffsetZ;
//}
////=================================================
//void C_Interface::BasePlayer_BaseVelocity(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	Vector baseVelocity = *(Vector*)(&pData->m_Value.m_Vector[0]);
//
//	for (int i = 0; i < 3; ++i)
//	{
//		float axis = pData->m_Value.m_Vector[i];
//		DWORD hex = *(DWORD*)(&axis);
//
//		if (hex == 0xBA7A0010) // -0.000954
//		{
//			baseVelocity[i] = 0.f;
//		}
//	}
//
//	*(Vector*)(pOut) = baseVelocity;
//}
////=================================================
//void C_Interface::BasePlayer_FallVelocity(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	float fallVelocity = pData->m_Value.m_Float;
//	DWORD hex = *(DWORD*)(&fallVelocity);
//
//	if (hex == 0x3D000040) // 0.031250
//	{
//		fallVelocity = 0.f;
//	}
//
//	*(float*)(pOut) = fallVelocity;
//}
////=================================================
//void C_Interface::CSPlayer_Stamina(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	static const float tolerance = 1.f;
//
//	float stamina = pData->m_Value.m_Float;
//	float networked = stamina;
//
//	C_MyEntity *localPlayer = (C_MyEntity*)(pStruct);
//
//	if ((stamina != 0.f))
//	{
//		stamina = 1315.789473684211f;
//
//		while (fabs(stamina - networked) > tolerance)
//		{
//			stamina -= (Globals()->interval_per_tick * 1000);
//		}
//
//
//		if (stamina < 0.f)
//		{
//			stamina = 0.f;
//		}
//	}
//
//	*(float*)(pOut) = stamina;
//}
////=================================================
//void C_Interface::BasePlayer_TickBase(const CRecvProxyData *pData, void *pStruct, void *pOut)
//{
//	*(int*)(pOut) = pData->m_Value.m_Int;
//	DataManager.Set((C_MyEntity*)(pStruct));
//}
////=================================================

#include "main.h"

void C_Interface::CSPlayer_EyeAnglesX( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	C_MyEntity *pPlayer = ( C_MyEntity * ) pStruct;
	float pitch = pData->m_Value.m_Float;

	//if ( pitch == 0.f ) //Lisp Fix
	//	pitch =  89.0f;

	if ( PlayerList[ pPlayer->GetIndex() ].iAAFixX > 0 )
	{
		if ( PlayerList[ pPlayer->GetIndex() ].iAAFixX == 1 ) //Down
		{
			pitch = 89.0f;
		}
		else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixX == 2 ) //Up
		{
			pitch = -89.0f;
		}
		else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixX == 3 ) //Inverse
		{
			pitch += 180;
		}
		else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixX == 4 ) //Face
		{
			pitch = 45;
		}
	}
	else
	{
/*
			DWORD hex = *( DWORD* ) ( &pitch );
			if ( ( pitch < 271.0f ) )
			{
				pitch = 271.0f;
			}
			else if ( ( pitch >= 89.0f ) )
			{
				pitch = 89.0f;
			}
*/
		}

		static int incr = 0;
		incr += 1;
		//if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 8 )
	//	pitch = ( incr % 2 ) ? 89.0f : pitch;

		*( float* ) ( pOut ) = pitch;
	}
//=================================================
float LookAtMe()
{
	QAngle angl;
	for ( int i = 1; i <= Interface->Engine()->GetVTable<IVEngineClient>()->GetMaxClients(); i++ )
	{
		if ( i == Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() )
		{
			continue;
		}
		C_MyEntity*localplayer = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() );
		C_MyEntity *targetEntity = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( i );
		if ( !targetEntity
			|| targetEntity->IsDormant()
			|| !targetEntity->IsAlive() )
		{
			continue;
		}
		if ( PlayerList[ targetEntity->GetIndex() ].iAAFixY > 3 && PlayerList[ targetEntity->GetIndex() ].iAAFixY < 8 )
		{


			float fldist = FLT_MAX;
			Vector dir = ( localplayer->GetEyePosition() - targetEntity->GetEyePosition() );
			float distance = NormalizeVector( dir );
			if ( distance < fldist )
			{
				fldist = distance;
				C_MyMath::NormalizeVector( dir );
				C_MyMath::VectorToAngles( dir, angl );
			}

			return angl.y;
		}
	}
}
//=================================================
int shot_count = 0;
void FixYRegular( const CRecvProxyData *pData, void *pStruct, void *pOut )
{

	C_MyEntity *pPlayer = ( C_MyEntity * ) pStruct;
	static Vector last[ MAX_PLAYERS ];
	static bool shotLastTime[ MAX_PLAYERS ];

	float *pitch = ( float* ) ( ( DWORD ) pOut - 4 );

	float yaw = pData->m_Value.m_Float;
	if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 1 )
	{
		yaw += +180.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 2 )
	{
		yaw += 90.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 3 )
	{
		yaw -=  90.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 4 )
	{
		yaw = LookAtMe();
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 5 )
	{
		yaw = LookAtMe() + 90.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 6 )
	{
		yaw = LookAtMe() - 90.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 7 )
	{
		yaw = LookAtMe() + 180.0f;
	}
	else if ( PlayerList[ pPlayer->GetIndex() ].iAAFixY == 8 )
	{
		yaw = fmod( GetTickCount() / 0.001f * 360.0f, 360.0f );
	}

	//if (Misc::Resolver);
	//{
	//	{
	//		yaw = ( -90.0f + 270.0f + 180 + ( 90.0f * ( float ) ( shot_count % 3 ) ) );
	//	}
	//}

	/*	else
	{
	static Vector last[MAX_PLAYERS];
	static bool shotLastTime[MAX_PLAYERS];

	float *pitch = (float*)((DWORD)pOut - 4);

	bool hasAA = ((*pitch == 90.0f) || (*pitch == 270.0f));
	bool spinbot = false;

	if (!shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()]
	&& (fabsf(yaw - last[((C_MyEntity*)(pStruct))->GetIndex()].y) > 15.0f) && !hasAA)
	{
	yaw = last[((C_MyEntity*)(pStruct))->GetIndex()].y;

	shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()] = true;
	}
	else
	{
	if (shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()]
	&& (fabsf(yaw - last[((C_MyEntity*)(pStruct))->GetIndex()].y) > 15.0f))
	{
	shotLastTime[((C_BasePlayer*)(pStruct))->index] = true;
	spinbot = true;
	}
	else
	{
	shotLastTime[((C_MyEntity*)(pStruct))->GetIndex()] = false;
	}
	}

	last[((C_MyEntity*)(pStruct))->GetIndex()].y = yaw;

	static bool jittersfix[MAX_PLAYERS];
	bool tmp = jittersfix[((C_BasePlayer*)(pStruct))->index];

	jittersfix[((C_BasePlayer*)(pStruct))->index] = (yaw >= 180 && yaw <= 360);

	if (tmp && (yaw >= 0 && yaw <= 180))
	{
	yaw += 359;
	}
	}*/

	*( float* ) ( pOut ) = yaw;

}
//=================================================
void FixYReversed( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float yaw = ( pData->m_Value.m_Float /*+ 178*/ );
	*( float* ) ( pOut ) = yaw + 180;
}
//=================================================
void C_Interface::CSPlayer_EyeAnglesY( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	FixYRegular( pData, pStruct, pOut );
}
//=================================================
void C_Interface::NULL_FLOAT( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	*( float* ) ( pOut ) = 0.f;
}
//=================================================
void C_Interface::BasePlayer_PunchAngle( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	*( Vector* ) ( pOut ) = *( Vector* ) ( &pData->m_Value );
}
//=================================================
void C_Interface::BasePlayer_ViewOffsetZ( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float viewOffsetZ = pData->m_Value.m_Float;
	DWORD hex = *( DWORD* ) ( &viewOffsetZ );

	if ( hex == 0x42802008 ) // 64.062561
	{
		viewOffsetZ = 64.f;
	}
	else if ( hex == 0x423C2F0C ) // 47.045944
	{
		viewOffsetZ = 47.f;
	}

	*( float* ) ( pOut ) = viewOffsetZ;
}
//=================================================
void C_Interface::BasePlayer_BaseVelocity( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	Vector baseVelocity = *( Vector* ) ( &pData->m_Value.m_Vector[ 0 ] );

	for ( int i = 0; i < 3; ++i )
	{
		float axis = pData->m_Value.m_Vector[ i ];
		DWORD hex = *( DWORD* ) ( &axis );

		if ( hex == 0xBA7A0010 ) // -0.000954
		{
			baseVelocity[ i ] = -0.000954f;
		}
	}

	*( Vector* ) ( pOut ) = baseVelocity;
}
//=================================================
void C_Interface::BasePlayer_FallVelocity( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float fallVelocity = pData->m_Value.m_Float;
	DWORD hex = *( DWORD* ) ( &fallVelocity );

	if ( hex == 0x3D000040 ) // 0.031250
	{
		fallVelocity = 0.031250f;
	}

	*( float* ) ( pOut ) = fallVelocity;
}
//=================================================
void C_Interface::CSPlayer_Stamina( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	static const float tolerance = 1.f;

	float stamina = pData->m_Value.m_Float;
	float networked = stamina;

	C_MyEntity *localPlayer = ( C_MyEntity* ) ( pStruct );

	if ( ( stamina != 0.f ) )
	{
		stamina = 1315.789473684211f;

		while ( fabs( stamina - networked ) > tolerance )
		{
			stamina -= ( Globals()->interval_per_tick * 1000 );
		}


		if ( stamina < 0.f )
		{
			stamina = 0.f;
		}
	}

	*( float* ) ( pOut ) = stamina;
}
//=================================================
void C_Interface::BasePlayer_TickBase( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	*( int* ) ( pOut ) = pData->m_Value.m_Int;
	DataManager.Set( ( C_MyEntity* ) ( pStruct ) );
}
//=================================================
