#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>
#include <Challenge/Renderer/VertexBuffer.h>
#include <Challenge/Renderer/GraphicsDevice.h>
#include <Challenge/Disk/ResourceCache.h>
#include <Challenge/Util/PrimitiveGenerator.h>
#include <Challenge/Font/Types.h>
#include <Challenge/Input/KeyboardListener.h>
#include <Challenge/Input/MouseListener.h>

namespace challenge 
{
	class InputManager;
	class ScriptEngine;

	class Model;
	class ModelMesh;
	class ModelResource;

	class Font;

	class View;

	class GameApplication;

	class IApplicationListener
	{
	public:
		virtual void OnApplicationInitialized(GameApplication *app) = 0;
		virtual void OnApplicationDestroyed(GameApplication *app) = 0;
		virtual void OnApplicationUpdate(GameApplication *app, uint32_t deltaMillis) = 0;
		virtual void OnApplicationRender(GameApplication *app, IGraphicsDevice *device) = 0;
	};

	typedef std::function<void(int)> AppCallback;

	class GameApplication
	{
	public:
		GameApplication(std::shared_ptr<Window> window, std::shared_ptr<IApplicationListener> listener);
		virtual ~GameApplication();

		virtual bool Initialize();
		std::shared_ptr<Window> GetWindow() { return mWindow; }

		bool IsInitialized() { return mInitialized; }
		
		bool IsRunning() { return mApplicationRunning; }
		void Exit() { mApplicationRunning = false; }

		IGraphicsDevice* GetGraphicsDevice() { return mGraphicsDevice; }

		const Size& GetScreenSize() { return mScreenSize; }

		void Update(uint32_t deltaMillis);

		void PreRender();
		void Render();
		void PostRender();

		/* Renderer methods */
		void LoadShaderConfig(const std::wstring &filepath);
		void LoadEffectsConfig(const std::wstring &filepath);

		/* Input methods */
		void AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener);
		void AddMouseListener(std::shared_ptr<IMouseListener> listener);

		void ProcessKeyboardEvent(KeyboardEventType type, uint32_t keyCode);
		void ProcessKeyboardEvent(KeyboardEventType type, uint32_t keyCode, uint32_t virtualKeyCode);
		void ProcessMouseEvent(MouseEventType type, unsigned int button, const Point &position);
		void ProcessMouseWheelEvent(MouseEventType type, int delta);

		/* GUI Methods */
		void ProcessMouseEvent(const MouseEvent &e);
		void ProcessKeyboardEvent(const KeyboardEvent &e);

	protected:
		std::shared_ptr<Window> mWindow;
		std::shared_ptr<IApplicationListener> mListener;

		IGraphicsDevice *mGraphicsDevice;
		InputManager *mInputManager;

		Size mScreenSize;

		bool mInitialized;
		
		static ScriptEngine *sScriptEngine;

		void StartRunning() { mApplicationRunning = true; }

	private:
		bool mApplicationRunning;

		void LoadStrings();
	};
};