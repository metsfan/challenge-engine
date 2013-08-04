#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class ModelBone
	{
	public:
		ModelBone(int numKeyframes);
		~ModelBone();

		void SetKeyframeTransform(int keyframe, glm::mat4 &transform) 
		{ 
			mKeyframeTransforms[keyframe] = transform; 
		}

		const glm::mat4& GetKeyframeTransform(int keyframe)
		{
			return mKeyframeTransforms[keyframe];
		}

	private:
		std::vector<glm::mat4> mKeyframeTransforms;
	};
};