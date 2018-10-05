#pragma once
#include "Event.h"
#include "Player.h"

class CreatePlayerEvent :
	public Event
{
public:
	CreatePlayerEvent(Player* _playerData, bool _isClient);
	~CreatePlayerEvent();

	Player playerData;
	bool isClient;
};

