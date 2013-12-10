#include <Challenge/Challenge.h>
#include "GameController.h"
using namespace challenge;

GameController::GameController()
{
	mView = NULL;
}

GameController::~GameController()
{
}

void GameController::OnUpdate()
{
	if(mView) {
		mView->OnUpdate();
	}
}

void GameController::OnRender()
{
	if(mView) {
		mView->OnRender();
	}
}