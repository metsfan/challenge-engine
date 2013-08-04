#pragma once

#include <Engine/Challenge.h>
#include <Engine/Event/EventData.h>

namespace challenge
{
	static std::string kMouseDownEventType = "mousedown";
	static std::string kMouseUpEventType = "mouseup";
	static std::string kMouseMoveEventType = "mousemove";

	class MouseEventData : public EventData
	{
	public:
		unsigned int button;
		Point position;

		MouseEventData(int timestamp) : EventData(timestamp) {}

		virtual std::string GetEventType() = 0;
	};

	class MouseDownEventData : public MouseEventData
	{
	public:
		MouseDownEventData(int timestamp) : MouseEventData(timestamp) {}
		std::string GetEventType() { return kMouseDownEventType; }
	};

	class MouseUpEventData : public MouseEventData
	{
	public:
		MouseUpEventData(int timestamp) : MouseEventData(timestamp) {}
		std::string GetEventType() { return kMouseUpEventType; }
	};

	class MouseMoveEventData : public MouseEventData
	{
	public:
		MouseMoveEventData(int timestamp) : MouseEventData(timestamp) {}
		std::string GetEventType() { return kMouseMoveEventType; }
	};
};