#pragma once
#include "main.h"
#include "usercmd.h"

class C_MyEntity;
class CVMT;

#define INDEX_WRITEUSERCMDDELTATOBUFFER 5
#define INDEX_GETUSERCMD 8
#define INDEX_DRAWSETCOLOR 15
#define INDEX_DRAWFILLEDRECT 16
#define INDEX_GLOBALVARS 13
#define INDEX_DRAWOUTLINEDRECT 18
#define INDEX_INPREDICTION 14
#define INDEX_DRAWLINE 19
#define INDEX_RUNCOMMAND 19
#define INDEX_SETUPMOVE 20
#define INDEX_FINISHMOVE 21
#define INDEX_PROCESSMOVEMENT 1
#define INDEX_DRAWSETTEXTFONT 23
#define INDEX_DRAWMODELEXECUTE 21
#define INDEX_DRAWSETTEXTCOLOR 25
#define INDEX_DRAWSETTEXTPOS 26
#define INDEX_SETVIEWANGLES 20
#define INDEX_IN_KEYEVENT 20
#define INDEX_CREATEMOVE 21
#define INDEX_DRAWPRINTTEXT 28
#define INDEX_FRAMESTAGENOTIFY 36
#define INDEX_GETNAME 36
#define INDEX_PAINTTRAVERSE 41
#define INDEX_CREATEFONT 71
#define INDEX_SETFONTGLYPHSET 72
#define INDEX_CREATEMATERIAL 83
#define INDEX_FINDMATERIAL 84
#define INDEX_GETTEXTSIZE 79
#define INDEX_DRAWPORTALS 76
#define INDEX_SETHOST 1
#define INDEX_FIREGAMEEVENTCLIENTSIDE 9
#define INDEX_PLAYSOUND 82

