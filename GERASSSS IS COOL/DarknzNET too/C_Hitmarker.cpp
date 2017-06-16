#include "C_Hitmarker.h"
#include "mmsystem.h"


C_HitMarkerManager HitMarkerManager;
C_HitListener* HitListener;
//=================================================
S_Hit::S_Hit(const Vector &origin, int damage, int maxDamage)
{
	m_origin = origin;
	m_damage = damage;
	m_maxDamage = maxDamage;

	m_spawnTime = (Globals()->framecount * Globals()->frametime);
	m_currentTime = m_spawnTime;
	m_fadeTime = (m_spawnTime + HITMARK_FADE_START_TIME);
	m_dieTime = (m_spawnTime + HITMARK_DECAY_TIME);
}
//=================================================
void S_Hit::RunFrame(C_MyEntity *localPlayer)
{
	// fucking retarded shit i had to div almost everything by 1 to get a proper result
	const float delta = (1.f - (1 / ((1 / (m_dieTime - m_currentTime)) / (1 / HITMARK_DECAY_TIME))));

	m_currentTime += Globals()->frametime;

	Vector origin = m_origin;
	origin.z += (delta * HITMARK_HEIGHT);
	
	Vector screen;
	if (!Draw.WorldToScreen(origin, screen))
	{
		return;
	}

	int g = (int)(255 - (((float)m_damage / (float)m_maxDamage) * 255));

	int b = (int)(delta * 255);

	// so it goes towards being white
	if (b >= g)
	{
		g = b;
	}

	int a = 255;

	if (m_currentTime >= m_fadeTime)
	{
		a = (((float)((m_dieTime - m_currentTime) / (HITMARK_DECAY_TIME - HITMARK_FADE_START_TIME))) * 255);
	}


	Color colour(255, g, b, a);
	Draw.DrawString(true, GetFontIndexByDistance((origin - localPlayer->GetEyePosition()).Length()), screen.x, screen.y, colour, "-%i", m_damage);
}
//=================================================
bool S_Hit::IsFinished(void)
{
	return (m_currentTime >= m_dieTime);
}
//=================================================
C_HitMarkerManager::~C_HitMarkerManager(void)
{
	Clear();
}
//=================================================
void C_HitMarkerManager::ReportHit(const Vector &origin, int damage, int maxDamage)
{
	S_Hit *hit = new S_Hit(origin, damage, maxDamage);
	
	m_hits.push_back(hit);
}
//=================================================
void C_HitMarkerManager::RunFrame(C_MyEntity *localPlayer)
{	
	for each (S_Hit *hit in m_hits)
	{
		if (hit)
		{
			hit->RunFrame(localPlayer);

			if (hit->IsFinished())
			{
				delete hit;
				m_hits.resize(std::remove(m_hits.begin(), m_hits.end(), hit) - m_hits.begin());
			}
		}
	}
}
//=================================================
void C_HitMarkerManager::Clear(void)
{
	C_MyEntity *localPlayer = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer());

	if (!localPlayer)
	{
		return;
	}

	for each (S_Hit *hit in m_hits)
	{
		delete hit;
		m_hits.resize(std::remove(m_hits.begin(), m_hits.end(), hit) - m_hits.begin());
	}

	m_hits.clear();
}
//=================================================
void IGameEventListener2::FireGameEvent(IGameEvent *event)
{

}
//=================================================
char szTestSay[512];
void C_HitListener::FireGameEvent(IGameEvent *event)
{
	static Vector impact;	

	if (strcmp(event->GetName(), "player_hurt") == 0)
	{
		int attacker = event->GetInt("attacker");
		attacker = Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerForUserID(attacker);

		int local = Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer();

		if (attacker == local)
		{
			int damage = event->GetInt("dmg_health");

			//Utils.Log("PlayerHit !");

			HitMarkerManager.ReportHit(impact, damage, Utils.GetHitgroupModifiedDamage(C_MyWeaponInfo::Get()->m_damage, 1));
			if (Misc::Hitsound)
			{
				//PlaySound("C:/Samhook/hitmark.wav", 0, SND_ASYNC);//WinApi cuz I suck and I cannot make the surface work properly + Asynchronous Processing cuztopkek //TODO embeded res, surface load.
			}

		}
	}
	else if (strcmp(event->GetName(), "bullet_impact") == 0)
	{
		impact.x = event->GetFloat("x");
		impact.y = event->GetFloat("y");
		impact.z = event->GetFloat("z");
	}
}
//=================================================
void C_HitListener::Init(void)
{	
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "bullet_impact", false);
	Interface->GameEventManager()->GetVTable<IGameEventManager2>()->AddListener(this, "player_hurt", false);
}