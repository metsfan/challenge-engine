#pragma once

#include <Engine/Challenge.h>
#include <aiScene.h>
#include <Engine/Model/Model.h>
#include <Engine/Model/ModelMaterial.h>

namespace challenge
{
	class ModelMesh
	{
	public:
		ModelMesh();
		ModelMesh(const ModelVertex *vertices, int nVerts);
		~ModelMesh();

		int GetMaterial() { return mMaterialId; }

		ModelVertex * GetBuffer() { return mMeshVertices; }
		int GetTotalFaces() { return mNumVertices; }
		

		aiVector3D GetVertexAtIndex(int index);
		void SetVertexAtIndex(int index, float x, float y, float z);

		aiVector3D GetNormalAtIndex(int index);
		void SetNormalAtIndex(int index, float x, float y, float z);

		void Transform(const glm::mat4 &transform);

		void Unserialize(std::istream &in);

	private:
		int mMaterialId;
		ModelVertex *mMeshVertices;
		int mNumVertices;
		glm::mat4 mNodeTransform;
		bool mUpdateNextRender;

	};
};