#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shader/ShaderProgram.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/UI/Window.h>
#include <Engine/Renderer/GraphicsContext.h>

namespace challenge
{
	enum BlendParam
	{
		BlendZero,
		BlendOne,
		BlendSrcColor,
		BlendOneMinusSrcColor,
		BlendSrcAlpha,
		BlendOneMinusSrcAlpha,
		BlendDstAlpha,
		BlendOneMinusDstAlpha,
		BlendDstColor,
		BlendOneMinusDstColor,
		BlendSrcAlphaSaturate,
		BlendBlendFactor,
		BlendOneMinusBlendFactor,
		BlendSrc1Color,
		BlendOneMinusSrc1Color,
		BlendSrc1Alpha,
		BlendOneMinusSrc1Alpha
	};

	enum DepthFunc
	{
		DepthFuncAlways,
		DepthFuncNever,
		DepthFuncLess,
		DepthFuncLessEqual,
		DpethFuncGreater,
		DepthFuncGreaterEqual,
		DepthFuncEqual,
		DepthFuncNotEqual,
	};


	enum GraphicsState
	{
		AlphaBlending,
		DepthTest,
		ScissorTest
	};

	class IGraphicsDevice
	{
	public:
		virtual IGraphicsContext* GetContext() = 0;

		virtual void EnableState(GraphicsState state) = 0;
		virtual void DisableState(GraphicsState state) = 0;
		virtual void SetBlendingFunction(BlendParam source, BlendParam destination) = 0;
		virtual void SetDepthFunction(DepthFunc function) = 0;

		virtual void PushScissorRect(int x, int y, int width, int height) = 0;
		virtual void PopScissorRect() = 0;

		virtual IShader* CreateShader(std::string filename, ShaderType type) = 0;
		virtual IShaderProgram* CreateShaderProgram() = 0;

		virtual IVertexBuffer* CreateVertexBuffer(VERTEX_BUFFER_DESC desc) = 0;

		//virtual ITexture1D* CreateTexture1D() = 0;
		virtual ITexture* CreateTexture2D(TEXTURE_DESC &desc) = 0;
		//virtual ITexture2DArray* CreateTexture2DArray() = 0;
		//virtual ITexture3D* CreateTexture3D() = 0;
		virtual ITexture* CreateTextureCube(TEXTURE_DESC &desc) = 0;


		virtual void PreRender() = 0;
		virtual void PostRender() = 0;

		virtual void Draw(PrimitiveType type, int count, int start) = 0;
	};

	class BaseGraphicsDevice : public IGraphicsDevice
	{
	public:
		BaseGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, const Size &screenSize);
		virtual ~BaseGraphicsDevice();

		IGraphicsContext* GetContext() { return mContext; }

		void EnableState(GraphicsState state);
		void DisableState(GraphicsState state);

	protected:
		GRAPHICS_DEVICE_DESC& GetDesc() { return mDesc; }

		void SetGraphicsContext(IGraphicsContext *context) { mContext = context; }

	private:
		GRAPHICS_DEVICE_DESC mDesc;
		IGraphicsContext *mContext;
		Size mScreenSize;

		virtual void SetAlphaBlending(bool state) = 0;
		virtual void SetDepthTest(bool state) = 0;
		virtual void SetScissorTest(bool state) = 0;
	};

	template <typename Renderer>
	class GraphicsDevice : public BaseGraphicsDevice {};

	template <typename Renderer>
	static IGraphicsDevice* CreateGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, HWND window, const Size &screenSize)
	{
		return new GraphicsDevice<Renderer>(graphicsDesc, window, screenSize);
	}
};


