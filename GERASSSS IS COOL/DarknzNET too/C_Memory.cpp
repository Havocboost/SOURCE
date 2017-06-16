#include "main.h"

namespace Memory
{
	namespace Sigscan_offsets
	{
		DWORD
			RemoveFromInterpolationList,
			MoveToLastReceivedPosition,
			GetCSWpnData,
			IsBreakableEntity,
			LoadFromBuffer,
			MoveHelper,
			Globals;
	};
}
//=================================================
DWORD Memory::FindPattern(HMODULE module, const std::string &signature)
{
	MODULEINFO info;

	if (!GetModuleInformation(GetCurrentProcess(), module, &info, sizeof(info)))
	{
		//Utils.Log( "GetModuleInformation failed on module: [%X]", (DWORD)module );
		return 0;
	}


	char *end = ((char*)(module)+info.SizeOfImage);

	for (char *current = (char*)(module); current <= end; ++current)
	{
		if (Check(current, signature))
		{
			return (DWORD)current;
		}
	}

	return 0;
}
//=================================================
bool Memory::Check(char *address, const std::string &signature)
{
	for (std::string::const_iterator it = signature.begin(); it != signature.end(); ++it)
	{
		if (*it == '?')
		{
			address++;
			continue;
		}

		if (*address != *it)
		{
			return false;
		}

		address++;
	}

	return true;
}
//=================================================
__declspec(naked, noinline) void *Memory::GetExtendedBasePointer(void)
{
	_asm
	{
		MOV EAX, EBP
		RETN
	}
}
//=================================================
__declspec(naked, noinline) void *Memory::GetExtendedSourceIndex(void)
{
	_asm
	{
		MOV EAX, ESI
		RETN
	}
}
//=================================================
__declspec(naked, noinline) void *Memory::GetExtendedDataRegister(void)
{
	_asm
	{
		MOV EAX, EDX
		RETN
	}
}
//=================================================
__declspec(naked, noinline) void *Memory::GetExtendedBaseRegister(void)
{
	_asm
	{
		MOV EAX, EBX
		RETN
	}
}
//=================================================
__declspec(naked, noinline) void *Memory::GetExtendedDestinationIndex(void)
{
	_asm
	{
		MOV EAX, EDI
		RETN
	}
}
//=================================================
__declspec(naked, noinline) void *Memory::GetProcessModuleInfo(void)
{
	_asm
	{
		MOV EAX, FS:[0x18] // TEB
		MOV EAX, [EAX + 0x30] // PEB
			MOV EAX, [EAX + 0xC] // PROCESS_MODULE_INFO
			RETN
	}
}
//=================================================
void Memory::Zero(void *address, int size)
{
	DWORD protection;

	if (VirtualProtect(address, size, PAGE_READWRITE, &protection))
	{
		SecureZeroMemory(address, size);// fill Zeros on paged memory area
		VirtualProtect(address, size, protection, 0);
		FlushInstructionCache(GetCurrentProcess(), address, size);
	}
}
//=================================================
void Memory::Fill_Sigscans()
{
	Utils.Log("Main Injection Done, Looking for Memory Patterns...");
	Utils.Log("//=====================//");


	Memory::Sigscan_offsets::RemoveFromInterpolationList = Memory::FindPattern(hmClient, "\x74\x25\x56\x90\x0F\xB7\xC8\xA1????\x0F\xB7\x74\xC8\x06\x8B\x0C\xC8\x8B\x41\x08\x83\xC1\x08\xFF\x50?") - 0xC;
	Utils.Log("RemoveFromInterpolationList 0x%X", Memory::Sigscan_offsets::RemoveFromInterpolationList - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::RemoveFromInterpolationList)
		Utils.Log("RemoveFromInterpolationList signature failed.");

	Memory::Sigscan_offsets::MoveToLastReceivedPosition = Memory::FindPattern(hmClient, "\x55\x8B\xEC\x80\x7D\x08?\x56\x8B\xF1\x75\x0D\x80\xBE\x75\x02???");
	Utils.Log("MoveToLastReceivedPosition 0x%X", Memory::Sigscan_offsets::MoveToLastReceivedPosition - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::MoveToLastReceivedPosition)
		Utils.Log("MoveToLastReceivedPosition signature failed.");


	//Memory::Sigscan_offsets::GetCSWpnData = Memory::FindPattern(hmClient, "\x55\x8B\xEC\x81\xEC????\xB8????\x57\x8B\xF9\x66\x39\x87\x60\x32??\x0F\x85????\x8B\x07\xFF\x90????");
	//Utils.Log("GetCSWpndata 0x%X", Memory::Sigscan_offsets::GetCSWpnData - (DWORD)hmClient);
	//if (!Memory::Sigscan_offsets::GetCSWpnData)
	//	Utils.Log("GetCSWpnData signature failed.");


	Memory::Sigscan_offsets::IsBreakableEntity = Memory::FindPattern(hmClient, "\x55\x8B\xEC\x51\x56\x8B\xF1\x85\xF6\x74\x68\x83\xBE\xFC????");
	Utils.Log("IsBreakableEntity 0x%X", Memory::Sigscan_offsets::IsBreakableEntity - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::IsBreakableEntity)
		Utils.Log("IsBrekableEntity signature failed.");

	Memory::Sigscan_offsets::LoadFromBuffer = Memory::FindPattern(hmClient, "\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x34\x53\x8B\x5D\x0C\x89");
	Utils.Log("LoadFromBuffer 0x%X", Memory::Sigscan_offsets::LoadFromBuffer - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::LoadFromBuffer)
		Utils.Log("LoadFromBuffer signature failed.");


	Memory::Sigscan_offsets::MoveHelper = **(PDWORD*)(Memory::FindPattern(hmClient, "\xFF\x35????\x8D\x86") + 2);
	Utils.Log("MoveHelper 0x%X", Memory::Sigscan_offsets::MoveHelper - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::MoveHelper)
		Utils.Log("MoveHelper signature failed.");


	Memory::Sigscan_offsets::Globals = *(DWORD*)(Memory::FindPattern(hmClient, "\xA1????\x89\x5E\x04") + 1);
	Utils.Log("Globals 0x%X", Memory::Sigscan_offsets::Globals - (DWORD)hmClient);
	if (!Memory::Sigscan_offsets::Globals)
		Utils.Log("Globals signature failed.");


	//Utils.Log("//=====================//");
	Utils.Log("All the Memory Patterns have been found, Enjoy.");
	Utils.Log("//=====================//");

}