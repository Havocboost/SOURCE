#include "main.h"

bool WriteUserCmd(bf_write *thisptr, CUserCmd *to, CUserCmd *from)
{
	typedef bool(__cdecl *WriteUserCmd_t)(bf_write *thisptr, CUserCmd *to, CUserCmd *from);
	static WriteUserCmd_t WriteUserCmd = (WriteUserCmd_t)((DWORD)GetModuleHandle("client.dll")  + 0x2DEAB0);

	if (!WriteUserCmd)
	{
		Utils.Log("WriteUserCmd not found");
	}


	return WriteUserCmd(thisptr, to, from);
}
//=================================================
bool __fastcall C_Interface::WriteUsercmdDeltaToBuffer(void *thisptr, int edx,int nSlot, bf_write *buf, int from, int to, bool isnewcommand)
{
	static CUserCmd nullCmd;
	CUserCmd *fromCmd = &nullCmd, *toCmd = &nullCmd;

	toCmd = Interface->Input()->GetVTable<CInput>()->GetUserCmd(nSlot,to);

	if (from != -1)
	{
		fromCmd = Interface->Input()->GetVTable<CInput>()->GetUserCmd(nSlot,from);
	}

	if (GetAsyncKeyState(VK_LMENU))
	{
		if (!(fromCmd->buttons & IN_ATTACK)
			&& !(toCmd->buttons & IN_ATTACK))
		{
			return false;
		}
	}	

	WriteUserCmd(buf, toCmd, fromCmd);


	return !buf->IsOverflowed();
}
