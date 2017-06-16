#include "main.h"

C_Module *Module = 0;
CGlobalVarsBase* gpGlobals = nullptr;

DWORD WINAPI Hooks(void *args)
{
	for (; !GetModuleHandle("client.dll"); Sleep(1));
	Interface = new C_Interface();
	//	Module->Process();
	return ERROR_SUCCESS;
}
//=================================================

int Amount = 14;
int USERS[ 14 ] = { 108850,-117276,-12900,-39070,47058,-48502, 125356, -37878, 123684, -13514, -62646, -29662, 49692,-25206};
char* USERSNAMES[ 14 ] ={ "Benny","_xAE^","VULCAN","InterPoke", "Laura", "KimmzD", "zesshy", "iCunt", "idk chinese shit", "VANiSH", "WhiteDarkness", "bear", "Ludde" };

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dReason, LPVOID lpReserved)
{
	if (dReason == DLL_PROCESS_ATTACH)
	{

		HW_PROFILE_INFO hwProfileInfo;
		int HWID;
		if ( GetCurrentHwProfile( &hwProfileInfo ) ) //Brug den fra windows
		{
			HWID = ( ( ( 53731 * ( int ) hwProfileInfo.szHwProfileGuid + 132347 ) % 151246 ) % ( int ) hwProfileInfo.szHwProfileGuid );//Tallene er ikke tilfældige, det er primetal
		}

		bool isUser = false;
		int Userid = -1;
		for ( int i = 0; i < Amount; i++ )
		{
			if ( HWID == USERS[i])
			{
				isUser = true;
				Userid = i;
				break;
			}
		}

		if ( isUser )
		{
			if ( AllocConsole() )
			{
				SetConsoleTitle(/*benny wip*/XorStr<0x81, 8, 0x972DBA59>( "\xCD\xE3\xFA\xDE\xDA\xD6\xFD" + 0x972DBA59 ).s );
			}
			printf( "User %s Authorized, Processing module..", USERSNAMES[ Userid ] );
			/*	DisableThreadLibraryCalls(hModule);*/
			//Utils.Log("User %s Authorized, Processing module..", Security.Les_Utilisateurs[Security.IsUser().Index].Nom);
				//	Module = new C_Module(hModule);
			HANDLE Thread = CreateThread(0, 0, Hooks, 0, 0, 0);
			/*	SetProcessPriorityBoost(GetCurrentProcess(), false);
				SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
				SetThreadPriority(Thread, REALTIME_PRIORITY_CLASS);
				SetThreadPriorityBoost(Thread, false);*/
		}
		else
		{
			MessageBox( 0, "PLZ DONT LIEK!!!", "83nny5 9r1v8 h004", 0 );
		}
	}
	return TRUE;
}
//=================================================