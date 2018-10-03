#include "EventSystem.h"
#include "EventListener.h"
#include "Event.h"
#include "EventQueue.h"

typedef std::pair<EventType, EventListener*> mapPair;

EventSystem* EventSystem::instance = nullptr;

EventSystem* EventSystem::getInstance()
{
	if (!instance)
		instance = new EventSystem();

	return instance;
}

EventSystem::EventSystem()
{
	eventQueue = new EventQueue();
}


EventSystem::~EventSystem()
{
	if (eventQueue)
	{
		delete eventQueue;

		eventQueue = nullptr;
	}
}


void EventSystem::addListener(EventListener* _pListener, EventType _type)
{
	mListenerMap.insert(mapPair(_type, _pListener));
}


void EventSystem::removeListenerFromEvent(EventListener* _pListener, EventType _type)
{
	std::pair<std::multimap<EventType, EventListener*>::iterator, std::multimap<EventType, EventListener*>::iterator> ret;

	ret = mListenerMap.equal_range(_type);
	std::multimap<EventType, EventListener*>::iterator iter;

	for (iter = ret.first; iter != ret.second; ++iter)
	{
		if (iter->second == _pListener)
		{
			mListenerMap.erase(iter);
			break;
		}
	}
}

void EventSystem::removeListenerFromAllEvents(EventListener* _pListener)
{
	std::multimap<EventType, EventListener*>::iterator iter;

	bool allTheWayThrough = false;

	while (!allTheWayThrough)
	{
		allTheWayThrough = true;
		for (iter = mListenerMap.begin(); iter != mListenerMap.end(); ++iter)
		{
			if (iter->second == _pListener)
			{
				mListenerMap.erase(iter);
				allTheWayThrough = false;
				break;
			}
		}
	}
}

void EventSystem::addToEventQueue(Event& _event)
{
	eventQueue->push(&_event);
}

void EventSystem::dispatchEvents()
{
	Event* currEvent;

	while (eventQueue->getSize() > 0)
	{
		currEvent = eventQueue->pop();

		dispatchEvent(*currEvent);

		delete currEvent;
	}
}

void EventSystem::dispatchEvent(const Event& _event)
{
	std::pair<std::multimap<EventType, EventListener*>::iterator, std::multimap<EventType, EventListener*>::iterator> ret;
	ret = mListenerMap.equal_range(_event.type);

	std::multimap<EventType, EventListener*>::iterator iter;
	for (iter = ret.first; iter != ret.second; ++iter)
	{
		iter->second->handleEvent(_event);
	}
}