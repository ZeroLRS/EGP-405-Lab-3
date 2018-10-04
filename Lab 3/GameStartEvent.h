#pragma once
#include "Event.h"
#include <vector>
#include "Player.h"

class GameStartEvent : public Event
{
public:
	GameStartEvent(std::vector<Player> _players);
	~GameStartEvent();

	std::vector<Player> playersInMatch;
};

