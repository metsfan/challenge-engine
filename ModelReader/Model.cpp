#include "Globals.h"
#include "Model.h"
#include "ModelMaterial.h"
#include "ModelMesh.h"
#include "ModelAnimation.h"
#include <aiScene.h>
#include <rapidxml.hpp>

namespace model
{
	Model::Model(std::string &filepath, glm::mat4 globalTransform) :
		mAnimData(NULL)
	{
		this->Load(filepath, globalTransform);
	}

	Model::~Model()
	{
	}

	void Model::Load(std::string &filepath, glm::mat4 globalTransform)
	{
		mScene = aiImportFile(filepath.c_str(), 0);
		if(!mScene) {
			throw "File not found!";
		}

		if(mScene->mNumAnimations > 0) {
			mAnimData = mScene->mAnimations[0];
			aiNodeAnim **animNodes = mAnimData->mChannels;
			for(int j = 0; j < mAnimData->mNumChannels; j++) {
				aiNodeAnim *nAnimNode = animNodes[j];
				aiNode *nNode = mScene->mRootNode->FindNode(nAnimNode->mNodeName);
				std::string nodeName = nAnimNode->mNodeName.data;
				mNodes[nodeName] = nNode;
			}
		}

		if(mScene->mNumMaterials > 0) {
			for(int i = 0; i < mScene->mNumMaterials; i++) {
				aiMaterial *material = mScene->mMaterials[i];
				mMaterials.push_back(new ModelMaterial(material));
			}
		}

		aiMatrix4x4 aiGlobalTransform;
		aiGlobalTransform = aiMatrix4x4(
			globalTransform[0][0], globalTransform[0][1], globalTransform[0][2], globalTransform[0][3],
			globalTransform[1][0], globalTransform[1][1], globalTransform[1][2], globalTransform[1][3],
			globalTransform[2][0], globalTransform[2][1], globalTransform[2][2], globalTransform[2][3],
			globalTransform[3][0], globalTransform[3][1], globalTransform[3][2], globalTransform[3][3]
		);

		mMinY = INFINITE;

		ReadModelData(mScene->mRootNode, aiGlobalTransform);

		/*for(int i = 0; i < mMeshes.size(); i++) {
			ModelMesh *mesh = mMeshes[i];
			mesh->MoveToOrigin(mMinY);
		}*/

		for(int i = 0; i < mMeshes.size(); i++) {
			mMeshes[i]->CalculateBoneWeights(mBones);
		}

		this->ConsolidateMeshes();
	}

	void Model::ReadModelData(const aiNode *node, aiMatrix4x4 globalTransform)
	{
		for(unsigned int i = 0; i < node->mNumMeshes; ++i) {
			const aiMesh *mesh = mScene->mMeshes[node->mMeshes[i]];
			int nVerts = mesh->mNumVertices;

			ModelVertex *verts = new ModelVertex[nVerts];
			memset(verts, 0, sizeof(ModelVertex) * nVerts);

			int m = 0;
			for(int j = 0; j < mesh->mNumFaces; ++j) {
				const struct aiFace* face = &mesh->mFaces[j];
				for(int k = 0; k < face->mNumIndices; k++) {
					int index = face->mIndices[k];
					aiVector3D pos = mesh->mVertices[index];

					aiMatrix4x4 xForm = globalTransform * node->mTransformation;
					aiMatrix3x3 normalXForm = aiMatrix3x3(xForm);
					aiTransformVecByMatrix4(&pos, &xForm);

					verts[m].position[0] = pos.x;
					verts[m].position[1] = pos.y;
					verts[m].position[2] = pos.z;

					if(pos.y < mMinY) {
						mMinY = pos.y;
					}
				
					if(mesh->mNormals != NULL) {
						aiVector3D normal = mesh->mNormals[index];
						aiTransformVecByMatrix3(&normal, &normalXForm);
						verts[m].normal[0] = normal.x;
						verts[m].normal[1] = normal.y;
						verts[m].normal[2] = normal.z;
					}

					if(mesh->mTextureCoords != NULL && mesh->mTextureCoords[0] != NULL) {
						aiVector3D texel = mesh->mTextureCoords[0][index];
						verts[m].texCoord[0] = texel.x;
						verts[m].texCoord[1] = texel.y;
					}

					m++;
				}
			}

			std::vector<aiBone *> bones;
			//ModelMesh *newMesh = new ModelMesh(n_vertices, n_normals, n_texels, mesh->mNumVertices);
			ModelMesh *newMesh = new ModelMesh(verts, nVerts);
			for (int k = 0; k < mesh->mNumBones; k++) {
				int boneIndex = mBones.size();
				newMesh->AddBone(boneIndex);
				mBones.push_back(mesh->mBones[k]);
			}

			newMesh->SetMaterial(mesh->mMaterialIndex);

			mMeshes.push_back(newMesh);
			mTotalFaces += mesh->mNumVertices;

			delete verts;
		}

		for(int i = 0 ; i < node->mNumChildren; i++) {
			ReadModelData(node->mChildren[i], globalTransform);
		}
	}

