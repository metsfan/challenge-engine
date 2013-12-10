#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class IEventData
	{
	public:
		virtual std::string GetEventType() = 0;
		virtual int GetTimestamp() = 0;
	};

	class EventData : public IEventData
	{
	public:
		EventData(int timestamp) { mTimestamp = timestamp; }

		virtual std::string GetEventType() { return "base_event"; }
		virtual int GetTimestamp() { return mTimestamp; }

	private:
		int mTimestamp;
	};
};