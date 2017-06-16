#include "C_AutoWall.h"

C_AutoWall AutoWall;

bool C_AutoWall::TraceDidHitWorld(trace_t* pTrace)
{

	return(pTrace->m_pEnt == (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(0));
}
bool C_AutoWall::TraceDidHitNonWorldEntity(trace_t* pTrace)
{
	if (!pTrace)
		return false;

	if (pTrace->m_pEnt == NULL)
		return false;

	if (TraceDidHitWorld(pTrace))
		return false;

	return true;
}
bool C_AutoWall::HandleBulletPenetration(FireBulletData& BulletData)
{
	surfacedata_t* pEnterSurfaceData = Interface->PhysicsSurfaceProps()->GetVTable<IPhysicsSurfaceProps>()->GetSurfaceData(BulletData.enter_trace.surface.surfaceProps);
	if (!pEnterSurfaceData)
		return false;

	int iEnterMaterial = pEnterSurfaceData->game.material;
	auto flEnterSurfacePenetrationModifier = pEnterSurfaceData->game.flPenetrationModifier;

	BulletData.trace_length += BulletData.enter_trace.fraction * BulletData.trace_length_remaining;
	BulletData.current_damage *= (float)pow(C_MyWeaponInfo::Get()->m_rangeModifier, (BulletData.trace_length * 0.002f));

	if ((BulletData.trace_length > 3000.f) || (flEnterSurfacePenetrationModifier < 0.1f))
		BulletData.penetrate_count = 0;

	if (BulletData.penetrate_count <= 0)
	{
		return false;

	}

	Vector vecTemp;
	trace_t ExitTrace;
	if (!TraceToExit(vecTemp, &BulletData.enter_trace, BulletData.enter_trace.endpos, BulletData.direction, &ExitTrace))
	{
		return false;
	}

	surfacedata_t* pExitSurfaceData = Interface->PhysicsSurfaceProps()->GetVTable<IPhysicsSurfaceProps>()->GetSurfaceData(BulletData.enter_trace.surface.surfaceProps);
	if (!pExitSurfaceData)
	{
		return false;
	}

	int iExitMaterial = pExitSurfaceData->game.material;
	auto flExitSurfacePenetrationModifier = pExitSurfaceData->game.flPenetrationModifier;
	auto flDinalDamageModifier = 0.16f;
	auto flCombinedPenetrarionModifier = 0.0f;

	if (((BulletData.enter_trace.contents & CONTENTS_GRATE) != 0) || (iEnterMaterial == CHAR_TEX_GLASS) || (iEnterMaterial == CHAR_TEX_GRATE))
	{
		flCombinedPenetrarionModifier = 3.0f;
		flDinalDamageModifier = 0.05f;
	}
	else
	{
		flCombinedPenetrarionModifier = (flEnterSurfacePenetrationModifier + flExitSurfacePenetrationModifier) * 0.5f;
	}


	if (iEnterMaterial == iExitMaterial)
	{
		if (iExitMaterial == CHAR_TEX_WOOD || iExitMaterial == 85)
			flCombinedPenetrarionModifier = 3.0f;
		else if (iExitMaterial == 76)
			flCombinedPenetrarionModifier = 2.0f;
		//Metal....
		//else if (iExitMaterial == 77)
		//flCombinedPenetrarionModifier = 0.4f;
	}

	auto flModifier = fmaxf(0.f, 1.0f / flCombinedPenetrarionModifier);
	auto flTakenDamage = (BulletData.current_damage * flDinalDamageModifier) + flModifier * 3.0f * fmaxf(0.0f, (3.0f / C_MyWeaponInfo::Get()->m_penetration) * 1.25f);
	float flThickness = VectorLength(ExitTrace.endpos - BulletData.enter_trace.endpos);

	flThickness *= flThickness;
	flThickness *= flModifier;
	flThickness /= 24.0f;

	auto flTravelDamage = fmaxf(0.0f, flTakenDamage + flThickness);

	if (flTravelDamage > BulletData.current_damage)
		return false;

	if (flTravelDamage >= 0.0f)
		BulletData.current_damage -= flTravelDamage;

	if (BulletData.current_damage < 1.0f)
		return false;

	BulletData.src = ExitTrace.endpos;
	BulletData.penetrate_count--;

	return true;
}
bool C_AutoWall::PenetrateWall(C_MyEntity* pBaseEntity, C_MyWeapon* pWeapon, const Vector& vecPoint, float& flDamage)
{
	if (!pBaseEntity || !pWeapon)
		return false;

	auto BulletData = FireBulletData(pBaseEntity->GetEyePosition());
	BulletData.filter.pSkip = pBaseEntity;

	QAngle qAngles;
	IWAimbot.CalcAngle(BulletData.src, const_cast<Vector&>(vecPoint), qAngles);
	AngleVectors(qAngles, &BulletData.direction);
	C_MyMath::VectorNormalizes(BulletData.direction);


	if (!SimulateFireBullet(pBaseEntity, pWeapon, BulletData))
	{
		return false;
	}
	
	flDamage = BulletData.current_damage;

	return true;
}
float GetHitgroupDamageMult(int iHitgroup)
{
	switch (iHitgroup)
	{
	case HITGROUP_GENERIC:
		return 1.f;
	case HITGROUP_HEAD:
		return 4.f;
	case HITGROUP_CHEST:
		return 1.f;
	case HITGROUP_STOMACH:
		return 1.5f;
	case HITGROUP_LEFTARM:
		return 1.f;
	case HITGROUP_RIGHTARM:
		return 1.f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.f;
	default:
		break;
	}

	return 1.f;
}
void C_AutoWall::ScaleDamage(int iHitgroup, C_MyEntity* pBaseEntity, float flWeaponArmorRatio, float& flDamage)
{
	if (!pBaseEntity)
		return;

	flDamage *= GetHitgroupDamageMult(iHitgroup);

	if (pBaseEntity->GetArmorValue() > 0)
	{
		if (iHitgroup == HITGROUP_HEAD)
		{
			if (pBaseEntity->HasHelmet())
				flDamage *= (flWeaponArmorRatio * 1.5f);
		}
		else flDamage *= (flWeaponArmorRatio * 0.5f);
	}
}
int GetPlayerModifiedDamage(const float &constdamage, bool isHeadshot, C_MyWeapon*Weapon, C_MyEntity *targetEntity)
{
	float damage = constdamage;

	int armor = targetEntity->GetArmorValue();
	if ((armor > 0) && (!isHeadshot || (isHeadshot)))
	{
		float weaponArmorRatio = (.5f * C_MyWeaponInfo::Get()->m_weaponArmorRatio);

		float newdamage = (weaponArmorRatio * damage);
		float armordamage = ((damage - newdamage) * .5f);

		if (armordamage <= (float)armor)
		{
			armordamage = armordamage;
		}
		else
		{
			newdamage = (damage + ((float)armor * -2.f));
			armordamage = (int)armor;
		}

		damage = newdamage;
	}
	else
	{
		damage = damage;
	}

	return (int)damage;
}
//=================================================
float GetHitgroupModifiedDamage(float dmg, int hitgroup)
{
	static float hitgroupModifiers[] = { 1.f, 4.f, 1.f, 1.25f, 1.f, 1.f, .75f, .75f };
	return (dmg * hitgroupModifiers[hitgroup]);
}
void C_AutoWall::UTIL_TraceLine(const Vector& vecStart, const Vector& vecEnd, unsigned int nMask, C_MyEntity* pCSIgnore, trace_t* pTrace)
{
	Ray_t ray;
	ray.Init(vecStart, vecEnd);

	CTraceFilter filter;
	filter.pSkip = pCSIgnore;
	Interface->EngineTrace()->GetVTable<IEngineTrace>()->TraceRay(ray, nMask, &filter, pTrace);
}

bool C_AutoWall::SimulateFireBullet(C_MyEntity* pBaseEntity, C_MyWeapon* pWeapon, FireBulletData& BulletData)
{
	if (!pBaseEntity || !pWeapon)
		return false;

	BulletData.penetrate_count = 4;
	BulletData.trace_length = 0.0f;

	BulletData.current_damage = (float)C_MyWeaponInfo::Get()->m_damage;
	while ((BulletData.penetrate_count > 0) && (BulletData.current_damage >= 1.0f))
	{
		BulletData.trace_length_remaining = C_MyWeaponInfo::Get()->m_maxRange - BulletData.trace_length;
		auto vecEnd = BulletData.src + BulletData.direction * BulletData.trace_length_remaining;
		UTIL_TraceLine(BulletData.src, vecEnd, 0x4600400B, pBaseEntity, &BulletData.enter_trace);


		if (BulletData.enter_trace.fraction == 1.0f)
			break;

		if ((BulletData.enter_trace.hitgroup <= 7) && (BulletData.enter_trace.hitgroup > 0) && pBaseEntity->GetTeamNum() != BulletData.enter_trace.m_pEnt->GetTeamNum())
		{
			BulletData.trace_length += BulletData.enter_trace.fraction * BulletData.trace_length_remaining;
			BulletData.current_damage *= (float)pow(C_MyWeaponInfo::Get()->m_rangeModifier, BulletData.trace_length * 0.002);
			ScaleDamage(BulletData.enter_trace.hitgroup, BulletData.enter_trace.m_pEnt, C_MyWeaponInfo::Get()->m_weaponArmorRatio, BulletData.current_damage);
			GetPlayerModifiedDamage(GetHitgroupModifiedDamage(BulletData.current_damage, BulletData.enter_trace.hitgroup), (BulletData.enter_trace.hitgroup == 1), pWeapon, pBaseEntity); //Comment here
			return true;
		}

		if (!HandleBulletPenetration(BulletData))
			break;
	}

	return false;
}


bool C_AutoWall::TraceToExit(Vector& vecEnd, trace_t* pEnterTrace, Vector vecStart, Vector vecDir, trace_t* pExitTrace)
{
	auto flDistance = 0.0f;
	while (flDistance <= 90.0f)
	{
		flDistance += 4.0f;
		vecEnd = vecStart + vecDir * flDistance;

		auto iPointContents = Interface->EngineTrace()->GetVTable<IEngineTrace>()->GetPointContents(vecEnd, MASK_SHOT_HULL | CONTENTS_HITBOX, NULL);
		if (iPointContents & MASK_SHOT_HULL && (!(iPointContents & CONTENTS_HITBOX)))
			continue;

		auto vecNewEnd = vecEnd - (vecDir * 4.0f);
		UTIL_TraceLine(vecEnd, vecNewEnd, 0x4600400B, 0, pExitTrace);

		if (!pExitTrace->m_pEnt)
		{
			return false;
		}

		if (pExitTrace->startsolid && pExitTrace->surface.flags & SURF_HITBOX)
		{
			UTIL_TraceLine(vecEnd, vecStart, 0x600400B, pExitTrace->m_pEnt, pExitTrace);
			if ((pExitTrace->fraction < 1.0f || pExitTrace->allsolid) && !pExitTrace->startsolid)
			{
				vecEnd = pExitTrace->endpos;
				return true;
			}
			continue;
		}

		if (!(pExitTrace->fraction < 1.0 || pExitTrace->allsolid || pExitTrace->startsolid) || pExitTrace->startsolid)
		{
			if (pExitTrace->m_pEnt)
			{
				if (TraceDidHitNonWorldEntity(pEnterTrace) /*Comment here*//*&& pEnterTrace->m_pEnt->IsBreakableEntity()*/) 
				{
					return true;
				}
			}
			continue;
		}

		if (((pExitTrace->surface.flags >> 7) & 1) && !((pEnterTrace->surface.flags >> 7) & 1))
			continue;


		if (pExitTrace->plane.normal.Dot(vecDir) <= 1.0f)
		{
			auto flFraction = pExitTrace->fraction * 4.0f;
			vecEnd = vecEnd - (vecDir * flFraction);
			return true;
		}
	}
	return false;
}