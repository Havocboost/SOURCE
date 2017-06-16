#include "C_Data.h"

C_DataManager DataManager;

void C_DataManager::Get(C_MyEntity *localPlayer)
{
	int tick = localPlayer->GetTickBase();

	S_Data *slot = &m_data[tick % HISTORY_MAX];

	slot->m_tick = tick;
	slot->m_punchAngle = localPlayer->GetPunchAngle();
	slot->m_viewOffset = localPlayer->GetViewOffset();
	slot->m_fallVelocity = localPlayer->GetFallVelocity();

	if (localPlayer->IsFirearm())
	{
		slot->m_accuracyPenalty = localPlayer->GetWeapon()->GetAccuracyPenalty();
	}
}
//=================================================
void C_DataManager::Set(C_MyEntity *localPlayer)
{
	static int sizes[] =
	{
		1,
		3,
		3,
		1,
		1,
	};


	int tick = localPlayer->GetTickBase();

	//if ( GetAsyncKeyState( 0x5 ) )
	//{
	//	tick += ( SPEED_MOD - 1 );
	//}
	
	S_Data *slot = &m_data[tick % HISTORY_MAX];
	
	bool validation[MAX_TARGETS];
	Validate(localPlayer, slot, validation);

	if (!validation[m_nTickBase])
	{
		bool wasFound = false;

		for (int i = 1; i < HISTORY_MAX; ++i)
		{
			slot = &m_data[(tick - i) % HISTORY_MAX];

			Validate(localPlayer, slot, validation);

			if (validation[m_nTickBase])
			{
				wasFound = true;
				break;
			}
		}

		if (!wasFound)
		{
			//Utils.Log("Unable to validate tick %i in history", tick);
			return;
		}
	}


	if (validation[m_vecPunchAngle])
	{
		localPlayer->GetPunchAngle() = slot->m_punchAngle;
	}
	
	if (validation[m_vecViewOffset])
	{
		localPlayer->GetViewOffset() = slot->m_viewOffset;
	}

	if (validation[m_flFallVelocity])
	{
		localPlayer->GetFallVelocity() = slot->m_fallVelocity;
	}

	if (validation[m_flAccuracyPenalty])
	{
		localPlayer->GetWeapon()->GetAccuracyPenalty() = slot->m_accuracyPenalty;
	}
}
//=================================================
void C_DataManager::Validate(C_MyEntity *localPlayer, S_Data *slot, bool *validated)
{
	int var = -1;
	validated[++var] = (slot->m_tick == localPlayer->GetTickBase());
	validated[++var] = ((slot->m_punchAngle - localPlayer->GetPunchAngle()).Length() < .33f);
	validated[++var] = ((slot->m_viewOffset - localPlayer->GetViewOffset()).Length() < .5f);
	validated[++var] = (fabs(slot->m_fallVelocity - localPlayer->GetFallVelocity()) < .5f);
	validated[++var] = (localPlayer->IsFirearm() && (fabs(slot->m_accuracyPenalty - localPlayer->GetWeapon()->GetAccuracyPenalty()) < .2f));
}