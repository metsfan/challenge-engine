#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include "Scene.h"
using namespace challenge;

Scene::Scene()
{
	mRoot = new RootNode();
	const Size& winSize = GameApplication::GetInstance()->GetWindow()->GetSize();
	Frustum frustum(1.0f, 1500.0f, 45.0f, (float)winSize.width / (float)winSize.height);
	//glm::mat4 cameraMatrix = glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	mCamera = new CameraNode(&cameraMatrix, &frustum);
	GameApplication::GetInstance()->SetMainCamera(mCamera);
}

Scene::~Scene()
{

}

void Scene::OnUpdate(const int elapsedMs)
{
	mRoot->OnUpdate(this, elapsedMs);
}

void Scene::OnRender()
{
	mCamera->SetView(this);
	mRoot->PreRender(this);
	mRoot->Render(this);
	mRoot->RenderChildren(this);
	mRoot->PostRender(this);
}

ISceneNode* Scene::FindActor(ActorId id)
{
	SceneActorMap::iterator i = mActorMap.find(id);
	if(i == mActorMap.end()) {
		return NULL;
	}
	return (*i).second;
}

void Scene::AddChild(ActorId id, ISceneNode *newChild)
{
	mActorMap[id] = newChild;
	mRoot->AddChild(newChild);
}

void Scene::RemoveChild(ActorId id)
{
	mActorMap.erase(id);
	mRoot->RemoveChild(id);
}

void Scene::PushAndSetMatrix(const glm::mat4 &toWorld)
{
	glm::mat4 top = GetTopMatrix();
	glm::mat4 newTop = top * toWorld;
	mMatrixStack.push(newTop);
}

void Scene::PopMatrix()
{
	mMatrixStack.pop();
	glm::mat4 topMatrix = GetTopMatrix();

}

const glm::mat4 Scene::GetTopMatrix()
{
	return mMatrixStack.top();
}