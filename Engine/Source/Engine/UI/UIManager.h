#include <Engine/Challenge.h>
#include <Engine/Input/InputManager.h>
#include <Engine/UI/UI.h>
//#include <Engine/Renderer/Shader/DX11/HLSLProgram.h>
//#include <Engine/Util/TextureAtlas.h>
#include <Engine/Util/Image.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace challenge
{
	static D3D11_INPUT_ELEMENT_DESC controlVertexDesc[3] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	struct ControlVertex
	{
		float position[3];
		float texel[2];
		float padding[3];
	};

	class UIManager : public IKeyboardListener, public IMouseListener
	{
		friend class View;

	public:
		UIManager(void);
		~UIManager(void);

		void AddRootControl(View *control);
		void AddControl(View *control);
		void AddImageToAtlas(Image *image);
		//TextureAtlasEntry GetImageForKey(std::string key);

		void Update(int deltaMillis);
		void Render();

		static UIManager *GetDefaultManager();

		//GLSLProgram* GetShader() { return mShader; }
		//HLSLProgram* GetShader() { return mShader; }

		void ProcessKeyboardEvent(const KeyboardEvent &e);
		void ProcessMouseEvent(const MouseEvent &e);

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

	private:
		TControlList mRootControls;
		int mControlCount;
		//GLSLProgram *mShader;
		//HLSLProgram *mShader;
		glm::mat4 mProjectionMatrix;
		IVertexBuffer *mVertexBuffer;

		//CTextureAtlas *mImageAtlas;
		//CTextureAtlas *mTextAtlas;
	};
};