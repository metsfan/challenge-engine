#pragma once

#include <Engine/Challenge.h>
#include <Engine/Event/EventData.h>

namespace challenge
{
	class IEventListener
	{
	public:
		explicit IEventListener() {};
		virtual ~IEventListener() {};

		virtual char const * GetName(void) = 0;
		virtual bool HandleEvent(IEventData *data) = 0
		{
			return true;
		}
	};

	typedef std::vector<IEventListener *> TEventListenerList;
	typedef std::map<std::string, TEventListenerList> TEventListenerMap;
	typedef std::list<IEventData *> TEventQueue;

	const int numEventQueues = 2;

	class EventManager
	{
	public:
		static std::string wildcardEvent;

		EventManager();

		void RegisterEvent(std::string pEventName, IEventListener *pListener);
		void UnregisterEvent(std::string pEventName, IEventListener *pListener);

		void FireEvent(IEventData *data);
		void QueueEvent(IEventData *data);
		
		void Tick(unsigned long maxMillis);
		void Abort(std::string pEventName, bool removeAll);

	private:
		TEventListenerMap mListeners;
		TEventQueue mQueues[numEventQueues];
		int mActiveQueue;
	};
};
