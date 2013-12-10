#include <Challenge/Challenge.h>
#include <Challenge/UI/Dialog/Dialog.h>

namespace challenge
{
	void Dialog::ShowInWindow(Window *window, bool modal)
	{
		if (modal) {
			mModalWindow = new View(window->GetFrame());
			mModalWindow->SetBackgroundColor(Color(0, 0, 0, 150));
			window->AddSubview(mModalWindow);
		}
	}

	void Dialog::Dismiss()
	{
		mModalWindow->RemoveFromSuperview();
		this->RemoveFromSuperview();
		this->SafeDelete();
	}

};