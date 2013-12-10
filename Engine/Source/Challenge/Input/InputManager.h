#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Input/KeyboardListener.h>
#include <Challenge/Input/MouseListener.h>
#include <Challenge/Util/Timer.h>
#include <Challenge/UI/Window.h>

namespace challenge
{
	typedef std::vector<IKeyboardListener *> TKeyboardListenerList;
	typedef std::vector<IMouseListener *> TMouseListenerList;
	
	enum SpecialKey
	{
		SpecialKeyShift = 0xF00F001,
		SpecialKeyCtrl = 0xF00F002,
		SpecialKeyAlt = 0xF00F003,
		SpecialKeyDelete = 0xF00F004,
		SpecialKeyLeft = 0xF00F005,
		SpecialKeyRight = 0xF00F006,
		SpecialKeyUp = 0xF00F007,
		SpecialKeyDown = 0xF00F008,
		SpecialKeyTab = 0xF00F009
	};

	class InputManager
	{
	public:
		InputManager();

		void AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener);
		void AddMouseListener(std::shared_ptr<IMouseListener> listener);

		void ProcessKeyboardEvent(KeyboardEventType type, unsigned int keyCode);
		void ProcessMouseEvent(MouseEventType type, unsigned int button, Point position);
		void ProcessMouseWheelEvent(MouseEventType type, int delta);

		std::vector<unsigned int> GetActiveKeys() { return mActiveKeys; }
		bool IsKeyDown() { return mKeyDown; }

		std::vector<unsigned int> GetActiveMouseButtons() { return mActiveMouseButtons; }
		bool IsMouseDown() { return mMouseDown; }
		Point GetMousePosition() { return mMousePosition; }

		void Update();

		/* Keyboard Events */
		void PostKeyboardEvent(const KeyboardEvent &e);

		/* Mouse Events */
		void PostMouseEvent(const MouseEvent &e);

	private:
		Timer *mKeyboardHoldTimer;
		std::vector<std::weak_ptr<IKeyboardListener>> mKeyboardListeners;
		std::vector<std::weak_ptr<IMouseListener>> mMouseListeners;

		std::vector<unsigned int> mActiveMouseButtons;
		std::vector<unsigned int> mActiveKeys;
		Point mMousePosition;
		bool mMouseDown;
		bool mMouseMoving;
		bool mKeyDown;

		bool mShiftDown;
		bool mAltDown;
		bool mCtrlDown;

		std::vector<KeyboardEvent> mKeyboardEventQueue;
		std::vector<MouseEvent> mMouseEventQueue;
	};
};