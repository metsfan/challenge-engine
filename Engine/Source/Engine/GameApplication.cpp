#include <Engine/Challenge.h>
#include <Engine/UI/UIManager.h>
#include <Engine/Model/ModelManager.h>
#include <Engine/Input/InputManager.h>
#include <Engine/Physics/PhysicsManager.h>
#include <Engine/Network/NetworkManager.h>
#include <Engine/Audio/AudioManager.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <Engine/Resource/ResourceCache.h>
#include <Engine/Model/Model.h>
#include <Engine/Util/XML/XMLDocument.h>
#include <Engine/Renderer/Effect.h>
#include "GameApplication.h"

namespace challenge
{
	static const std::string kDefaultFont = "arial";
	static const int kDefaultFontSize = 15;

	GameApplication* GameApplication::mGameInstance = NULL;
	Font* GameApplication::sDefaultFont = NULL;

	GameApplication::GameApplication(const Size &screenSize) :
		mScreenSize(screenSize),
		mInitialized(false),
		mEventManager(NULL),
		mNetworkManager(NULL),
		mDatabaseManager(NULL),
		mInputManager(NULL),
		mModelManager(NULL),
		mPrimitiveGenerator(NULL)
	{
		mGameInstance = NULL;
	}

	GameApplication::~GameApplication()
	{
		delete mWindow;
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

		mUIManager = new UIManager(mScreenSize);

		mPrimitiveGenerator = new PrimitiveGenerator(this);
		//mInputManager->AddKeyboardListener(mUIManager);
		//mInputManager->AddMouseListener(mUIManager);

		return true;
	}

	void GameApplication::Update()
	{
		//mPhysicsManager->OnUpdate();
		mInputManager->Update();
		mUIManager->Update(0);
	}

	void GameApplication::PreRender()
	{
		mGraphicsDevice->PreRender();
	}

	void GameApplication::Render()
	{
		mUIManager->Render(mGraphicsDevice);
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
	void GameApplication::LoadShaderConfig(const std::string &filepath)
	{
		std::string kShaderDir = "C:/gamedev/engine-dev/Engine/Debug/";
		IGraphicsContext *context = mGraphicsDevice->GetContext();

		XMLDocument doc(filepath);
		XMLNode& rootNode = doc.GetRootNode();

		TXMLNodeList &shaders = rootNode.GetFirstChild("Shaders").GetChildrenByName("Shader");
		for(XMLNode &node : shaders) {
			std::string filename = node.GetAttributeString("filename");
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

			IShader *shader = mGraphicsDevice->CreateShader(kShaderDir + filename, type);
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

	void GameApplication::LoadEffectsConfig(const std::string &filepath)
	{
		IGraphicsContext *context = mGraphicsDevice->GetContext();

		XMLDocument doc(filepath);
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

	void GameApplication::AddKeyboardListener(IKeyboardListener *pListener)
	{
		if(mInputManager) {
			mInputManager->AddKeyboardListener(pListener);
		}
	}

	void GameApplication::AddMouseListener(IMouseListener *pListener)
	{
		if(mInputManager) {
			mInputManager->AddMouseListener(pListener);
		}
	}

	/* Factory Methods */

	Model* GameApplication::CreateModel(const std::string &filename)
	{
		std::hash<std::string> hashfn;
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

	Model* GameApplication::CreateModel(const std::string &name, const std::vector<ModelMesh *> &meshes)
	{
		std::hash<std::string> hashfn;
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
		if(mPrimitiveGenerator) {
			return mPrimitiveGenerator->CreatePrimitive(type);
		}

		return NULL;
	}

	/* GUI Methods */
	void GameApplication::SetRootView(View *view)
	{
		mUIManager->SetRootView(view);
	}

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
}




