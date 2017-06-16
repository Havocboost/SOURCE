#include "main.h"


C_Interface *Interface = 0;
PlayerList_t PlayerList[ 64 ];
HMODULE hmClient;
HMODULE hmEngine;
void __stdcall CreateMove( void *thisptr, CUserCmd* pCmd, bool& bSendPacket );

bool __fastcall Hook_ModeCreateMove( CInput*thisptr, void* edx, float a1, CUserCmd* pCmd )
{
	if ( !pCmd->command_number )
		return false;

	void* rEBP;
	__asm mov rEBP, ebp;

	bool* b_send = ( bool* ) ( *( bool** ) ( rEBP ) -0x1C );
	bool send = *b_send;

	CreateMove( thisptr, pCmd, send );

	*b_send = send;

	return false;
}
CVMT *C_Interface::Client( void *instance, bool shouldHook )
{
	static CVMT client( instance, shouldHook );


	if ( instance && shouldHook )
	{
		//	client.HookMethod(&Hook_CreateMove, INDEX_CREATEMOVE);
		client.HookMethod( &FrameStageNotify, INDEX_FRAMESTAGENOTIFY );
		//client.HookMethod( &IN_KeyEvent, INDEX_IN_KEYEVENT );
	}

	return &client;
}
CVMT *C_Interface::ClientMode( void *instance, bool shouldHook )
{
	static CVMT clientmode( instance, shouldHook );


	if ( instance && shouldHook )
	{
		clientmode.HookMethod( &Hook_ModeCreateMove, 24 );
	}

	return &clientmode;
}
//=================================================
CVMT *C_Interface::EntityList( void *instance, bool shouldHook )
{
	static CVMT entityList( instance, shouldHook );
	return &entityList;
}
//=================================================
CVMT *C_Interface::MoveHelper( void *instance, bool shouldHook )
{
	static CVMT moveHelper( instance, shouldHook );
	return &moveHelper;
}
//=================================================
CVMT *C_Interface::Prediction( void *instance, bool shouldHook )
{
	static CVMT prediction( instance, shouldHook );


	if ( instance && shouldHook )
	{
		//prediction.HookMethod(&InPrediction, INDEX_INPREDICTION);
		prediction.HookMethod( &RunCommand, INDEX_RUNCOMMAND );
		//prediction.HookMethod( &FinishMove, INDEX_FINISHMOVE ); 
	}

	return &prediction;
}
//=================================================
CVMT *C_Interface::GameMovement( void *instance, bool shouldHook )
{
	static CVMT gameMovement( instance, shouldHook );
	return &gameMovement;
}
//=================================================
CVMT *C_Interface::Engine( void *instance, bool shouldHook )
{
	static CVMT engine( instance, shouldHook );
	engine.HookMethod( &DrawPortals, INDEX_DRAWPORTALS );
	return &engine;
}
//=================================================
CVMT *C_Interface::Input( void *instance, bool shouldHook )
{
	static CVMT input( instance, shouldHook );


	if ( instance && shouldHook )
	{
		input.HookMethod( &GetUserCmd, INDEX_GETUSERCMD );
		//	input.HookMethod(&WriteUsercmdDeltaToBuffer, INDEX_WRITEUSERCMDDELTATOBUFFER);
	}

	return &input;
}
//=================================================
CVMT *C_Interface::Cvar( void *instance, bool shouldHook )
{
	static CVMT cvar( instance, shouldHook );
	return &cvar;
}
//=================================================
CVMT *C_Interface::ModelInfo( void *instance, bool shouldHook )
{
	static CVMT modelInfo( instance, shouldHook );
	return &modelInfo;
}
//=================================================
CVMT *C_Interface::EngineTrace( void *instance, bool shouldHook )
{
	static CVMT engineTrace( instance, shouldHook );
	return &engineTrace;
}
//=================================================
CVMT *C_Interface::PhysicsSurfaceProps( void *instance, bool shouldHook )
{
	static CVMT physicsSurfaceProps( instance, shouldHook );
	return &physicsSurfaceProps;
}
//=================================================
CVMT *C_Interface::Panel( void *instance, bool shouldHook )
{
	static CVMT panel( instance, shouldHook );

	if ( instance && shouldHook )
	{
		panel.HookMethod( &PaintTraverse, INDEX_PAINTTRAVERSE );
	}

	return &panel;
}
//=================================================

CVMT *C_Interface::Surface( void *instance, bool shouldHook )
{
	static CVMT surface( instance, shouldHook );
	return &surface;
}
//=================================================
CVMT *C_Interface::DebugOverlay( void *instance, bool shouldHook )
{
	static CVMT debugOverlay( instance, shouldHook );
	return &debugOverlay;
}
//=================================================
CVMT *C_Interface::RenderView( void *instance, bool shouldHook )
{
	static CVMT renderView( instance, shouldHook );
	return &renderView;
}


