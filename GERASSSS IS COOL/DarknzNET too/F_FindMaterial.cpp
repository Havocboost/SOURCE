#include "main.h"

IMaterial *__fastcall C_Interface::FindMaterial(void *thisptr, void *edx, const char *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix)
{
	IMaterial *material = Interface->MaterialSystem()->GetOriginalMethod<FindMaterial_t>(INDEX_FINDMATERIAL)(thisptr, pMaterialName, pTextureGroupName, complain, pComplainPrefix);

	if (material)
	{

		if (Visual::NoSky)
		{
			if (strstr(material->GetName(), "skybox"))
			{
				material->ColorModulate(0.f, 0.f, 0.f);
			}
		}
		else
		{
			if (strstr(material->GetName(), "skybox"))
			{
				material->ColorModulate(1.0f, 1.0f, 1.0f);
			}
		}


		for ( MaterialHandle_t i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->FirstMaterial(); i != Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->InvalidMaterial(); i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->NextMaterial( i ) )
		{
			IMaterial *pMaterial = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->GetMaterial(i);

			if (!pMaterial)
				continue;

			//if (Visual::Asus)
			/*	for ( MaterialHandle_t i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->FirstMaterial(); i != Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->InvalidMaterial(); i = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->NextMaterial( i ) )*/
			//	{
			//		IMaterial *pMaterial = Interface->MaterialSystem()->GetVTable<IMaterialSystem>()->GetMaterial( i );

			//		if ( !pMaterial )
			//			continue;

			//		if ( Interface->Cvar()->GetVTable<ICvar>()->FindVar( "vis_asus" )->GetBool() == 0 )
			//		{
			//			pMaterial->AlphaModulate( 0.5f );
			//		}
			//		if ( strstr( material->GetName(), "World" ) )
			//		{
			//			pMaterial->AlphaModulate( 0.7f );
			//		}
			//	}
		}

		if (Visual::NoHands)
		{
			if (strstr(material->GetName(), "arms"))
			{
				material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			}
		}
		else
		{
			if (strstr(material->GetName(), "arms"))
			{
				material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			}
		}
	}

	return material;
}

