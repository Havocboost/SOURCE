#include "main.h"
#include "interface.h"
#include "C_Interface.h"
#include "C_Netvars.h"
typedef Vector Angle;
void __fastcall C_Interface::FrameStageNotify( void *thisptr, int edx, ClientFrameStage_t curStage )
{
	C_MyEntity *pLocal = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() );


	QAngle *PunchAngle, OldPunch;
	QAngle *vPunchAngle, vOldPunch;
	if ( curStage == FRAME_RENDER_START )
	{
		if ( pLocal )
		{
			//("\x55\x8B\xEC\x80\x7D\x08?\x56\x8B\xF1\x75\x0D\x80\xBE\x75\x02???");
			//static DWORD g_InterpolationList = Memory::FindPattern( GetModuleHandle( "client.dll" ), "\x0F\xB7\x05????????????????\x3D????????????????\x74\x3F");
			//if ( g_InterpolationList )
			//{
			//	DWORD* togoto0 = reinterpret_cast<DWORD*>( static_cast<DWORD>( g_InterpolationList ) + 18 );//array size/ list gotta clear it
			//	togoto0 = 0;
			//	DWORD* interplist = reinterpret_cast<DWORD*>( static_cast<DWORD>( g_InterpolationList ) + 12 ); //invalidate the head interpolation
			//	interplist = ( DWORD* ) 0xFFFF;
			//}

			QAngle* pEyeAngles = ( QAngle* ) ( ( unsigned long ) pLocal + Netvars->GetOffset( "DT_CSPlayer", "deadflag" ) + 4 );
			Interface->m_vecEyeAngles = *pEyeAngles;

			extern CInput* g_pInput;
			if ( !g_pInput )
				return;


			if ( *( bool* ) ( ( unsigned long ) g_pInput + 0xA5 ) )
			{
				static QAngle s_qViewAngles = Interface->m_LastCmdInfo.m_LastCmd.viewangles;

				if ( Interface->m_LastCmdInfo.m_bSendPacket )
					s_qViewAngles = Interface->m_LastCmdInfo.m_LastCmd.viewangles;

				//if ( s_qViewAngles.y > 180000  )
				//{
				//	s_qViewAngles.y = 0;
				//}

				//if ( s_qViewAngles.x > 180000 )
				//{
				//	s_qViewAngles.x = 0;
				//}

				*pEyeAngles = s_qViewAngles;
			}
		}



		if ( Interface->Engine()->GetVTable<IVEngineClient>()->IsInGame() )
		{
			if ( pLocal && pLocal->IsAlive() )
			{


				C_MyWeapon* pActiveWeapon = pLocal->GetWeapon();

				C_MyEntity* pViewModel = pLocal->GetViewModel();




				player_info_t localinfo;
				Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerInfo( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer(), &localinfo );
				for ( int i = 0; i < pLocal->GetMyWeapons()[ i ]; i++ )
				{
					C_MyWeapon* pWeapon = ( C_MyWeapon* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntityFromHandle( pLocal->GetMyWeapons()[ i ] );

					if ( !pWeapon )
						continue;

					if ( pWeapon->GetOwner() != pLocal )
						continue;


					if ( pWeapon->GetID() == WEAPON_KNIFE_T || pWeapon->GetID() == WEAPON_KNIFE_CT )
					{
						pWeapon->GetItemIDHigh() = 1;
						pWeapon->GetPaintKit() = 38;
						pWeapon->GetID() = 507;
						pWeapon->GetEntityQuality() = 3;
						pWeapon->GetSkinWear() = 0.01;
						pWeapon->GetSkinSeed() = 58;
					}
					else if ( pWeapon->GetID() == WEAPON_AK47 )
					{
						pWeapon->GetItemIDHigh() = 1;
						pWeapon->GetPaintKit() = 302;
						pWeapon->GetSkinWear() = 0.00000000001f;
						pWeapon->GetSkinSeed() = 58;
					}
					else if ( pWeapon->GetID() == WEAPON_NEGEV )
					{
						pWeapon->GetItemIDHigh() = 1;
						pWeapon->GetPaintKit() = 12;
						pWeapon->GetSkinWear() = 0.00000000001f;
						pWeapon->GetSkinSeed() = 58;
					}
					else if ( pWeapon->GetID() == WEAPON_AWP )
					{
						pWeapon->GetItemIDHigh() = 1;
						pWeapon->GetPaintKit() = 344;
						pWeapon->GetSkinWear() = 0.00000000001f;
						pWeapon->GetSkinSeed() = 58;
					}
					else if ( pWeapon->GetID() == WEAPON_GLOCK )
					{
						pWeapon->GetItemIDHigh() = 1;
						pWeapon->GetPaintKit() = 38;
						pWeapon->GetSkinWear() = 0.00000000001f;
						pWeapon->GetSkinSeed() = 58;
					}


				}
				if ( pActiveWeapon->GetID() == WEAPON_KNIFE_KARAMBIT )
				{
					pViewModel->SetWeaponModel( "models/weapons/v_knife_karam.mdl", pActiveWeapon );
				}


				PunchAngle = &pLocal->GetPunchAngle();
				vPunchAngle = &pLocal->GetViewPunchAngle();


				OldPunch = *PunchAngle;
				*PunchAngle = QAngle( 0, 0, 0 );

				vOldPunch = *vPunchAngle;
				*vPunchAngle = QAngle( 0, 0, 0 );


			}
		}
	}

	if ( curStage == FRAME_RENDER_END )
	{
		if ( pLocal )
		{
			QAngle* pEyeAngles = ( QAngle* ) ( ( unsigned long ) pLocal + Netvars->GetOffset( "DT_CSPlayer", "deadflag" ) + 4 );
			*pEyeAngles = Interface->m_vecEyeAngles;
		}
	}

	Interface->Client()->GetOriginalMethod<FrameStageNotify_t>( INDEX_FRAMESTAGENOTIFY )( thisptr, curStage );


	if ( curStage == FRAME_RENDER_START )
	{



		if ( Interface->Engine()->GetVTable<IVEngineClient>()->IsInGame() && pLocal && pLocal->IsAlive() )
		{
			*PunchAngle = OldPunch;
			*vPunchAngle = vOldPunch;
		}
	}
}