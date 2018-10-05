#pragma once
#include "Event.h"
class DeleteAllCoinsEvent :
	public Event
{
public:
	DeleteAllCoinsEvent();
	~DeleteAllCoinsEvent();
};

