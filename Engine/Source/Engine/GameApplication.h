#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Window.h>
#include <Engine/Scene/Nodes/CameraNode.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <Engine/Renderer/GraphicsDevice.h>
#include <Engine/Disk/ResourceCache.h>
#include <Engine/Util/PrimitiveGenerator.h>
#include <Engine/Font/FontTypes.h>
#include <Engine/Input/KeyboardListener.h>
#include <Engine/Input/MouseListener.h>

namespace challenge 
{
	class UIManager;
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

	typedef std::function<void(int)> AppCallback;

	class GameApplication : public IKeyboardListener,
							public IMouseListener
	{
	public:
		GameApplication(const Size &screenSize);
		virtual ~GameApplication();

		virtual bool Initialize();
		IWindow* GetWindow() { return mWindow; }

		bool IsInitialized() { return mInitialized; }
		
		virtual void RunMainLoop(AppCallback updateCallback, AppCallback renderCallback) = 0;
		bool IsRunning() { return mApplicationRunning; }
		void Exit() { mApplicationRunning = false; }

		IGraphicsDevice* GetGraphicsDevice() { return mGraphicsDevice; }
		UIManager *GetUIManager() const { return mUIManager; }
		ModelManager *GetModelManager() const { return mModelManager; }
		InputManager *GetInputManager() const { return mInputManager; }
		PhysicsManager *GetPhysicsManager() const { return mPhysicsManager; }
		EventManager *GetEventManager() const { return mEventManager; }
		DatabaseManager *GetDatabaseManager() const { return mDatabaseManager; }
		NetworkManager *GetNetworkManager() const { return mNetworkManager; }
		AudioManager *GetAudioManager() const { return mAudioManager; }

		const Size& GetScreenSize() { return mScreenSize; }

		void SetMainCamera(CameraNode *camera) { mMainCamera = camera; }
		CameraNode* GetMainCamera() { return mMainCamera; }

		void Update();
		void PreRender();
		void Render();
		void PostRender();

		static GameApplication *GetInstance();

		IVertexBuffer* CreateVertexBuffer(void *buffer, int size);
		RendererType GetRendererType();

		/* Renderer methods */
		void LoadShaderConfig(const std::string &filepath);
		void LoadEffectsConfig(const std::string &filepath);

		/* Input methods */
		void AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener);
		void AddMouseListener(std::shared_ptr<IMouseListener> listener);

		/* Factory methods */
		Model* CreateModel(const std::string &filename);
		Model* CreateModel(const std::string &name, const std::vector<ModelMesh *> &meshes);
		Model* CreatePrimitive(PrimitiveShape type);

		/* GUI Methods */
		void SetRootView(View *view);

		/* IKeyboardListener methods */
		void OnKeyDown(const KeyboardEvent &e);
		void OnKeyUp(const KeyboardEvent &e);
		void OnKeyPress(const KeyboardEvent &e);

		/* IMouseListener methods */
		void OnMouseDown(const MouseEvent &e);
		void OnMouseUp(const MouseEvent &e);
		void OnMouseMove(const MouseEvent &e);
		void OnMouseClick(const MouseEvent &e);
		void OnMouseDblClick(const MouseEvent &e);
		void OnMouseWheelMove(const MouseEvent &e);

	protected:
		IGraphicsDevice *mGraphicsDevice;
		IWindow *mWindow;
		UIManager *mUIManager;
		ModelManager *mModelManager;
		InputManager *mInputManager;
		PhysicsManager *mPhysicsManager;
		EventManager *mEventManager;
		DatabaseManager *mDatabaseManager;
		NetworkManager *mNetworkManager;
		AudioManager *mAudioManager;

		ResourceCache<ModelResource> mModelCache;
		PrimitiveGenerator *mPrimitiveGenerator;

		CameraNode *mMainCamera;

		Size mScreenSize;

		bool mInitialized;
		
		static GameApplication *mGameInstance;
		static Font* sDefaultFont;

		void StartRunning() { mApplicationRunning = true; }

	private:
		bool mApplicationRunning;
		std::vector<std::weak_ptr<IKeyboardListener>> mKeyboardListeners;
		std::vector<std::weak_ptr<IMouseListener>> mMouseListeners;

		void ProcessMouseEvent(const MouseEvent &e);
		void ProcessKeyboardEvent(const KeyboardEvent &e);
	};
};