//=================================================
CVMT *C_Interface::MaterialSystem( void *instance, bool shouldHook )
{
	static CVMT materialSystem( instance, shouldHook );


	if ( instance && shouldHook )
	{
		materialSystem.HookMethod( &FindMaterial, INDEX_FINDMATERIAL );
	}

	return &materialSystem;
}
//=================================================
CVMT *C_Interface::ModelRender( void *instance, bool shouldHook )
{
	static CVMT modelRender( instance, shouldHook );


	if ( instance && shouldHook )
	{
		modelRender.HookMethod( &DrawModelExecute, INDEX_DRAWMODELEXECUTE );
	}

	return &modelRender;
}
//=================================================
CVMT *C_Interface::GameEventManager( void *instance, bool shouldHook )
{
	static CVMT gameEventManager( instance, shouldHook );

	if ( instance && shouldHook )
	{
		gameEventManager.HookMethod( &FireEventClientSide, INDEX_FIREGAMEEVENTCLIENTSIDE );
	}

	return &gameEventManager;
}
//=================================================
float NewClientInterpolation()
{
	return Globals()->interval_per_tick;
}
//=================================================
float __fastcall NewClientStateInterpolation( void*thisptr, int edx )
{
	return -FLT_MAX;
}//=================================================

float __fastcall NewCL_INTERP( void*thisptr, int edx )
{
	return -FLT_MAX;
}
//=================================================
float __fastcall new_Entity_Interpolation( void*thisptr, int edx, int flags )
{
	return Globals()->interval_per_tick;
}
//=================================================
DWORD Old;
void InterpolateServerEntities()
{
	for ( int i = 64; i >= 1; i-- )
	{
		C_MyEntity *Player = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( i );

		C_BasePlayer *BasePlayer = ( C_BasePlayer* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( i );

		if ( Player == nullptr ) continue;

		if ( Player->GetIndex() == Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() ) continue;

		Player->MoveToLastReceivedPosition( true );//?

		Player->RemoveFromInterpolationList();
	}

	( ( void( *)( ) )( Old ) )( );
}
//=================================================
DWORD Old2;
void __fastcall new_Entity_AddVar( void*thisptr, int edx, void *data, void *watcher, int type, bool bSetup )
{
	type &= ~INTERPOLATE_OMIT_UPDATE_LAST_NETWORKED;

	//type |= INTERPOLATE_LINEAR_ONLY;

	( ( void( __thiscall* )( void*, void*, void*, int, bool ) )( Old2 ) )( thisptr, data, watcher, type, bSetup );
}

//=================================================
CInput* g_pInput = NULL;
C_Interface::C_Interface( void )
{
	m_vecEyeAngles = vec3_angle;
	hmClient = GetModuleHandle( "client.dll" );

	hmEngine = GetModuleHandle( "engine.dll" );


	Memory::Fill_Sigscans();

	CreateInterfaceFn clientFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "client.dll" ), "CreateInterface" ) );
	if ( clientFactory )
	{
		void *client = 0;

		if ( FindInterface( &clientFactory, "VClient", &client ) )
		{
			Client( client, true );
		}
		else
		{
			Utils.Log( "VClient not found" );
		}

		void *clientmode = **( void*** ) ( ( ( *( DWORD** ) ( client ) )[ 10 ] ) + 0x5 );

		if ( clientmode )
		{
			ClientMode( clientmode, true );
		}
		else
		{
			Utils.Log( "client mode not found" );
		}


		void *input = *( void** ) ( Client()->GetOriginalMethod<DWORD>( 21 ) + 0x62 );//28

		g_pInput = ( CInput* ) input;

		if ( input )
		{
			Input( input, true );
		}
		else
		{
			Utils.Log( "CInput not found" );
		}


		void *entityList = 0;
		if ( FindInterface( &clientFactory, "VClientEntityList", &entityList ) )
		{
			EntityList( entityList );
		}
		else
		{
			Utils.Log( "VClientEntityList not found" );
		}


		void *prediction = 0;
		if ( FindInterface( &clientFactory, "VClientPrediction", &prediction ) )
		{
			Prediction( prediction, true );
		}
		else
		{
			Utils.Log( "VClientPrediction not found" );
		}


		void *gameMovement = 0;
		if ( FindInterface( &clientFactory, "GameMovement", &gameMovement ) )
		{
			GameMovement( gameMovement );
		}
		else
		{
			Utils.Log( "GameMovement not found" );
		}

		void *moveHelper = ( void* ) ( ( DWORD ) Memory::Sigscan_offsets::MoveHelper );
		if ( moveHelper )
		{
			MoveHelper( moveHelper );
		}
		else
		{
			Utils.Log( "MoveHelper not found" );
		}
	}





	CreateInterfaceFn engineFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "engine.dll" ), "CreateInterface" ) );
	CreateInterfaceFn vguiFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "vgui2.dll" ), "CreateInterface" ) );
	CreateInterfaceFn vstdlibfactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "vstdlib.dll" ), "CreateInterface" ) );
	CreateInterfaceFn vphysicsFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "vphysics.dll" ), "CreateInterface" ) );
	CreateInterfaceFn vguimatsurfaceFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "vguimatsurface.dll" ), "CreateInterface" ) );
	CreateInterfaceFn materialsystemFactory = ( CreateInterfaceFn ) ( GetProcAddress( GetModuleHandle( "materialsystem.dll" ), "CreateInterface" ) );


	if ( engineFactory )
	{
		void *engine = 0;
		if ( FindInterface( &engineFactory, "VEngineClient", &engine ) )
		{
			Engine( engine, false );
		}
		else
		{
			Utils.Log( "VEngineClient not found" );
		}
	}

	if ( vstdlibfactory )
	{
		void *cvar = 0;
		if ( FindInterface( &vstdlibfactory, "VEngineCvar", &cvar ) )
		{
			Cvar( cvar );
		}
		else
		{
			Utils.Log( "VEngineCvar not found" );
		}
	}

	if ( engineFactory )
	{
		void *modelInfo = 0;
		if ( FindInterface( &engineFactory, "VModelInfoClient", &modelInfo ) )
		{
			ModelInfo( modelInfo );
		}
		else
		{
			Utils.Log( "VModelInfoClient not found" );
		}
	}

	if ( engineFactory )
	{

		void *engineTrace = 0;
		if ( FindInterface( &engineFactory, "EngineTraceClient", &engineTrace ) )
		{
			EngineTrace( engineTrace );
		}
		else
		{
			Utils.Log( "EngineTraceClient not found" );
		}
	}

	if ( vphysicsFactory )
	{
		void *physicsSurfaceProps = 0;
		if ( FindInterface( &vphysicsFactory, "VPhysicsSurfaceProps", &physicsSurfaceProps ) )
		{
			PhysicsSurfaceProps( physicsSurfaceProps );
		}
		else
		{
			Utils.Log( "VPhysicsSurfaceProps not found" );
		}
	}

	if ( vguiFactory )
	{
		void *panel = 0;
		if ( FindInterface( &vguiFactory, "VGUI_Panel", &panel ) )
		{
			Panel( panel, true );
		}
		else
		{
			Utils.Log( "VGUI_Panel not found" );
		}
	}

	if ( vguimatsurfaceFactory )
	{
		void *surface = 0;
		if ( FindInterface( &vguimatsurfaceFactory, "VGUI_Surface", &surface ) )
		{
			Surface( surface );
		}
		else
		{
			Utils.Log( "VGUI_Surface not found" );
		}
	}

	if ( engineFactory )
	{
		void *debugOverlay = 0;
		if ( FindInterface( &engineFactory, "VDebugOverlay", &debugOverlay ) )
		{
			DebugOverlay( debugOverlay );
		}
		else
		{
			Utils.Log( "VDebugOverlay not found" );
		}
	}

	if ( engineFactory )
	{
		void *renderView = 0;
		if ( FindInterface( &engineFactory, "VEngineRenderView", &renderView ) )
		{
			RenderView( renderView );
		}
		else
		{
			Utils.Log( "VEngineRenderView not found" );
		}
	}

	if ( materialsystemFactory )
	{
		void *materialSystem = 0;
		if ( FindInterface( &materialsystemFactory, "VMaterialSystem", &materialSystem ) )
		{
			MaterialSystem( materialSystem, false );
		}
		else
		{
			Utils.Log( "VMaterialSystem not found" );
		}
	}

	if ( engineFactory )
	{
		void *modelRender = 0;
		if ( FindInterface( &engineFactory, "VEngineModel", &modelRender ) )
		{
			ModelRender( modelRender, true );
		}
		else
		{
			Utils.Log( "VEngineModel not found" );
		}
	}

	if ( engineFactory )
	{
		void *gameEventManager = engineFactory( "GAMEEVENTSMANAGER002", 0 );
		if ( gameEventManager )
		{
			GameEventManager( gameEventManager, true );
		}
		else
		{
			Utils.Log( "GAMEEVENTSMANAGER not found" );
		}
	}

	Netvars = new C_Netvars();

	Netvars->HookProp( "DT_CSPlayer", "m_angEyeAngles[0]", CSPlayer_EyeAnglesX );
	Netvars->HookProp( "DT_CSPlayer", "m_angEyeAngles[1]", CSPlayer_EyeAnglesY );
	Netvars->HookProp( "DT_BasePlayer", "m_aimPunchAngle", BasePlayer_PunchAngle );
	Netvars->HookProp( "DT_BasePlayer", "m_vecViewOffset[2]", BasePlayer_ViewOffsetZ );
	Netvars->HookProp( "DT_BasePlayer", "m_vecBaseVelocity", BasePlayer_BaseVelocity );
	Netvars->HookProp( "DT_BasePlayer", "m_flFallVelocity", BasePlayer_FallVelocity );
	//Netvars->HookProp("DT_CSPlayer", "m_flStamina", CSPlayer_Stamina);
	Netvars->HookProp( "DT_BasePlayer", "m_nTickBase", BasePlayer_TickBase );
	Netvars->HookProp( "DT_CSPlayer", "m_flFlashDuration", NULL_FLOAT );
	Netvars->HookProp( "DT_ParticleSmokeGrenade", "m_CurrentStage", NULL_FLOAT );




	void *thisptr = Interface->Surface()->thisptr();

	fontMenu = Interface->Surface()->GetOriginalMethod<CreateFont_t>( INDEX_CREATEFONT )( thisptr );
	Interface->Surface()->GetOriginalMethod<SetFontGlyphSet_t>( INDEX_SETFONTGLYPHSET )( thisptr, fontMenu, "Courier New", 14, 450, 0, 0, FONTFLAG_OUTLINE, 0, 0 );

	MenuBoxesTitle = Interface->Surface()->GetOriginalMethod<CreateFont_t>( INDEX_CREATEFONT )( thisptr );
	Interface->Surface()->GetOriginalMethod<SetFontGlyphSet_t>( INDEX_SETFONTGLYPHSET )( thisptr, MenuBoxesTitle, "Tahoma", 12, 450, 0, 0, FONTFLAG_NONE, 0, 0 );

	for ( int i = 0; i < 6; ++i )
	{
		Draw.SetFont( &Draw.m_distanceFonts[ i ], "Tahoma", ( 14 - i ), FONTFLAG_DROPSHADOW );
	}

	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_extrapolate" )->SetValue( 0 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_extrapolate_amount" )->SetValue( 0 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_interp" )->SetValue( 0 );
	Interface->Cvar()->GetVTable<ICvar>()->FindVar( "cl_interpolate" )->SetValue( 0 );

	Draw.m_font = Draw.m_distanceFonts[ 0 ];

}
//=================================================
// bruteforces the version of the interface
bool C_Interface::FindInterface( CreateInterfaceFn *factory, const std::string interfaceName, void** interfaceInstance )
{
	for ( int version = 0; version < 0xFF; ++version )
	{
		std::ostringstream tmp;
		tmp << interfaceName.c_str() << std::setfill( '0' ) << std::setw( 3 ) << version;

		*interfaceInstance = ( *factory )( tmp.str().c_str(), 0 );

		if ( *interfaceInstance )
		{
			return true;
		}
	}

	return false;
}

