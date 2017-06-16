// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <SDKDDKVer.h>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
#include <list>
#include <limits>
#include <assert.h>
#include <cmath>
#include <Objbase.h>
#include <WinCrypt.h>
#include <algorithm>
#include "TlHelp32.h"
#include "Synchapi.h"
#include <thread> 
#include "IPTypes.h"
#include <Iphlpapi.h>
#include <Mmsystem.h>

#include "sdk.h"
#include "Detours.h"
#include "C_Vmt.h"
#include "C_Security.h"
#include "C_Module.h"
#include "C_Memory.h"
#include "C_Netvars.h"
#include "C_Interface.h"
#include "C_MyEntity.h"
#include "C_MyWeapon.h"
#include "C_Draw.h"
#include "C_Prediction.h"
#include "C_MyWeaponInfo.h"
#include "C_Aimbot.h"
#include "C_MyMaths.h"
#include "C_AntiAim.h"
#include "C_Data.h"
#include "C_Cvars.h"
#include "C_Menu.h"
#include "C_Mouse.h"
#include "C_Utils.h"
#include "C_GameEvent.h"
#include "C_Hitmarker.h"
#include "C_AutoWall.h"

extern int shot_count;
//=========
#undef KEY
#undef BUFLEN
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private:
	XorStr();
public:
	char s[BUFLEN];

	XorStr(const char* xs);
#ifndef DEBUG_OPTION
	~XorStr() { for (int i = 0; i < BUFLEN; i++)s[i] = 0; } // clear string from stack
#endif
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for (; i < (BUFLEN - 1); i++) {
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}


template< typename Function > Function CallVirtual(PVOID Base, DWORD Index)
{
	PDWORD* VTablePointer = (PDWORD*)Base;
	PDWORD VTableFunctionBase = *VTablePointer;
	DWORD dwAddress = VTableFunctionBase[Index];

	return (Function)(dwAddress);
}
//========
struct PlayerList_t
{
	float flWhitelist;
	int iAAFixX;
	int iAAFixY;
	float flBodyaim;
	bool bPlayerListActive;

} extern PlayerList[64];

#pragma once

typedef struct _UNICODE_STRING
{
	USHORT                                  Length;
	USHORT                                  MaximumLength;
	PWSTR                                   Buffer;
} UNICODE_STRING, *PUNICODE_STRING;


