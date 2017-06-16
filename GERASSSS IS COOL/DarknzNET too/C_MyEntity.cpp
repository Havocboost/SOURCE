#include "main.h"


void C_MyEntity::SetCurrentCommand(CUserCmd *cmd)
{	
//	*Member<CUserCmd**>(this, 0x101C) = cmd;
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_hConstraintEntity");
	*Member<CUserCmd**>(this, (offset - 0xC)) = cmd;
}
//=================================================
CUserCmd *C_MyEntity::GetCurrentCommand(void)
{
	//return *Member<CUserCmd**>(this, 0x101C);
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_hConstraintEntity");
	return *Member<CUserCmd**>(this, (offset - 0xC));
}
//=================================================
BYTE C_MyEntity::GetMoveType(void)
{
	static int offset = (Netvars->GetOffset("DT_CSPlayer", "m_nRenderMode") + 0x1);
	return *Member<BYTE*>(this, offset);
}
//=================================================
IClientRenderable *C_MyEntity::GetRenderable(void)
{
	return Member<IClientRenderable*>(this, 4);
}
//=================================================
IClientNetworkable *C_MyEntity::GetNetworkable(void)
{
	return Member<IClientNetworkable*>(this, 8);
}
//=================================================
ClientClass *C_MyEntity::GetClientClass(void)
{
	typedef ClientClass *(__thiscall *GetClientClass_t)(void *thisptr);
	return ((GetClientClass_t)(*Member<DWORD*>(*(DWORD*)(GetNetworkable()), 8)))(GetNetworkable());
}
//=================================================
bool C_MyEntity::IsDormant(void)
{
	typedef bool(__thiscall *IsDormant_t)(void *thisptr);
	return ((IsDormant_t)(*Member<DWORD*>(*(DWORD*)(GetNetworkable()), 0x24)))(GetNetworkable());
}
//=================================================
int C_MyEntity::GetIndex(void)
{
	typedef int(__thiscall *GetIndex_t)(void *thisptr);
	return ((GetIndex_t)(*Member<DWORD*>(*(DWORD*)(GetNetworkable()), 0x28)))(GetNetworkable());
}
//=================================================
const model_t *C_MyEntity::GetModel(void)
{
	typedef const model_t *(__thiscall *GetModel_t)(void *thisptr);
	return ((GetModel_t)(*Member<DWORD*>(*(DWORD*)(GetRenderable()), 0x20)))(GetRenderable());
}
//=================================================
bool C_MyEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	typedef bool(__thiscall *SetupBones_t)(void *thisptr, matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	return ((SetupBones_t)(*Member<DWORD*>(*(DWORD*)(GetRenderable()), 0x34)))(GetRenderable(), pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}
//=================================================
Vector C_MyEntity::GetAbsOrigin(void)
{
	typedef Vector &(__thiscall *GetAbsOrigin_t)(void *thisptr);
	return ((GetAbsOrigin_t)(*Member<DWORD*>(*(DWORD*)(this), 0x28)))(this);
}
//=================================================
C_BaseAnimating *C_MyEntity::GetBaseAnimating(void)
{
	typedef C_BaseAnimating*(__thiscall *GetAbsOrigin_t)(void *thisptr);
	return ((GetAbsOrigin_t)(*Member<DWORD*>(*(DWORD*)(this), 0x0B0)))(this);
}
//=================================================
bool C_MyEntity::IsBreakableEntity(void)
{
	typedef bool(__thiscall *IsBreakableEntity_t)(void *thisptr);
	static IsBreakableEntity_t IsBreakableEntity = (IsBreakableEntity_t)Memory::Sigscan_offsets::IsBreakableEntity;

	if (!IsBreakableEntity)
	{
		Utils.Log("IsBreakableEntity not found");
	}
	return IsBreakableEntity(this);
}
//=================================================
Vector C_MyEntity::GetEstimatedAbsVelocity(void)
{

	typedef void(__thiscall *EstimateAbsVelocity_t)(void *thisptr,Vector &velocity);
	Vector velocity;
	((EstimateAbsVelocity_t)(*Member<DWORD*>(*(DWORD*)(this), 0x234)))(this, velocity);

	return velocity;
}
//=================================================
C_MyWeapon *C_MyEntity::GetWeapon(void)
{
	static int offset = (Netvars->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon"));
	return (C_MyWeapon*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntityFromHandle(*Member<int*>(this, offset));
}
//=================================================
int *C_MyEntity::GetMyWeapons(void)
{
	static int offset = (Netvars->GetOffset("DT_BaseCombatCharacter", "m_LastHitGroup") + 0x84);
	return Member<int*>(this, offset);
}
//=================================================
C_MyEntity* C_MyEntity::GetViewModel(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_hVehicle") + 0x8;
	return (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntityFromHandle(*Member<int*>(this, offset));
}
//=================================================
void C_MyEntity::SetWeaponModel(const char* name, C_MyWeapon*weapon)
{
	typedef void(__thiscall *SetWeaponViewModel_t)(void *thisptr, const char*, C_MyWeapon*);
	((SetWeaponViewModel_t)(*Member<DWORD*>(*(DWORD*)(this), 0x3C8)))(this, name, weapon);
}
//=================================================
void C_MyEntity::ItemPostFrame(void)
{
	((void_t)(*Member<DWORD*>(*(DWORD*)(this), 0x3F8)))(this);
}
//=================================================
bool C_MyEntity::IsPlayer(void)
{
	typedef bool(__thiscall *IsPlayer_t)(void *thisptr);
	return ((IsPlayer_t)(*Member<DWORD*>(*(DWORD*)(this), 0x200)))(this);
}
//=================================================
int	C_MyEntity::GetUserID(void)
{
	player_info_t pi;

	if (!Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerInfo(GetIndex(), &pi))
		return -1;

	return pi.m_nUserID;
}
//=================================================
bool C_MyEntity::IsScoped(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_bIsScoped");
	return (*Member<bool*>(this, offset));
}
//=================================================
bool C_MyEntity::IsProtected(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
	return (*Member<bool*>(this, offset));
}
//=================================================
QAngle &C_MyEntity::GetPunchAngle(void)
{
	static int offset = (Netvars->GetOffset("DT_CSPlayer", "m_aimPunchAngle"));
	return *Member<QAngle*>(this, 0x0000301C);
}
//=================================================
QAngle &C_MyEntity::GetViewPunchAngle(void)
{
	static int offset = (Netvars->GetOffset("DT_CSPlayer", "m_viewPunchAngle"));
	return *Member<QAngle*>(this, offset);
}
//=================================================
int C_MyEntity::GetCollisionGroup(void)
{
	static int offset = Netvars->GetOffset("DT_PlantedC4", "m_CollisionGroup");
	return *Member<int*>(this, offset);
}
//=================================================
bool C_MyEntity::IsAlive(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_lifeState");
	return (*Member<BYTE*>(this, offset) == LIFE_ALIVE);
}
//=================================================
bool C_MyEntity::IsBroken(void)
{
	static int offset = Netvars->GetOffset("DT_BreakableSurface", "m_bIsBroken");
	return (*Member<bool*>(this, offset));
}
//=================================================
int &C_MyEntity::GetTickBase(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_nTickBase");
	return *Member<int*>(this, offset);
}
//=================================================
IClientVehicle* C_MyEntity::GetVehicle(void)
{
	typedef IClientVehicle* (__thiscall *GetVehicle_t)(void *thisptr);
	return ((GetVehicle_t)(*Member<DWORD*>(*(DWORD*)(this), 0x14C)))(this);
}
//=================================================
void C_MyEntity::SetLocalViewAngles(const QAngle &viewangles)
{
	typedef void(__thiscall *SetLocalViewAngles_t)(void *thisptr, const QAngle&);
	((SetLocalViewAngles_t)(*Member<DWORD*>(*(DWORD*)(this), 0x488)))(this, viewangles);
}
//=================================================
BYTE C_MyEntity::GetWaterLevel(void)
{
	return *Member<BYTE*>(this, 0x25A);
}
//=================================================
void C_MyEntity::ItemPreFrame(void)
{
	((void_t)(*Member<DWORD*>(*(DWORD*)(this), 0x3F4)))(this);
}
//=================================================
void C_MyEntity::SelectItem(const char *pstr, int iSubType)
{
	typedef void(__thiscall *SelectItem_t)(void *thisptr, const char *pstr, int iSubType);
	((SelectItem_t)(*Member<DWORD*>(*(DWORD*)(this), 0x410)))(this, pstr, iSubType);
}
//=================================================
int C_MyEntity::GetFlags(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_fFlags");
	return *Member<int*>(this, offset);
}
//=================================================
float &C_MyEntity::GetNextAttack(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_flNextAttack");
	return *Member<float*>(this, offset);
}
//=================================================
int C_MyEntity::GetHitboxSet(void)
{
	static int offset = Netvars->GetOffset("DT_BaseAnimating", "m_nHitboxSet");
	return *Member<int*>(this, offset);
}
//=================================================
QAngle &C_MyEntity::GetEyeAngles(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_angEyeAngles[0]");
	return *Member<QAngle*>(this, offset);
}
//=================================================
Vector &C_MyEntity::GetViewOffset(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_vecViewOffset[0]");
	return *Member<Vector*>(this, offset);
}
//=================================================
int C_MyEntity::GetTeamNum(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_iTeamNum");
	return *Member<int*>(this, offset);
}
//=================================================
int C_MyEntity::GetHealth(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_iHealth");
	return *Member<int*>(this, offset);
}
//=================================================
color32 C_MyEntity::GetRenderColor(void)
{
	static int offset = Netvars->GetOffset("DT_BaseEntity", "m_clrRender");
	return *Member<color32*>(this, offset);
}
//=================================================
int C_MyEntity::GetArmorValue(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_ArmorValue");
	return *Member<int*>(this, offset);
}
//=================================================
bool C_MyEntity::HasHelmet(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_bHasHelmet");
	return *Member<bool*>(this, offset);
}
//=================================================
Vector &C_MyEntity::GetVelocity(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_vecVelocity[0]");
	return *Member<Vector*>(this, offset);
}
//=================================================
Vector &C_MyEntity::GetAbsVelocity(void)
{
	static int offset = (Netvars->GetOffset("DT_BasePlayer", "m_vecVelocity[0]") + 0xC); // it's next to m_vecVelocity
	return *Member<Vector*>(this, offset);
}
//=================================================
Vector &C_MyEntity::GetBaseVelocity(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_vecBaseVelocity");
	return *Member<Vector*>(this, offset);
}
//=================================================
float &C_MyEntity::GetFallVelocity(void)
{
	static int offset = Netvars->GetOffset("DT_BasePlayer", "m_flFallVelocity");
	return *Member<float*>(this, offset);
}
//=================================================
float &C_MyEntity::GetSimulationTime(void)
{
	static int offset = Netvars->GetOffset( "DT_BaseEntity", "m_flSimulationTime" );
	return *Member<float*>( this, offset );
}
//=================================================
float &C_MyEntity::GetOldAnimationTime(void)
{
	static int offset = Netvars->GetOffset("DT_BaseEntity", "m_flSimulationTime") - 0x4;
	return *Member<float*>(this, offset);
}
//=================================================
float &C_MyEntity::GetStamina(void)
{
	static int offset = Netvars->GetOffset("DT_CSPlayer", "m_flStamina");
	return *Member<float*>(this, offset);
}
//=================================================
Vector C_MyEntity::GetEyePosition(void)
{
	return (GetAbsOrigin() + GetViewOffset());
}
//=================================================
bool C_MyEntity::IsOnGround(void)
{
	return (GetFlags() & FL_ONGROUND);
}
//=================================================
QAngle C_MyEntity::GetModifiedAimPunch(void)
{
	return (GetPunchAngle() * 2);
}
//=================================================
bool C_MyEntity::CanNextAttack()
{
	bool Result = false;

	if (GetNextAttack() <= Globals()->curtime)
		Result = true;

	return Result;
}
//=================================================
bool C_MyEntity::IsShotBeingFired(CUserCmd *cmd, bool isattackingbeforefix)
{
	C_MyWeapon *weapon = GetWeapon();

	if (!IsFirearm())
	{
		return false;
	}


	bool isattacking = (cmd->buttons & IN_ATTACK);

	int id = weapon->GetID();
	int offsetIndex = C_MyWeapon::GetIDToOffsetIndex(id);

	if ((((weapon->GetID() == WEAPON_GLOCK) || (weapon->GetID() == WEAPON_FAMAS))
		&& (weapon->IsSpecialMode(offsetIndex)
			&& weapon->HasBurstShotsRemaining(offsetIndex))))
	{
		isattacking = (isattacking || (isattackingbeforefix && (Globals()->curtime >= weapon->GetNextBurstShootTime(offsetIndex))));
	}

	return isattacking;
}
//=================================================
bool C_MyEntity::IsFirearm(void)
{
	C_MyWeapon *weapon = GetWeapon();

	return (weapon && weapon->IsFirearm());
}


QAngle C_MyEntity::GetSpreadAngles(const QAngle &view, int seed, bool isAA, Vector *bullets, int *bestShot, Vector2D *spread)
{
	C_MyWeapon *weapon = GetWeapon();

	if (!IsFirearm())
	{
		return QAngle(0.f, 0.f, 0.f);
	}


	const float constInaccuracy = weapon->GetInaccuracy();
	const float constSpread = weapon->GetSpread();


	Vector direction, right, up;
	C_MyMath::AngleToVectors(view, &direction, &right, &up);


	RandomSeed(seed + 1);


	float pi_1 = RandomFloat(0.f, 6.283185f);//je suis sur que c'est cette petite valeur qui fou la merde D
	float inaccuracy = RandomFloat(0.f, constInaccuracy);
	Vector2D leftSpread((cos(pi_1) * inaccuracy), (sin(pi_1) * inaccuracy));


	Vector2D rightSpread[10];

	for (int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet)
	{
		float pi_2 = RandomFloat(0.f, 6.283185f);
		float spread = RandomFloat(0.f, constSpread);
		rightSpread[bullet] = Vector2D((cos(pi_2) * spread), (sin(pi_2) * spread));
	}

	Vector2D totalSpread;

	if (C_MyWeaponInfo::Get()->m_bulletsPerShot == 1)
	{
		totalSpread = (leftSpread + rightSpread[0]);

		if (bestShot)
		{
			*bestShot = 0;
		}
	}
	else
	{
		float bestDistance = FLT_MAX;
		int bestBullet = -1;

		for (int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet)
		{
			float totalDistance = 0.f;
			Vector2D bulletSpread = (leftSpread + rightSpread[bullet]);

			// median
			for (int i = 0; i < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++i)
			{
				if (i == bullet)
				{
					continue;
				}

				Vector2D tmpSpread = (leftSpread + rightSpread[i]);
				totalDistance += (tmpSpread - bulletSpread).Length();
			}


			if (totalDistance < bestDistance)
			{
				bestDistance = totalDistance;
				bestBullet = bullet;
			}
		}


		totalSpread = (leftSpread + rightSpread[bestBullet]);

		if (bestShot)
		{
			*bestShot = bestBullet;
		}
	}


	for (int bullet = 0; bullet < C_MyWeaponInfo::Get()->m_bulletsPerShot; ++bullet)
	{
		Vector2D tmpSpread = (leftSpread + rightSpread[bullet]);

		if (isAA)
		{
			tmpSpread = -tmpSpread;
		}


		Vector shot = (direction + (right * tmpSpread.x) + (up * tmpSpread.y));
		C_MyMath::NormalizeVector(shot);

		if (bullets)
		{
			bullets[bullet] = shot;
		}
	}


	if (isAA)
	{
		totalSpread *= -1;
	}


	if (spread)
	{
		*spread = totalSpread;
	}

	float flIdentity[3][3];
	Vector shot = (direction + (right * totalSpread.x) + (up * totalSpread.y));
	C_MyMath::NormalizeVector(shot);

	flIdentity[2][0] = 1.0f;
	flIdentity[2][1] = -totalSpread[0];
	flIdentity[2][2] = totalSpread[1];

	NormalizeVector(flIdentity[2]);

	flIdentity[0][0] = 0.0f;
	flIdentity[0][1] = -totalSpread[0];
	flIdentity[0][2] = (1.0f / totalSpread[1]) + (1.0f / flIdentity[2][2]) + totalSpread[1];

	if (totalSpread[0] > 0.0f && totalSpread[1] < 0.0f)
	{
		if (flIdentity[0][1] < 0.0f)
			flIdentity[0][1] = -flIdentity[0][1];
	}
	else if (totalSpread[0] < 0.0f && totalSpread[1] < 0.0f)
	{
		if (flIdentity[0][1] > 0.0f)
			flIdentity[0][1] = -flIdentity[0][1];
	}

	if (flIdentity[0][2] < 0.0f)
		flIdentity[0][2] = -flIdentity[0][2];

	NormalizeVector(flIdentity[0]);

	// Get the left vector via crossproduct.

	CrossProduct(flIdentity[0], flIdentity[2], flIdentity[1]);
	NormalizeVector(flIdentity[1]);

	// Calculate the roll angle.

	float flCross = (flIdentity[1][1] * flIdentity[2][0]) - (flIdentity[1][0] * flIdentity[2][1]);
	float flRoll;

	if (view[0] > 84.0f || view[0] < -84.0f)
		flRoll = RAD2DEG(atan2f(flIdentity[1][2], sqrtf(flCross)));
	else
		flRoll = RAD2DEG(atan2f(flIdentity[1][2], flCross));

	if (flRoll < 0.0f)
		flRoll += 360.0f;



	QAngle angles;
	C_MyMath::VectorToAngles(shot, up, angles);
	angles[2] += flRoll;

	angles -= view;
	C_MyMath::NormalizeAngles(angles);

	return angles;
}

//=================================================
void C_MyEntity::RemoveFromInterpolationList()
{
	typedef void(__thiscall* RemoveFromInterpolationList_t)(void*thisptr);
	static DWORD result = (DWORD)Memory::Sigscan_offsets::RemoveFromInterpolationList;
	((RemoveFromInterpolationList_t)(result))(this);
}
//=================================================
/*void C_MyEntity::SetLocalOrigin( const Vector& Origin )
{
typedef void (__thiscall *SetLocalOrigin_t)(void*thisptr, const Vector& Origin);

((SetLocalOrigin_t)((DWORD)GetModuleHandleA("client")+0x43720))(this,Origin);
}*/
//=================================================
void C_MyEntity::MoveToLastReceivedPosition(bool Force)
{
	typedef void(__thiscall* MoveToLastReceivedPosition_t)(void*thisptr, bool Force);
	static DWORD result = (DWORD)Memory::Sigscan_offsets::MoveToLastReceivedPosition;
	((MoveToLastReceivedPosition_t)(result))(this,Force);
}
//=================================================
void C_MyEntity::Interp_RestoreToLastNetworked(VarMapping_t *map)
{
	typedef void(__thiscall *GetAbsOrigin_t)(void *thisptr);
	((GetAbsOrigin_t)(*Member<DWORD*>(*(DWORD*)(this), 0x1BC)))(this);
}

void C_MyEntity::Interpolate(void)
{	
	typedef bool(__thiscall *InterPolate_t)(void *thisptr, float);
	bool bReturn = ((InterPolate_t)(*Member<DWORD*>(*(DWORD*)(this), 0x1C0)))(this, Globals()->curtime);

	*(bool*)(this + 0x274) = bReturn;
}
