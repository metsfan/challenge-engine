#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include <Engine/Util/Logger.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Model/ModelMaterial.h>
#include <Engine/Model/ModelBone.h>
#include <rapidxml/rapidxml.hpp>
#include "Model.h"

namespace challenge
{
	std::string Model::s_ModelDir = "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Media/Models/";
	std::map<std::string, std::shared_ptr<ModelResource>> Model::sResourceCache;

	Model::Model(std::shared_ptr<ModelResource> resource) :
		mActiveAnimFrame(0),
		mResource(resource),
		mBoundingVolume(NULL)
	{
	}

	Model::Model(const std::string &filepath) :
		mActiveAnimFrame(0),
		mBoundingVolume(NULL)
	{
		memset(&mActiveAnimation, 0, sizeof(ModelAnimation));

		if(sResourceCache.count(filepath)) {
			mResource = sResourceCache[filepath];	
		} else {
			std::shared_ptr<ModelResource> newResource(new ModelResource());
			if(newResource->Initialize(filepath)) {
				sResourceCache[filepath] = newResource;
				mResource = newResource;
			} else {
				throw "Failed to initialize model resource";
			}
		}
	}

	IGeometricShape* Model::CreateBoundingVolume(GeometricShapeType type, const glm::mat4 &transform)
	{
		mBoundingVolume = mResource->CreateBoundingVolume(type, transform)->Clone();

		return mBoundingVolume;
	}

	void Model::Transform(const glm::mat4 &transform)
	{
		/*for(int i = 0; i < mResource->mMeshes.size(); i++) {
			mResource->mMeshes[i]->Transform(transform);
		}*/
		if(mBoundingVolume) {
			mBoundingVolume->SetTransform(transform);
		}
	}

	/*void Model::SetAnimFrame(int frame)
	{
		if(mActiveAnimFrame == frame) {
			return;
		}
		mActiveAnimFrame = frame;

		aiNodeAnim **nodeAnims = mAnimData->mChannels;
		for(int j = 0; j < mAnimData->mNumChannels; j++) {
			aiNodeAnim *nAnimNode = nodeAnims[j];
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

		// calculate bone matrices
		for (int i = 0; i < mMeshes.size(); i++) {
			ModelMesh *mesh = mMeshes[i];
			TBoneList bones = mesh->GetBones();
			std::vector<aiMatrix4x4> boneMatrices(bones.size());

			TBoneList::iterator bones_it = bones.begin();
			int j = 0;
			while(bones_it != bones.end()) 
			{
				const aiBone* bone = (*bones_it);
  
				// find the corresponding node by again looking recursively through the node hierarchy for the same name
				std::string nodeName = bone->mName.data;
				aiNode *nNode = mNodes[nodeName];
  
				// start with the mesh-to-bone matrix 
				boneMatrices[j] = bone->mOffsetMatrix;
				// and now append all node transformations down the parent chain until we're back at mesh coordinates again
				const aiNode* tempNode = nNode;
				while( tempNode)
				{
					boneMatrices[j] = tempNode->mTransformation * boneMatrices[j];   // check your matrix multiplication order here!!!
					tempNode = tempNode->mParent;
				}

				++bones_it;
				
				j++;
			}
			/*std::vector<aiVector3D> resultPos(mesh->GetNumVertices()); 
			std::vector<aiVector3D> resultNorm(mesh->GetNumVertices());
			int nVertices = mesh->GetTotalFaces();
			aiVector3D *resultPos = new aiVector3D[nVertices];
			aiVector3D *resultNorm = new aiVector3D[nVertices];
			for(int j = 0; j < bones.size(); j++) {
				aiBone *nBone = bones[j]; 
				const aiMatrix4x4& posTransform = boneMatrices[j];
				aiMatrix3x3 normalTransform = aiMatrix3x3( posTransform);
				for(int k = 0; k < nBone->mNumWeights; k++) {
					const aiVertexWeight weight = nBone->mWeights[k];
					int vertexId = weight.mVertexId;
					aiVector3D srcPos = mesh->GetVertexAtIndex(vertexId);
					//aiVector3D srcNorm = mesh->GetNormalAtIndex(vertexId);
					resultPos[vertexId] += weight.mWeight * (posTransform * srcPos);
					//resultNorm[vertexId] += weight.mWeight * (normalTransform * srcNorm);
				}
			}

			for (int vertexId = 0; vertexId < nVertices; vertexId++) {
				aiVector3D pos = resultPos[vertexId];
				mesh->SetVertexAtIndex(vertexId, pos.x, pos.y, pos.z);
				//aiVector3D norm = resultNorm[vertexId];
				//mesh->SetNormalAtIndex(vertexId, norm.x, norm.y, norm.z);
			}
			mesh->SetUpdateNextRender(true);
			delete resultPos;
			delete resultNorm;
		}

		mUpdateNextRender = true;
	}*/

