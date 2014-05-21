#pragma once

#include <Challenge/Challenge.h>
//#include <Challenge/Renderer/Shader/ShaderProgram.h>
#include <Challenge/Renderer/Texture.h>

namespace challenge
{
	class IShaderProgram;

	class ShaderData
	{
	public:
		ShaderData()
		{
		}

		ShaderData(void *data) :
			mData(data)
		{
		}

		virtual ~ShaderData()
		{
		}

		void * GetData() { return mData; }

		virtual void Apply(IShaderProgram *program, int index, int type)
		{
		}

	private:
		void *mData;
	};

	template <typename T>
	class ShaderDataPrimitive : public ShaderData
	{
	public:
		ShaderDataPrimitive() :
			ShaderData(),
			mData(NULL),
			mCount(0)
		{
		}

		ShaderDataPrimitive(const T *data, int count) :
			ShaderData(),
			mData(data),
			mCount(count)
		{
		}

		~ShaderDataPrimitive() 
		{
		}

		void SetData(const T *data, int count)
		{
			mData = data;
			mCount = count;
		}

		void Apply(IShaderProgram *program, int index, int type)
		{
			//program->SetConstantData(index, mData, mCount, type);
		}

	private:
		const T *mData;
		int mCount;
	};

	typedef ShaderDataPrimitive<float> ShaderDataFloat;
	typedef ShaderDataPrimitive<int> ShaderDataInt;
	typedef ShaderDataPrimitive<glm::vec2> ShaderDataVector2f;
	typedef ShaderDataPrimitive<glm::vec3> ShaderDataVector3f;
	typedef ShaderDataPrimitive<glm::vec4> ShaderDataVector4f;
	typedef ShaderDataPrimitive<glm::mat2> ShaderDataMatrix2f;
	typedef ShaderDataPrimitive<glm::mat3> ShaderDataMatrix3f;
	typedef ShaderDataPrimitive<glm::mat4> ShaderDataMatrix4f;

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

		void Apply(IShaderProgram *program, int index, int type)
		{
			//program->SetConstantDataStruct(index, mData, mSize, type);
		}

	private:
		const void *mData;
		size_t mSize;
		int mCount;
	};

	class ShaderDataTexture : public ShaderData
	{
	public:
		ShaderDataTexture() :
			ShaderData(),
			mTexture(NULL)
		{
		}

		ShaderDataTexture(ITexture *texture) :
			ShaderData(),
			mTexture(texture)
		{
		}

		~ShaderDataTexture()
		{
		}

		void Apply(IShaderProgram *program, int index, int type)
		{
			//program->SetTexture(index, mTexture, type);
		}

		ITexture * GetTexture() { return mTexture; }

	private:
		ITexture *mTexture;
	};
};