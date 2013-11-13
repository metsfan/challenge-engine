#pragma once

#include <Engine/Challenge.h>

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
			shiftDown(false),
			ctrlDown(false),
			altDown(false),
			capslockOn(false)
		{}

		KeyboardEvent(KeyboardEventType _type, unsigned int _keyCode) :
			type(_type), 
			keyCode(_keyCode),
			shiftDown(false),
			ctrlDown(false),
			altDown(false),
			capslockOn(false)
		{}


		unsigned int keyCode; 
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