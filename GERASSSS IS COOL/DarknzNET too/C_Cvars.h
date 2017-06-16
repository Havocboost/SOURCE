#pragma once
#include "main.h"


class C_Cvars {
public:
	C_Cvars();
};

extern C_Cvars Cvars;


namespace Aimbot {
	extern float Enable, Autoshoot, Silent, pSilent, SendAttck, Autowall, Hitchance;
	extern float Adjust_X, Adjust_Y, Adjust_Z,AutowallDmg;
	extern int Selected, Hitscans, Hitbox, TargetSelection, Teamcheck, Inaccuracy;
}

namespace Visual {
	namespace Esp {
		extern float Enable, Box, Health, Armor, Name, Weapon, AAx, AAy, FovChanger;
	};

	namespace Chams {
		extern float Enable, Player, PlayerOutline, Weapon, WeaponOutline;
	};

	namespace Colors {
		extern float TRed, TGreen, TBlue, CTred, CTGreen, CTBlue, ChamsTRed, ChamsTGreen, ChamsTBlue, ChamsCTRed, ChamsCTGreen, ChamsCTBlue, WhiteListRED, WhiteListGreen, WhiteListBlue,
			AimspotRed, AimspotGreen, AimspotBlue, CrosshairRed, CrosshairGreen, CrosshairBlue, MenuRed, MenuGreen, MenuBlue, CursorRed, CursorGreen, CursorBlue;
		extern int ElementColorSelected;
	};

	extern float Hitmarker, Crosshair, NoSky, NoHands, Asus;

	extern bool canmodify;
}

namespace Misc {
	extern float Bunnyhop, AutoStrafer, FastRun, Sv_CheatsBypass, Hitsound, Roundsay, HeadshotSay, BuyBotEnable, AutoMM, Resolver;
	extern int BuyBot;
	extern bool MenuActive;
	extern int Menu_X, Menu_Y;

	namespace AntiAim {
		extern float Enable;
		extern int AntiaimType, Pitch, AntiAimMode, FakelagMode, EdgeMode;
		extern float Constant_Force, InAttackForce, TicksBlocked, TicksSent,JitterAngle,Spinspeed;
	};

}