//CGlobalVarsBase *Globals;
//=================================================
/*__forceinline CGlobalVarsBase *Globals(void)
{
IBaseClientDLL *Client = Interface->Client()->GetVTable<IBaseClientDLL>();
static CGlobalVarsBase *globals;
PDWORD pdwClient = (PDWORD)*(PDWORD)Client;
DWORD dwInitAddr = (DWORD)(pdwClient[0]);
for (DWORD dwIter = 0; dwIter <= 0xFF; dwIter++)
{
if (*(PBYTE)(dwInitAddr + dwIter) == 0xA3)
{
globals = (CGlobalVarsBase*)*(PDWORD)*(PDWORD)(dwInitAddr + dwIter + 1);
if (globals)
{
break;
}
}
}

return globals;
}*/
CGlobalVarsBase *Globals( void )
{
	static CGlobalVarsBase *globals = *( CGlobalVarsBase** ) ( ( DWORD ) Memory::Sigscan_offsets::Globals );

	if ( !globals )
	{
		Utils.Log( "CGlobalVarsBase not found" );
	}


	return globals;
}
//=================================================
IGameResources *GameResources( void )
{
	typedef IGameResources *( *GetGameResources_t )( void );
	static GetGameResources_t GetGameResources = ( GetGameResources_t ) Memory::FindPattern( GetModuleHandle( "client.dll" ), "\xA1????\x85\xC0\x74\x06\x05" );

	if ( !GetGameResources )
	{
		Utils.Log( "GetGameResources not found" );
	}


	return GetGameResources();
}

