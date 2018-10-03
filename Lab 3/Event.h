#pragma once
#include <string>

enum EventType
{
	DEFAULT_EVENT = -1,
	PLAYER_MOVE
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

