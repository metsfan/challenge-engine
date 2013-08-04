#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class View;

	class UIEventArgs
	{
	public:
		UIEventArgs(std::string type) :
			mType(type) {}
		virtual ~UIEventArgs();

		const std::string& GetType() const { return mType; }

	private:
		std::string mType;
	};

	typedef std::function<void (View *sender, const UIEventArgs &e)> UIEventDelegate;
	typedef std::map<std::string, std::vector<UIEventDelegate>> TUIEventDelegateMap;

	class MouseEventArgs : public UIEventArgs
	{
	public:
		MouseEventArgs(std::string type, Point position) : 
			UIEventArgs(type), mPosition(position) {}

		const Point& GetPosition() const { return mPosition; }

	private:
		Point mPosition;
	};

	typedef std::function<void (View *sender, const MouseEvent &e)> MouseEventDelegate;
	typedef std::map<MouseEventType, std::vector<MouseEventDelegate>> TMouseEventDelegateMap;

	class KeyboardEventArgs : public UIEventArgs
	{
	public:
		KeyboardEventArgs(std::string type, int keyCode, bool shiftDown, bool ctrlDown, bool altDown) : 
			UIEventArgs(type), mKeyCode(keyCode), mShiftDown(shiftDown), 
			mCtrlDown(ctrlDown), mAltDown(altDown) {}

		
		int GetKeyCode() { return mKeyCode; }
		bool IsShiftDown() { return mShiftDown; }
		bool IsCtrlDown() { return mCtrlDown; }
		bool IsAltDown() { return mAltDown; }

	private:
		int mKeyCode;
		bool mShiftDown;
		bool mCtrlDown;
		bool mAltDown;
	};

	typedef std::function<void (View *sender, const KeyboardEvent &e)> KeyboardEventDelegate;
	typedef std::map<KeyboardEventType, std::vector<KeyboardEventDelegate>> TKeyboardEventDelegateMap;
};

