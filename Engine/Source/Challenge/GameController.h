#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/View/GameView.h>

namespace challenge
{
	//typedef std::vector<GameView *> TViewList;

	class GameController
	{
	public:
		GameController();
		virtual ~GameController();

		virtual void OnUpdate();
		virtual void OnRender();
		
		void SetView(GameView *view) { mView = view; }
		GameView* GetView() { return mView; }


	protected:
		GameView *mView;
	};
};