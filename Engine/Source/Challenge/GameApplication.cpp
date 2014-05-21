#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>
#include <Challenge/Input/InputManager.h>
#include <Challenge/Network/Network.h>
#include <Challenge/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <Challenge/Disk/ResourceCache.h>
#include <Challenge/Model/Model.h>
#include <Challenge/Util/XML/XMLDocument.h>
#include <Challenge/Renderer/Effect.h>
#include <Challenge/Font/FontManager.h>
#include "GameApplication.h"

namespace challenge
{
	static const std::string kDefaultFont = "arial";
	static const int kDefaultFontSize = 15;

	GameApplication::GameApplication(std::shared_ptr<Window> window, std::shared_ptr<IApplicationListener> listener) :
		mWindow(window),
		mListener(listener),
		mInitialized(false),
		mInputManager(NULL)
	{
	}

	GameApplication::~GameApplication()
	{
		if (mListener) {
			mListener->OnApplicationDestroyed(this);
		}
	}

	bool GameApplication::Initialize()
	{
		mInputManager = new InputManager();
		this->AddKeyboardListener(mWindow);
		this->AddMouseListener(mWindow);

		FontManager::LoadSystemFont("win32");

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

			TXMLNodeList &globals = node.GetChildrenByName("Global");
			for (XMLNode &globalNode : globals) {
				std::string name = globalNode.GetAttributeString("name");
				std::string semantic = globalNode.GetAttributeString("semantic");
				std::string typeStr = globalNode.GetAttributeString("shader");
				std::string dataTypeStr = globalNode.GetAttributeString("type");
				int num = 1;
				if (globalNode.HasAttribute("num")) {
					num = globalNode.GetAttributeInt("num");
				}

				ShaderType type;
				if (typeStr == "vertex") {
					type = ShaderTypeVertexShader;
				}
				else if (typeStr == "pixel") {
					type = ShaderTypePixelShader;
				}
				else if (typeStr == "domain") {
					type = ShaderTypeDomainShader;
				}
				else if (typeStr == "hull") {
					type = ShaderTypeHullShader;
				}
				else if (typeStr == "geometry") {
					type = ShaderTypeGeometryShader;
				}
				else if (typeStr == "compute") {
					type = ShaderTypeComputeShader;
				}

				ShaderVarType dataType;
				if (dataTypeStr == "vec2") {
					dataType = ShaderVarVec2;
				}
				else if (dataTypeStr == "vec3") {
					dataType = ShaderVarVec3;
				}
				else if (dataTypeStr == "vec4") {
					dataType = ShaderVarVec4;
				}
				else if (dataTypeStr == "mat2") {
					dataType = ShaderVarMat2;
				}
				else if (dataTypeStr == "mat3") {
					dataType = ShaderVarMat3;
				}
				else if (dataTypeStr == "mat4") {
					dataType = ShaderVarMat4;
				}
				else if (dataTypeStr == "float") {
					dataType = ShaderVarFloat;
				}
				else if (dataTypeStr == "int") {
					dataType = ShaderVarInt;
				}
				else if (dataTypeStr == "texture") {
					dataType = ShaderVarTexture;
				}

				int index = context->RegisterGlobal(semantic);
				shader->AddGlobalVariable(index, name, semantic, dataType, num);
			}

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

	void GameApplication::ProcessKeyboardEvent(KeyboardEventType type, uint32_t keyCode)
	{
		mInputManager->ProcessKeyboardEvent(type, keyCode, keyCode);
	}

	void GameApplication::ProcessKeyboardEvent(KeyboardEventType type, uint32_t keyCode, uint32_t virtualKeyCode)
	{
		mInputManager->ProcessKeyboardEvent(type, keyCode, virtualKeyCode);
	}

	void GameApplication::ProcessMouseEvent(MouseEventType type, unsigned int button, const Point &position)
	{
		if (type == MouseEventMouseMove) {
			Cursor::SetPosition(position);
		}

		mInputManager->ProcessMouseEvent(type, button, position);
	}

	void GameApplication::ProcessMouseWheelEvent(MouseEventType type, int delta)
	{
		mInputManager->ProcessMouseWheelEvent(type, delta);
	}
}




