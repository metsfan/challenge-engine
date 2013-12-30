#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>
#include <Challenge/Model/ModelManager.h>
#include <Challenge/Input/InputManager.h>
#include <Challenge/Physics/PhysicsManager.h>
#include <Challenge/Network/NetworkManager.h>
#include <Challenge/Audio/AudioManager.h>
#include <Challenge/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <Challenge/Disk/ResourceCache.h>
#include <Challenge/Model/Model.h>
#include <Challenge/Util/XML/XMLDocument.h>
#include <Challenge/Renderer/Effect.h>
#include "GameApplication.h"

namespace challenge
{
	static const std::string kDefaultFont = "arial";
	static const int kDefaultFontSize = 15;

	GameApplication* GameApplication::mGameInstance = NULL;
	Font* GameApplication::sDefaultFont = NULL;

	GameApplication::GameApplication(std::shared_ptr<Window> window, std::shared_ptr<IApplicationListener> listener) :
		mWindow(window),
		mListener(listener),
		mInitialized(false),
		mEventManager(NULL),
		mNetworkManager(NULL),
		mDatabaseManager(NULL),
		mInputManager(NULL),
		mModelManager(NULL)
		//mPrimitiveGenerator(NULL)
	{
		mGameInstance = NULL;
	}

	GameApplication::~GameApplication()
	{
		if (mListener) {
			mListener->OnApplicationDestroyed(this);
		}
	}

	bool GameApplication::Initialize()
	{
		//FontManager *fontManager = FontManager::GetInstance();
		//fontManager->AddFont("arial", "arial.ttf", 15);
		//fontManager->AddFont("arial", "arial.ttf", 18);

		/*mNetworkManager = new NetworkManager();
		if(!mNetworkManager->Initialize()) {
			return false;
		}

		mAudioManager = new AudioManager();
		if(!mAudioManager->Initialize()) {
			return false;
		}*/

		mInputManager = new InputManager();
		this->AddKeyboardListener(mWindow);
		this->AddMouseListener(mWindow);

		if (mListener) {
			mListener->OnApplicationInitialized(this);
		}

		return true;
	}

	void GameApplication::Update(uint32_t deltaMillis)
	{
		Dispatch::ExecuteQueue(Dispatch::MainQueue);

		mInputManager->Update();

		mWindow->Update(deltaMillis);

		if (mListener) {
			mListener->OnApplicationUpdate(this, deltaMillis);
		}
	}

	void GameApplication::PreRender()
	{
		mGraphicsDevice->PreRender();
	}

	void GameApplication::Render()
	{
		this->PreRender();

		if (mListener) {
			mListener->OnApplicationRender(this, mGraphicsDevice);
		}

		RenderState windowState;
		mWindow->Render(mGraphicsDevice, windowState, Frame());

		this->PostRender();
	}

	void GameApplication::PostRender()
	{
		mGraphicsDevice->PostRender();
	}

	IVertexBuffer* GameApplication::CreateVertexBuffer(void *buffer, int size)
	{
		IVertexBuffer *vertBuffer = NULL;
		RendererType type = GetRendererType();
		/*if(type == RendererTypeDX11) {
			vertBuffer = new VertexBufferDX11(buffer, size, D3D11_USAGE_DEFAULT, sizeof(ModelVertex));
		}*/

		return vertBuffer;
	}

	/* Renderer methods */
	void GameApplication::LoadShaderConfig(const std::wstring &filepath)
	{
		IGraphicsContext *context = mGraphicsDevice->GetContext();

		Asset file(filepath);
		if (!file.ReadData()) {
			return;
		}

		XMLDocument doc(&file);
		XMLNode& rootNode = doc.GetRootNode();

		TXMLNodeList &shaders = rootNode.GetFirstChild("Shaders").GetChildrenByName("Shader");
		for(XMLNode &node : shaders) {
			std::wstring filename = StringUtil::ToWide(node.GetAttributeString("filename"));
			std::string typeStr = node.GetAttributeString("type");

			ShaderType type;
			if(typeStr == "vertex") {
				type = ShaderTypeVertexShader;
			} else if(typeStr == "pixel") {
				type = ShaderTypePixelShader;
			} else if(typeStr == "domain") {
				type = ShaderTypeDomainShader;
			} else if(typeStr == "hull") {
				type = ShaderTypeHullShader;
			} else if(typeStr == "geometry") {
				type = ShaderTypeGeometryShader;
			} else if(typeStr == "compute") {
				type = ShaderTypeComputeShader;
			}

			IShader *shader = mGraphicsDevice->CreateShader(filename, type);
			shader->Load();

			context->AddShader(node.GetAttributeString("name"), shader);
		}

		TXMLNodeList &shaderPrograms = rootNode.GetFirstChild("ShaderPrograms").GetChildrenByName("ShaderProgram");
		for(XMLNode &programNode : shaderPrograms) {
			IShaderProgram *shaderProgram = mGraphicsDevice->CreateShaderProgram();

			TXMLNodeList &shaders = programNode.GetFirstChild("Shaders").GetChildrenByName("Shader");
			for(XMLNode &shaderNode : shaders) {
				shaderProgram->SetShader(context->GetShader(shaderNode.GetAttributeString("name")));
			}

			InputLayout *inputLayout = new InputLayout();
			TXMLNodeList &inputElements = programNode.GetFirstChild("InputLayout").GetChildrenByName("InputElement");
			for(XMLNode &node : inputElements) {
				std::string name = node.GetAttributeString("name");
				int size = node.GetAttributeInt("size");
				int offset = node.GetAttributeInt("offset");

				inputLayout->AddElement(name, size, offset);
			}

			shaderProgram->SetInputLayout(inputLayout);

			shaderProgram->Build();

			context->AddShaderProgram(programNode.GetAttributeString("name"), shaderProgram);
		}
		
	}

