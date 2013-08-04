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
			type(KeyboardEventKeyDown), keyCode(0) {}
		KeyboardEvent(KeyboardEventType _type, unsigned int _keyCode) :
			type(_type), keyCode(_keyCode) {}


		unsigned int keyCode; 
		KeyboardEventType type;
		bool shiftDown;
		bool ctrlDown;
		bool altDown;
	};

	class IKeyboardListener
	{
	public:
		virtual void OnKeyDown(const KeyboardEvent &e) = 0;
		virtual void OnKeyUp(const KeyboardEvent &e) = 0;
		virtual void OnKeyPress(const KeyboardEvent &e) = 0;
	};
};