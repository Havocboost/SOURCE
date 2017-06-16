#include "main.h"

void __fastcall C_Interface::DrawPortals(void *thisptr, int edx)
{
	static bool oldhands = false;
	static bool oldasus = false;

	if ((Interface->Engine()->GetVTable<IVEngineClient>()->IsInGame()))	{

		IMaterialSystem *materialsys = Interface->MaterialSystem()->GetVTable<IMaterialSystem>();

		for (MaterialHandle_t i = materialsys->FirstMaterial(); i != materialsys->InvalidMaterial(); i = materialsys->NextMaterial(i))
		{
			IMaterial *material = materialsys->GetMaterial(i);

			if (!material)
				continue;

			// no hands
			if (Visual::NoHands != oldhands)
			{
				if (strstr(material->GetName(), "hands"))
				{
					materialsys->FindMaterial(material->GetName(), material->GetTextureGroupName());
					oldhands = Visual::NoHands;
				}
			}

			// asus
			if (Visual::NoSky != oldasus)
			{
				if (strstr(material->GetName(), "hands"))
				{
					materialsys->FindMaterial(material->GetName(), material->GetTextureGroupName());
					oldasus = Visual::NoSky;
				}
			}
		}

	}
	else
	{
		oldhands = false;
		oldasus = false;
	}

	// call
	Interface->Engine()->GetOriginalMethod<DrawPortals_t>(INDEX_DRAWPORTALS)(thisptr);
}