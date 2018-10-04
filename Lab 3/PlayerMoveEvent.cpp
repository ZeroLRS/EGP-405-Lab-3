#include "PlayerMoveEvent.h"

PlayerMoveEvent::PlayerMoveEvent(Vector2 _direction, RakNet::NetworkID _playerID) : Event(PLAYER_MOVE)
{
	moveDirection = _direction;

	playerID = _playerID;
}


PlayerMoveEvent::~PlayerMoveEvent()
{}
