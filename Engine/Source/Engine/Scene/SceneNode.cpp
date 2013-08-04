#include <Engine/Challenge.h>
#include "SceneNode.h"
using namespace challenge;

SceneNode::SceneNode(ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld=NULL) {

	mProps.mActorId = actorId;
	mProps.mName = name;
	mProps.mRenderPass = renderPass;

	SetTransform(toWorld, fromWorld);
}

SceneNode::~SceneNode()
{
}

void SceneNode::SetTransform(glm::mat4 *toWorld, glm::mat4 *fromWorld)
{
	mProps.mToWorld = *toWorld;

	if(fromWorld) {
		mProps.mFromWorld = *fromWorld;
	} else {
		mProps.mFromWorld = glm::inverse(mProps.mToWorld);
	}
}

bool SceneNode::OnUpdate(Scene *pScene, long elapsedMs)
{
	SceneNodeList::iterator i = mChildren.begin();
	SceneNodeList::iterator end = mChildren.end();
	while(i != end) {
		(*i)->OnUpdate(pScene, elapsedMs);
		i++;
	}
	return true;
}

bool SceneNode::PreRender(Scene *pScene)
{
	return true;
}
void SceneNode::Render(Scene *pScene)
{
}

void SceneNode::RenderChildren(Scene *pScene)
{
	SceneNodeList::iterator i = mChildren.begin();
	SceneNodeList::iterator end = mChildren.end();
	while(i != end) {
		ISceneNode *node = *i;
		
		if(node->PreRender(pScene)) {
			node->Render(pScene);
			node->RenderChildren(pScene);
			node->PostRender(pScene);
		}

		i++;
	}
}
void SceneNode::PostRender(Scene *pScene)
{
}

void SceneNode::AddChild(ISceneNode *newChild)
{
	mChildren.push_back(newChild);
	newChild->SetParent(this);
}

void SceneNode::RemoveChild(ActorId id)
{
	SceneNodeList::iterator i = mChildren.begin();
	SceneNodeList::iterator end = mChildren.end();
	while(i != end) {
		ISceneNode *node = *i;
		if(node->GetProps().ActorId() == id) {
			mChildren.erase(i);
			break;
		}
		i++;
	}
}