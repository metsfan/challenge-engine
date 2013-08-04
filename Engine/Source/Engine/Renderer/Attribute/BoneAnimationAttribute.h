#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class BoneAnimationAttribute
	{
		static const int kMaxBones = 64;

	public:
		BoneAnimationAttribute()
		{
		}

		~BoneAnimationAttribute()
		{
		}

		//void AddBoneMatrix(const glm::mat4 &matrix) { mMatrices.push_back(matrix); }
		void SetBoneMatrix(int index, const glm::mat4 &matrix)
		{
			if(index < kMaxBones) {
				mMatrices[index] = matrix;
			}
		}
		void SetBoneMatrices(std::vector<glm::mat4> &matrices, int startIndex)
		{
			int nMatrices = matrices.size();
			if(startIndex + nMatrices < kMaxBones) {
				memcpy(&mMatrices[startIndex], &matrices[0], sizeof(glm::mat4) * nMatrices);
			}
		}

		glm::mat4& GetBoneMatrix(int index) { return mMatrices[index]; }
		int GetNumBoneMatrices() { return kMaxBones; }
		const glm::mat4* GetBoneMatrices() const { return mMatrices; }

	private:
		glm::mat4 mMatrices[64];
	};
};
