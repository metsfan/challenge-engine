#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class ShadingAttribute
	{
	public:
		ShadingAttribute() :
			mDiffuseColor(1.0f),
			mSpecularColor(1.0f),
			mAmbientColor(1.0f),
			mShininess(0.0f)
		{
		}

		~ShadingAttribute()
		{
		}

		void SetAmbientColor(glm::vec4 ambient) { mAmbientColor = ambient; }
		const glm::vec4& GetAmbientColor() const { return mAmbientColor; }

		void SetDiffuseColor(glm::vec4 diffuse) { mDiffuseColor = diffuse; }
		const glm::vec4& GetDiffuseColor() const { return mDiffuseColor; }

		void SetSpecularColor(glm::vec4 specular) { mSpecularColor = specular; }
		const glm::vec4& GetSpecularColor() const { return mSpecularColor; }

		void SetShininess(float shininess) { mShininess = shininess; }
		const float GetShininess() const { return mShininess; }

	private:
		glm::vec4 mDiffuseColor;
		glm::vec4 mAmbientColor;
		glm::vec4 mSpecularColor;
		float mShininess;
	};
};