	void Model::LoadAnimations(std::string &filepath)
	{
		std::stringstream fileData;
		std::ifstream file(filepath);
		fileData << file.rdbuf();
		std::string text = fileData.str();

		if(text.length() > 0) {
			std::vector<char> xml_copy(text.begin(), text.end());
			xml_copy.push_back('\0');

			rapidxml::xml_document<> doc;
			doc.parse<0>(&xml_copy[0]);

			rapidxml::xml_node<> *root = doc.first_node("animations");

			rapidxml::xml_node<> *animationNode = root->first_node("animation");

			while(animationNode != NULL) {
				std::string name = animationNode->first_node("name")->value();
				int startFrame = atoi(animationNode->first_node("startFrame")->value());
				int endFrame = atoi(animationNode->first_node("endFrame")->value());

				int startTime = (mAnimData->mChannels[0]->mPositionKeys[startFrame].mTime * 1000) / 2;
				int endTime = (mAnimData->mChannels[0]->mPositionKeys[endFrame].mTime * 1000) / 2;
				int duration = endTime - startTime;

				ModelAnimation *anim = new ModelAnimation(name, startFrame, endFrame, duration);
				mAnimations.push_back(anim);

				animationNode = animationNode->next_sibling();
			}

			printf("stop");
		}
	}

	void Model::Serialize(std::ostream &out)
	{
		// Write meshes
		int nMeshes = mMeshes.size();
		out.write((char *)&nMeshes, sizeof(int));

		for(int i = 0; i < nMeshes; i++) {
			if(mMeshes[i]) {
				mMeshes[i]->Serialize(out, mNodes, mAnimData);
			}
		}

		bool animated = mAnimData != NULL;
		out.write((char *)&animated, sizeof(bool));
		if(mAnimData) {
			// Write keyframe times
			int numKeyframes = mAnimData->mChannels[0]->mNumPositionKeys;
			out.write((char *)&numKeyframes, sizeof(int));
			for(int i = 0; i < numKeyframes; i++) {
				double frameTime = mAnimData->mChannels[0]->mPositionKeys[i].mTime;
				out.write((char *)&frameTime, sizeof(double));
			}

			// Write bone transforms for each keyframe
			this->WriteBones(out, numKeyframes);
		}

		// Write materials
		int nMaterials = mMaterials.size();
		out.write((char *)&nMaterials, sizeof(int));
		
		for(int i = 0; i < nMaterials; i++) {
			mMaterials[i]->Serialize(out);
		}
	}

	void Model::WriteBones(std::ostream &out, int numKeyframes)
	{
		int nBones = mBones.size();

		// Write number of bones
		out.write((char *)&nBones, sizeof(int));
		if(mBones.size() > 0) {
			// Write bone matrices for each animation keyframe
			for(int frame = 0; frame < numKeyframes; frame++) {
				// Find animation for this keyframe and set node transforms
				aiNodeAnim **nodeAnims = mAnimData->mChannels;
				for(int i = 0; i < mAnimData->mNumChannels; i++) {
					aiNodeAnim *nAnimNode = nodeAnims[i];
					if(nAnimNode->mNumPositionKeys >= frame &&
						nAnimNode->mNumRotationKeys >= frame) {
						std::string nodeName = nAnimNode->mNodeName.data;
						aiNode *nNode = mNodes[nodeName];
						aiVector3D curPosition = nAnimNode->mPositionKeys[frame].mValue;
						aiQuaternion curRotation = nAnimNode->mRotationKeys[frame].mValue;
						aiMatrix4x4 transform = aiMatrix4x4(curRotation.GetMatrix());
						transform.a4 = curPosition.x;
						transform.b4 = curPosition.y;
						transform.c4 = curPosition.z;
						mNodes[nodeName]->mTransformation = transform;
					}
				}

				// Create bone matrices for next keyframe
				int nBones = mBones.size();

				std::vector<aiMatrix4x4> boneMatrices(nBones);
				for(int i = 0; i < mBones.size(); i++) {
					const aiBone *bone = mBones[i];

					std::string nodeName = bone->mName.data;
					aiNode *nNode = mNodes[nodeName];
  
					boneMatrices[i] = bone->mOffsetMatrix;
					const aiNode* tempNode = nNode;
					while( tempNode)
					{
						boneMatrices[i] = tempNode->mTransformation * boneMatrices[i];
						tempNode = tempNode->mParent;
					}
				}

				// Write bone matrices
				out.write((char *)&boneMatrices[0][0][0], sizeof(aiMatrix4x4) * boneMatrices.size());
			}
		}
	}

	void Model::ConsolidateMeshes()
	{
		int nMaterials = mMaterials.size();
		TMeshList newMeshes(nMaterials);
		for(int i = 0; i < newMeshes.size(); i++) {
			newMeshes[i] = NULL;
		}

		for(int i = 0; i < mMeshes.size(); i++) {
			ModelMesh *mesh = mMeshes[i];
			int materialId = mesh->GetMaterial();
			if(newMeshes[materialId] == NULL) {
				newMeshes[materialId] = mesh;
			} else {
				newMeshes[materialId]->CopyMesh(mesh);
				delete mesh;
			}
		}

		mMeshes = newMeshes;
	}
};