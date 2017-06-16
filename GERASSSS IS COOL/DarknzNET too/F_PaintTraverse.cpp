#include "main.h"
#define BUILDSTAMP ( __DATE__ " @ " __TIME__ )


void ESP(C_MyEntity* Localplayer, C_MyEntity* TargetPLayer)
{
	static Vector duckOffset = Vector(0.f, 0.f, 53.5f); // VEC_DUCK_HULL_MAX
	static Vector standOffset = Vector(0.f, 0.f, 72.f); // VEC_HULL_MAX

	int teamnumenemy = TargetPLayer->GetTeamNum();
	Color colour = Color(255, 255, 255, 255);


	if (teamnumenemy == 2)
	{
		colour = Color(Visual::Colors::TRed, Visual::Colors::TGreen, Visual::Colors::TBlue, 255);
	}
	if (teamnumenemy == 3)
	{
		colour = Color(Visual::Colors::CTred, Visual::Colors::CTGreen, Visual::Colors::CTBlue, 255);
	}

	if (PlayerList[TargetPLayer->GetIndex()].flWhitelist)
	{
		colour = Color(Visual::Colors::WhiteListRED, Visual::Colors::WhiteListGreen, Visual::Colors::WhiteListBlue, 255);
	}

	int iWidth, iHeight;

	player_info_t PlayerInfo;
	Interface->Engine()->GetVTable<IVEngineClient>()->GetPlayerInfo(((C_MyEntity*)(TargetPLayer))->GetIndex(), &PlayerInfo);

	Interface->Engine()->GetVTable<IVEngineClient>()->GetScreenSize(iWidth, iHeight);

	iWidth *= 0.5f;
	iHeight *= 0.5f;

	int teamnumme = *(int*)((DWORD)Localplayer + 0x98);

	Vector origin;
	if (!Draw.WorldToScreen(TargetPLayer->GetAbsOrigin(), origin))
	{
		return;
	}

	if (!Localplayer)
	{
		return;
	}

	Vector offset = (TargetPLayer->GetFlags() & FL_DUCKING) ? duckOffset : standOffset;
	Vector max = (TargetPLayer->GetAbsOrigin() + offset);

	Vector top;
	if (!Draw.WorldToScreen(max, top))
	{
		return;
	}

	float len = 0.f;
	int fontIndex = 0;

	if (Localplayer)
	{
		//len = ( max - localPlayer->GetEyePosition() ).Length();
		//fontIndex = GetFontIndexByDistance( len );
	}

	float boxHeight = (origin.y - top.y);
	float boxHalfWidth = (boxHeight * 0.225f);

	{
		boxHalfWidth *= 1.345794392523364f;
	}

	Vector box((top.x - boxHalfWidth), top.y, 0.f);

	Draw.DrawOutlinedRect((box.x - 1), (box.y - 1), ((boxHalfWidth * 2) + 2), (boxHeight + 2), Color(0, 0, 0, 255));
	Draw.DrawOutlinedRect((box.x + 1), (box.y + 1), ((boxHalfWidth * 2) - 2), (boxHeight - 2), Color(0, 0, 0, 255));
	Draw.DrawOutlinedRect(box.x, box.y, (boxHalfWidth * 2), boxHeight, colour);
	//========================================
	//Health ESP
	if (Visual::Esp::Health)
	{
		float health = TargetPLayer->GetHealth();
		if (health > 0)
		{
			int scale = (health * 2.55f);
			Color patch(0, 0, 0, 255);
			if (health > 100)
			{
				patch.SetColor(255, 255, 255, 255);
			}
			Draw.DrawOutlinedRect(box.x, box.y + boxHeight, (boxHalfWidth * 2)*(health / 100), 4, Color(0, 0, 0, 255));
			Draw.DrawOutlinedRect(box.x, box.y + boxHeight + 1, (boxHalfWidth * 2)*(health / 100), 2, Color(0, scale, 0, 255));
		}
	}
	//========================================
	//Armor ESP
	if (Visual::Esp::Armor)
	{
		int armorstatus = TargetPLayer->GetArmorValue();
		float armor = min(armorstatus, 100);
		if (armor > 0)
		{
			int scale = (armor * 2.55f);
			Color patch(85, 85, 85, 255);
			if (TargetPLayer->HasHelmet())
			{
				patch.SetColor(0, 0, 0, 255);
			}
			Draw.DrawOutlinedRect(box.x, box.y + boxHeight + 3, (boxHalfWidth * 2)*(armor / 100), 4, patch);
			Draw.DrawOutlinedRect(box.x, box.y + boxHeight + 1 + 3, (boxHalfWidth * 2)*(armor / 100), 2, Color(scale, scale, scale, 255));
		}

		top.x += (boxHalfWidth + 5);
		top.y -= 4;
	}
	//========================================
	//Name ESP
	if (Visual::Esp::Name)
	{
		const char *tmpname = PlayerInfo.name;
		char Name[0xFF];
		strcpy(Name, tmpname);
		char *cname = Name;
		while (*cname)
		{
			*cname = toupper(*cname);
			++cname;
		}
		Draw.DrawString(false, fontIndex, top.x, top.y, colour, "%s", Name);
		top.y += ((12 - GetFontIndexByDistance(len))); // newline: 16 - font index = height, +1 is for a space in between
	}
	//========================================
	//Weapon ESP
	if (Visual::Esp::Weapon)
	{
		C_MyWeapon *weapon = TargetPLayer->GetWeapon();
		std::string wepname = weapon->GetWeaponName();
		std::string remove = "weapon_";
		std::string::size_type idx = wepname.find("weapon_");

		if (idx != std::string::npos)
			wepname.erase(idx, remove.length());

		for (auto & c : wepname) c = toupper(c);

		Draw.DrawString(false, fontIndex, top.x, top.y, colour, "%s", wepname.c_str());
		top.y += ((12 - GetFontIndexByDistance(len))); // newline: 16 - font index = height, +1 is for a space in between
	}
	//========================================
	//Health ESP
	if (Visual::Esp::Health)
	{
		int healthtext = TargetPLayer->GetHealth();
		Draw.DrawString(false, fontIndex, top.x, top.y, colour, "%i", healthtext);
		top.y += ((12 - GetFontIndexByDistance(len))); // newline: 16 - font index = height, +1 is for a space in between
	}
	//========================================
	//AA ESP
	if (Visual::Esp::AAx)
	{
		Draw.DrawString(false, fontIndex, top.x, top.y, colour, "X: %0.2f", TargetPLayer->GetEyeAngles().x);
		top.y += ((12 - GetFontIndexByDistance(len))); // newline: 16 - font index = height, +1 is for a space in between	}		
	}
	if (Visual::Esp::AAy)
	{
		Draw.DrawString(false, fontIndex, top.x, top.y, colour, "Y: %0.2f", TargetPLayer->GetEyeAngles().y);
		top.y += ((12 - GetFontIndexByDistance(len))); // newline: 16 - font index = height, +1 is for a space in between
	}
	//========================================
}
//=================================================
void DrawCrossHair() {

	int iWidth, iHeight;

	Interface->Engine()->GetVTable<IVEngineClient>()->GetScreenSize(iWidth, iHeight);

	iWidth *= 0.5f;
	iHeight *= 0.5f;

	Draw.OutRGBA(iWidth - 1, iHeight - 4, iWidth + 2, iHeight + 5, Color(0, 0, 0, 255));
	Draw.OutRGBA(iWidth - 4, iHeight - 1, iWidth + 5, iHeight + 2, Color(0, 0, 0, 255));


	Draw.OutRGBA(iWidth, iHeight - 3, iWidth + 1, iHeight + 4, Color(Visual::Colors::CrosshairRed, Visual::Colors::CrosshairGreen, Visual::Colors::CrosshairBlue, 255));
	Draw.OutRGBA(iWidth - 3, iHeight, iWidth + 4, iHeight + 1, Color(Visual::Colors::CrosshairRed, Visual::Colors::CrosshairGreen, Visual::Colors::CrosshairBlue, 255));

}
//=================================================
void __fastcall C_Interface::PaintTraverse(void *thisptr, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	Interface->Panel()->GetOriginalMethod<PaintTraverse_t>(INDEX_PAINTTRAVERSE)(thisptr, vguiPanel, forceRepaint, allowForce);

	//Remove scope
	if (!strcmp(Interface->Panel()->GetOriginalMethod<GetName_t>(INDEX_GETNAME)(thisptr, vguiPanel), "HudZoom"))
	{
		Interface->Panel()->GetVTable<IPanel>()->SetVisible(vguiPanel, false);
		Interface->Panel()->GetVTable<IPanel>()->SetSize(vguiPanel, 0,0);
	}

	if (!strcmp(Interface->Panel()->GetOriginalMethod<GetName_t>(INDEX_GETNAME)(thisptr, vguiPanel), "MatSystemTopPanel"))
	{
		//Draw.DrawString(false, 1, 5, 2, Color(255, 255, 255, 255), "LayZ_Pz : Binary Build Date : %s", BUILDSTAMP);
		Draw.PrintText(fontMenu, 1, 5, Color(255, 255, 255, 255), false, "Lonely Hills : )" /*:Binary Build Date : %s", BUILDSTAMP*/);

		//:)
		Visual::canmodify = Misc::MenuActive;
		if (GetAsyncKeyState(VK_INSERT) & 0x01)
		{
			Misc::MenuActive = !Misc::MenuActive;
			Interface->Cvar()->GetVTable<ICvar>()->FindVar("cl_mouseenable")->SetValue(!(float)Misc::MenuActive);
		}

		if (Misc::MenuActive)
		{
			gMenu.Render();
		}

		if (Interface->Engine()->GetVTable<IVEngineClient>()->IsInGame())
		{
			if (Visual::Crosshair)
			{
				DrawCrossHair();
			}

			int local = Interface->Engine()->GetVTable<IVEngineClient>()->GetLocalPlayer();
			C_MyEntity *localPlayer = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(local);

			for (int index = 1; index <= Globals()->maxClients; ++index)
			{
				if (index == local)
				{
					continue;
				}

				C_MyEntity *player = (C_MyEntity*)Interface->EntityList()->GetVTable<IClientEntityList>()->GetClientEntity(index);

				if (!player
					|| player->IsDormant()
					|| !player->IsAlive())
				{
					continue;
				}

				if (Visual::Esp::Enable)
				{
					ESP(localPlayer, player);
				}

			}

			if (Visual::Hitmarker)
			{
				HitMarkerManager.RunFrame(localPlayer);
			}



		}
		else
		{
			HitMarkerManager.Clear();
		}
	}

}