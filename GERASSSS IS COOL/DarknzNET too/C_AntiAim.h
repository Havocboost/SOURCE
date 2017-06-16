#pragma once
#include "main.h"

class C_AntiAim
{
public :

	void Spinbot(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void Crownt(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void AlternativeAngles(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets, Vector pVecAbs);
	void Backwards(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void Sideways(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void SetupPitch(CUserCmd *cmd);

	void RunAntiAim(C_MyEntity* LocalPlayer, CUserCmd* Cmd, bool &bSendPackets);
	void RunFakelags(C_MyEntity *localPlayer, CUserCmd *cmd, bool &bSendPackets);
	void EdgeAntAim(CUserCmd* Cmd, C_MyEntity* LocalPlayer, float Angle, bool CornersToo, bool ShouldSendOnCorners, bool ShouldSendNormal, bool &bSendPacket);
	void MovementFix(CUserCmd* pCmd);

};
extern C_AntiAim AntiAim;