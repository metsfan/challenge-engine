#pragma once

#include <Engine/Challenge.h>
#include <gl/glew.h>
#include <Engine/Util/Image.h>

namespace challenge
{
	enum TextureFormat
	{
		TextureFormatInt32,
		TextureFormatFloat32,
		TextureFormatRGBA,
		TextureFormatBGRA,
		TextureFormatAlpha
	};

	static const int TextureFormatNumComponents[] = 
	{
		1, //TextureFormatInt32,
		1, //TextureFormatFloat32
		4, //TextureFormatRGBA
		4, //TextureFormatBGRA
		1  //TextureFormatAlpha
	};

	enum TextureFilter
	{
		TextureFilterNearest,
		TextureFilterLinear
	};

	enum TextureClamp
	{
		TextureClampEdge,
		TextureClampWrap
	};

	struct TEXTURE_DESC
	{
		TEXTURE_DESC() :
			Format(TextureFormatBGRA),
			InternalFormat(TextureFormatBGRA),
			Min(TextureFilterLinear),
			Mag(TextureFilterLinear),
			ClampS(TextureClampEdge),
			ClampT(TextureClampEdge)
		{
		}

		TextureFormat Format;
		TextureFormat InternalFormat;
		TextureFilter Min;
		TextureFilter Mag;
		TextureClamp ClampS;
		TextureClamp ClampT;
	};

	class ITexture 
	{
	public:
		virtual bool Initialize(Image *image) = 0;
		virtual bool Initialize(const BYTE *buffer, const Size &size) = 0;
		virtual bool Initialize(std::vector<const BYTE *> &buffers, const Size &size) = 0;

		virtual const Size& GetSize() = 0;
		virtual bool IsLoaded() = 0;
	};

	class BaseTexture : public ITexture
	{
	public:
		BaseTexture(void);
		virtual ~BaseTexture(void);

		virtual bool Initialize(Image *image);
		virtual bool Initialize(const BYTE *buffer, const Size &size);
		virtual bool Initialize(std::vector<const BYTE *> &buffers, const Size &size);

		const Size& GetSize() { return mSize; }
		bool IsLoaded() { return mLoaded; }

	private:
		Size mSize;
		bool mLoaded;

		virtual bool LoadTextureData(std::vector<const BYTE *> &buffers) = 0;
	};

	template <typename Renderer>
	class Texture : public BaseTexture {};

	template <typename Renderer>
	class Texture1D : public Texture<Renderer> {};

	template <typename Renderer>
	class Texture2D : public Texture<Renderer> {};

	template <typename Renderer>
	class Texture2DArray : public Texture<Renderer> {};

	template <typename Renderer>
	class Texture3D : public Texture<Renderer> {};

	template <typename Renderer>
	class TextureCube : public Texture<Renderer> {};
};