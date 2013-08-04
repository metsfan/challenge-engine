#pragma once

#include <stack>
#include <Engine/Challenge.h>
#include <Engine/Renderer/Attribute.h>
#include <Engine/Renderer/Lights/LightSource.h>
#include <Engine/Renderer/ShaderData.h>

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
		void PopTransform() 
		{
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

		void SetShaderData(std::string field, ShaderData *data)
		{
			mShaderData[field] = data;
		}

		ShaderData* GetShaderData(std::string &field) 
		{
			return mShaderData[field];
		}

	private:
		std::vector<LightSource *> mLightSources;
		std::stack<glm::mat4> mTransformStack;
		glm::mat4 mProjection;
		glm::mat4 mTopTransform;
		glm::mat4 mWVP;
		std::unordered_map<std::string, ShaderData *> mShaderData;
		Material *mMaterial;
	};
};