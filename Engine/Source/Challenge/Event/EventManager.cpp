#include <Challenge/Challenge.h>
#include "EventManager.h"
using namespace challenge;

std::string EventManager::wildcardEvent = "wildcard";

EventManager::EventManager()
{
	mActiveQueue = 0;
}

void EventManager::RegisterEvent(std::string pEventName, IEventListener *pListener)
{
	if (pEventName.length() > 0) {
		bool found = false;
		
		TEventListenerList listeners =  mListeners[pEventName];
		if (listeners.size() > 0) {
			TEventListenerList::iterator i = listeners.begin();
			while (i != listeners.end()) {
				if ((*i) == pListener) {
					found = true;
					break;
				}
				i++;
			}
		}

		if (!found) {
			mListeners[pEventName].push_back(pListener);
		}
	}
}

void EventManager::UnregisterEvent(std::string pEventName, IEventListener *pListener)
{
	if (pEventName.length() > 0) {
		TEventListenerList newListeners;
		TEventListenerList listeners =  mListeners[pEventName];
		if (listeners.size() > 0) {
			TEventListenerList::iterator i = listeners.begin();
			while (i != listeners.end()) {
				if ((*i) != pListener) {
					newListeners.push_back((*i));
				}
				i++;
			}
		}
		mListeners[pEventName] = newListeners;
	}
}

void EventManager::FireEvent(IEventData *data)
{
	if (data == NULL) {
		return;
	}

	std::string eventType = data->GetEventType();
	if (eventType.length() > 0) {
		TEventListenerList wildcardListeners = mListeners[wildcardEvent];
		if (wildcardListeners.size() > 0) {
			TEventListenerList::iterator i = wildcardListeners.begin();
			while (i != wildcardListeners.end()) {
				(*i)->HandleEvent(data);
				i++;
			}
		}

		TEventListenerList listeners = mListeners[eventType];
		if (listeners.size() > 0) {
			TEventListenerList::iterator i = listeners.begin();
			while (i != listeners.end()) {
				(*i)->HandleEvent(data);
				i++;
			}
		}
	}

	delete data;
}

void EventManager::QueueEvent(IEventData *data)
{  
	if (data == NULL) {
		return;
	}

	std::string eventType = data->GetEventType();
	if (eventType.length() > 0) {
		if(mListeners.count(eventType)) {
			mQueues[mActiveQueue].push_back(data);
		}
	}
}
		
void EventManager::Tick(unsigned long maxMillis)
{
	unsigned long curMs = GetTickCount();
	unsigned long maxMs = maxMillis == kInfinity ? kInfinity : curMs + maxMillis;

	int queueToProcess = mActiveQueue;
	mActiveQueue = (mActiveQueue + 1) % numEventQueues;
	mQueues[mActiveQueue].clear();

	while (mQueues[queueToProcess].size() > 0) {
		IEventData *data = mQueues[queueToProcess].front();
		mQueues[queueToProcess].pop_front();

		std::string eventType = data->GetEventType();
		TEventListenerList listeners = mListeners[eventType];
		if (listeners.size() > 0) {
			TEventListenerList::iterator i = listeners.begin();
			while (i != listeners.end()) {
				(*i)->HandleEvent(data);
				i++;
			}
		}

		delete data;

		if (maxMillis != kInfinity) {
			curMs = GetTickCount();
			if (curMs >= maxMs) {
				break;
			} 
		}
	}

	bool queueEmpty = (mQueues[queueToProcess].size() == 0);

	if (!queueEmpty) {
		while (mQueues[queueToProcess].size() > 0) {
			IEventData *data = mQueues[queueToProcess].back();
			mQueues[queueToProcess].pop_back();
			mQueues[mActiveQueue].push_front(data);
		}
	}
}

void EventManager::Abort(std::string pEventType, bool removeAll)
{
	if (pEventType.length() > 0) {
		TEventListenerList listeners = mListeners[pEventType];
		if (listeners.size() > 0) {
			TEventListenerList::iterator i = listeners.begin();
			while (i != listeners.end()) {
				
				i++;
			}
		}
	}
}