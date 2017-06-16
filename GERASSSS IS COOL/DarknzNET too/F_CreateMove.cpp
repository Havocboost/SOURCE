#include "main.h"

bool MustActiveBhop = false;
static bool bLastJumped = false;
static bool bShouldFake = false;

QAngle OldAngle, OldAngleFORS;
 
//=================================================
QAngle GetSpreadAngles( const QAngle &view, int seed, bool isAA, Vector *bullets, int *bestShot, Vector2D *spread, C_MyWeapon* weapon )
{

	const float constInaccuracy = weapon->GetInaccuracy();
	const float constSpread = weapon->GetSpread();


	Vector direction, right, up;
	C_MyMath::AngleToVectors( view, &direction, &right, &up );


	RandomSeed( seed + 1 );

	float fRand1 = RandomFloat( 0.f, 1.f );
	float pi_1 = RandomFloat( 0.f, 2.f * ( float ) M_PI );
	float inaccuracy = fRand1 * constInaccuracy;
	Vector2D leftSpread( ( cos( pi_1 ) * inaccuracy ), ( sin( pi_1 ) * inaccuracy ) );


	Vector2D rightSpread;

	//for ( int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet )
	{
		float fRand2 = RandomFloat( 0.f, 1.f );
		float pi_2 = RandomFloat( 0.f, 2.f * ( float ) M_PI );
		float fspread = fRand2 * constSpread;
		rightSpread = Vector2D( ( cos( pi_2 ) * fspread ), ( sin( pi_2 ) * fspread ) );
	}

	Vector2D totalSpread;

//	if ( C_MyWeaponInfo::Get()->m_bulletsPerShot == 1 )
	{
		totalSpread = ( leftSpread + rightSpread );

		if ( bestShot )
		{
			*bestShot = 0;
		}
	}
	/*else
	{
		float bestDistance = FLT_MAX;
		int bestBullet = -1;

		for ( int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet )
		{
			float totalDistance = 0.f;
			Vector2D bulletSpread = ( leftSpread + rightSpread[ bullet ] );

			// median
			for ( int i = 0; i < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++i )
			{
				if ( i == bullet )
				{
					continue;
				}

				Vector2D tmpSpread = ( leftSpread + rightSpread[ i ] );
				totalDistance += ( tmpSpread - bulletSpread ).Length();
			}


			if ( totalDistance < bestDistance )
			{
				bestDistance = totalDistance;
				bestBullet = bullet;
			}
		}


		totalSpread = ( leftSpread + rightSpread[ bestBullet ] );

		if ( bestShot )
		{
			*bestShot = bestBullet;
		}
	}*/


/*	for ( int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet )
	{
		Vector2D tmpSpread = ( leftSpread + rightSpread[ bullet ] );

		if ( isAA )
		{
			tmpSpread = -tmpSpread;
		}


		Vector shot = ( direction + ( right * tmpSpread.x ) + ( up * tmpSpread.y ) );
		C_MyMath::NormalizeVector( shot );

		if ( bullets )
		{
			bullets[ bullet ] = shot;
		}
	}*/


//	if ( isAA )
	{
		totalSpread *= -1;
	}


	if ( spread )
	{
		*spread = totalSpread;
	}

	float flIdentity[ 3 ][ 3 ];
	Vector shot = ( direction + ( right * totalSpread.x ) + ( up * totalSpread.y ) );
	C_MyMath::NormalizeVector( shot );

	flIdentity[ 2 ][ 0 ] = 1.0f;
	flIdentity[ 2 ][ 1 ] = -totalSpread[ 0 ];
	flIdentity[ 2 ][ 2 ] = totalSpread[ 1 ];

	NormalizeVector( flIdentity[ 2 ] );

	flIdentity[ 0 ][ 0 ] = 0.0f;
	flIdentity[ 0 ][ 1 ] = -totalSpread[ 0 ];
	flIdentity[ 0 ][ 2 ] = ( 1.0f / totalSpread[ 1 ] ) + ( 1.0f / flIdentity[ 2 ][ 2 ] ) + totalSpread[ 1 ];

	if ( totalSpread[ 0 ] > 0.0f && totalSpread[ 1 ] < 0.0f )
	{
		if ( flIdentity[ 0 ][ 1 ] < 0.0f )
			flIdentity[ 0 ][ 1 ] = -flIdentity[ 0 ][ 1 ];
	}
	else if ( totalSpread[ 0 ] < 0.0f && totalSpread[ 1 ] < 0.0f )
	{
		if ( flIdentity[ 0 ][ 1 ] > 0.0f )
			flIdentity[ 0 ][ 1 ] = -flIdentity[ 0 ][ 1 ];
	}

	if ( flIdentity[ 0 ][ 2 ] < 0.0f )
		flIdentity[ 0 ][ 2 ] = -flIdentity[ 0 ][ 2 ];

	C_MyMath::VectorNormalizes( flIdentity[ 0 ] );


	// Get the left vector via crossproduct.

	CrossProduct( flIdentity[ 0 ], flIdentity[ 2 ], flIdentity[ 1 ] );
	C_MyMath::VectorNormalizes( flIdentity[ 1 ] );

	// Calculate the roll angle.

	float flCross = ( flIdentity[ 1 ][ 1 ] * flIdentity[ 2 ][ 0 ] ) - ( flIdentity[ 1 ][ 0 ] * flIdentity[ 2 ][ 1 ] );
	float flRoll;

	if ( view[ 0 ] > 84.0f || view[ 0 ] < -84.0f )
		flRoll = RAD2DEG( atan2f( flIdentity[ 1 ][ 2 ], sqrtf( flCross ) ) );
	else
		flRoll = RAD2DEG( atan2f( flIdentity[ 1 ][ 2 ], flCross ) );

	if ( flRoll < 0.0f )
		flRoll += 360.0f;



	QAngle angles;
	C_MyMath::VectorToAngles( shot, up, angles );
	angles[ 2 ] += flRoll;

	//angles -= view;
	C_MyMath::NormalizeAngles( angles );

	return angles;
}
//=================================================
void ForceLowSpread( C_MyWeapon *weapon, CUserCmd *cmd )
{
	int desiredSpreadSeed = 165;

	if ( weapon )
	{
		if ( weapon->GetID() == WEAPON_M3 )
		{
			desiredSpreadSeed = 64;
		}
		else if ( weapon->GetID() == WEAPON_XM1014 )
		{
			desiredSpreadSeed = 213;
		}
	}


	if ( desiredSpreadSeed != -1 )
	{
		for ( ; ; ++cmd->command_number )
		{
			cmd->random_seed = ( MD5_PseudoRandom( cmd->command_number ) & 0x7FFFFFFF );

			if ( ( cmd->random_seed & 0xFF ) == desiredSpreadSeed )
			{
				break;
			}
		}
	}
}
//=================================================
void ForceCvars()
{
	//Interface->Cvar()->GetVTable<ICvar>()->FindVar("sv_cheats")->SetValue(1.0f);

	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_ragdoll_physics_enable" )->SetValue( 0.0f );


	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "rate" )->SetValue( 1048576 );
	//Interface->Cvar()->GetVTable<ICvar>()->FindVar( "viewmodel_fov" )->SetValue( 80 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_interp" )->SetValue( 0.01f );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_cmdrate" )->SetValue( 66 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_updaterate" )->SetValue( 66 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_interp_all" )->SetValue( 0.0f );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_interp_ratio" )->SetValue( 1.0f );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_smooth" )->SetValue( 0.0f );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_smoothtime" )->SetValue( 0.01f );
		


	//Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_clanid" )->SetValue( 10927482 );
	//Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_showpos" )->SetValue( 1 );//skype?


	//Interface->Cvar()->GetVTable<ICvar>()->FindVar("name")->SetValue("\n");
	if ( Misc::Sv_CheatsBypass ) 
	{
		Interface->Cvar()->GetVTable<ICvar>()->FindVar( "sv_cheats" )->SetValue( 1.0f );
	}
	else
	{
		Interface->Cvar()->GetVTable<ICvar>()->FindVar( "sv_cheats" )->SetValue( 0.0f );
	}
	//if ( Misc::Sv_CheatsBypass )
	//{
	//	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "sv_cheats" )->SetValue( 1 );
	//}

}
//=================================================
void FastRun( CUserCmd *cmd )
{
	static bool _FastRun;

	if ( ( cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVELEFT ) || ( cmd->buttons&IN_BACK && cmd->buttons&IN_MOVERIGHT ) )
	{
		if ( _FastRun )
		{
			_FastRun = false;
			cmd->sidemove -= 204, 000031;
			cmd->forwardmove -= 204, 000031;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 204, 000031;
			cmd->forwardmove += 204, 000031;
		}
	}
	else if ( ( cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVERIGHT ) || ( cmd->buttons&IN_BACK && cmd->buttons&IN_MOVELEFT ) )
	{
		if ( _FastRun )
		{
			_FastRun = false;
			cmd->sidemove -= 204, 000031;
			cmd->forwardmove += 204, 000031;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 204, 000031;
			cmd->forwardmove -= 204, 000031;
		}
	}
	else if ( cmd->buttons&IN_FORWARD || cmd->buttons&IN_BACK )
	{
		if ( _FastRun )
		{
			_FastRun = false;
			cmd->sidemove -= 204, 000031;
		}
		else
		{
			_FastRun = true;
			cmd->sidemove += 204, 000031;
		}
	}
	else if ( cmd->buttons&IN_MOVELEFT || cmd->buttons&IN_MOVERIGHT )
	{
		if ( _FastRun )
		{
			_FastRun = false;
			cmd->forwardmove -= 204, 000031;
		}
		else
		{
			_FastRun = true;
			cmd->forwardmove += 204, 000031;
		}
	}
}
//=================================================
bool CheckFirePrimary( C_MyEntity*Player, C_MyWeapon*weapon )
{
	if ( !weapon ) return false;

	bool canFire = ( ( Globals()->curtime > weapon->GetNextPrimaryAttack() )
		&& ( Globals()->curtime > Player->GetNextAttack() ) );

	int id = weapon->GetID();
	int offsetIndex = weapon->GetIDToOffsetIndex( id );

	if ( ( id == WEAPON_GLOCK ) || ( id == WEAPON_FAMAS ) )
	{
		if ( weapon->IsSpecialMode( offsetIndex ) && ( weapon->GetBurstShotsRemaining( offsetIndex ) > 0 ) )
		{
			canFire = ( canFire || ( Globals()->curtime >= weapon->GetNextBurstShootTime( offsetIndex ) ) );
		}
	}

	return canFire;
}
//=================================================
void AutoFirePrimary( C_MyEntity*Player, C_MyWeapon*weapon, CUserCmd* cmd )
{
	if ( !weapon ) return;

	if ( !weapon->IsFirearm() ) return;

	bool canFire = ( cmd->buttons & IN_ATTACK ) && ( ( Globals()->curtime > weapon->GetNextPrimaryAttack() )
		&& ( Globals()->curtime > Player->GetNextAttack() ) );

	int id = weapon->GetID();
	int offsetIndex = weapon->GetIDToOffsetIndex( id );

	if ( ( id == WEAPON_GLOCK ) || ( id == WEAPON_FAMAS ) )
	{
		if ( weapon->IsSpecialMode( offsetIndex ) && ( weapon->GetBurstShotsRemaining( offsetIndex ) > 0 ) )
		{
			canFire = ( canFire || ( Globals()->curtime > weapon->GetNextBurstShootTime( offsetIndex ) ) );
		}
	}

	cmd->buttons &= ~IN_ATTACK;
	if ( canFire )
	{
		cmd->buttons |= IN_ATTACK;
	}
}


