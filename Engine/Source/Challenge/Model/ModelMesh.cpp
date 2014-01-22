#include <Challenge/Challenge.h>
#include "ModelMesh.h"

namespace challenge
{
	ModelMesh::ModelMesh() :
		mMeshVertices(NULL),
		mNumVertices(0)
	{
	}

	ModelMesh::ModelMesh(const std::vector<ModelVertex> verts) :
		mMaterialId(-1)
	{
		mMeshVertices = verts;

		mNumVertices = verts.size();
	}

	ModelMesh::~ModelMesh()
	{
	}

	void ModelMesh::Unserialize(FileInputStream &in)
	{
		// Read mesh vertices
		mNumVertices = in.Read<int>();

		// Read model vertices
		mMeshVertices.resize(mNumVertices);
		in.Read((char *)&mMeshVertices[0], sizeof(ModelVertex) * mNumVertices);

		// Read material
		mMaterialId = in.Read<int>();
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

	bool ModelMesh::GetIntersection(const Ray &ray, float &t)
	{
		Triangle tri;

		float minT = INFINITY;

		for(int i = 0; i < mMeshVertices.size(); i += 3) {
			tri[0].x = mMeshVertices[i].position[0];
			tri[0].y = mMeshVertices[i].position[1];
			tri[0].z = mMeshVertices[i].position[2];
			tri[1].x = mMeshVertices[i+1].position[0];
			tri[1].y = mMeshVertices[i+1].position[1];
			tri[1].z = mMeshVertices[i+1].position[2];
			tri[2].x = mMeshVertices[i+2].position[0];
			tri[2].y = mMeshVertices[i+2].position[1];
			tri[2].z = mMeshVertices[i+2].position[2];

			if(ray.GetIntersection(tri, t)) {
				if(t < minT) {
					minT = t;
				}
			}
		}

		t = minT;
		return minT != INFINITY ;
	}
};