	void Model::SetAnimFrame(int frame)
	{
		mActiveAnimFrame = frame;
	}

	void Model::SetNextFrame(int deltaMillis)
	{
		if(mActiveAnimation.startFrame > 0 && mActiveAnimation.endFrame > 0) {
			mActiveAnimation.elapsed += deltaMillis;
			//printf("%d\n", mElapsed);
			if(mActiveAnimation.startFrame == mActiveAnimation.endFrame) {
				mActiveAnimation.currentFrame = mActiveAnimation.startFrame;
			} else {
				float currentTime = (mActiveAnimation.elapsed % mActiveAnimation.timeDelta) + mActiveAnimation.startTime;
				for(int i = mActiveAnimation.startFrame; i <= mActiveAnimation.endFrame; i++) {
					float time = (mResource->mAnimKeyframeTimes[i] * 1000);
					if(time >= currentTime) {
						//printf("%d\n", i);
						mActiveAnimation.currentFrame = i;
						break;
					}
				}
			
			}
			this->SetAnimFrame(mActiveAnimation.currentFrame);

			if(mActiveAnimation.currentFrame == mActiveAnimation.endFrame) {
				if(!mActiveAnimationData.loop) {
					mActiveAnimation.startFrame = -1;
					mActiveAnimationData = ModelAnimParams();
				}
				this->PopQueue();
			}
		} else {
			this->PopQueue();
		}
	}

	void Model::PopQueue()
	{
		if(mAnimationQueue.size() > 0) {
			ModelAnimParams front = mAnimationQueue.front();
			this->SetActiveAnimation(front);
			mAnimationQueue.pop_front();
		}
	}

	void Model::SetActiveAnimation(std::string animation)
	{
		this->SetActiveAnimation(animation, true);	
	}

	void Model::SetActiveAnimation(std::string animation, bool loop)
	{
		ModelAnimParams animData;
		if(animation == "") {
			mActiveAnimation.startFrame = -1;
		} else if(mActiveAnimationData.name != animation) {
			//Logger::log(LogDebug, animation);
			ModelAnimParams animData;
			animData.name = animation;
			animData.loop = loop;
			this->SetActiveAnimation(animData);
			mAnimationQueue.clear();
		}
	}

	void Model::SetActiveAnimation(ModelAnimParams animation)
	{
		mActiveAnimationData = animation;
		mActiveAnimation = mResource->mAnimations[animation.name];
		mActiveAnimation.currentFrame = mActiveAnimation.startFrame;
	}

	void Model::QueueAnimation(std::string animation, bool loop)
	{
		if(animation != "") {
			ModelAnimParams animData;
			animData.name = animation;
			animData.loop = loop;
			mAnimationQueue.push_back(animData);
		}
	}

	void Model::Render(IGraphicsDevice *device, RenderState &state)
	{
		mResource->Render(device, state, mActiveAnimation.currentFrame, 0);
	}

	bool Model::GetIntersection(const Ray &ray, float &t)
	{
		//if(mBoundingVolume) {
			//return mBoundingVolume->RayIntersects(ray, t);
		//} else {
		float minT = INFINITY;

		const TMeshList &meshes = mResource->GetMeshes();
		for(ModelMesh *mesh : meshes) {
			if(mesh->GetIntersection(ray, t)) {
				if(t < minT) {
					minT = t;
				}
			}
		}

		t = minT;
		return minT != INFINITY;
		//}
	}
};
