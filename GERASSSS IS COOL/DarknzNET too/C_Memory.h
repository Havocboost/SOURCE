#pragma once


#include "main.h"
#include "Psapi.h"

#pragma comment( lib, "psapi.lib" )


namespace Memory
{
	DWORD FindPattern(HMODULE module, const std::string &signature);
	bool Check(char *address, const std::string &signature);
	void *GetExtendedBasePointer(void);
	void *GetExtendedSourceIndex(void);
	void *GetExtendedDataRegister(void);
	void *GetExtendedBaseRegister(void);
	void *GetExtendedDestinationIndex(void);
	void *GetProcessModuleInfo(void);
	void Zero(void *address, int size);
	void Fill_Sigscans();

	namespace Sigscan_offsets
	{
		extern DWORD
			RemoveFromInterpolationList,
			MoveToLastReceivedPosition,
			GetCSWpnData,
			IsBreakableEntity,
			LoadFromBuffer,
			MoveHelper,
			Globals;
	};
};

