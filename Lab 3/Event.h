#pragma once
#include <string>

enum EventType
{
	DEFAULT = -1,
	PLAYER_MOVE
};

class Event
{
public:
	Event();
	~Event();

	std::string TestString;

	EventType type;
};

