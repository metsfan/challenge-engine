#pragma once

#include <Engine/Challenge.h>
#include <Engine/Input/KeyboardListener.h>
#include <Engine/Input/MouseListener.h>
#include <Engine/Util/Timer.h>
#include <Engine/Renderer/Window.h>

namespace challenge
{
	typedef std::vector<IKeyboardListener *> TKeyboardListenerList;
	typedef std::vector<IMouseListener *> TMouseListenerList;
	
	static const int kShiftKey = 16;
	static const int kCtrlKey = 17;
	static const int kAltKey = 18;

	class InputManager : public IWindowInputReader
	{
	public:
		InputManager();

		void AddKeyboardListener(IKeyboardListener *pListener);
		void AddMouseListener(IMouseListener *pListener);

		/* IWindowInputReader methods */
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
		void KeyDown(const KeyboardEvent &e);
		void KeyUp(const KeyboardEvent &e);
		void KeyPress(const KeyboardEvent &e);

		/* Mouse Events */
		void MouseDown(const MouseEvent &e);
		void MouseUp(const MouseEvent &e);
		void MouseMove(const MouseEvent &e);
		void MouseClick(const MouseEvent &e);
		void MouseDblClick(const MouseEvent &e);
		void MouseWheelMove(const MouseEvent &e);

	private:
		CTimer *mKeyboardHoldTimer;
		TKeyboardListenerList mKeyboardListeners;
		TMouseListenerList mMouseListeners;
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