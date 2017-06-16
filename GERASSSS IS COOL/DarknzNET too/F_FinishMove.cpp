#include "main.h"

void __fastcall C_Interface::FinishMove(void *thisptr, int edx, C_MyEntity *player, CUserCmd *ucmd, CMoveData *move)
{
	Interface->Prediction()->GetOriginalMethod<FinishMove_t>(INDEX_FINISHMOVE)(thisptr, player, ucmd, move);

	player->GetAbsVelocity() = (player->GetBaseVelocity() + player->GetVelocity());
}