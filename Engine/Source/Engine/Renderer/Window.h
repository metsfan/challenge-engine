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
	};

	class IWindow
	{
	public:
		virtual bool Initialize() = 0;

		virtual void SetInputReader(IWindowInputReader *reader) = 0;

		virtual void SetWindowVisibility(WindowVisibility visibility) = 0;
		virtual WindowVisibility GetWindowVisibility() = 0;

		virtual void SetSize(Size size) = 0;
		virtual const Size& GetSize() const = 0;

		virtual void SetTitle(std::string title) = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void AttachToDevice(GraphicsDevice<RendererTypeDX11> *device) = 0;
		virtual void AttachToDevice(GraphicsDevice<RendererTypeOpenGL> *device) = 0;
	};

	class BaseWindow : public IWindow
	{
	public:
		BaseWindow(std::string title, Size size);
		virtual ~BaseWindow();

		void SetInputReader(IWindowInputReader *reader) { mInputReader = reader; }

		virtual void SetWindowVisibility(WindowVisibility visibility) { mVisibility = visibility; }
		WindowVisibility GetWindowVisibility() { return mVisibility; }

		virtual void SetSize(Size size) { mSize = size; }
		const Size& GetSize() const { return mSize; }

		virtual void SetTitle(std::string title) { mTitle = title; }
		virtual const std::string& GetTitle() const { return mTitle; }

		virtual void AttachToDevice(GraphicsDevice<RendererTypeDX11> *device)
		{
			throw "Unsupported Renderer!";
		}

		virtual void AttachToDevice(GraphicsDevice<RendererTypeOpenGL> *device) 
		{
			throw "Unsupported Renderer!";
		}

	protected:
		IWindowInputReader* GetInputReader() { return mInputReader; }

	private:
		Size mSize;
		std::string mTitle;
		WindowVisibility mVisibility;
		IWindowInputReader *mInputReader;
	};

	template <typename Platform>
	class Window : public BaseWindow {};
};