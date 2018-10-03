#pragma once
#include <map>
#include "Event.h"

class EventQueue;
class EventListener;

class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	static EventSystem* getInstance();

	void addListener(EventListener* _listener, EventType _type);
	void removeListenerFromEvent(EventListener* _pListener, EventType _type);
	void removeListenerFromAllEvents(EventListener* _pListener);

	void addToEventQueue(Event* _event);
	void dispatchEvents();

private:
	static EventSystem* instance;

	EventQueue* eventQueue;
	std::multimap<EventType, EventListener*> mListenerMap;

	void dispatchEvent(const Event& _event);
};

