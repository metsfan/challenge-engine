#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Util/Util.h>
#include <Challenge/Disk/Asset.h>
#include <Challenge/Renderer/GraphicsObject.h>
#include <Challenge/Renderer/RenderState.h>

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

	enum ShaderVarType
	{
		ShaderVarFloat,
		ShaderVarInt,
		ShaderVarVec2,
		ShaderVarVec3,
		ShaderVarVec4,
		ShaderVarMat2,
		ShaderVarMat3,
		ShaderVarMat4,
		ShaderVarStruct,
		ShaderVarTexture
	};

	struct ShaderGlobalVar
	{
		std::string name;
		std::string semantic;
		uint32_t globalId;
		uint32_t localId;
		ShaderVarType type;
		size_t size;
		uint32_t num;
	};

	static const int ShaderVarSizes[9] = {
		sizeof(float),
		sizeof(int),
		sizeof(float) * 2,
		sizeof(float) * 3,
		sizeof(float) * 4,
		sizeof(float) * 4,
		sizeof(float) * 9,
		sizeof(float) * 16,
		sizeof(int)
	};

	class IShaderProgram;

	class IShader
	{
	public:
		virtual void Load() = 0;
		virtual void AttachToProgram(IShaderProgram *program) = 0;
		virtual const TByteArray& GetShaderSource() = 0;
		virtual const int GetSourceSize() = 0;
		virtual ShaderType GetType() = 0;
		virtual void AddGlobalVariable(uint32_t index, const std::string &name, 
			const std::string &semantic, ShaderVarType type, int size) = 0;
		virtual int32_t GetVariableIndex(const std::string &semantic) = 0;
		virtual void UpdateState(IShaderProgram *program, RenderState &state) = 0;
	};

	class BaseShader : public IShader, GraphicsObject
	{
	public:
		BaseShader(IGraphicsDevice *device, std::wstring filename, ShaderType type) :
			GraphicsObject(device),
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

		void AddGlobalVariable(uint32_t index, const std::string &name, 
			const std::string &semantic, ShaderVarType type, int size);
		int32_t GetVariableIndex(const std::string &semantic);

		void UpdateState(IShaderProgram *program, RenderState &state);

	protected:
		virtual int32_t GetVariableLocalIndex(const std::string &name) = 0;

		const ShaderGlobalVar& GetVariable(int index)
		{
			return mGlobalVars[index];
		}

	private:
		ShaderType mType;
		TByteArray mShaderSource;
		int mSourceSize;
		bool mLoaded;
		std::vector<ShaderGlobalVar> mGlobalVars;
		std::vector<uint32_t> mGlobalIndices;
	};

	template <typename Renderer>
	class Shader : public BaseShader {};
};