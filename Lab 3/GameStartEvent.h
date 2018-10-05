#pragma once
#include "Event.h"
#include <vector>
#include "Player.h"

class GameStartEvent : public Event
{
public:
	GameStartEvent(std::vector<Entity> _coins);
	~GameStartEvent();

	std::vector<Entity> coins;
};

