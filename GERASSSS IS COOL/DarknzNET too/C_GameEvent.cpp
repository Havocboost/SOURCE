#include "C_GameEvent.h"

C_GameEvent* Event;
char szRoundSay[512];
/*
int Kills, Headshots, Deaths;
float HeadshotRatio = 0;*/
//=================================================
float GetRatio(float one, float two)
{
	float final;
	if (one > two) {
		final = (float)two / (float)one * 100.0f;
	}
	else {
		final = (float)one / (float)two * 100.0f;
	}
	return final;
}
//=================================================
void C_GameEvent::FireGameEvent(IGameEvent* event)
{

	const char* szEventName = event->GetName();
	if (!szEventName)
		return;

	if (Misc::Roundsay == 1)
	{ 
		if (!strstr(szEventName, "round_start"))
			Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say lonely hills");
	}
	if (Misc::BuyBotEnable)
	{
		if (Misc::BuyBot == 0)
		{
			if (!strcmp(szEventName, "round_start"))
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say !ak!usp!helmet");
		}
		if (Misc::BuyBot == 1)
		{
			if (!strcmp(szEventName, "round_start"))
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say !m249!usp!helmet");
		}
		if (Misc::BuyBot == 2)
		{
			if (!strcmp(szEventName, "round_start"))
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say !ak!deagle!helmet");
		}
		if (Misc::BuyBot == 3)
		{
			if (!strcmp(szEventName, "round_start"))
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say !m249!deagle!helmet");
		}
		if (Misc::BuyBot == 4)
		{
			if (!strcmp(szEventName, "round_start"))
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say !awp!deagle!helmet");
		}
	}

	if (!strcmp(szEventName, "round_start"))
	{
		//Aimbot.BulletCounter = 0;
		Interface->DebugOverlay()->GetVTable<IVDebugOverlay>()->ClearAllOverlays();
	}

	if (!strcmp(szEventName, "player_death"))
	{
		int me = Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer();
		int killer = Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(event->GetInt("attacker"));
		if (killer == me)
		{
			//Aimbot.BulletCounter = 0;
		}
	}
	
	if (!strcmp(szEventName, "player_death") && Misc::HeadshotSay == 1)
	{
		int me = Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer();
		int dead = Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(event->GetInt("userid"));
		int killer = Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(event->GetInt("attacker"));
		//g_pSurface->PlaySound("death");
		bool headshot = event->GetBool("headshot");
		if (killer == me && dead != me)
		{
			if (!headshot)
			{
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say No Headshot !");
			}
			else
			{
				Interface->Engine()->GetVTable<IVEngineClient>()->ClientCmd("say Headshot !");
			}
		}
	}
}
//=================================================
void C_GameEvent::RegisterSelf()
{
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "game_newmap", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "game_start", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "round_start", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "round_end", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "player_death", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "player_connect", false);
}


bool __fastcall C_Interface::FireEventClientSide(void *thisptr,int edx,IGameEvent* event)
{

	if (!event->GetName())
		return false;

	const char* eventname = event->GetName();


	static Vector impact;

	if (strcmp(eventname, "player_hurt") == 0)
	{
		int attacker = event->GetInt("attacker");
		attacker = Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(attacker);

		int local = Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer();

		if (attacker == local)
		{
			int damage = event->GetInt("dmg_health");
			C_MyEntity * ent = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(event->GetInt("userid")));

			HitMarkerManager.ReportHit(ent->GetEyePosition(), damage, Utils.GetHitgroupModifiedDamage(C_MyWeaponInfo::Get()->m_damage, 1));
			if (Misc::Hitsound)
			{
				Interface->Surface()->GetOriginalMethod<PlaySound_t>(INDEX_PLAYSOUND)(Interface->Surface()->thisptr(), "ambient/animal/horse_5.wav");
			}

		}
	}

	return Interface->GameEventManager()->GetOriginalMethod<FireGameEventClientSide_t>(INDEX_FIREGAMEEVENTCLIENTSIDE)(thisptr, event);
}