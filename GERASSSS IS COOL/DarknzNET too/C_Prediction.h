#pragma once


#include "main.h"


#define SPEED_MOD 15


class C_Prediction
{
public:

	// wtf compil0r
	C_Prediction(void) {};
	void RunSpeedHack(void);
	void AdjustTickBase(C_MyEntity *localplayer, int simulation_ticks);
	// call this before the cmd is modified
	void PreModification(C_MyEntity *localPlayer, CUserCmd *cmd);
	// call this after we're done with the cmd
	void PostModification(C_MyEntity *localPlayer);
	bool IsSpeeding(void);
	void RunSimulation(CUserCmd*Cmd, C_BasePlayer*LocalPlayer);


private:

	// predicts m_fAccuracyPenalty
	void PredictWeapon(C_MyEntity *localPlayer);
	bool m_isSpeeding;
	float m_oldFrameTime;
	float m_oldCurTime;
	int lastTick;
	// backups
	int m_tickBase;
	QAngle m_punchAngle;
	Vector m_velocity;
	float m_accuracyPenalty;};


extern C_Prediction MyPrediction;
extern int counter;