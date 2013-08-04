#pragma once

#include "Globals.h"
#include <aiScene.h>
#include "ModelMaterial.h"
#include "Model.h"

namespace model
{
	class ModelMesh
	{
	public:
		//ModelMesh(float *vertices, float *normals, float *texels, int totalFaces);
		ModelMesh(ModelVertex *vertices, int nVerts);
		~ModelMesh();
		
		void CalculateBoneWeights(TBoneList &bones);
		void AddBone(int boneId) { mBones.push_back(boneId); }

		void SetMaterial(int material) { mMaterial = material; }
		int GetMaterial() { return mMaterial; }

		void CopyMesh(ModelMesh *other);

		void Serialize(std::ostream &out, TNodeList &nodes, aiAnimation *animData);

	private:
		std::vector<int> mBones;
		int mMaterial;
		ModelVertex *mMeshBuffer;
		int mTotalFaces;
		glm::mat4 mNodeTransform;
		bool mUpdateNextRender;

	};
};