#pragma once

#include <Engine/Challenge.h>

namespace challenge 
{
	typedef enum {
		RenderPassStatic,
		RenderPassActor,
		RenderPassLast
	} RenderPass;

	class SceneNodeProperties
	{
		friend class SceneNode;

	protected:
		ActorId mActorId;
		std::string mName;
		glm::mat4 mToWorld, mFromWorld;
		float mRadius;
		RenderPass mRenderPass;
		bool mHasAlpha;

	public:
		ActorId ActorId() { return mActorId; }

		glm::mat4 ToWorld() { return mToWorld; }
		glm::mat4 FromWorld() { return mFromWorld; }
		void Transform(glm::mat4 toWorld, glm::mat4 fromWorld) 
		{
			mToWorld = toWorld;
			mFromWorld = fromWorld;
		}

		const char * Name() { return mName.c_str(); }

		bool HasAlpha() { return mHasAlpha; }
		void SetAlpha(bool hasAlpha) { mHasAlpha = hasAlpha; }

		float Radius() { return mRadius; }

		RenderPass RenderPass() { return mRenderPass; }
	};

	class Scene;

	class ISceneNode 
	{
	public:
		virtual SceneNodeProperties GetProps() = 0;

		virtual void SetTransform(glm::mat4 *toWorld, glm::mat4 *fromWorld) = 0;

		virtual bool OnUpdate(Scene *pScene, long elapsedMs) = 0; 

		virtual bool PreRender(Scene *pScene) = 0;
		virtual void Render(Scene *pScene) = 0;
		virtual void RenderChildren(Scene *pScene) = 0;
		virtual void PostRender(Scene *pScene) = 0;

		virtual void AddChild(ISceneNode *newChild) = 0;
		virtual void SetParent(ISceneNode *parent) = 0;
	};

	typedef std::vector<ISceneNode *> SceneNodeList;

	class SceneNode : public ISceneNode
	{
		friend class Scene;

	public:
		SceneNode(ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld);
		virtual ~SceneNode();

		virtual SceneNodeProperties GetProps() { return mProps; }

		virtual void SetTransform(glm::mat4 *toWorld, glm::mat4 *fromWorld);

		virtual bool OnUpdate(Scene *pScene, long elapsedMs); 

		virtual bool PreRender(Scene *pScene);
		virtual void Render(Scene *pScene);
		virtual void RenderChildren(Scene *pScene);
		virtual void PostRender(Scene *pScene);

		virtual void AddChild(ISceneNode *newChild);
		virtual void RemoveChild(ActorId id);

		void SetParent(ISceneNode *parent) { mParent = parent; }

	protected:
		SceneNodeList mChildren;
		ISceneNode *mParent;
		SceneNodeProperties mProps;
	};
};