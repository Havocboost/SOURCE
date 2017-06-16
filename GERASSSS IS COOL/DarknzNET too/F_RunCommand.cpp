#include "main.h"

void AdjustTickBase(C_MyEntity *localplayer, int simulation_ticks)
{
	INetChannelInfo *netinfo = Interface->Engine()->GetVTable<IVEngineClient>()->GetNetChannelInfo();

	int correctionTicks = /*max( */TIME2TICKS(netinfo->GetLatency(FLOW_OUTGOING))/*, 1 )*/;
	int idealTick = (localplayer->GetTickBase() + correctionTicks);

	localplayer->GetTickBase() = ((idealTick - simulation_ticks) + counter - 1);

	if (counter == SPEED_MOD)
	{
		counter = 1;
	}
	else
	{
		counter++;
	}
}
//=================================================
void __fastcall C_Interface::RunCommand(void *thisptr, int edx, C_MyEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper)
{
	/*if ( g_CustomPrediction.IsSpeeding() )
	{
	AdjustTickBase( player, SPEED_MOD );
	}*/

	Interface->Prediction()->GetOriginalMethod<RunCommand_t>(INDEX_RUNCOMMAND)(thisptr, player, ucmd, moveHelper);

	int tick = player->GetTickBase();

	DataManager.Get(player);

	player->GetTickBase() = tick;
}