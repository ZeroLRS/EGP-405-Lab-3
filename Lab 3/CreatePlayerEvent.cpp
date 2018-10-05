#include "CreatePlayerEvent.h"

CreatePlayerEvent::CreatePlayerEvent(Player* _playerData, bool _isClient) : Event(CREATE_PLAYER)
{
	playerData = *_playerData;
	isClient = _isClient;
}


CreatePlayerEvent::~CreatePlayerEvent()
{
}
