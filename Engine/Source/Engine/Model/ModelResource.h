#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	struct ModelAnimation {
		int startFrame;
		int endFrame;
		int numFrames;
		int currentFrame;
		int elapsed;
		int startTime;
		int timeDelta;
	};

	struct ModelVertex {
		float position[3];
		float normal[3];
		float texCoord[2];
		float boneWeights[4];
		float boneIndices[4];
	};

	class ModelMesh;
	class ModelMaterial;
	class ModelBone;

	typedef std::vector<ModelMesh *> TMeshList;
	//typedef std::vector<ModelAnimation *> TAnimList;
	typedef std::vector<ModelMaterial *> TMaterialList;
	typedef std::map<std::string, ModelAnimation> TAnimList;
	typedef std::vector<ModelBone *> TBoneList;

	class ModelResource
	{
		friend class Model;

	public:
		ModelResource();
		~ModelResource();

		bool Initialize(const std::vector<ModelMesh *> &meshes);
		bool Initialize(const ModelVertex *verts, int nVerts);
		bool Initialize(const std::string &filename);

	private:
		std::string mModelPath;
		TMeshList mMeshes;
		TAnimList mAnimations;
		TMaterialList mMaterials;
		TBoneList mBones;
		std::vector<double> mAnimKeyframeTimes;
		std::vector<std::vector<glm::mat4> > mBoneMatrices;
		int mNumVerts;

		bool Unserialize(std::ifstream &in);
		void LoadAnimations();
	};
};