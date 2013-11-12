#include <Engine/Challenge.h>
#include <Engine/UI/ViewManager.h>
#include "GameView.h"
using namespace challenge;

GameView::GameView()
{
	mRootControl = new View();
	//ViewManager::GetDefaultManager()->AddRootControl(mRootControl);
}

GameView::~GameView()
{
}

void GameView::OnUpdate()
{
	/*TActorList::iterator it = mActors.begin();

	while (it != mActors.end()) {
		it->second->OnUpdate(16);
		it++;
	}*/
}

void GameView::OnRender()
{

}

void GameView::AddControl(View *control)
{
	//mRootControl->AddSubcontrol(control);
}

void GameView::AddActor(IActor *actor)
{
	mActors[actor->GetId()] = actor;
}