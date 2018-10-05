#pragma once
#include "Event.h"
#include "Entity.h"

class PlaceCoinEvent :
	public Event
{
public:
	PlaceCoinEvent(Entity* _coinData);
	~PlaceCoinEvent();

	Entity coinData;
};

