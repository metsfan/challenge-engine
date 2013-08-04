#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shader/ShaderProgram.h>
#include <Engine/Renderer/VertexBuffer.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Renderer/Window.h>
#include <Engine/Renderer/GraphicsContext.h>

namespace challenge
{
	class IGraphicsDevice
	{
	public:
		virtual IGraphicsContext* GetContext() = 0;
		virtual IWindow* GetWindow() = 0;

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
		BaseGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window);
		virtual ~BaseGraphicsDevice();

		IGraphicsContext* GetContext() { return mContext; }
		IWindow* GetWindow() { return mWindow; }

	protected:
		GRAPHICS_DEVICE_DESC& GetDesc() { return mDesc; }

		void SetGraphicsContext(IGraphicsContext *context) { mContext = context; }

	private:
		GRAPHICS_DEVICE_DESC mDesc;
		IWindow *mWindow;
		IGraphicsContext *mContext;
	};

	template <typename Renderer>
	class GraphicsDevice : public BaseGraphicsDevice {};

	template <typename Renderer>
	static IGraphicsDevice* CreateGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window)
	{
		return new GraphicsDevice<Renderer>(graphicsDesc, window);
	}
};


