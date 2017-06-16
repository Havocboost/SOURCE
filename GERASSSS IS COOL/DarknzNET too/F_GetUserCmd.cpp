#include "main.h"

CUserCmd *__fastcall C_Interface::GetUserCmd(void *thisptr, int edx,int nSlot, int sequence_number)
{
	CUserCmd *commands = *(CUserCmd**)((DWORD)thisptr + 0xEC);
	CUserCmd *cmd = &commands[sequence_number % MULTIPLAYER_BACKUP];
	return cmd;
}