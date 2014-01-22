#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Model/Model.h>
#include <Challenge/Model/ModelMaterial.h>
#include <Challenge/Disk/FileInputStream.h>

namespace challenge
{
	class ModelMesh
	{
	public:
		ModelMesh();
		ModelMesh(const std::vector<ModelVertex> verts);
		~ModelMesh();

		int GetMaterial() { return mMaterialId; }

		ModelVertex * GetBuffer() { return &mMeshVertices[0]; }
		int GetTotalFaces() { return mNumVertices; }
	
		void Transform(const glm::mat4 &transform);

		void Unserialize(FileInputStream &in);

		bool GetIntersection(const Ray &ray, float &t);

	private:
		int mMaterialId;
		std::vector<ModelVertex> mMeshVertices;
		int mNumVertices;
		glm::mat4 mNodeTransform;
		bool mUpdateNextRender;

	};
};