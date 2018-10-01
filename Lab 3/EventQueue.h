#pragma once

#include "Event.h"

struct EventQueueItem
{
	Event* event;
	EventQueueItem* nextItem;
};

class EventQueue
{
public:
	EventQueue();
	~EventQueue();

	void push(Event* newEvent);
	Event* pop();

	int getSize();

private:
	EventQueueItem* mFirstItem;
	EventQueueItem* mNewestItem;
	int mSize;

};
