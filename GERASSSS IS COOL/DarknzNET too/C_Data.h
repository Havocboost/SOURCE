#pragma once
#include "main.h"
#define HISTORY_MAX 128


enum E_Targets
{
	m_nTickBase,
	m_vecPunchAngle,
	m_vecViewOffset,
	m_flFallVelocity,
	m_flAccuracyPenalty,
	MAX_TARGETS
};


struct S_Data
{
	void *operator[](int i)
	{
		return &((void**)(this))[i];
	}

	int		m_tick;	
	QAngle	m_punchAngle;
	Vector	m_viewOffset;
	float	m_fallVelocity;
	float	m_accuracyPenalty;
};


class C_DataManager
{
public:

	// called in RunCommand to store predicted data
	void Get(C_MyEntity *localPlayer);


	// called in a proxy to set our own predicted data
	void Set(C_MyEntity *localPlayer);


	// validates our data
	void Validate(C_MyEntity *localPlayer, S_Data *slot, bool *validated);


private:

	S_Data m_data[HISTORY_MAX];
};


extern C_DataManager DataManager;