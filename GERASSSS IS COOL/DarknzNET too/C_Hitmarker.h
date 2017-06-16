#pragma once
#include "main.h"


#define HITMARK_DECAY_TIME 2.0f
#define HITMARK_FADE_START_TIME .30f
#define HITMARK_HEIGHT 200.f


struct S_Hit
{
	S_Hit(const Vector &origin, int damage, int maxDamage);

	void RunFrame(C_MyEntity *localPlayer);

	bool IsFinished(void);

	Vector	m_origin;
	int		m_damage;
	int		m_maxDamage;
	float	m_spawnTime;
	float	m_currentTime;
	float	m_fadeTime;
	float	m_dieTime;
};


class C_HitMarkerManager
{
public:

	~C_HitMarkerManager(void);

	void ReportHit(const Vector &origin, int damage, int maxDamage);

	void RunFrame(C_MyEntity *localPlayer);

	void Clear(void);

private:

	std::vector<S_Hit*> m_hits;
};


extern C_HitMarkerManager HitMarkerManager;


class C_HitListener : public IGameEventListener2
{
public:
	C_HitListener();
	void Init(void);

	void FireGameEvent(IGameEvent *event);
};


extern C_HitListener* HitListener;