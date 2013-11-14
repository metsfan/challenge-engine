#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Input/KeyboardListener.h>
#include <Engine/Input/MouseListener.h>
#include <Engine/UI/View.h>

namespace challenge
{
	template <typename Renderer>
	class GraphicsDevice;

	enum WindowVisibility
	{
		WindowVisible,
		WindowMinimized,
		WindowHidden
	};

	class IWindowInputReader
	{
	public:
		virtual void ProcessKeyboardEvent(KeyboardEventType type, unsigned int keyCode) = 0;
		virtual void ProcessMouseEvent(MouseEventType type, unsigned int button, Point position) = 0;
		virtual void ProcessMouseWheelEvent(MouseEventType type, int delta) = 0;
	};

	class GameApplication;
	class View;
	class IWindow;
	class IGraphicsDevice;
	class ViewManager;

	/*class IWindow
	{
	public:
		virtual bool Initialize() = 0;

		virtual void SetRootView(View *rootView) = 0;
		virtual void SetFocusedView(View *focusedView) = 0;
		virtual void UnfocusView(View *view) = 0;

		virtual void SetInputReader(IWindowInputReader *reader) = 0;

		virtual void SetWindowVisibility(WindowVisibility visibility) = 0;
		virtual WindowVisibility GetWindowVisibility() = 0;

		virtual void SetSize(Size size) = 0;
		virtual const Size& GetSize() const = 0;

		virtual void SetTitle(std::string title) = 0;
		virtual const std::string& GetTitle() const = 0;
	};*/

	class Window : public View,
					public IKeyboardListener,
					public IMouseListener
	{
	public:
		Window(Size size);
		virtual ~Window();

		virtual bool Initialize();

		void SetFocusedView(View *focusedView);
		void UnfocusView(View *view);

		void AddSubview(View *view);
		void RemoveSubview(View *view);

		virtual void SetWindowVisibility(WindowVisibility visibility) { mVisibility = visibility; }
		WindowVisibility GetWindowVisibility() { return mVisibility; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		/* IKeyboardListener methods */
		bool OnKeyboardEvent(const KeyboardEvent &e);

		/* IMouseListener methods */
		bool OnMouseEvent(const MouseEvent &e);

	private:
		WindowVisibility mVisibility;

		View *mFocusedView;
		View *mHoveredView;
		OrthoCamera *mCamera;

		void RegisterCoreUIClasses();
		void PostMouseEvent(MouseEventType type, View *view);
	};
};