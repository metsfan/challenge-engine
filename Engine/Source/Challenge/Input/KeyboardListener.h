#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	enum KeyboardEventType 
	{
		KeyboardEventKeyDown,
		KeyboardEventKeyUp,
		KeyboardEventKeyPress
	};

	struct KeyboardEvent
	{
		KeyboardEvent() :
			type(KeyboardEventKeyDown), 
			keyCode(0),
			virtualKeyCode(0),
			shiftDown(false),
			ctrlDown(false),
			altDown(false),
			capslockOn(false)
		{}

		KeyboardEvent(KeyboardEventType _type, uint32_t _keyCode, uint32_t _virtualKeyCode) :
			type(_type),
			keyCode(_keyCode),
			virtualKeyCode(_virtualKeyCode),
			shiftDown(false),
			ctrlDown(false),
			altDown(false),
			capslockOn(false)
		{}


		uint32_t keyCode;
		uint32_t virtualKeyCode;
		KeyboardEventType type;
		bool shiftDown;
		bool ctrlDown;
		bool altDown;
		bool capslockOn;
	};

	class IKeyboardListener
	{
	public:
		virtual bool OnKeyboardEvent(const KeyboardEvent &e) = 0;
	};
};