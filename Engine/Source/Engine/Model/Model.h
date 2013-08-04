#pragma once

#include <Engine/Challenge.h>
#include <Engine/Model/ModelResource.h>

namespace challenge
{
	
	struct ModelAnimParams {
		std::string name;
		bool loop;
	};
	
	__declspec(align(16))
	struct ModelCBMatrices {
		glm::mat4 gWVPMatrix;
		glm::mat3 gNormalMatrix;
	};

	class Model
	{
	public:
		Model(std::shared_ptr<ModelResource> resource);
		~Model();

		void Transform(glm::mat4 &transform);

		TMeshList& GetMeshes() { return mResource->mMeshes; }
		int GetVertexCount() { return mResource->mNumVerts; }

		const std::vector<glm::mat4>& GetBonesForKeyframe(int keyframe);

		TMaterialList& GetMaterials() { return mResource->mMaterials; }

		//void SetTexture(Texture *texture) { mTexture = texture; }
		//Texture * GetTexture() { return mTexture; }

		void SetIsStatic(bool isStatic) { mStatic = isStatic; }
		bool IsStatic() { return mStatic; }
		void Model::SetAnimFrame(int frame);
		void Model::SetNextFrame(int deltaMillis);

		bool UpdateNextRender() { return mUpdateNextRender; }

		void SetActiveAnimation(std::string animation);
		void SetActiveAnimation(std::string animation, bool loop);
		void SetActiveAnimation(ModelAnimParams animation);
		void QueueAnimation(std::string animation, bool loop);
		std::string GetActiveAnimationName() { return mActiveAnimationData.name; }
		ModelAnimation GetActiveAnimation() { return mActiveAnimation; }

		static std::string GetModelBaseDir() { return s_ModelDir; }

		void Unserialize(std::istream &in);

		int GetCurrentAnimationFrame() { return mActiveAnimFrame; }

	protected:
		std::shared_ptr<ModelResource> mResource;

		int mTotalFaces;
		std::string mModelPath;
		bool mStatic;
		int mActiveAnimFrame;
		bool mUpdateNextRender;
		ModelAnimation mActiveAnimation;
		ModelAnimParams mActiveAnimationData;
		std::list<ModelAnimParams> mAnimationQueue;

		void LoadAnimations();
		void PopQueue();

		static std::string s_ModelDir;
	};
};