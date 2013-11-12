#include "Globals.h"
#include "ModelMesh.h"
#include <set>
#include <tuple>
#include <numeric>

namespace model
{
	ModelMesh::ModelMesh(ModelVertex *verts, int nVerts) :
		mMaterial(0)
	{
		int verticesSize = nVerts * sizeof(ModelVertex);

		mMeshBuffer = new ModelVertex[nVerts];
		memcpy(mMeshBuffer, verts, verticesSize);

		mTotalFaces = nVerts;

		mMaterial = NULL;
	}

	ModelMesh::~ModelMesh()
	{
		delete mMeshBuffer;
	}

	void ModelMesh::MoveToOrigin(float miny)
	{
		for(int i = 0; i < mTotalFaces; i++) {
			ModelVertex &vert = mMeshBuffer[i];
			vert.position[1] -= miny;
		}
	}

	void ModelMesh::CalculateBoneWeights(TBoneList &bones)
	{
		typedef std::map<int, std::vector<std::tuple<int, float> > > TWeightsMap;
		TWeightsMap weights;
		for(int i = 0; i < bones.size(); i++) {
			if(std::find(mBones.begin(), mBones.end(), i) != mBones.end()) {
				aiBone *bone = bones[i];
				for(int j = 0; j < bone->mNumWeights; j++) {
					int vertexId = bone->mWeights[j].mVertexId;
					weights[vertexId].push_back(std::tuple<int, float>(i, bone->mWeights[j].mWeight));
				}
			}
		}

		TWeightsMap::iterator it = weights.begin();
		while(it != weights.end()) {
			int vertexId = (*it).first;
			std::vector<std::tuple<int, float> > &weights = (*it).second;
			if(weights.size() > 4) {
				// If there's more than 4 weights, sort them, and renormalize so they add up to 1
				std::sort(weights.begin(), weights.end(), 
					[](std::tuple<int, float> a, std::tuple<int, float> b) {
						return std::get<1>(a) > std::get<1>(b);
					}
				);

				float total = 0;
				for(int i = 0; i < 4; i++) {
					total += std::get<1>(weights[i]);
				}

				for(int i = 0; i < 4; i++) {
					std::get<1>(weights[i]) /= total;
				}

				// Remove excess elements
				while(weights.size() > 4) {
					weights.pop_back();
				}
			}
			++it;
		}

		// Write bone incides and weights  to mesh vertices
		for(int i = 0; i < mTotalFaces; i++) {
			std::vector<std::tuple<int, float> > &vWeights = weights[i];
			int nWeights = vWeights.size();

			for(int j = 0; j < nWeights; j++) {
				mMeshBuffer[i].boneIndices[j] = std::get<0>(vWeights[j]);
				mMeshBuffer[i].boneWeights[j] = std::get<1>(vWeights[j]);
			}
		}
	}

	void ModelMesh::CopyMesh(ModelMesh *other)
	{
		int newSize = mTotalFaces + other->mTotalFaces;
		ModelVertex *newBuffer = new ModelVertex[newSize];

		memcpy(&newBuffer[0], &mMeshBuffer[0], sizeof(ModelVertex) * mTotalFaces);
		memcpy(&newBuffer[mTotalFaces], &other->mMeshBuffer[0], sizeof(ModelVertex) * other->mTotalFaces);

		delete mMeshBuffer;
		mMeshBuffer = newBuffer;
		mTotalFaces += other->mTotalFaces;

		for(int i = 0; i < other->mBones.size(); i++) {
			mBones.push_back(other->mBones[i]);
		}
	}

	void ModelMesh::Serialize(std::ostream &out, TNodeList &nodes, aiAnimation *animData)
	{
		// Compute per-vertex bone weights
		out.write((char *)&mTotalFaces, sizeof(int));
		out.write((char *)mMeshBuffer, sizeof(ModelVertex) * mTotalFaces);

		// Write material
		out.write((char *)&mMaterial, sizeof(int));

		/*if(frame == 11) {
			aiVector3D *resultPos = new aiVector3D[mTotalFaces];
			aiVector3D *resultNorm = new aiVector3D[mTotalFaces];

			for(int i = 0; i < mTotalFaces; i++) {
				ModelVertex &vertex = mMeshBuffer[i];
				aiVector3D pos = aiVector3D(vertex.position[0], vertex.position[1], vertex.position[2]);
				aiVector3D norm = aiVector3D(vertex.normal[0], vertex.normal[1], vertex.normal[2]);

				for(int j = 0; j < 4; j++) {
					int index = vertex.boneIndices[j];
					resultPos[i] += vertex.boneWeights[j] * (boneMatrices[index] * pos);
					resultNorm[i] += vertex.boneWeights[j] * (aiMatrix3x3(boneMatrices[index]) * norm);
				}

				vertex.position[0] = resultPos[i].x;
				vertex.position[1] = resultPos[i].y;
				vertex.position[2] = resultPos[i].z;

				resultNorm[i] = resultNorm[i].Normalize();

				vertex.normal[0] = resultNorm[i].x;
				vertex.normal[1] = resultNorm[i].y;
				vertex.normal[2] = resultNorm[i].z;
			}

			out.write((char *)mMeshBuffer, sizeof(ModelVertex) * mTotalFaces);
			delete resultPos;
			delete resultNorm;
		}*/
	}
};
