#pragma once
#include "Utils.h"
#include "Event.h"

class PlayerMoveEvent : public Event
{
public:
	PlayerMoveEvent(Vector2 _direction);
	~PlayerMoveEvent();

	Vector2 moveDirection;
};

