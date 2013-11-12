#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Input/KeyboardListener.h>
#include <Engine/Input/MouseListener.h>

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

	class IWindowListener
	{
	public:
		virtual void OnWindowInitialized(IWindow *window, GameApplication *app) = 0;
		virtual void OnWindowDestroyed(IWindow *window, GameApplication *app) = 0;
		virtual void OnWindowUpdate(IWindow *window, GameApplication *app, uint32_t deltaMillis) = 0;
		virtual void OnWindowDraw(IWindow *window, GameApplication *app, IGraphicsDevice *device) = 0;
	};

	class IWindow
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
	};

	class BaseWindow : public IWindow
	{
	public:
		BaseWindow(std::string title, Size size, IWindowListener *listener);
		virtual ~BaseWindow();

		void SetRootView(View *rootView);
		void SetFocusedView(View *focusedView);
		void UnfocusView(View *view);

		void SetInputReader(IWindowInputReader *reader) { mInputReader = reader; }

		virtual void SetWindowVisibility(WindowVisibility visibility) { mVisibility = visibility; }
		WindowVisibility GetWindowVisibility() { return mVisibility; }

		virtual void SetSize(Size size) { mSize = size; }
		const Size& GetSize() const { return mSize; }

		virtual void SetTitle(std::string title) { mTitle = title; }
		virtual const std::string& GetTitle() const { return mTitle; }

	protected:
		IWindowInputReader* GetInputReader() { return mInputReader; }

		virtual void WindowInitialized(GameApplication *app);
		virtual void WindowDestroyed();
		virtual void WindowUpdate(uint32_t deltaMillis);
		virtual void WindowDraw();

	private:
		Size mSize;
		std::string mTitle;
		WindowVisibility mVisibility;
		IWindowInputReader *mInputReader;
		ViewManager *mViewManager;
		IWindowListener *mListener;
		GameApplication *mApplication;
	};

	template <typename Platform>
	class Window : public BaseWindow {};
};