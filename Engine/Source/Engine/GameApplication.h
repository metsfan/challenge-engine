#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Window.h>
#include <Engine/Scene/Nodes/CameraNode.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <Engine/Renderer/GraphicsDevice.h>
#include <Engine/Resource/ResourceCache.h>
#include <Engine/Util/PrimitiveGenerator.h>

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

	class IKeyboardListener;
	class IMouseListener;

	class Model;
	class ModelMesh;
	class ModelResource;

	typedef std::function<void(int)> AppCallback;

	class GameApplication
	{
	public:
		GameApplication(void);
		virtual ~GameApplication(void);

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
		void AddKeyboardListener(IKeyboardListener *pListener);
		void AddMouseListener(IMouseListener *pListener);

		/* Factory methods */
		Model* CreateModel(const std::string &filename);
		Model* CreateModel(const std::string &name, const std::vector<ModelMesh *> &meshes);
		Model* CreatePrimitive(PrimitiveShape type);

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

		bool mInitialized;
		
		static GameApplication *mGameInstance;

		void StartRunning() { mApplicationRunning = true; }

	private:
		bool mApplicationRunning;
	};
};