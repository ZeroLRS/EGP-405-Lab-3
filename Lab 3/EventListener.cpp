#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener()
{
	//does nothing
}

EventListener::~EventListener()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
}