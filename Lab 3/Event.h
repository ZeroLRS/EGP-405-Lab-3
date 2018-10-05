#pragma once
#include <string>

enum EventType
{
	DEFAULT_EVENT = -1,
	GAME_START,
	PLAYER_MOVE,
	COIN_COLLECTED,
	GAME_END,
	CREATE_PLAYER,
	DELETE_ALL_COINS,
	PLACE_COIN
};

class Event
{
public:
	//Event();
	Event(EventType _type);
	~Event();

	std::string TestString;

	EventType type;
};

