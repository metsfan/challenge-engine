#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Model/ModelResource.h>
#include <Challenge/Renderer/Renderer.h>
#include <Challenge/Math/Ray.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	
	struct ModelAnimParams {
		std::string name;
		bool loop;
	};
	
	__declspec(align(16))
	struct ModelCBMatrices {
		glm::mat4 gWVPMatrix;
		glm::mat3 gNormalMatrix;
	};

	class ModelAnimationManager;

	class Model
	{
	public:
		Model(std::shared_ptr<ModelResource> resource);
		Model(const std::wstring &filepath);
		Model(const std::string &filepath) :
			Model(StringUtil::ToWide(filepath))
		{
		}
		Model(const std::vector<ModelVertex> &points);

		~Model();

		const std::wstring GetFilepath() { return mFilepath; }

		void Transform(const glm::mat4 &transform);

		//void SetTexture(Texture *texture) { mTexture = texture; }
		//Texture * GetTexture() { return mTexture; }
		IGeometricShape* CreateBoundingVolume(GeometricShapeType type, const glm::mat4 &transform);

		void SetIsStatic(bool isStatic) { mStatic = isStatic; }
		bool IsStatic() { return !mResource->IsAnimated(); }
		void SetAnimFrame(int frame);
		void SetNextFrame(int deltaMillis);

		bool UpdateNextRender() { return mUpdateNextRender; }

		void SetActiveAnimation(std::string animation);
		void SetActiveAnimation(std::string animation, bool loop);
		void SetActiveAnimation(ModelAnimParams animation);
		void QueueAnimation(std::string animation, bool loop);
		std::string GetActiveAnimationName() { return mActiveAnimationData.name; }
		ModelAnimation GetActiveAnimation() { return mActiveAnimation; }

		static std::string GetModelBaseDir() { return s_ModelDir; }

		void Unserialize(std::istream &in);

		int GetCurrentAnimationFrame() { return mActiveAnimFrame; }

		void Render(IGraphicsDevice *device, RenderState &state);

		bool GetIntersection(const Ray &ray, float &t);

		void SetBlendColor(const glm::vec4 &color) { mBlendColor = color; }

	protected:
		IGeometricShape *mBoundingVolume;
		std::shared_ptr<ModelResource> mResource;

		int mTotalFaces;
		std::string mModelPath;
		bool mStatic;
		int mActiveAnimFrame;
		bool mUpdateNextRender;
		ModelAnimation mActiveAnimation;
		ModelAnimParams mActiveAnimationData;
		std::list<ModelAnimParams> mAnimationQueue;
		std::wstring mFilepath;
		glm::vec4 mBlendColor;

		void LoadAnimations();
		void PopQueue();

		static std::string s_ModelDir;

		static std::map<std::wstring, std::shared_ptr<ModelResource>> sResourceCache;
		static ModelAnimationManager *mModelAnimator;
	};
};