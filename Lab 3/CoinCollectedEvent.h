#pragma once
#include "Event.h"
#include "RakNet/NetworkIDObject.h"

class CoinCollectedEvent :
	public Event
{
public:
	CoinCollectedEvent(RakNet::NetworkID _coinID, RakNet::NetworkID _collectorID);
	~CoinCollectedEvent();

	RakNet::NetworkID coinID;
	RakNet::NetworkID collectorID;

};

