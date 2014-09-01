#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Dialog : public View
	{
	public:
		Dialog() :
			View(Frame(0, 0, 0, 0)),
			mModalWindow(NULL)
		{
		}

		virtual ~Dialog()
		{
			mModalWindow->RemoveFromSuperview();
			delete mModalWindow;
		}

		virtual void ShowInWindow(Window *window, bool modal = true);
		virtual void Dismiss();

	private:
		View *mModalWindow;
	};
};