#pragma once

namespace challenge
{
	enum MouseEventType 
	{
		MouseEventMouseDown,
		MouseEventMouseUp,
		MouseEventMouseMove,
		MouseEventMouseDrag,
		MouseEventMouseClick,
		MouseEventMouseDblClick,
		MouseEventMouseWheelMove
	};

	struct MouseEvent 
	{
		MouseEvent() :
			type(MouseEventMouseDown), button(0), position(Point(0, 0)),
			wheelDelta(0), shiftDown(false), ctrlDown(false), altDown(false) {}
		MouseEvent(MouseEventType _type, unsigned int _button, Point _position) :
			type(_type), button(_button), position(_position),
			mouseDown(false), wheelDelta(0), 
			shiftDown(false), ctrlDown(false), altDown(false) {}

		MouseEventType type;
		unsigned int button;
		Point position; 
		bool mouseDown;
		int wheelDelta;
		bool shiftDown;
		bool ctrlDown;
		bool altDown;
	};
	
	typedef enum {
		MouseButtonLeft,
		MouseButtonRight
	} MouseButton;

	class IMouseListener
	{
	public:
		virtual void OnMouseDown(const MouseEvent &e) = 0;
		virtual void OnMouseUp(const MouseEvent &e) = 0;
		virtual void OnMouseMove(const MouseEvent &e) = 0;
		virtual void OnMouseClick(const MouseEvent &e) = 0;
		virtual void OnMouseDblClick(const MouseEvent &e) = 0;
		virtual void OnMouseWheelMove(const MouseEvent &e) = 0;
	};
};