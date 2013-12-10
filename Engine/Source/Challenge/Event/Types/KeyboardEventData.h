#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Event/EventData.h>

namespace challenge
{
	static std::string kKeyDownEventType = "keydown";
	static std::string kKeyUpEventType = "keyup";

	class KeyboardEventData : public EventData
	{
	public:
		char keyCode;
		bool shiftKey, ctrlKey, altKey;

		KeyboardEventData(int timestamp) : EventData(timestamp) {}

		virtual std::string GetEventType() = 0;
	};

	class KeyDownEventData : public KeyboardEventData
	{
	public:
		KeyDownEventData(int timestamp) : KeyboardEventData(timestamp) {}
		std::string GetEventType() { return kKeyDownEventType; }
	};

	class KeyUpEventData : public KeyboardEventData
	{
	public:
		KeyUpEventData(int timestamp) : KeyboardEventData(timestamp) {}
		std::string GetEventType() { return kKeyUpEventType; }
	};
};