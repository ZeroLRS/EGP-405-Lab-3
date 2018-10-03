#include "PlayerMoveEvent.h"

PlayerMoveEvent::PlayerMoveEvent(Vector2 _direction) : Event(PLAYER_MOVE)
{
	moveDirection = _direction;
}


PlayerMoveEvent::~PlayerMoveEvent()
{}
