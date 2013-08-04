#pragma once

#pragma once

#include <Engine/Challenge.h>
#include <Engine/View/GameView.h>

namespace challenge
{
	typedef std::vector<GameView *> TViewList;

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