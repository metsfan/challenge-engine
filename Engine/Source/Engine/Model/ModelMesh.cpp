#include <Engine/Challenge.h>
#include "ModelMesh.h"

namespace challenge
{
	ModelMesh::ModelMesh() :
		mMeshVertices(NULL),
		mNumVertices(0)
	{
	}

	ModelMesh::ModelMesh(const ModelVertex *verts, int nVerts)
	{
		int verticesSize = nVerts * sizeof(ModelVertex);

		mMeshVertices = new ModelVertex[nVerts];
		memcpy(mMeshVertices, verts, verticesSize);

		mNumVertices = nVerts;
	}

	ModelMesh::~ModelMesh()
	{
		if(mMeshVertices) {
			delete[] mMeshVertices; 
		}
	}

	void ModelMesh::Unserialize(std::istream &in)
	{
		// Read mesh vertices
		in.read((char *)&mNumVertices, sizeof(int));

		mMeshVertices = new ModelVertex[mNumVertices];
		in.read((char *)mMeshVertices, sizeof(ModelVertex) * mNumVertices);

		// Read material
		in.read((char *)&mMaterialId, sizeof(int));
	}

	void ModelMesh::Transform(const glm::mat4 &transform)
	{
		glm::mat3 normalMatrix = glm::mat3(
				transform[0].x, transform[1].x, transform[2].x,
				transform[0].y, transform[1].y, transform[2].y,
				transform[0].z, transform[1].z, transform[2].z
			);
		normalMatrix = glm::transpose(glm::inverse(normalMatrix));

		for(int i = 0; i < mNumVertices; i++) {
			ModelVertex *vert = &mMeshVertices[i];

			glm::vec4 position(vert->position[0], vert->position[1], vert->position[2], 1.0f);
			glm::vec3 normal(vert->normal[0], vert->normal[1], vert->normal[2]);

			position = position * transform;
			normal = normalMatrix * normal;

			vert->position[0] = position.x;
			vert->position[1] = position.y;
			vert->position[2] = position.z;
			vert->normal[0] = normal.x;
			vert->normal[1] = normal.y;
			vert->normal[2] = normal.z;
		}
	}
};
