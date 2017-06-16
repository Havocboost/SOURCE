#pragma once
#include "main.h"


enum
{
	UNASSIGNED,
	SPECTATOR,
	TERRORIST,
	COUNTER_TERRORIST
};

class C_MyWeapon;

class C_MyEntity
{
public:
	void SetCurrentCommand(CUserCmd *cmd);
	CUserCmd *GetCurrentCommand(void);
	BYTE GetMoveType(void);
	IClientRenderable *GetRenderable(void);
	IClientNetworkable *GetNetworkable(void);
	C_BaseAnimating *GetBaseAnimating(void);
	ClientClass *GetClientClass(void);
	bool IsDormant(void);
	int GetIndex(void);
	const model_t *GetModel(void);
	bool SetupBones(matrix3x4_t * pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	Vector GetAbsOrigin(void);
	Vector GetEstimatedAbsVelocity(void);
	C_MyWeapon *GetWeapon(void);
	int * GetMyWeapons(void);
	C_MyEntity * GetViewModel(void);
	void SetWeaponModel(const char * name, C_MyWeapon * weapon);
	void ItemPostFrame(void);
	bool IsPlayer(void);
	int GetUserID(void);
	bool IsScoped(void);
	QAngle &GetPunchAngle(void);
	QAngle &GetViewPunchAngle(void);
	bool IsAlive(void);
	int GetCollisionGroup(void);
	int &GetTickBase(void);
	int GetFlags(void);
	float &GetNextAttack(void);
	int GetHitboxSet(void);
	QAngle &GetEyeAngles(void);
	bool IsBroken(void);
	bool IsProtected(void);
	bool IsBreakableEntity(void);
	Vector &GetViewOffset(void);
	int GetTeamNum(void);
	int GetHealth(void);
	color32 GetRenderColor(void);
	int GetArmorValue(void);
	bool HasHelmet(void);
	Vector &GetVelocity(void);
	Vector &GetAbsVelocity(void);
	Vector &GetBaseVelocity(void);
	float &GetFallVelocity(void);
	float &GetSimulationTime(void);
	float &GetOldAnimationTime(void);
	float &GetStamina(void);
	Vector GetEyePosition(void);
	bool IsOnGround(void);
	QAngle GetModifiedAimPunch(void);
	QAngle GetSpreadAngles(const QAngle &view, int seed, bool isAA, Vector *bullets = 0, int *bestShot = 0, Vector2D *spread = 0);
	bool CanFire(bool burstIncluded);
	bool IsShotBeingFired(CUserCmd *cmd, bool isattackingbeforefix);
	bool IsFirearm(void);	void SetLocalViewAngles(const QAngle &viewangles);
	void SetLocalAngles(const QAngle &angle);
	C_MyEntity* GetGroundEntity(void);
	void ApplyAbsVelocityImpulse(const Vector &vecImpulse);
	IClientVehicle* GetVehicle(void);
	bool UsingStandardWeaponsInVehicle(void);
	void SelectItem(const char *pstr, int iSubType = 0);
	void SetPredictionRandomSeed(CUserCmd* cmd);
	void ItemPreFrame(void);
	BYTE GetWaterLevel(void);
	void RemoveFromInterpolationList();
	void SetLocalOrigin(const Vector& Origin);
	void MoveToLastReceivedPosition(bool Force);
	void Interp_RestoreToLastNetworked(VarMapping_t *map);
	bool CanNextAttack();
	QAngle NoSpread(CUserCmd*Cmd, C_MyEntity*LocalPlayer, C_MyEntity*weapon);
	void Interpolate(void);


};