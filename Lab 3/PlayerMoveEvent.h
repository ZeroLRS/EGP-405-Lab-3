#pragma once
#include "Utils.h"
#include "Event.h"
#include "RakNet/NetworkIDObject.h"

class PlayerMoveEvent : public Event
{
public:
	PlayerMoveEvent(Vector2 _direction, RakNet::NetworkID _playerID);
	~PlayerMoveEvent();

	RakNet::NetworkID playerID;
	Vector2 moveDirection;
};

