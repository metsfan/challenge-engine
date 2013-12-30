#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>
#include <Challenge/Renderer/VertexBuffer.h>
#include <Challenge/Renderer/GraphicsDevice.h>
#include <Challenge/Disk/ResourceCache.h>
#include <Challenge/Util/PrimitiveGenerator.h>
#include <Challenge/Font/FontTypes.h>
#include <Challenge/Input/KeyboardListener.h>
#include <Challenge/Input/MouseListener.h>

namespace challenge 
{
	class ViewManager;
	class ModelManager;
	class InputManager;
	class PhysicsManager;
	class EventManager;
	class DatabaseManager;
	class NetworkManager;
	class AudioManager;

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
		ViewManager *GetViewManager() const { return mViewManager; }
		ModelManager *GetModelManager() const { return mModelManager; }
		InputManager *GetInputManager() const { return mInputManager; }
		PhysicsManager *GetPhysicsManager() const { return mPhysicsManager; }
		EventManager *GetEventManager() const { return mEventManager; }
		DatabaseManager *GetDatabaseManager() const { return mDatabaseManager; }
		NetworkManager *GetNetworkManager() const { return mNetworkManager; }
		AudioManager *GetAudioManager() const { return mAudioManager; }

		const Size& GetScreenSize() { return mScreenSize; }

		void Update(uint32_t deltaMillis);

		void PreRender();
		void Render();
		void PostRender();

		static GameApplication *GetInstance();

		IVertexBuffer* CreateVertexBuffer(void *buffer, int size);
		RendererType GetRendererType();

		/* Renderer methods */
		void LoadShaderConfig(const std::wstring &filepath);
		void LoadEffectsConfig(const std::wstring &filepath);

		/* Input methods */
		void AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener);
		void AddMouseListener(std::shared_ptr<IMouseListener> listener);

		void ProcessKeyboardEvent(KeyboardEventType type, unsigned int keyCode);
		void ProcessMouseEvent(MouseEventType type, unsigned int button, const Point &position);
		void ProcessMouseWheelEvent(MouseEventType type, int delta);

		/* Factory methods */
		Model* CreateModel(const std::wstring &filename);
		Model* CreateModel(const std::wstring &name, const std::vector<ModelMesh *> &meshes);
		Model* CreatePrimitive(PrimitiveShape type);

		/* GUI Methods */

		void ProcessMouseEvent(const MouseEvent &e);
		void ProcessKeyboardEvent(const KeyboardEvent &e);

	protected:
		std::shared_ptr<Window> mWindow;
		std::shared_ptr<IApplicationListener> mListener;

		IGraphicsDevice *mGraphicsDevice;
		ViewManager *mViewManager;
		ModelManager *mModelManager;
		InputManager *mInputManager;
		PhysicsManager *mPhysicsManager;
		EventManager *mEventManager;
		DatabaseManager *mDatabaseManager;
		NetworkManager *mNetworkManager;
		AudioManager *mAudioManager;

		ResourceCache<ModelResource> mModelCache;
		//PrimitiveGenerator *mPrimitiveGenerator;

		Size mScreenSize;

		bool mInitialized;
		
		static GameApplication *mGameInstance;
		static Font* sDefaultFont;

		void StartRunning() { mApplicationRunning = true; }

	private:
		bool mApplicationRunning;

		void LoadStrings();
	};
};