#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Dialog/Dialog.h>
#include <Challenge/UI/Controls/ButtonView.h>

namespace challenge
{
	class AlertDialog;

	typedef std::function<void(AlertDialog *, int, std::string)> AlertDialogButtonClickDelegate;

	class AlertDialog : public Dialog
	{
	public:
		AlertDialog(const char *title, const char *message,
			const char *mainButtonText, const char * ...);
		~AlertDialog();

		void AddButtonClickDelegate(AlertDialogButtonClickDelegate del)
		{
			mClickDelegates.push_back(del);
		}

		void SetButtons(const char *mainButtonText, const char *...);

		void SetTitle(const std::string &title)
		{
			mTitleLabel->SetText(title);
		}

		void SetMessage(const std::string &message)
		{
			mMessageLabel->SetText(message);
		}

		void ShowInWindow(Window *window, bool modal = true);

	private:
		std::vector<AlertDialogButtonClickDelegate> mClickDelegates;
		std::vector<ButtonView *> mButtons;
		LabelView *mTitleLabel;
		LabelView *mMessageLabel;
		View *mButtonsView;

		void SetButtons(const char *mainButtonText, va_list others);
	};
};