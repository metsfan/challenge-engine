#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/UI.h>
#include <Challenge/View/Actor.h>

namespace challenge
{
	typedef std::map<ActorId, IActor*> TActorList;

	class GameView
	{
	public:
		GameView(void);
		virtual ~GameView();

		virtual void OnUpdate();
		virtual void OnRender();
		virtual void AddControl(View *control);
		virtual void AddActor(IActor *actor);

	protected:
		View *mRootControl;
		TActorList mActors;
	};
};