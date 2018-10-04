#pragma once
#include "Event.h"
#include "RakNet/NetworkIDObject.h"

class GameEndEvent : public Event
{
public:
	GameEndEvent(RakNet::NetworkID _winnerID);
	~GameEndEvent();

	RakNet::NetworkID winnerID;

};

