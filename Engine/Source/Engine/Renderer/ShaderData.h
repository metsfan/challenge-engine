#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shader/ShaderProgram.h>
#include <Engine/Renderer/Texture.h>

namespace challenge
{
	class ShaderData
	{
	public:
		ShaderData()
		{
		}

		~ShaderData()
		{
		}

		virtual void Apply(IShaderProgram *program, int index, ShaderType type) = 0;
	};

	template <typename T>
	class ShaderDataPrimitive : public ShaderData
	{
	public:
		ShaderDataPrimitive(const T *data, int count) :
			ShaderData(),
			mData(data),
			mCount(count)
		{
		}

		~ShaderDataPrimitive() 
		{
		}

		void Apply(IShaderProgram *program, int index, ShaderType type)
		{
			program->SetConstantData(index, mData, mCount, type);
		}

	private:
		const T *mData;
		int mCount;
	};

	typedef ShaderDataPrimitive<float> ShaderDataFloat;
	typedef ShaderDataPrimitive<int> ShaderDataInt;
	typedef ShaderDataPrimitive<glm::vec2> ShaderDataVector2;
	typedef ShaderDataPrimitive<glm::vec3> ShaderDataVector3;
	typedef ShaderDataPrimitive<glm::vec4> ShaderDataVector4;
	typedef ShaderDataPrimitive<glm::mat2> ShaderDataMatrix2;
	typedef ShaderDataPrimitive<glm::mat3> ShaderDataMatrix3;
	typedef ShaderDataPrimitive<glm::mat4> ShaderDataMatrix4;

	class ShaderDataStruct : public ShaderData
	{
	public:
		ShaderDataStruct(const void *data, size_t size, int count) :
			ShaderData(),
			mData(data),
			mSize(size),
			mCount(count)
		{
		}

		~ShaderDataStruct()
		{
		}

		void Apply(IShaderProgram *program, int index, ShaderType type)
		{
			program->SetConstantDataStruct(index, mData, mSize, type);
		}

	private:
		const void *mData;
		size_t mSize;
		int mCount;
	};

	class ShaderDataTexture : public ShaderData
	{
	public:
		ShaderDataTexture(ITexture *texture) :
			ShaderData(),
			mTexture(texture)
		{
		}

		~ShaderDataTexture()
		{
		}

		void Apply(IShaderProgram *program, int index, ShaderType type)
		{
			program->SetTexture(index, mTexture, type);
		}

	private:
		ITexture *mTexture;
	};
};