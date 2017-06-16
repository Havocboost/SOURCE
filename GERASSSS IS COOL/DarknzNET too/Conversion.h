#pragma once
#include "main.h"
#include "shareddefs.h"

__forceinline float UTIL_RoundTimeToTicks( float flTime )
{
	return TICKS_TO_TIME( TIME_TO_TICKS( flTime ) );
}