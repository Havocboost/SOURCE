#include "C_AntiAim.h"

C_AntiAim AntiAim;

class CTraceFilterNoPlayers : public CTraceFilter
{
public:

	CTraceFilterNoPlayers(void)
	{
		m_maxClients = -1;
	}

	virtual bool ShouldHitEntity(IHandleEntity *pEntity, int contentsMask)
	{
		if (m_maxClients == -1)
		{
			m_maxClients = Interface->Engine()->GetVTable<IVEngineClient>()->GetMaxClients();
		}


		C_MyEntity *entity = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntityFromHandle(pEntity->GetRefEHandle());

		return ((entity->GetIndex() < 1) || (entity->GetIndex() > m_maxClients));
	}

private:

	int m_maxClients;
};
//=================================================
void C_AntiAim::MovementFix(CUserCmd* pCmd)
{
	QAngle qReal;
	Interface->Engine()->GetVTable<IVEngineClient>()->GetViewAngles(qReal);
	Vector vMoveDir(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float fSpeed = vMoveDir.Length2D();
	NormalizeVector(vMoveDir);
	QAngle qMove;
	VectorAngles(vMoveDir, qMove);
	QAngle vDelta = qMove + (pCmd->viewangles - qReal);
	Vector vForward;
	AngleVectors(vDelta, &vForward);
	Vector vSet = vForward * fSpeed;
	pCmd->forwardmove = vSet.x;
	if (pCmd->viewangles.x < -89.0f || pCmd->viewangles.x > 89.0f)
		pCmd->sidemove = -vSet.y;
	else
		pCmd->sidemove = vSet.y;

	pCmd->upmove = vSet.z;
}


//=================================================
void C_AntiAim::EdgeAntAim(CUserCmd* Cmd, C_MyEntity* LocalPlayer, float Angle, bool CornersToo, bool ShouldSendOnCorners, bool ShouldSendNormal, bool &SendPacket)
{
	CTraceFilterNoPlayers filter;

	Vector localPosition = LocalPlayer->GetAbsOrigin() + LocalPlayer->GetViewOffset();


	for (int y = 360; y >= 0.0f; --y)
	{
		QAngle tmp(10.f, Cmd->viewangles.y, 0.f);
		tmp.y += y;
		C_MyMath::NormalizeAngles(tmp);

		Vector forward;
		AngleVectors(tmp, &forward, 0, 0);

		float length = ((16 + 3) + ((16 + 3) * sin(DEG2RAD(10.f)))) + 7;
		forward *= length;

		Ray_t ray;
		trace_t traceData;
		ray.Init(localPosition, (localPosition + forward));
		Interface->EngineTrace()->GetVTable<IEngineTrace>()->TraceRay(ray, 0x200400B, (ITraceFilter*)&filter, &traceData);

		if (traceData.fraction != 1.f)
		{

			QAngle angles;
			VectorAngles(-traceData.plane.normal, angles);
			tmp.y = angles.y;
			C_MyMath::NormalizeAngles(tmp);

			trace_t leftTrace, rightTrace;
			Vector left, right;
			AngleVectors(tmp + QAngle(0.f, 30.f, 0.f), &left, 0, 0);
			AngleVectors(tmp - QAngle(0.f, 30.f, 0.f), &right, 0, 0);

			left *= (length + (length * sin(DEG2RAD(30.f))));
			right *= (length + (length * sin(DEG2RAD(30.f))));

			ray.Init(localPosition, (localPosition + left));
			Interface->EngineTrace()->GetVTable<IEngineTrace>()->TraceRay(ray, 0x200400B, (ITraceFilter*)&filter, &leftTrace);

			ray.Init(localPosition, (localPosition + right));
			Interface->EngineTrace()->GetVTable<IEngineTrace>()->TraceRay(ray, 0x200400B, (ITraceFilter*)&filter, &rightTrace);

			bool Active = false;

			if ((leftTrace.fraction == 1.0f)
				&& (rightTrace.fraction != 1.0f))
			{
				Active = true;
				tmp.y -= 90.f;
			}
			else if ((leftTrace.fraction != 1.0f)
				&& (rightTrace.fraction == 1.0f))
			{
				Active = true;
				tmp.y += 90.f;
			}

			Cmd->viewangles.x = 177.99f;

			if (!Active || CornersToo)
				Cmd->viewangles.y = tmp.y - Angle;
			else
				Cmd->viewangles.y = tmp.y;

			if (Active)
			{
				SendPacket = ShouldSendOnCorners;
			}
			else
			{
				SendPacket = ShouldSendNormal;
			}

		}
	}
}

static float LookAtMe()
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


//=================================================
static float RunAimPlayerBehindWall(CUserCmd* Cmd, C_MyEntity* LocalPlayer)
{
	for (int i = Globals()->maxClients; i >= 1; --i)
	{
		if (i == LocalPlayer->GetIndex())
		{
			continue;
		}

		C_MyEntity *targetEntity = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(i);

		if (!targetEntity
			|| targetEntity->IsDormant()
			|| !targetEntity->IsAlive()
			|| (targetEntity->GetTeamNum() == LocalPlayer->GetTeamNum())
			|| targetEntity->IsProtected())
		{
			continue;
		}

		int health = targetEntity->GetHealth();

		if (!(health > 0)
			|| (targetEntity->GetHealth() >= 500))
		{
			continue;
		}

		float fldist = FLT_MAX;
		Vector dir = (targetEntity->GetAbsOrigin() - LocalPlayer->GetAbsOrigin());
		float distance = NormalizeVector(dir);
		if (distance < fldist)
		{
			fldist = distance;
			C_MyMath::NormalizeVector(dir);
			C_MyMath::VectorToAngles(dir, Cmd->viewangles);
		}

		return Cmd->viewangles.y;
	}
}
//=================================================
Vector AlternativeCheck(C_MyEntity* pLocalPlayer, CUserCmd* pCmd)
{
	Vector AbsVelocity = pLocalPlayer->GetEstimatedAbsVelocity();

	float angle = RunAimPlayerBehindWall(pCmd, pLocalPlayer);

	bool Check;
	if (pLocalPlayer->GetTeamNum() == 3)
	{
		Check = !((angle >= 0.0f) && (angle <= 180.0f));
	}
	else
	{
		Check = (angle > 0.0f) && (angle < 180.0f);
	}

	if (Check)
	{
		AbsVelocity.x = -AbsVelocity.x;
	}

	return AbsVelocity;
}
//=================================================
void C_AntiAim::SetupPitch( CUserCmd *cmd )
{

	if ( Misc::AntiAim::Pitch == 1 )//´safe down
	{
		cmd->viewangles.x = 88.9f;
	}

	if ( Misc::AntiAim::Pitch == 2 )//FakeDown
	{
		cmd->viewangles.x = -271;
	}

	if ( Misc::AntiAim::Pitch == 3 )//Emotion
	{
		cmd->viewangles.x = 70;
	}

	if ( Misc::AntiAim::Pitch == 4 )//MM Down
	{
		cmd->viewangles.x = 177.99f;
	}
	if ( Misc::AntiAim::Pitch == 5 ) // test 
	{
		cmd->viewangles.x = 261.f || 180.f;
	}
	if ( Misc::AntiAim::Pitch == 6 ) // zero
	{
		cmd->viewangles.x = 0.0f;
	}
	if ( Misc::AntiAim::Pitch == 7 ) //up
	{
		cmd->viewangles.x = -89;
	}

}
//=================================================
void C_AntiAim::Sideways(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;
	if (Misc::AntiAim::AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			if (localPlayer->GetTeamNum() == 2)
			{
				cmd->viewangles.y = 360.f;
			}
			else
			{
				cmd->viewangles.y = 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (localPlayer->GetTeamNum() == 2)
			{
				cmd->viewangles.y = 180.f;
			}
			else
			{
				cmd->viewangles.y = 270.0f;
			}
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			if (localPlayer->GetTeamNum() == 2)
			{
				cmd->viewangles.y -= 155.f;
			}
			else
			{
				cmd->viewangles.y -= 300.f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (localPlayer->GetTeamNum() == 2)
			{
				cmd->viewangles.y -= 10.0f;
			}
			else
			{
				cmd->viewangles.y -= 271.0f;
			}
			bSendPackets = false;
		}
	}
}
//=================================================
void C_AntiAim::Backwards(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (Misc::AntiAim::AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y = 180.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y = 360.0f;
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= 180.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y -= 360.0f;
			bSendPackets = false;
		}
	}
}
//=================================================
void C_AntiAim::AlternativeAngles(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets, Vector pVecAbs)
{
	static bool first;
	if (Misc::AntiAim::AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y = 90.0f;
				else
					cmd->viewangles.y = 270.0f;
			}
			else
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y = 270.0f;
				else
					cmd->viewangles.y = 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y = 270.0f;
				else
					cmd->viewangles.y = 90.0f;
			}
			else
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y = 90.0f;
				else
					cmd->viewangles.y = 270.0f;
			}
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y -= 90.0f;
				else
					cmd->viewangles.y -= 270.0f;
			}
			else
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y -= 270.0f;
				else
					cmd->viewangles.y -= 90.0f;
			}
			bSendPackets = true;
		}
		else
		{
			first = true; 
			if (pVecAbs.x >= 0.0f)
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y -= 270.0f;
				else
					cmd->viewangles.y -= 90.0f;
			}
			else
			{
				if (localPlayer->GetTeamNum() == 2)
					cmd->viewangles.y -= 90.0f;
				else
					cmd->viewangles.y -= 270.0f;
			}
			bSendPackets = false;
		}
	}
}
//=================================================
void C_AntiAim::Crownt(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (Misc::AntiAim::AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y += 155.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y -= 115.0f;
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= 155.0f;
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y += 115.0f;
			bSendPackets = false;
		}
	}
}
//=================================================
void C_AntiAim::Spinbot(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{
	static bool first;

	if (Misc::AntiAim::AntiAimMode == 0)
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y = (GetTickCount() / 0.001f * 360.0);
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y = (GetTickCount() / 0.001f * -360.0f);
			bSendPackets = false;
		}
	}
	else
	{
		if (first)
		{
			first = false;
			cmd->viewangles.y -= (GetTickCount() / 0.001f * 360.0);
			bSendPackets = true;
		}
		else
		{
			first = true;
			cmd->viewangles.y += (GetTickCount() / 0.001f * -360.0f);
			bSendPackets = false;
		}
	}
}
//=================================================
void C_AntiAim::RunFakelags(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets)
{

	//Alternative Check 
	Vector vTemp = AlternativeCheck(localPlayer, cmd);


	//==================================================

	//Setup Pitch

	SetupPitch(cmd);

	//=================================================
	
	

	float ***GetLowerBodyYawTarget;

	GetLowerBodyYawTarget[ 0x39F8 ][ 0xE6996CCF ] [ 0xE6996CCF ];



	//Setup Yaw
	static bool jitterswitch = false;
	if (Misc::AntiAim::AntiaimType == 0) //Sideways
	{
		cmd->viewangles.y = ( localPlayer && 180, bSendPackets = false);

	}

	if (Misc::AntiAim::AntiaimType == 1) //Backwards
	{
		Backwards( localPlayer, cmd, bSendPackets );
	}
	
	if (Misc::AntiAim::AntiaimType == 2) //Test
	{
		cmd->viewangles.y = 180.f;
	}
	else
	{
		cmd->viewangles.y = 270;
		bSendPackets = false;
	}

	if ( Misc::AntiAim::AntiaimType == 3 ) //test
	{
		if ( jitterswitch = false )
		{
			cmd->viewangles.y = 360 || 90;
		}
		else
		{
			cmd->viewangles.y = 270 || 180;
			bSendPackets = false;
			jitterswitch = true;
		}

	}
		//static float flCurYaw = cmd->viewangles.y;
		//bool bSwitch = ( cmd->command_number % 2 == 0 );


		//int random = rand() % 100;
		//int random2 = rand() % 1000;

		//static bool bDirrectionAmbi = false;

		//random = rand() % 100;
		//random2 = rand() % 1000;

		//if ( random == 1 ) bDirrectionAmbi = !bDirrectionAmbi;

		//if ( bDirrectionAmbi )
		//	flCurYaw += Misc::AntiAim::Spinspeed;
		//else
		//	flCurYaw -= Misc::AntiAim::Spinspeed;


		//if ( bSwitch )
		//{
		//	cmd->viewangles.y = flCurYaw;
		//}
		//else
		//{
		//	cmd->viewangles.y = flCurYaw + 180;
		//	bSendPackets = false( );
		//}

		//if ( random == random2 )
		//	cmd->viewangles.y += random;

	if (Misc::AntiAim::AntiaimType == 4) //Backwards Jitter
	{
		if (jitterswitch)
		{
			cmd->viewangles.y -= (180.0f - Misc::AntiAim::JitterAngle);
			jitterswitch = false;
		}
		else
		{
			cmd->viewangles.y -= (180.0f + Misc::AntiAim::JitterAngle);
			jitterswitch = true;
		}
	}
	if (Misc::AntiAim::AntiaimType == 5) //Sideways Jitter
	{
		if (jitterswitch)
		{
			cmd->viewangles.y -= (90.0f - Misc::AntiAim::JitterAngle);
			jitterswitch = false;
		}
		else
		{
			cmd->viewangles.y -= (90.0f + Misc::AntiAim::JitterAngle);
			jitterswitch = true;
		}
	}
	if (Misc::AntiAim::AntiaimType == 6) //Backwards Jitter 2
	{
		static bool sendpackets = false;

		if (sendpackets)
		{
			bSendPackets = true;
			if (jitterswitch)
			{
				cmd->viewangles.y -= 145.0f;
				jitterswitch = false;
			}
			else
			{
				cmd->viewangles.y -= 215.0f;
				jitterswitch = true;
			}
			sendpackets = false;
		}
		else
		{
			bSendPackets = false;
			cmd->viewangles.y -= 360.0f;
			sendpackets = true;
		}
	}


	if ( Misc::AntiAim::AntiaimType == 7 )//FAKE FORWARD
	{
		if ( cmd->command_number % 3 )
		{
			
			cmd->viewangles.y += 180.0f;
		}
		else
		{
			bSendPackets = false;
			cmd->viewangles.y -= 180.0f;
		}

	}
	
	if ( Misc::AntiAim::AntiaimType == 8 ) //Jitter Synced
	{
	{
			//Jitter Synced
			if ( cmd->command_number % 3 )
			cmd->viewangles.y = cmd->viewangles.y + 100.0;
			bSendPackets = false;
		}
	}
	
	if ( Misc::AntiAim::AntiaimType == 9 )
	{
		//Sideways
		{
			Spinbot( localPlayer, cmd, bSendPackets );
		}
	}

	if ( Misc::AntiAim::AntiaimType == 10 )
	{
		static bool spin;
		if (spin) 
		{
			spin = true;
			cmd->viewangles.y += 360.f;
		}
		else
		{
			spin = false;
			cmd->viewangles.y = 69.02738273f;
			bSendPackets = false;
		}

	}
	//=================================================

	//Following AntiAim

	if (Misc::AntiAim::AntiAimMode == 3 && Misc::AntiAim::AntiaimType != 4)
	{
		RunAimPlayerBehindWall(cmd,localPlayer);
	}

	//=================================================

	//Setup FakeLags

	if (Misc::AntiAim::FakelagMode == 1)//Constant
	{
		static int Ticks =  13;
		if (Ticks <= 0)
		{
			bSendPackets = true;

			Vector vel = localPlayer->GetVelocity();
			vel.z = 0.0f;

			int f = ( int ) ( ceilf( ( 64.0f / 0.0078125f ) / vel.Length() ) );

			if ( f < 1 )
				f = 1;

			if ( f > 13 )
				f = 13;

			static bool diff = false;
			diff = !diff;

			Ticks = f - (diff ? 1 : 0);
		}
		else
		{
			bSendPackets = false;
			Ticks--;
		}
	}

	if ( Misc::AntiAim::FakelagMode == 2 )//SQCH FAKELAG
	{
		static int iTick;
		if ( iTick < Misc::AntiAim::Constant_Force && !( cmd->buttons & IN_ATTACK ) ) 
		{
			bSendPackets = false;
			iTick++;
		}
		else 
		{
			bSendPackets = true;
			iTick = 0;
		}
	}

	if (Misc::AntiAim::FakelagMode == 3)//Constant + Disable IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			bSendPackets = true;
		}
		static int Ticks = Misc::AntiAim::Constant_Force;
		if (Ticks <= 0)
		{
			bSendPackets = true;
			Ticks = Misc::AntiAim::Constant_Force;
		}
		else
		{
			bSendPackets = false;
			Ticks--;
		}
	}

	if (Misc::AntiAim::FakelagMode == 4) // Alternative
	{
		static int Ticks = 0;
		static bool Packet_Drop = false;
		bool Reset_Counter = false;
		if (Packet_Drop)
			bSendPackets = false;
		if (Packet_Drop&&Ticks > Misc::AntiAim::TicksBlocked) // 5 or 7 //4 !
		{
			Reset_Counter = true;
			Packet_Drop = false;
		}
		else if (!Packet_Drop&&Ticks > Misc::AntiAim::TicksSent) //2 or 4 //2 !
		{
			Reset_Counter = true;
			Packet_Drop = true;
		}
		Ticks++;
		if (Reset_Counter)
			Ticks = 0;
	}

	if (Misc::AntiAim::FakelagMode == 5) // Alternative + Custom IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			static int Ticks = Misc::AntiAim::InAttackForce;
			if (Ticks <= 0)
			{
				bSendPackets = true;
				Ticks = Misc::AntiAim::InAttackForce;
			}
			else
			{
				bSendPackets = false;
				Ticks--;
			}
		}
		else
		{
			static int Ticks = 0;
			static bool Packet_Drop = false;
			bool Reset_Counter = false;
			if (Packet_Drop)
				bSendPackets = false;
			if (Packet_Drop&&Ticks > Misc::AntiAim::TicksBlocked) // 5 or 7 //4 !
			{
				Reset_Counter = true;
				Packet_Drop = false;
			}
			else if (!Packet_Drop&&Ticks > Misc::AntiAim::TicksSent) //2 or 4 //2 !
			{
				Reset_Counter = true;
				Packet_Drop = true;
			}
			Ticks++;
			if (Reset_Counter)
				Ticks = 0;
		}
	}

	if (Misc::AntiAim::FakelagMode == 6) // Alternative + Off IN_ATTACK
	{
		if (cmd->buttons & IN_ATTACK)
		{
			bSendPackets = true;
		}
		else
		{
			static int Ticks = 0;
			static bool Packet_Drop = false;
			bool Reset_Counter = false;
			if (Packet_Drop)
				bSendPackets = false;
			if (Packet_Drop&&Ticks > Misc::AntiAim::TicksBlocked) // 5 or 7 //4 !
			{
				Reset_Counter = true;
				Packet_Drop = false;
			}
			else if (!Packet_Drop&&Ticks > Misc::AntiAim::TicksSent) //2 or 4 //2 !
			{
				Reset_Counter = true;
				Packet_Drop = true;
			}
			Ticks++;
			if (Reset_Counter)
				Ticks = 0;
		}
	}


	//TODO

	/*
	static int droppp;
	static int send;


	droppp = g_Cvars.AA_Blocked;
	send = g_Cvars.AA_Sent;


	static int testsent =  g_Cvars.AA_Sent;
	static int Ticks2 = g_Cvars.AA_Blocked;
	if (Ticks2 <= 0)
	{
	if (testsent <= 0)
	{
	sendPacket = true;
	testsent = send;
	}
	else
	{
	testsent--;
	}
	//--
	//**SendPacket = true;
	Ticks2 = droppp;
	}
	else
	{
	sendPacket = false;
	Ticks2--;
	}*/


}
//=================================================
void C_AntiAim::RunAntiAim(C_MyEntity* LocalPlayer, CUserCmd* Cmd, bool &bSendPackets)
{

	/*if ((Cmd->buttons & IN_DUCK) && (LocalPlayer->GetVelocity().Length() < 300.f))
	{
		RunAimPlayerBehindWall(Cmd, LocalPlayer);
		Cmd->viewangles.x = 180;
		static int Ticks = 1;
		if (Ticks <= 0)
		{
			EdgeAntAim(Cmd, LocalPlayer, 180.0f, false, true, false, bSendPackets);
			Cmd->viewangles.y -= 360;
			Cmd->buttons &= ~IN_DUCK;
			bSendPackets = false;
			Ticks = 1;
		}
		else
		{
			bSendPackets = true;
			Cmd->viewangles.y -= 180;
			EdgeAntAim(Cmd, LocalPlayer, 0.0f, false, true, true, bSendPackets);
			Ticks--;
		}
	}
	else
	{*/
	RunFakelags(LocalPlayer, Cmd, bSendPackets);
	if (LocalPlayer->GetVelocity().Length() < 300.f)
		EdgeAntAim( Cmd, LocalPlayer, 0, true, true, true, bSendPackets );
	//	}
}