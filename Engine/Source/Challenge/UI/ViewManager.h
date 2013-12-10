 #include <Challenge/Challenge.h>
#include <Challenge/Input/InputManager.h>
#include <Challenge/Renderer/Renderer.h>
#include <Challenge/UI/UI.h>
#include <Challenge/Util/Image.h>

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

	class ViewManager
	{
		friend class View;

	public:
		ViewManager(const Size &screenSize);
		~ViewManager();

		void SetRootView(View *view);
		void SetFocusedView(View *view);
		void UnfocusView(View *view); 

		void AddImageToAtlas(Image *image);

		void Update(int deltaMillis);
		void Render(IGraphicsDevice *device);

		bool ProcessKeyboardEvent(const KeyboardEvent &e);
		bool ProcessMouseEvent(const MouseEvent &e);

	private:
		View *mRootView;
		View *mFocusedView;
		OrthoCamera *mCamera;
		IVertexBuffer *mVertexBuffer;

		void RegisterCoreUIClasses();
	};
};