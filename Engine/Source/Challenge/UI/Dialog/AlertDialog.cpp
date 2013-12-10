#include <Challenge/Challenge.h>
#include <Challenge/UI/Dialog/AlertDialog.h>
#include <Challenge/UI/Layout/LinearLayout.h>

namespace challenge
{
	AlertDialog::AlertDialog(const char *title, const char *message,
		const char *mainButtonText, const char * ...) :
		Dialog(),
		mTitleLabel(new LabelView(Frame(0, 0, 100, 30))),
		mMessageLabel(new LabelView(Frame(0, 0, 100, 30))),
		mButtonsView(new View())
	{
		this->SetLayoutType(LayoutTypeLinear);

		this->AddInternalSubview(mTitleLabel);
		mTitleLabel->SetText(title);

		this->AddInternalSubview(mMessageLabel);
		mMessageLabel->SetText(message);

		mButtonsView->SetLayoutEngine(new LinearLayout(LinearLayoutHorizontal));
		this->AddInternalSubview(mButtonsView);

		va_list args;
		va_start(args, mainButtonText);
		this->SetButtons(mainButtonText, args);
		va_end(args);

		this->SetBackgroundColor(Color::Gray());
	}

	AlertDialog::~AlertDialog()
	{
	}

	void AlertDialog::SetButtons(const char *mainButtonText, const char * ...)
	{
		va_list args;
		va_start(args, mainButtonText);
		this->SetButtons(mainButtonText, args);
		va_end(args);
	
	}

	void AlertDialog::SetButtons(const char *mainButtonText, va_list others)
	{
		int i = 0;
		while (true) {
			const char *arg = NULL;

			if (i == 0) {
				arg = mainButtonText;
			}
			else {
				arg = va_arg(others, const char *);
			}

			if (arg == NULL) {
				break;
			}

			ButtonView *button = new ButtonView(Frame(0, 0, 100, 30));
			button->SetTitleText(arg);
			button->AddMouseEvent(MouseEventMouseUp, [this, i, arg](View *sender, const MouseEvent &e) {
				for (auto del : mClickDelegates) {
					del(this, i, arg);
				}
			});

			mButtonsView->AddSubview(button);

			i++;
		}
	}

	void AlertDialog::ShowInWindow(Window *window, bool modal)
	{
		Dialog::ShowInWindow(window, modal);

		window->AddSubview(this);
		int x = (window->GetWidth() * 0.5) - (this->GetWidth() * 0.5);
		int y = (window->GetHeight() * 0.5) - (this->GetHeight() * 0.5);

		this->SetPosition(x, y);
	}
}