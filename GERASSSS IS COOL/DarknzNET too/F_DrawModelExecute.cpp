#include "main.h"
#include "C_Draw.h"


IMaterial *CreateMaterial(bool shouldIgnoreZ, bool isWireframe = false)
{
	static int created = 0;

	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"VGUI/white\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$nocull\" \"1\"\
		\n\t\"$nofog\" \"1\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"1\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};


	static const char baseType[] = "VertexLitGeneric";

	char material[512];

	sprintf_s(material, sizeof(material), tmp, baseType, (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char name[512];

	sprintf_s(name, sizeof(name), "custom_material_%i.vmt", created);

	++created;

	CKeyValues* keyValues = new CKeyValues(baseType);

	keyValues->LoadFromBuffer(keyValues, name, material);


	IMaterial *createdMaterial = Interface->MaterialSystem()->GetOriginalMethod<CreateMaterial_t>(INDEX_CREATEMATERIAL)(Interface->MaterialSystem()->thisptr(), name, keyValues);

	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}


//=================================================
void ForceMaterial(const Color &colour, IMaterial *mat, bool shouldColour = true)
{
	static const float scale = (1.f / 255.f);

	if (shouldColour)
	{
		float tmp[] = { (colour.r() * scale), (colour.g() * scale), (colour.b() * scale), (255 * scale) };
		Interface->RenderView()->GetVTable<IVRenderView>()->SetColorModulation(tmp);
	}
	Interface->ModelRender()->GetVTable<IVModelRender>()->ForcedMaterialOverride(mat);
}

//=================================================
void __fastcall C_Interface::DrawModelExecute( void *thisptr, int edx, void*context, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld )
{

	static IMaterial *outline = CreateMaterial( true, true );

	static IMaterial *inner = CreateMaterial( true );

	static IMaterial *outer = CreateMaterial( false );

	// slate grey
	static const Color grey( 0x70, 0x80, 0x90 );

	// light coral
	static const Color lightRed( 0xF0, 0x80, 0x80 );
	static const Color red( 0xFF, 0, 0 );

	// cornflower blue
	static const Color lightBlue( 0x64, 0x95, 0xED );
	static const Color blue( 0, 0, 0xFF );


	static const Color black( 0, 0, 0 );
	static const Color white( 0xFF, 0xFF, 0xFF );
	static const Color greeen( 0, 255, 0, 255 );

	static const Color Green( 30, 150, 65, 255 );
	static const Color dwYellow( 255, 200, 15, 150 );


	std::string modelName = Interface->ModelInfo()->GetVTable<IVModelInfo>()->GetModelName( pInfo.pModel );

	bool active = false;

	if ( Visual::Chams::Enable )
	{
		if ( Visual::Chams::Player )
		{
			if ( modelName.find( "models/player" ) != std::string::npos )
			{
				const Color *colour = &white;

				C_MyEntity *localPlayer = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer() );
				C_MyEntity *entity = ( C_MyEntity* ) Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity( pInfo.entity_index );


				if ( entity && ( entity->GetHealth() > 0 ) )
				{
					if ( Visual::Chams::PlayerOutline )
					{
						ForceMaterial( red, outline );
						Interface->ModelRender()->GetOriginalMethod<DrawModelExecute_t>( INDEX_DRAWMODELEXECUTE )( thisptr, context, state, pInfo, pCustomBoneToWorld );
					}

					switch ( entity->GetTeamNum() )
					{
					case TERRORIST:
						colour = &red;
						break;

					case COUNTER_TERRORIST:
						colour = &greeen;
						break;


					default:
						break;
					}


					// draw inner layer
					ForceMaterial( *colour, inner );
					Interface->ModelRender()->GetOriginalMethod<DrawModelExecute_t>( INDEX_DRAWMODELEXECUTE )( thisptr, context, state, pInfo, pCustomBoneToWorld );


					// if ent is alive and it's not ( spawnprotected and an enemy )
					if ( !( ( ( entity->GetHealth() >= 500 )
						|| ( entity->GetRenderColor().a < 255 ) )
						&& ( entity->GetTeamNum() != localPlayer->GetTeamNum() ) ) )
					{
						switch ( entity->GetTeamNum() )
						{
						case TERRORIST:
							colour = &Color( Visual::Colors::ChamsTRed, Visual::Colors::ChamsTGreen, Visual::Colors::ChamsTBlue, 255 );
							break;

						case COUNTER_TERRORIST:

							colour = &Color( Visual::Colors::ChamsCTRed, Visual::Colors::ChamsCTGreen, Visual::Colors::ChamsCTBlue, 255 );
							break;

						default:
							break;
						}

						player_info_t info;

						if ( !Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerInfo( ( ( C_MyEntity* ) ( entity ) )->GetIndex(), &info ) )
						{
							return;
						}


						if ( PlayerList[ entity->GetIndex() ].flWhitelist )
						{
							colour = &Color( Visual::Colors::WhiteListRED, Visual::Colors::WhiteListGreen, Visual::Colors::WhiteListBlue, 255 );
						}
						// force outer layer's colour
						ForceMaterial( *colour, outer );
						active = true;
					}
					else
					{
						// reset
						ForceMaterial( black, 0, false );
						return;
					}
				}
				else
				{
					// if it's a body force white
					ForceMaterial( *colour, outer );
					active = true;
				}
			}
		}

		if ( Visual::Chams::Enable && Visual::Chams::Weapon )
		{
			if ( modelName.find( "models/weapons/w_" ) != std::string::npos )
			{
				if ( Visual::Chams::WeaponOutline )
				{
					// draw outline
					ForceMaterial( red, outline );
					Interface->ModelRender()->GetOriginalMethod<DrawModelExecute_t>( INDEX_DRAWMODELEXECUTE )( thisptr, context, state, pInfo, pCustomBoneToWorld );
				}

				if ( Visual::Chams::Weapon )
				{
					// we only need 1 layer for weapons
					ForceMaterial( black, inner );
					active = true;
				}
			}
		}

		//for ( MaterialHandle_t i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->FirstMaterial(); i != Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->InvalidMaterial(); i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->NextMaterial( i ) )
		//{
		//	IMaterial *pMaterial = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->GetMaterial( i );

		//	if ( !pMaterial )
		//		continue;
		//	if ( Visual::Asus ) //Asuswall
		//	{
		//		if ( strstr( pMaterial->GetTextureGroupName(), TEXTURE_GROUP_WORLD ) )
		//		{
		//			pMaterial->AlphaModulate( 0.4f );
		//			pMaterial->ColorModulate( 0.2f, 0.2f, 0.2f );
		//			pMaterial->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_TRANSLUCENT, true );
		//		}

		//	}
		//	else
		//	{
		//		if ( strstr( pMaterial->GetTextureGroupName(), TEXTURE_GROUP_WORLD ) )
		//		{
		//			pMaterial->SetMaterialVarFlag( MaterialVarFlags_t::MATERIAL_VAR_TRANSLUCENT, false );
		//			pMaterial->AlphaModulate( 1.0f );
		//			pMaterial->ColorModulate( 1.0f, 1.0f, 1.0f );
		//		}
		//	}
		//		if ( Visual::NoSky ) //No Sky
		//		{
		//			if ( strstr( pMaterial->GetName(), "skybox" ) )
		//			{
		//				pMaterial->ColorModulate( 0.f, 0.f, 0.f );
		//			}
		//		}
		//		else
		//		{
		//			if ( strstr( pMaterial->GetName(), "skybox" ) )
		//			{
		//				pMaterial->ColorModulate( 1.0f, 1.0f, 1.0f );
		//			}
		//		}
		//		if ( Visual::NoHands ) //No Hands
		//		{
		//			if ( strstr( pMaterial->GetName(), "arms" ) )
		//			{
		//				pMaterial->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, true );
		//			}
		//		}
		//		else
		//		{
		//			if ( strstr( pMaterial->GetName(), "arms" ) )
		//			{
		//				pMaterial->SetMaterialVarFlag( MATERIAL_VAR_NO_DRAW, false );
		//			}
		//		}

		//}



		Interface->ModelRender()->GetOriginalMethod<DrawModelExecute_t>( INDEX_DRAWMODELEXECUTE )( thisptr, context, state, pInfo, pCustomBoneToWorld );

		// reset if we forced materials
		if ( active )
		{
			ForceMaterial( black, 0, false );
		}
	}

}
