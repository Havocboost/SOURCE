#include "main.h"
#include "usercmd.h"
#include "shareddefs.h"
#include "C_Aimbot.h"

void CUserCmd::ProcessSimulation( float flTime )
{
	if ( flTime <= 0.0f )
		return;

	int target_Tick_men = TIME_TO_TICKS( flTime );
	if ( ( tick_count - target_Tick_men ) > 8 || ( tick_count - target_Tick_men ) < -10 )
		return;

	tick_count = target_Tick_men + TIME_TO_TICKS( 0.031f );
}