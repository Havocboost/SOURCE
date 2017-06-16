#include "main.h"

#ifndef _EVENTS_H_
#define _EVENTS_H_

class C_GameEvent : public IGameEventListener2 {
public:
	C_GameEvent();
	void FireGameEvent(IGameEvent* event);
	void RegisterSelf();
};

extern C_GameEvent* Event;

#endif