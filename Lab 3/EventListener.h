#pragma once
#include <vector>
#include "Event.h"

class Event;

class EventListener
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& _event) = 0;
};