#include "GameEndEvent.h"

GameEndEvent::GameEndEvent(RakNet::NetworkID _winnerID) : Event(GAME_END), winnerID(_winnerID)
{}

GameEndEvent::~GameEndEvent()
{}
