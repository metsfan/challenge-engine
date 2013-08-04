#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/SceneNode.h>
#include <Engine/Scene/Nodes/CameraNode.h>
#include <Engine/Scene/Nodes/RootNode.h>

namespace challenge
{
	typedef std::map<ActorId, ISceneNode *> SceneActorMap;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void OnUpdate(const int elapsedMs);
		void OnRender();

		ISceneNode* FindActor(ActorId id);
		void AddChild(ActorId id, ISceneNode *newChild);
		void RemoveChild(ActorId id); 

		void SetCamera(CameraNode* camera) { mCamera = camera; }
		CameraNode* GetCamera() { return mCamera; }

		void PushAndSetMatrix(const glm::mat4 &toWorld);
		void PopMatrix();
		const glm::mat4 GetTopMatrix();

	protected:
		RootNode *mRoot;
		CameraNode *mCamera;
		std::stack<glm::mat4> mMatrixStack;
		SceneActorMap mActorMap;
	};
};