//=================================================
void __stdcall CreateMove( void *thisptr, CUserCmd* pCmd, bool& bSendPacket)
{
	ForceCvars();

	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;

	m_oldangle = pCmd->viewangles;
	m_oldforward = pCmd->forwardmove;
	m_oldsidemove = pCmd->sidemove;

	if ( Misc::MenuActive && GetAsyncKeyState( VK_LBUTTON ) )
	{
		pCmd->buttons &= ~IN_ATTACK;
	}

	C_MyEntity *plocalPlayer = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() );

	if ( !plocalPlayer )
	{
		return;
	}
	if ( ( plocalPlayer->GetWaterLevel() < 2 ) && ( plocalPlayer->GetMoveType() != MOVETYPE_LADDER ) && !( plocalPlayer->GetFlags() & FL_ONGROUND ) )
	{
		MustActiveBhop = true;
	}
	else
	{
		MustActiveBhop = false;
	}

	Vector vel = plocalPlayer->GetVelocity();
	float len = sqrtf( ( vel.x * vel.x ) + ( vel.y * vel.y ) );

	float angle = 12.0f;

	while ( angle > 0.01f )
	{
		float radians = DEG2RAD( 90.0f );
		radians += DEG2RAD( angle );

		if ( ( len * cosf( radians ) * -1.0f ) <= ( 30.0f ) )
			break;

		if ( angle > 8.0f )
			angle -= 0.01f;
		else
			angle -= 0.001f;
	}

	float base_angle = angle;

	if ( angle > 15.2f )
		angle = 15.2f;

	static float add_angle = 0.0f;

	if ( GetAsyncKeyState( 'C' ) )
		add_angle += ( pCmd->command_number % 7 );
	else
		add_angle = 0.0f;

	if ( add_angle > 180.0f )
		add_angle -= 360.0f;

	pCmd->viewangles.y += add_angle;

	if ( pCmd->viewangles.y > 180.0f )
		pCmd->viewangles.y -= 360.0f;

	MyPrediction.PreModification( plocalPlayer, pCmd );

	OldAngle = pCmd->viewangles;
	OldAngleFORS = pCmd->viewangles;

	C_MyWeaponInfo::Clear();

	//if ( !C_MyWeaponInfo::Init( plocalPlayer ) )
	//{

	//}

	C_MyWeapon *pWeapon = plocalPlayer->GetWeapon();

	if ( Aimbot::Enable )
	{
		if ( Aimbot::Selected == 1 )
			IWAimbot.Main( pCmd, plocalPlayer, pWeapon );
	}
	AutoFirePrimary( plocalPlayer, pWeapon, pCmd );//Cvars Control this ? aPistol
	if ( pWeapon )
	{
		if ( pWeapon->IsFirearm() )
		{
			if ( pCmd->buttons & IN_ATTACK )
			{
				if ( CheckFirePrimary( plocalPlayer, pWeapon ) && ( pCmd->buttons & IN_ATTACK ) )
				{
					shot_count += 1;
					if ( Aimbot::Inaccuracy )
					{
						unsigned int seed = MD5_PseudoRandom(pCmd->command_number) & 255;
						pCmd->viewangles = GetSpreadAngles( pCmd->viewangles, ( seed ), !false, nullptr, nullptr, nullptr, pWeapon );
						pCmd->viewangles -= plocalPlayer->GetPunchAngle() * 2.0f;
					}

					bSendPacket = false;
					if ( pWeapon->GetID() == WEAPON_AWP || pWeapon->GetID() == WEAPON_SCOUT || Aimbot::SendAttck )
					{
						bSendPacket = true;
					}
				}
			}
			else
			{
				if ( plocalPlayer && plocalPlayer->IsAlive() && plocalPlayer->GetMoveType() != MOVETYPE_LADDER && pWeapon->IsFirearm() && !( pCmd->buttons & IN_USE ) && Misc::AntiAim::Enable )
					AntiAim.RunAntiAim( plocalPlayer, pCmd, bSendPacket );
			}
		}
		else
		{
			if ( plocalPlayer && plocalPlayer->IsAlive() && plocalPlayer->GetMoveType() != MOVETYPE_LADDER && pWeapon->IsFirearm() && !( pCmd->buttons & IN_USE ) && Misc::AntiAim::Enable )
				AntiAim.RunAntiAim( plocalPlayer, pCmd, bSendPacket );
		}

	}

	Vector m_vecVelocityMe = plocalPlayer->GetVelocity();
	if ( Misc::AutoStrafer )
	{
		if ( pCmd->buttons & IN_JUMP )
		{
			float Speed = sqrt( ( m_vecVelocityMe[ 0 ] * m_vecVelocityMe[ 0 ] ) + ( m_vecVelocityMe[ 1 ] * m_vecVelocityMe[ 1 ] ) );
			float Value = 3.4 - ( Speed / 340 );

			if ( Speed > 500 )
			{
				Value = 2 - ( Speed / 1000 );
			}
			if ( Value <= 0.275 )
			{
				Value = 0.275;
			}


			static float OldY;
			float Difference = AngleNormalize( OldAngleFORS.y - OldY );
			if ( abs( Difference ) < Value )
			{
				static bool Flip = false;
				if ( Flip )
				{
					OldAngle.y -= Value;
					pCmd->sidemove = -400;
					Flip = false;
				}
				else
				{
					OldAngle.y += Value;
					pCmd->sidemove = 400;
					Flip = true;
				}
			}
			else
			{
				if ( Difference > 0.0f )
				{
					pCmd->sidemove = -400;
				}
				if ( Difference < 0.0f )
				{
					pCmd->sidemove = 400;
				}
			}

			OldY = OldAngleFORS.y;
		}
	}

	if ( !bLastJumped && bShouldFake ) {
		bShouldFake = false;
		pCmd->buttons |= IN_JUMP;
	}
	else if ( pCmd->buttons & IN_JUMP ) {
		if ( !MustActiveBhop ) {
			bLastJumped = true;
			bShouldFake = true;
		}
		else {
			pCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else {
		bLastJumped = false;
		bShouldFake = false;
	}

	//bool IsLisp[ 2 ] = { false, false };
	//if ( pCmd->viewangles.x > 180000 )
	//	IsLisp[ 0 ] = true;
	//if ( pCmd->viewangles.y > 180000 )
	//	IsLisp[ 1 ] = true;

	C_MyMath::NormalizeAngles( pCmd->viewangles );
	Vector Direction( pCmd->forwardmove, pCmd->sidemove, pCmd->upmove );
	float Velocity = Direction.Length();
	NormalizeVector( Direction );
	QAngle Angles;

	VectorAngles( Direction, Angles );

	float delta = ( pCmd->viewangles.y - OldAngle.y );
	float yaw = DEG2RAD( delta + Angles.y );

	if ( plocalPlayer->GetMoveType() != MOVETYPE_LADDER )
	{
		if ( ( pCmd->viewangles.x >= 90.0f ) || ( pCmd->viewangles.x <= -90.0f ) )
			pCmd->forwardmove = ( -cos( yaw ) * Velocity );
		else
			pCmd->forwardmove = ( cos( yaw ) * Velocity );

		pCmd->sidemove = ( sin( yaw ) * Velocity );
	}

	//if ( IsLisp[ 0 ] )
	//	pCmd->viewangles.x += 36000000;
	//if ( IsLisp[ 1 ] )
	//	pCmd->viewangles.y += 36000000;

	static bool frozen = false;
	if ( GetAsyncKeyState( VK_LMENU ) & 1 )
		frozen = !frozen;

	if ( frozen )
	{
		pCmd->tick_count = INT_MAX;
		pCmd->forwardmove = FLT_MAX;
		pCmd->sidemove = FLT_MAX;
		pCmd->upmove = FLT_MAX;
	}

	MyPrediction.PostModification( plocalPlayer );

	Interface->m_LastCmdInfo.m_LastCmd = *pCmd;
	Interface->m_LastCmdInfo.m_bSendPacket = bSendPacket;
}
//=================================================