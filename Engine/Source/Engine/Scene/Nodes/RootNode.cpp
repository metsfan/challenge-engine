#include <Engine/Challenge.h>
#include "RootNode.h"
using namespace challenge;

RootNode::RootNode() : SceneNode("", "Root", RenderPassStatic, &glm::mat4(1.0f), NULL)
{
	SceneNode *staticGroup = new SceneNode("", "StaticGroup", RenderPassStatic, &glm::mat4(1.0f), NULL);
	mChildren.push_back(staticGroup);

	SceneNode *actorGroup = new SceneNode("", "ActorGroup", RenderPassActor, &glm::mat4(1.0f), NULL);
	mChildren.push_back(actorGroup);
}

void RootNode::AddChild(ISceneNode *newChild)
{
	mChildren[newChild->GetProps().RenderPass()]->AddChild(newChild);
}

void RootNode::RenderChildren(Scene *pScene)
{
	for(int pass = RenderPassStatic; pass < RenderPassLast; ++pass) {
		mChildren[pass]->RenderChildren(pScene);
	}
}