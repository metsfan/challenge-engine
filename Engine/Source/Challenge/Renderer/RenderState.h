#pragma once

#include <stack>
#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Attribute.h>
#include <Challenge/Renderer/Lights/LightSource.h>
#include <Challenge/Renderer/ShaderData.h>

namespace challenge
{
	class Material;

	class RenderState
	{
	public:
		RenderState();
		~RenderState();

		void SetProjection(const glm::mat4 &projection) 
		{ 
			if(mProjection != projection) {
				mProjection = projection; 
				mWVP = mProjection * mTopTransform;
			}
		}

		glm::mat4& GetProjection() { return mProjection; }

		void PushTransform(const glm::mat4 &transform) 
		{ 
			mTransformStack.push(mTopTransform * transform); 
			mTopTransform = mTransformStack.top();
			mWVP = mProjection * mTopTransform;
		}
		
		glm::mat4 PopTransform() 
		{
			glm::mat4 oldTop = mTopTransform;

			if(mTransformStack.size() > 0) {
				mTransformStack.pop();

				if(mTransformStack.size() > 0) {
					mTopTransform = mTransformStack.top();
					mWVP = mProjection * mTopTransform;
				} else {
					mTopTransform = glm::mat4();
					mWVP = mProjection;
				}
			}

			return oldTop;
		}

		glm::mat4 GetTransform() 
		{ 
			return mTopTransform;
		}

		glm::mat4& GetWorldViewProjection()
		{
			return mWVP;
		}

		void AddLight(LightSource *light);
		void RemoveLight(LightSource *light);
		std::vector<LightSource *>& GetLights() { return mLightSources; }

		void SetMaterial(Material *material) { mMaterial = material; }
		Material* GetMaterial() { return mMaterial; }

		void SetShaderData(int index, void *data, uint32_t num = 1)
		{
			if (index < 0) {
				return;
			}

			if (mShaderData.size() <= index) {
				mShaderData.resize(index + 1);
				mShaderDataNum.resize(index + 1);
			}

			mShaderData[index] = data;
			mShaderDataNum[index] = num;
		}

		void * GetShaderData(int index) 
		{
			if (mShaderData.size() > index) {
				return mShaderData[index];
			}
			
			return NULL;
		}

		uint32_t GetShaderDataNum(int index)
		{
			if (mShaderData.size() > index) {
				return mShaderDataNum[index];
			}

			return 1;
		}

	private:
		std::vector<LightSource *> mLightSources;
		std::stack<glm::mat4> mTransformStack;
		glm::mat4 mProjection;
		glm::mat4 mTopTransform;
		glm::mat4 mWVP;
		std::vector<void *> mShaderData;
		std::vector<uint32_t> mShaderDataNum;
		Material *mMaterial;
	};
};