class CKeyValues;
typedef void(__thiscall *CreateMove_t) (void *thisptr, int sequence_number, float input_sample_frametime, bool active);
typedef void(__thiscall *FrameStageNotify_t)(void *thisptr, ClientFrameStage_t curStage);
typedef int(__thiscall *IN_KeyEvent_t)(void *thisptr, int eventcode, ButtonCode_t keynum, const char *pszCurrentBinding);
typedef void(__thiscall *PaintTraverse_t)(void *thisptr, unsigned int vguiPanel, bool forceRepaint, bool allowForce);
typedef bool(__thiscall *InPrediction_t)(void *thisptr);
typedef void(__thiscall *DrawModelExecute_t) (void *thisptr, void*context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
typedef void(__thiscall *RunCommand_t)(void *thisptr, C_MyEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper);
typedef IMaterial * (__thiscall *FindMaterial_t)(void *thisptr, const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
typedef IMaterial * (__thiscall *CreateMaterial_t)(void *thisptr, const char *pMaterialName, CKeyValues *pVMTKeyValues);
typedef void(__thiscall *SetViewAngles_t)(void *thisptr, QAngle& angle);
typedef DWORD(__thiscall *CreateFont_t)(void *thisptr);
typedef bool(__thiscall *SetFontGlyphSet_t)(void *thisptr, DWORD font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax);
typedef void(__thiscall *DrawSetTextColor_t)(void *thisptr, int r, int g, int b, int a);
typedef void(__thiscall *DrawSetTextFont_t)(void *thisptr, DWORD font);
typedef void(__thiscall *DrawSetTextPos_t)(void *thisptr, int x, int y);
typedef void(__thiscall *DrawPrintText_t)(void *thisptr, const wchar_t *text, int textLen, int drawType);
typedef void(__thiscall *DrawSetColor_t)(void *thisptr, int r, int g, int b, int a);
typedef void(__thiscall *DrawRect_t)(void *thisptr, int x0, int y0, int x1, int y1);
typedef void(__thiscall *DrawLine_t)(void *thisptr, int x0, int y0, int x1, int y1);
typedef void(__thiscall *GetTextSize_t)(void *thisptr, DWORD font, const wchar_t *text, int &wide, int &tall);
typedef const char *(__thiscall *GetName_t)(void *thisptr, uint vguiPanel);
typedef void(__thiscall *DrawPortals_t)(void* thisptr);
typedef void(__thiscall *SetupMove_t)(void *thisptr, C_MyEntity*, CUserCmd*, PVOID, PVOID);
typedef void(__thiscall *FinishMove_t)(void *thisptr, C_MyEntity*, CUserCmd*, PVOID);
typedef void(__thiscall *ProcessMovement_t)(void *thisptr, C_MyEntity*, PVOID);
typedef void(__thiscall *SetHost_t)(void *thisptr, C_MyEntity*);
typedef bool(__thiscall *FireGameEventClientSide_t)(void *thisptr, IGameEvent*);
typedef void(__thiscall* PlaySound_t)(void*thisptr, const char*);
extern HMODULE hmClient;
extern HMODULE hmEngine;
class CKeyValues
{
public:
	static void SetUseGrowableStringTable(bool bUseGrowableTable);

	CKeyValues(const char *setName)
	{
		Init();
		SetName(setName);
	}
	void SetName(const char *setName)
	{
		m_iKeyName = 2;
	}

	CKeyValues& operator=(CKeyValues& src);


public:
	CKeyValues(CKeyValues&);

	~CKeyValues();

	void Init()
	{
		m_iKeyName = -1;
		m_iDataType = 0;

		m_pSub = NULL;
		m_pPeer = NULL;
		m_pChain = NULL;

		m_sValue = NULL;
		m_wsValue = NULL;
		m_pValue = NULL;

		m_bHasEscapeSequences = false;

		memset(unused, 0, sizeof(unused));
	}

	int m_iKeyName;

	char *m_sValue;
	wchar_t *m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char	   m_iDataType;
	char	   m_bHasEscapeSequences;
	char	   m_bEvaluateConditionals;
	char	   unused[1];

	CKeyValues *m_pPeer;
	CKeyValues *m_pSub;
	CKeyValues *m_pChain;

public:

	bool LoadFromBuffer(CKeyValues *pThis, const char *pszFirst, const char *pszSecond, PVOID pSomething = 0, PVOID pAnother = 0, PVOID pLast = 0)
	{
		typedef bool(__thiscall *LoadFromBuffer_t)(CKeyValues*, const char*, const char*, PVOID, PVOID, PVOID);

		static LoadFromBuffer_t callLoadBuff = (LoadFromBuffer_t)Memory::Sigscan_offsets::LoadFromBuffer;


		return callLoadBuff(pThis, pszFirst, pszSecond, pSomething, pAnother, pLast);
	}
};
class C_Interface
{
public:

	C_Interface(void);
	//=====
	static void __fastcall DrawPortals(void *thisptr, int edx);
	static void __fastcall PaintTraverse(void *thisptr, int edx, vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce = true);
	static void __fastcall CreateMove(void *thisptr, int edx, int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket);
	static void __fastcall ModeCreateMove( void *thisptr, int edx, float a1, CUserCmd* pCmd );
	static bool __fastcall InPrediction(void *thisptr, int edx);
	static void __fastcall RunCommand(void *thisptr, int edx, C_MyEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper);
	static CUserCmd *__fastcall GetUserCmd(void *thisptr, int edx, int nSlot, int sequence_number);
	static bool __fastcall WriteUsercmdDeltaToBuffer(void *thisptr, int edx, int nSlot, bf_write *buf, int from, int to, bool isnewcommand);
	static IMaterial *__fastcall FindMaterial(void *thisptr, void *edx, const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
	static void __fastcall DrawModelExecute(void *thisptr, int edx, void*context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);

	static void __fastcall FrameStageNotify(void *thisptr, int edx, ClientFrameStage_t curStage);
	static void __fastcall FinishMove(void *thisptr, int edx, C_MyEntity *player, CUserCmd *ucmd, CMoveData *move);
	static void __fastcall SetViewAngles(void *thisptr, int edx, QAngle& angle);
	static bool __fastcall FireEventClientSide(void*thisptr, int edx, IGameEvent* pGameEvent);
	//=====
	CVMT *Client(void *thisInterface = 0, bool shouldHook = false);
	CVMT *ClientMode( void *thisInterface = 0, bool shouldHook = false );
	CVMT *EntityList(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Prediction(void *thisInterface = 0, bool shouldHook = false);
	CVMT *GameMovement(void *thisInterface = 0, bool shouldHook = false);
	CVMT *MoveHelper(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Engine(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Input(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Cvar(void *thisInterface = 0, bool shouldHook = false);
	CVMT *ModelInfo(void *thisInterface = 0, bool shouldHook = false);
	CVMT *EngineTrace(void *thisInterface = 0, bool shouldHook = false);
	CVMT *PhysicsSurfaceProps(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Panel(void *thisInterface = 0, bool shouldHook = false);
	CVMT *Surface(void *thisInterface = 0, bool shouldHook = false);
	CVMT *DebugOverlay(void *thisInterface = 0, bool shouldHook = false);
	CVMT *RenderView(void *thisInterface = 0, bool shouldHook = false);
	CVMT *MaterialSystem(void *thisInterface = 0, bool shouldHook = false);
	CVMT *ModelRender(void *thisInterface = 0, bool shouldHook = false);
	CVMT *GameEventManager(void *thisInterface = 0, bool shouldHook = false);


	//=====
	static void CSPlayer_EyeAnglesX(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void CSPlayer_EyeAnglesY(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void NULL_FLOAT(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void BasePlayer_PunchAngle(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void BasePlayer_ViewOffsetZ(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void BasePlayer_BaseVelocity(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void BasePlayer_FallVelocity(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void CSPlayer_Stamina(const CRecvProxyData *pData, void *pStruct, void *pOut);
	static void BasePlayer_TickBase(const CRecvProxyData *pData, void *pStruct, void *pOut);
	//=====
	bool FindInterface(CreateInterfaceFn *factory, const std::string interfaceName, void **interfaceInstance);

public:
	typedef struct CmdSendInfo_t
	{
		CUserCmd			m_LastCmd;
		bool				m_bSendPacket;
	}CmdSendInfo_t;

	CmdSendInfo_t			m_LastCmdInfo;
	QAngle					m_vecEyeAngles;
};

extern C_Interface *Interface;
extern __forceinline CGlobalVarsBase *Globals(void);