	void GameApplication::LoadEffectsConfig(const std::wstring &filepath)
	{
		IGraphicsContext *context = mGraphicsDevice->GetContext();

		Asset file(filepath);
		if (!file.ReadData()) {
			return;
		}

		XMLDocument doc(&file);
		XMLNode &rootNode = doc.GetRootNode();

		TXMLNodeList &effects = rootNode.GetChildrenByName("Effect");

		for(XMLNode &effectNode : effects) {
			Effect *effect = new Effect(effectNode.GetAttributeString("name"));

			TXMLNodeList &techniques = effectNode.GetChildrenByName("Technique");
			for(XMLNode &techniqueNode : techniques) {
				Technique *technique = new Technique(techniqueNode.GetAttributeString("name"));
				
				TXMLNodeList &passes = techniqueNode.GetChildrenByName("Pass");
				for(XMLNode &passNode : passes) {
					Pass *pass = new Pass();
					
					std::string shaderProgram = passNode.GetFirstChild("ShaderProgram").GetAttributeString("name");
					pass->SetShader(context->GetShaderProgram(shaderProgram));

					TXMLNodeList &globals = passNode.GetChildrenByName("Global");
					for(XMLNode &globalNode : globals) {
						std::string name = globalNode.GetAttributeString("name");
						std::string semantic = globalNode.GetAttributeString("semantic");
						std::string typeStr = globalNode.GetAttributeString("shader");

						ShaderType type;
						if(typeStr == "vertex") {
							type = ShaderTypeVertexShader;
						} else if(typeStr == "pixel") {
							type = ShaderTypePixelShader;
						} else if(typeStr == "domain") {
							type = ShaderTypeDomainShader;
						} else if(typeStr == "hull") {
							type = ShaderTypeHullShader;
						} else if(typeStr == "geometry") {
							type = ShaderTypeGeometryShader;
						} else if(typeStr == "compute") {
							type = ShaderTypeComputeShader;
						}

						pass->AddGlobal(name, semantic, type);
					}

					technique->AddPass(pass);
				}

				effect->AddTechnique(technique);
			}

			context->AddEffect(effect->GetName(), effect);
		}

	}

	/* Input Methods */

	void GameApplication::AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener)
	{
		mInputManager->AddKeyboardListener(listener);
	}

	void GameApplication::AddMouseListener(std::shared_ptr<IMouseListener> listener)
	{
		mInputManager->AddMouseListener(listener);
	}

	void GameApplication::ProcessKeyboardEvent(KeyboardEventType type, unsigned int keyCode)
	{
		mInputManager->ProcessKeyboardEvent(type, keyCode);
	}

	void GameApplication::ProcessMouseEvent(MouseEventType type, unsigned int button, const Point &position)
	{
		mInputManager->ProcessMouseEvent(type, button, position);
	}

	void GameApplication::ProcessMouseWheelEvent(MouseEventType type, int delta)
	{
		mInputManager->ProcessMouseWheelEvent(type, delta);
	}

	/* Factory Methods */

	Model* GameApplication::CreateModel(const std::wstring &filename)
	{
		std::hash<std::wstring> hashfn;
		long key = hashfn(filename);
		std::shared_ptr<ModelResource> resource = mModelCache.RetrieveResource(key);
		if(!resource) {
			ModelResource newResource;
			if(newResource.Initialize(filename)) {
				mModelCache.AddResource(key, newResource);
			} else {
				return NULL;
			}

			return new Model(mModelCache.RetrieveResource(key));
		}

		return new Model(resource);
	}

	Model* GameApplication::CreateModel(const std::wstring &name, const std::vector<ModelMesh *> &meshes)
	{
		std::hash<std::wstring> hashfn;
		long key = hashfn(name);
		std::shared_ptr<ModelResource> resource = mModelCache.RetrieveResource(key);
		if(!resource) {
			ModelResource newResource;
			if(newResource.Initialize(meshes)) {
				mModelCache.AddResource(key, newResource);
			} else {
				return NULL;
			}

			return new Model(mModelCache.RetrieveResource(key));
		}

		return new Model(resource);
	}

	Model* GameApplication::CreatePrimitive(PrimitiveShape type)
	{
		//if(mPrimitiveGenerator) {
			//return mPrimitiveGenerator->CreatePrimitive(type);
		//}

		return NULL;
	}

	/* GUI Methods */

	RendererType GameApplication::GetRendererType()
	{
		//return mWindow->GetRenderer()->GetType();
		return RendererTypeDX11();
	}

	GameApplication *GameApplication::GetInstance() 
	{
		/*if(mGameInstance == NULL) {
			mGameInstance = new GameApplication();
			if(!mGameInstance->Initialize()) {
				mGameInstance = NULL;
			}
		}*/
		return mGameInstance;
	}

	/*void GameApplication::ProcessMouseEvent(const MouseEvent &e)
	{
		bool handled = mViewManager->ProcessMouseEvent(e);
		if(!handled) {
			for(int i = 0; i < mMouseListeners.size(); i++) {
				std::shared_ptr<IMouseListener> listener = mMouseListeners[i].lock();
				if (listener) {
					listener->OnMouseEvent(e);
				}
			}
		}
	}

	void GameApplication::ProcessKeyboardEvent(const KeyboardEvent &e)
	{
		bool handled = mViewManager->ProcessKeyboardEvent(e);
		if(!handled) {
			for(int i = 0; i < mKeyboardListeners.size(); i++) {
				std::shared_ptr<IKeyboardListener> listener = mKeyboardListeners[i].lock();
				if(listener) {
					listener->OnKeyboardEvent(e);
				}
			}
		}
	}*/
}




