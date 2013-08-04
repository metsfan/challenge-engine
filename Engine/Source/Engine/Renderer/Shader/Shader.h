#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Util/Util.h>

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
		virtual const unsigned char * GetShaderSource() = 0;
		virtual const int GetSourceSize() = 0;
		virtual ShaderType GetType() = 0;
	};

	class BaseShader : public IShader
	{
	public:
		BaseShader(std::string filename, ShaderType type) :
			mType(type),
			mShaderSource(NULL),
			mSourceSize(0)
		{
			mSourceSize = Util::ReadContentsOfBinaryFile(filename, &mShaderSource);
		}

		virtual ~BaseShader()
		{
			if(mShaderSource) {
				delete mShaderSource;
			}
		}

		const unsigned char * GetShaderSource() { return mShaderSource; }
		const int GetSourceSize() { return mSourceSize; }

		bool IsLoaded() { return mLoaded; }
		void SetLoaded(bool loaded) { mLoaded = loaded; }

		ShaderType GetType() { return mType; }

	private:
		ShaderType mType;
		unsigned char *mShaderSource;
		int mSourceSize;
		bool mLoaded;
	};

	template <typename Renderer>
	class Shader : public BaseShader {};
};