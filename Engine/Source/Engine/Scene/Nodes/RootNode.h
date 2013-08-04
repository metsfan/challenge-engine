#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/SceneNode.h>

namespace challenge
{
	class RootNode : public SceneNode
	{
	public:
		RootNode();
		
		virtual void AddChild(ISceneNode *newChild);
		virtual void RenderChildren(Scene *pScene);
	};
};