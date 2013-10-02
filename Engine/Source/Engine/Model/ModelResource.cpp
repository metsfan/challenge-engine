#include <Engine/Challenge.h>
#include <Engine/Model/ModelResource.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Model/ModelBone.h>
#include <Engine/Model/ModelMaterial.h>
#include <Engine/Util/Util.h>

#include <rapidxml/rapidxml.hpp>

namespace challenge
{
	ModelResource::ModelResource() :
		mShape(NULL)
	{
	}

	ModelResource::~ModelResource()
	{
	}

	bool ModelResource::Initialize(const std::vector<ModelMesh *> &meshes)
	{
		mMeshes = meshes;
		for(int i = 0; i < mMeshes.size(); i++) {
			mNumVerts += mMeshes[i]->GetTotalFaces();
		}

		this->LoadAnimations();

		return true;
	}

	bool ModelResource::Initialize(const ModelVertex *verts, int nVerts)
	{
		ModelMesh *mesh = new ModelMesh(verts, nVerts);
		mMeshes.push_back(mesh);
		mNumVerts = nVerts;

		this->LoadAnimations();

		return true;
	}

	bool ModelResource::Initialize(const std::string &filename)
	{
		std::ifstream file(filename, std::ios::in | std::ios::binary);

		if(file.good()) {
			
			int lastSlash = filename.rfind('/');
			mModelPath = filename.substr(0, lastSlash+1);

			//Logger::log(LogDebug, "Model path: %s", mModelPath.c_str());
			
			this->Unserialize(file);
			this->LoadAnimations();

			return true;
		}
		
		return false;
	}

	bool ModelResource::Unserialize(std::ifstream &in)
	{
		// Read number of meshes
		int nMeshes;
		in.read((char *)&nMeshes, sizeof(int));

		// Read meshes
		for(int i = 0; i < nMeshes; i++) {
			ModelMesh *mesh = new ModelMesh();
			mesh->Unserialize(in);
			mMeshes.push_back(mesh);
		}

		bool animated;
		in.read((char *)&animated, sizeof(bool));

		if(animated) {
			// Read keyframe times
			int nKeyframes;
			in.read((char *)&nKeyframes, sizeof(int));
			for(int i = 0; i < nKeyframes; i++) {
				double animTime;
				in.read((char *)&animTime, sizeof(double));
				mAnimKeyframeTimes.push_back(animTime);
			}

			// Read bones
			int nBones;
			in.read((char *)&nBones, sizeof(int));

			glm::mat4 transform;
			for(int i = 0; i < nKeyframes; i++) {
				mBoneMatrices.push_back(std::vector<glm::mat4>());

				for(int j = 0; j < nBones; j++) {
					in.read((char *)&transform[0][0], sizeof(float) * 16);
					//mBones[j]->SetKeyframeTransform(i, transform);
					mBoneMatrices[i].push_back(transform);
				}
			}
		}

		int nMaterials;
		in.read((char *)&nMaterials, sizeof(int));
		for(int i = 0; i < nMaterials; i++) {
			ModelMaterial *material = new ModelMaterial();
			material->Unserialize(in, mModelPath);
			mMaterials.push_back(material);
		}

		return true;
	}

	void ModelResource::LoadAnimations()
	{
		std::string text = Util::ReadContentsOfFile(mModelPath + "animations.xml");

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

				ModelAnimation anim;
				anim.startFrame = anim.currentFrame = startFrame;
				anim.endFrame = endFrame;
				anim.numFrames = endFrame - startFrame;
				anim.startTime = (mAnimKeyframeTimes[startFrame] * 1000);
				int endTime = (mAnimKeyframeTimes[endFrame] * 1000);
				anim.timeDelta = endTime - anim.startTime;
				anim.elapsed = 0;

				mAnimations[name] = anim;

				animationNode = animationNode->next_sibling();
			}

			printf("stop");
		}
	}

	const std::vector<glm::mat4>& ModelResource::GetBonesForKeyframe(int keyframe)
	{
		return mBoneMatrices[keyframe];
	}

	void ModelResource::Render(IGraphicsDevice *device, RenderState &state, int animFrame, int materialId)
	{
		if(!mShape) {
			mShape = new ModelShape(device, this);
		}

		mShape->SetCurrentAnimFrame(animFrame);
		mShape->SetMaterialId(materialId);

		mShape->Draw(device, state);
	}

	IGeometricShape* ModelResource::CreateBoundingVolume(const GeometricShapeType type, const glm::mat4 &transform)
	{
		// Check for a cached version
		if(mBoundingVolumes.count(type)) {
			return mBoundingVolumes[type];
		}

		// No cached version, so we must create it.  So let's aggregate a list of each mesh's points
		int totalVerts = 0;
		for(ModelMesh *mesh : mMeshes) {
			int numVerts = mesh->GetTotalFaces();
			totalVerts += numVerts;
		}

		std::vector<glm::vec3> pointsList;
		pointsList.reserve(totalVerts);

		for(ModelMesh *mesh : mMeshes) {
			ModelVertex *verts = mesh->GetBuffer();
			int numVerts = mesh->GetTotalFaces();

			for(int i = 0; i < numVerts; i++) {
				ModelVertex &vert = verts[i];
				pointsList.push_back(glm::vec3(vert.position[0], vert.position[1], vert.position[2]));
			}
		}

		mBoundingVolumes[type] = GeometricShapeFactory::CreateFromPointsList(type, pointsList, transform);

		return mBoundingVolumes[type];
	}
};