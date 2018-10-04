#include "GameStartEvent.h"

GameStartEvent::GameStartEvent(std::vector<Player> _players) : Event(GAME_START)
{
	playersInMatch = _players;
}


GameStartEvent::~GameStartEvent()
{
}
