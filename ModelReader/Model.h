#pragma once

#include "Globals.h"
#include <assimp.h>
#include <aiScene.h>
#include <glm/glm.hpp>

namespace model
{
	struct ModelVertex {
		float position[3];
		float normal[3];
		float texCoord[2];
		float boneWeights[4];
		float boneIndices[4];
	};

	class ModelMaterial;
	class ModelMesh;
	class ModelAnimation;

	typedef std::vector<ModelMaterial *> TMaterialList;
	typedef std::map<std::string, aiNode *> TNodeList;
	typedef std::vector<ModelMesh *> TMeshList;
	typedef std::vector<ModelAnimation *> TAnimationList;
	typedef std::vector<aiBone *> TBoneList;

	class Model
	{
	public:
		Model(std::string &filepath, glm::mat4 globalTransform);
		~Model();

		void Load(std::string &filepath, glm::mat4 globalTransform);
		void LoadAnimations(std::string &filepath);

		void Serialize(std::ostream &out);

	private:
		const aiScene *mScene;
		TNodeList mNodes;
		aiAnimation *mAnimData;
		TMaterialList mMaterials;
		TMeshList mMeshes;
		TAnimationList mAnimations;
		int mTotalFaces;
		TBoneList mBones;
		float mMinY;

		void ReadModelData(const aiNode *node, aiMatrix4x4 globalTransform);
		void ConsolidateMeshes();
		void WriteBones(std::ostream &out, int numKeyframes);
	};
};