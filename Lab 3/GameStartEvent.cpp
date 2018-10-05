#include "GameStartEvent.h"

GameStartEvent::GameStartEvent(std::vector<Entity> _coins) : Event(GAME_START)
{
	coins = _coins;
}


GameStartEvent::~GameStartEvent()
{
}
