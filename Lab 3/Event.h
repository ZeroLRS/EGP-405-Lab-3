#pragma once
#include <string>

enum EventType
{
	DEFAULT_EVENT = -1,
	GAME_START,
	PLAYER_MOVE,
	COIN_COLLECTED,
	GAME_END
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