typedef struct _PEB_LDR_DATA
{
	ULONG									Length;
	BOOLEAN									Initialized;
	PVOID									SsHandle;
	LIST_ENTRY								InLoadOrderModuleList;
	LIST_ENTRY								InMemoryOrderModuleList;
	LIST_ENTRY								InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;


typedef struct _LDR_MODULE
{
	LIST_ENTRY								InLoadOrderModuleList;
	LIST_ENTRY								InMemoryOrderModuleList;
	LIST_ENTRY								InInitializationOrderModuleList;
	PVOID									Baseintess;
	PVOID									EntryPoint;
	ULONG									SizeOfImage;
	UNICODE_STRING							FullDllName;
	UNICODE_STRING							BaseDllName;
	ULONG									Flags;
	SHORT									LoadCount;
	SHORT									TlsIndex;
	LIST_ENTRY								HashTableEntry;
	ULONG									TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;


// credits to lilxam
typedef struct _MMSECTION_FLAGS {
	/*0x000*/     UINT32       BeingDeleted : 1;
	/*0x000*/     UINT32       BeingCreated : 1;
	/*0x000*/     UINT32       BeingPurged : 1;
	/*0x000*/     UINT32       NoModifiedWriting : 1;
	/*0x000*/     UINT32       FailAllIo : 1;
	/*0x000*/     UINT32       Image : 1;
	/*0x000*/     UINT32       Based : 1;
	/*0x000*/     UINT32       File : 1;
	/*0x000*/     UINT32       Networked : 1;
	/*0x000*/     UINT32       NoCache : 1;
	/*0x000*/     UINT32       PhysicalMemory : 1;
	/*0x000*/     UINT32       CopyOnWrite : 1;
	/*0x000*/     UINT32       Reserve : 1;
	/*0x000*/     UINT32       Commit : 1;
	/*0x000*/     UINT32       FloppyMedia : 1;
	/*0x000*/     UINT32       WasPurged : 1;
	/*0x000*/     UINT32       UserReference : 1;
	/*0x000*/     UINT32       GlobalMemory : 1;
	/*0x000*/     UINT32       DeleteOnClose : 1;
	/*0x000*/     UINT32       FilePointerNull : 1;
	/*0x000*/     UINT32       DebugSymbolsLoaded : 1;
	/*0x000*/     UINT32       SetMappedFileIoComplete : 1;
	/*0x000*/     UINT32       CollidedFlush : 1;
	/*0x000*/     UINT32       NoChange : 1;
	/*0x000*/     UINT32       HadUserReference : 1;
	/*0x000*/     UINT32       ImageMappedInSystemSpace : 1;
	/*0x000*/     UINT32       UserWritable : 1;
	/*0x000*/     UINT32       Accessed : 1;
	/*0x000*/     UINT32       GlobalOnlyPerSession : 1;
	/*0x000*/     UINT32       Rom : 1;
	/*0x000*/     UINT32       filler : 2;
} MMSECTION_FLAGS, *PMMSECTION_FLAGS;


typedef struct _MMVAD_FLAGS {
	/*0x000*/     ULONG32      CommitCharge : 19;
	/*0x000*/     ULONG32      PhysicalMapping : 1;
	/*0x000*/     ULONG32      ImageMap : 1;
	/*0x000*/     ULONG32      UserPhysicalPages : 1;
	/*0x000*/     ULONG32      NoChange : 1;
	/*0x000*/     ULONG32      WriteWatch : 1;
	/*0x000*/     ULONG32      Protection : 5;
	/*0x000*/     ULONG32      LargePages : 1;
	/*0x000*/     ULONG32      MemCommit : 1;
	/*0x000*/     ULONG32      PrivateMemory : 1;
} MMVAD_FLAGS, *PMMVAD_FLAGS;

typedef struct _MMVAD_FLAGS2 {
	/*0x000*/     UINT32       FileOffset : 24;
	/*0x000*/     UINT32       SecNoChange : 1;
	/*0x000*/     UINT32       OneSecured : 1;
	/*0x000*/     UINT32       MultipleSecured : 1;
	/*0x000*/     UINT32       ReadOnly : 1;
	/*0x000*/     UINT32       LongVad : 1;
	/*0x000*/     UINT32       ExtendableFile : 1;
	/*0x000*/     UINT32       Inherit : 1;
	/*0x000*/     UINT32       CopyOnWrite : 1;
} MMVAD_FLAGS2, *PMMVAD_FLAGS2;

typedef struct CONTROL_AREA {
	/*0x000*/     struct _SEGMENT *Segment;
	/*0x004*/     struct _LIST_ENTRY DereferenceList;
	/*0x00C*/     ULONG32      NumberOfSectionReferences;
	/*0x010*/     ULONG32      NumberOfPfnReferences;
	/*0x014*/     ULONG32      NumberOfMappedViews;
	/*0x018*/     UINT16       NumberOfSubsections;
	/*0x01A*/     UINT16       FlushInProgressCount;
	/*0x01C*/     ULONG32      NumberOfUserReferences;
	union
	{
		/*0x020*/         ULONG32      LongFlags;
		/*0x020*/         struct _MMSECTION_FLAGS Flags;
	}u;
	/*0x024*/     struct _FILE_OBJECT *FilePointer;
	/*0x028*/     struct _EVENT_COUNTER *WaitingForDeletion;
	/*0x02C*/     UINT16       ModifiedWriteCount;
	/*0x02E*/     UINT16       NumberOfSystemCacheViews;
} CONTROL_AREA, *PCONTROL_AREA;


typedef struct MMVAD {
	/*0x000*/     ULONG32      StartingVpn;
	/*0x004*/     ULONG32      EndingVpn;
	/*0x008*/     struct _MMVAD *Parent;
	/*0x00C*/     struct _MMVAD *LeftChild;
	/*0x010*/     struct _MMVAD *RightChild;
	union
	{
		/*0x014*/         ULONG32      LongFlags;
		/*0x014*/         struct _MMVAD_FLAGS VadFlags;
	}u;
	/*0x018*/     struct _CONTROL_AREA *ControlArea;
	/*0x01C*/     struct _MMPTE *FirstPrototypePte;
	/*0x020*/     struct _MMPTE *LastContiguousPte;
	union
	{
		/*0x024*/         ULONG32      LongFlags2;
		/*0x024*/         struct _MMVAD_FLAGS2 VadFlags2;
	}u2;
} MMVAD, *PMMVAD;