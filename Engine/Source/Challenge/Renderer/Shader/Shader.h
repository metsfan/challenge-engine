#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Util/Util.h>
#include <Challenge/Disk/Asset.h>

namespace challenge
{
	enum ShaderType
	{
		ShaderTypeVertexShader,
		ShaderTypePixelShader,
		ShaderTypeGeometryShader,
		ShaderTypeComputeShader,
		ShaderTypeDomainShader,
		ShaderTypeHullShader
	};

	static const int kShaderTypeMin = ShaderTypeVertexShader;
	static const int kShaderTypeMax = ShaderTypeHullShader;

	static const int kShaderDefaultCacheSize = 10;

	class IShaderProgram;

	class IShader
	{
	public:
		virtual void Load() = 0;
		virtual void AttachToProgram(IShaderProgram *program) = 0;
		virtual const TByteArray& GetShaderSource() = 0;
		virtual const int GetSourceSize() = 0;
		virtual ShaderType GetType() = 0;
	};

	class BaseShader : public IShader
	{
	public:
		BaseShader(std::wstring filename, ShaderType type) :
			mType(type),
			mShaderSource(NULL),
			mSourceSize(0)
		{
			Asset file(filename);
			if (file.ReadData()) {
				mSourceSize = file.GetData().size();
				mShaderSource = file.GetData();
			}
			
		}

		virtual ~BaseShader()
		{
		}

		const TByteArray& GetShaderSource() { return mShaderSource; }
		const int GetSourceSize() { return mSourceSize; }

		bool IsLoaded() { return mLoaded; }
		void SetLoaded(bool loaded) { mLoaded = loaded; }

		ShaderType GetType() { return mType; }

	private:
		ShaderType mType;
		TByteArray mShaderSource;
		int mSourceSize;
		bool mLoaded;
	};

	template <typename Renderer>
	class Shader : public BaseShader {};
};