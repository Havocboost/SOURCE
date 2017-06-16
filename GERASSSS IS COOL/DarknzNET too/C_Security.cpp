#include "main.h"
C_Security Security;
//=================================================
void C_Security::GetMACAddress(std::string &sOut)
{
	IP_ADAPTER_INFO AdapterInfo[16];
	DWORD dwBufLen = sizeof(AdapterInfo);
	char *pszMacAddy = new char[256];
	GetAdaptersInfo(AdapterInfo, &dwBufLen);
	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;

	do
	{
		sprintf(pszMacAddy, /*%02X:%02X:%02X:%02X:%02X:%02X*/XorStr<0xCD, 30, 0x4BB1266F>("\xE8\xFE\xFD\x88\xEB\xF7\xE3\xE6\x8D\xEC\xF2\xE8\xEB\x82\xE1\xF9\xED\xEC\x87\xDA\xC4\xD2\xD1\xBC\xDF\xC3\xD7\xDA\xB1" + 0x4BB1266F).s,
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

		sOut = pszMacAddy;
		delete[] pszMacAddy;
		return;

		pAdapterInfo = pAdapterInfo->Next;

	} while (pAdapterInfo);
}
//=================================================
std::string C_Security::GetHWID(void)
{
	std::string sMAC;
	char* buffer;
	GetMACAddress(sMAC);
	//MyLog(/*String %s*/XorStr<0x64, 10, 0x4EFF48BB>("\x37\x11\x14\x0E\x06\x0E\x4A\x4E\x1F" + 0x4EFF48BB).s, sMAC);
	getchar();
	return sMAC;
}
//=================================================
void C_Security::Fillusers(void)
{	
	Les_Utilisateurs[1].HWID = /*94:65:9C:C0:AF:A3*/XorStr<0x3F, 18, 0x53A54EBC>("\x06\x74\x7B\x74\x76\x7E\x7C\x05\x7D\x0B\x79\x70\x0A\x0A\x77\x0F\x7C" + 0x53A54EBC).s;
	Les_Utilisateurs[1].Nom = "Paradoxxx_";

	Les_Utilisateurs[0].HWID = /*00:FF:B1:FF:74:D6*/XorStr<0x08, 18, 0x06A0346B>("\x38\x39\x30\x4D\x4A\x37\x4C\x3E\x2A\x57\x54\x29\x23\x21\x2C\x53\x2E" + 0x06A0346B).s;
	Les_Utilisateurs[0].Nom = "Plague";
}
//=================================================
IS_USER C_Security::IsUser(void)
{
	IS_USER Is_User = { 0,0 };
	Fillusers();
	std::string user = GetHWID();
	for (int L_Index = 0; L_Index < Nombre_Users; L_Index++)
	{
		if (user == Les_Utilisateurs[L_Index].HWID)
		{
			Is_User.Verified = true;
			Is_User.Index = L_Index;
			break;
		}
		else
		{
			Is_User.Verified = false;
		}
	}
	return Is_User;
}