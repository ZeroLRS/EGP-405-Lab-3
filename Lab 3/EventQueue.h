#pragma once

#include "Event.h"
#include <mutex>

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

	std::mutex queueMutex;

private:
	EventQueueItem* mFirstItem;
	EventQueueItem* mNewestItem;
	int mSize;
};
