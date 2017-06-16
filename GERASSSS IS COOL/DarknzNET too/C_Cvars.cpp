#include "C_Cvars.h"
C_Cvars Cvars;//Kinda stupid but necessary to use overriden constructor..

//We'll fill the Cvars from here;
C_Cvars::C_Cvars()
{
	Aimbot::Enable = 1;
	Aimbot::Selected = 1;
	Aimbot::Autoshoot = 1;
	Aimbot::Autoshoot = 1;
	Aimbot::Silent = 1;
	Aimbot::pSilent = 0;
	Aimbot::SendAttck = 0;
	Aimbot::Autowall = 0;

	Aimbot::Adjust_X = 0.0f;
	Aimbot::Adjust_Y = 0.0f;
	Aimbot::Adjust_Z = 0.0f;
	Aimbot::AutowallDmg = 0.0f;

	Aimbot::Hitscans = 1;
	Aimbot::Hitbox = 4;
	Aimbot::TargetSelection = 3; //Deprecated atm //TODO Implement Target Selection (NanoCat's)
	Aimbot::Inaccuracy = 3;

	//======

	Visual::Esp::Enable = 1;
	Visual::Esp::Box = 1;
	Visual::Esp::Health = 0;
	Visual::Esp::Armor = 0;
	Visual::Esp::Name = 1;
	Visual::Esp::Weapon = 1;
	Visual::Esp::AAx = 1;
	Visual::Esp::AAy = 0;

	Visual::Chams::Enable = 1;
	Visual::Chams::Player = 1;
	Visual::Chams::Weapon = 0;
	Visual::Chams::WeaponOutline = 0;

	Visual::Colors::TRed = 255;
	Visual::Colors::CTBlue = 255;
	Visual::Colors::ChamsTRed = 255;
	Visual::Colors::ChamsCTBlue = 255;
	Visual::Colors::WhiteListRED = 255;
	Visual::Colors::WhiteListGreen = 255;
	Visual::Colors::WhiteListBlue = 255;
	Visual::Colors::CrosshairRed = 200;
	Visual::Colors::CrosshairGreen = 200;
	Visual::Colors::CrosshairBlue = 200;
	Visual::Colors::MenuRed = 43;
	Visual::Colors::MenuGreen = 42;
	Visual::Colors::MenuBlue = 40;
	Visual::Colors::CursorRed = 40;
	Visual::Colors::CursorGreen = 60;
	Visual::Colors::CursorBlue = 120;

	Visual::Hitmarker = 0;
	Visual::Crosshair = 1;
	Visual::NoSky = 0;
	Visual::NoHands = 0;
	Visual::Asus = 0;

	//======

	Misc::AntiAim::Enable = 1;
	Misc::AntiAim::AntiaimType = 3;
	Misc::AntiAim::Pitch = 4;
	Misc::AntiAim::AntiAimMode = 5;
	Misc::AntiAim::FakelagMode = 2;
	Misc::AntiAim::Constant_Force = 7;
	Misc::AntiAim::InAttackForce = 7;
	Misc::AntiAim::TicksBlocked = 7;
	Misc::AntiAim::TicksSent = 9;
	Misc::AntiAim::JitterAngle = 40.0f;
	Misc::AntiAim::Spinspeed = 8.0f;

	Misc::Bunnyhop = 1;
	Misc::AutoStrafer = 1;
	Misc::FastRun = 1;
	Misc::Sv_CheatsBypass = 1;
	Misc::Hitsound = 0;
	Misc::Roundsay = 1;
	Misc::HeadshotSay = 0;
	Misc::BuyBotEnable = 0;
	Misc::BuyBot = 0;
	Misc::Menu_X = 450;
	Misc::Menu_Y = 300;


}
//=================================================
namespace Aimbot {
	float Enable, Autoshoot, Silent, pSilent, SendAttck, Autowall, Hitchance;
	float Adjust_X, Adjust_Y, Adjust_Z,AutowallDmg;
	int Selected, Hitscans, Hitbox, TargetSelection, Teamcheck, Inaccuracy;
}
//=================================================
namespace Visual {
	namespace Esp {
		float Enable, Box, Health, Armor, Name, Weapon, AAx, AAy, FovChanger;
	};

	namespace Chams {
		float Enable, Player, PlayerOutline, Weapon, WeaponOutline;
	};

	namespace Colors {
		float TRed, TGreen, TBlue, CTred, CTGreen, CTBlue, ChamsTRed, ChamsTGreen, ChamsTBlue, ChamsCTRed, ChamsCTGreen, ChamsCTBlue, WhiteListRED, WhiteListGreen, WhiteListBlue,
			AimspotRed, AimspotGreen, AimspotBlue, CrosshairRed, CrosshairGreen, CrosshairBlue, MenuRed, MenuGreen, MenuBlue, CursorRed, CursorGreen, CursorBlue;
		int ElementColorSelected;
	};

	float Hitmarker, Crosshair, NoSky, NoHands, Asus;

	bool canmodify;
}
//=================================================
namespace Misc 
{
	float Bunnyhop, AutoStrafer, FastRun, Sv_CheatsBypass, Hitsound, Roundsay, HeadshotSay, BuyBotEnable, AutoMM, Resolver;
	int BuyBot;
	bool MenuActive;
	int Menu_X, Menu_Y;

	namespace AntiAim 
	{
		float Enable;
		int AntiaimType, Pitch, AntiAimMode, FakelagMode, EdgeMode;
		float Constant_Force, InAttackForce, TicksBlocked, TicksSent, JitterAngle, Spinspeed;
	};
}