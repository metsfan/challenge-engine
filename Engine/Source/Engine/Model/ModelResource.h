#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape/ModelShape.h>
#include <Engine/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	struct ModelAnimation {
		int startFrame;
		int endFrame;
		int numFrames;
		int currentFrame;
		int elapsed;
		int startTime;
		int timeDelta;
	};

	struct ModelVertex {
		float position[3];
		float normal[3];
		float texCoord[2];
		float boneWeights[4];
		float boneIndices[4];
	};

	class ModelMesh;
	class ModelMaterial;
	class ModelBone;

	typedef std::vector<ModelMesh *> TMeshList;
	//typedef std::vector<ModelAnimation *> TAnimList;
	typedef std::vector<ModelMaterial *> TMaterialList;
	typedef std::map<std::string, ModelAnimation> TAnimList;
	typedef std::vector<ModelBone *> TBoneList;

	class ModelResource
	{
		friend class Model;

	public:
		ModelResource();
		~ModelResource();

		bool Initialize(const std::vector<ModelMesh *> &meshes);
		bool Initialize(const ModelVertex *verts, int nVerts);
		bool Initialize(const std::string &filename);

		const TMeshList& GetMeshes() { return mMeshes; }
		int GetVertexCount() { return mNumVerts; }
		TMaterialList& GetMaterials() { return mMaterials; }
		const std::vector<glm::mat4>& GetBonesForKeyframe(int keyframe);

		bool IsAnimated() { return mAnimations.size() > 0; }

		void Render(IGraphicsDevice *device, RenderState &state, int animFrame, int materialId);

		void SetBlendColor(const glm::vec4 &color) { mBlendColor = color; }

	private:
		ModelShape *mShape;
		std::string mModelPath;
		TMeshList mMeshes;
		TAnimList mAnimations;
		TMaterialList mMaterials;
		TBoneList mBones;
		std::vector<double> mAnimKeyframeTimes;
		std::vector<std::vector<glm::mat4> > mBoneMatrices;
		int mNumVerts;
		int mActiveAnimFrame;
		std::map<GeometricShapeType, IGeometricShape *> mBoundingVolumes;
		glm::vec4 mBlendColor;

		bool Unserialize(std::ifstream &in);
		void LoadAnimations();

		IGeometricShape* CreateBoundingVolume(const GeometricShapeType type, const glm::mat4 &transform);
	};
};