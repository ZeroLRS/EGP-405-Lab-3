#pragma once
#include "Event.h"
#include "Utils.h"

class PlaceCoinEvent :
	public Event
{
public:
	PlaceCoinEvent(Vector2 _coinPos);
	~PlaceCoinEvent();

	Vector2 coinPos;
};

