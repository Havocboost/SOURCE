#include "C_Prediction.h"


C_Prediction MyPrediction;


//int counter = SPEED_MOD;
//void CCustomPrediction::RunSpeedHack( void )
//{
//	m_isSpeeding = ( GetAsyncKeyState( 0x4 ) && ( counter > 1 ) )
//					|| ( ( counter != ( SPEED_MOD - 1 ) ) && ( counter > 1 )
//					|| ( counter == 1 ) );
//
//
//	DWORD ebp = (DWORD)Memory::GetExtendedBasePointer();
//	ebp = **(DWORD**)( ebp ); // ebp of cl_move that called this createmove
//
//
//	if ( m_isSpeeding && ( counter != 1 ) )
//	{
//		*(DWORD*)( ebp + 4 ) -= 5;
//
//		// we do this to send it all in 1 packet
//		*(bool*)( ebp - 1 ) = false;
//
//		--counter;
//	}
//	else
//	{
//		// we do this to send it all in 1 packet
//		*(bool*)( ebp - 1 ) = true;
//
//		counter = ( SPEED_MOD - 1 );
//	}
//}

int counter = 1;
void C_Prediction::RunSpeedHack(void)
{
	m_isSpeeding = (GetAsyncKeyState(0x4) && (counter <= SPEED_MOD))
		|| ((counter != 1) && (counter <= SPEED_MOD))
		|| (counter == SPEED_MOD);
	
	DWORD ebp = (DWORD)Memory::GetExtendedBasePointer();
	ebp = **(DWORD**)(ebp); 

	if (m_isSpeeding && (counter != SPEED_MOD))
	{
		*(DWORD*)(ebp + 4) -= 5;

		*(bool*)(ebp - 1) = false;
	}
	else
	{

		*(bool*)(ebp - 1) = true;
	}
}
//=================================================
void C_Prediction::AdjustTickBase(C_MyEntity *localplayer, int simulation_ticks)
{
	// client pred fix
	if (counter == SPEED_MOD)
	{
		counter = 1;
	}

	if (counter == 1)
	{
		INetChannelInfo *netinfo = Interface->Engine()->GetVTable<IVEngineClient>()->GetNetChannelInfo();

		int correctionTicks = /*max( */TIME2TICKS(netinfo->GetLatency(FLOW_OUTGOING))/*, 1 )*/;
		int idealTick = (localplayer->GetTickBase() + correctionTicks);
		
		localplayer->GetTickBase() = ((idealTick - simulation_ticks) + counter /*- 1*/);
	}
}


//=================================================
void C_Prediction::PreModification(C_MyEntity *localPlayer, CUserCmd *cmd)
{
	//RunSpeedHack();
	void* movehelperptr = Interface->MoveHelper()->thisptr();

	m_tickBase = localPlayer->GetTickBase();

	if (m_isSpeeding)
	{
		AdjustTickBase(localPlayer, SPEED_MOD);
	}


	if (localPlayer->GetTickBase() == lastTick)
	{
		localPlayer->GetTickBase() += 1;
	}

	lastTick = localPlayer->GetTickBase();
	m_punchAngle = localPlayer->GetPunchAngle();
	m_velocity = localPlayer->GetVelocity();

	m_oldFrameTime = Globals()->frametime;
	Globals()->frametime = Globals()->interval_per_tick;

	m_oldCurTime = Globals()->curtime;
	Globals()->curtime = (localPlayer->GetTickBase() * Globals()->interval_per_tick);

	if (localPlayer->IsAlive())
	{
		Interface->MoveHelper()->GetOriginalMethod<SetHost_t>(INDEX_SETHOST)(movehelperptr, localPlayer);
		localPlayer->SetCurrentCommand(cmd);
	//	*(int*)(hmClient + 0x0A761EC) = cmd->random_seed;
		//*(C_MyEntity**)(hmClient + 0x2EDA538) = localPlayer;
	}


	char tmp[0xFF];

	void *thisptr = Interface->Prediction()->thisptr();
	void *moveptr = Interface->GameMovement()->thisptr();

	Interface->Prediction()->GetOriginalMethod<SetupMove_t>(INDEX_SETUPMOVE)(thisptr, localPlayer, cmd, 0, (CMoveData*)&tmp);
	Interface->GameMovement()->GetOriginalMethod<ProcessMovement_t>(INDEX_PROCESSMOVEMENT)(moveptr, localPlayer, (CMoveData*)&tmp);
	Interface->Prediction()->GetOriginalMethod<FinishMove_t>(INDEX_FINISHMOVE)(thisptr, localPlayer, cmd, (CMoveData*)&tmp);
	
	PredictWeapon(localPlayer);
}
//=================================================
void C_Prediction::PostModification(C_MyEntity *localPlayer)
{
	void *thisptr = Interface->MoveHelper()->thisptr();
	
		localPlayer->GetPunchAngle() = m_punchAngle;
		localPlayer->GetVelocity() = m_velocity;

		C_MyWeapon *weapon = localPlayer->GetWeapon();

		if (weapon)
		{
			weapon->GetAccuracyPenalty() = m_accuracyPenalty;
		}
	

	Globals()->frametime = m_oldFrameTime;
	Globals()->curtime = m_oldCurTime;

	localPlayer->SetCurrentCommand(NULL);
	//*(int*)(hmClient + 0x0A761EC) = -1;
	//*(DWORD*)(hmClient + 0x2EDA538) = NULL;

	if (localPlayer->GetTickBase() == lastTick)
	{
		localPlayer->GetTickBase() += 1;
	}
	else
	{
		localPlayer->GetTickBase() = 0;
	}


	Interface->MoveHelper()->GetOriginalMethod<SetHost_t>(INDEX_SETHOST)(thisptr, NULL);
	
}
//=================================================
bool C_Prediction::IsSpeeding(void)
{
	return m_isSpeeding;
}
//=================================================
void C_Prediction::PredictWeapon(C_MyEntity *localPlayer)
{
	C_MyWeapon *weapon = localPlayer->GetWeapon();

	if (!weapon)
	{
		return;
	}
	
	bool shouldupdate = true;

	int id = weapon->GetID();
	int offsetIndex = C_MyWeapon::GetIDToOffsetIndex(id);

	if ((id == WEAPON_GLOCK) || (id == WEAPON_FAMAS))
	{
		if (weapon->IsSpecialMode(offsetIndex)
			&& weapon->HasBurstShotsRemaining(offsetIndex))
		{
			shouldupdate = false;
		}
	}

	if (shouldupdate)
	{
		m_accuracyPenalty = weapon->GetAccuracyPenalty();
		weapon->UpdateAccuracyPenalty();
	}
}
//=================================================