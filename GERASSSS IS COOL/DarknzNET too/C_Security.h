#pragma once
#include "main.h"

typedef struct
{
	std::string HWID;
	const char* Nom;

}T_USERS;

typedef struct
{
	bool Verified;
	int Index;

}IS_USER;

#define Nombre_Users 2

class C_Security
{
public:
	void GetMACAddress(std::string &sOut);
	std::string GetHWID(void);
	void Fillusers(void);
	IS_USER IsUser(void);
	T_USERS Les_Utilisateurs[Nombre_Users];

};

extern C_Security Security;

