#include <Engine/Challenge.h>
#include <Engine/UI/Window.h>
#include <Engine/UI/View.h>
#include <Engine/UI/ViewManager.h>

namespace challenge
{
	Window::Window(Size size) :
		View(Frame(0, 0, size.width, size.height)),
		mFocusedView(NULL)
	{
		mCamera = new OrthoCamera(0.0f, size.width, size.height, 0.0f, -1000.0f, 1000.0f, size);

		this->RegisterCoreUIClasses();
	}

	Window::~Window()
	{
	}

	bool Window::Initialize()
	{
		return true;
	}

	void Window::SetFocusedView(View *focusedView)
	{
		if (mFocusedView) {
			mFocusedView->mFocused = false;
		}

		mFocusedView = focusedView;
	}

	void Window::UnfocusView(View *view)
	{
		if (mFocusedView == view) {
			mFocusedView = NULL;
			view->mFocused = false;
		}
	}

	void Window::Update(int deltaMillis)
	{
		View::Update(deltaMillis);
	}

	void Window::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		state.SetProjection(mCamera->GetProjectionMatrix());

		//state.PushTransform(mCamera->GetViewMatrix());
		device->DisableState(DepthTest);
		device->EnableState(AlphaBlending);

		View::Render(device, state, parentFrame);
	}

	void Window::RegisterCoreUIClasses()
	{
		View::RegisterViewClass("View", [](Frame frame) { return new View(frame); });
		View::RegisterViewClass("Button", [](Frame frame) { return new ButtonView(frame); });
		View::RegisterViewClass("Checkbox", [](Frame frame) { return new CheckboxView(frame); });
		View::RegisterViewClass("Form", [](Frame frame) { return new Form(frame); });
		View::RegisterViewClass("Label", [](Frame frame) { return new LabelView(frame); });
		View::RegisterViewClass("Options", [](Frame frame) { return new OptionsView(frame); });
		View::RegisterViewClass("Panel", [](Frame frame) { return new PanelView(frame); });
		View::RegisterViewClass("SelectList", [](Frame frame) { return new SelectListView(frame); });
		View::RegisterViewClass("TextField", [](Frame frame) { return new TextFieldView(frame); });
	}

	/* IKeyboardListener methods */
	bool Window::OnKeyboardEvent(const KeyboardEvent &e)
	{
		const TViewList &subviews = this->GetSubviews();
		if (!subviews.size()) {
			return false;
		}

		View *selectedView = mFocusedView;
		bool handled = false;

		while (selectedView) {
			if (selectedView->mKeyboardDelegates.size() > 0 &&
				selectedView->mKeyboardDelegates[e.type].size() > 0) {
				std::vector<KeyboardEventDelegate> delegates = selectedView->mKeyboardDelegates[e.type];

				for (int i = 0; i < delegates.size(); i++) {
					delegates[i](selectedView, e);
				}

				handled = true;
			}

			selectedView = selectedView->GetParent();
		}

		return handled;
	}

	/* IMouseListener methods */
	bool Window::OnMouseEvent(const MouseEvent &e)
	{
		const TViewList &subviews = this->GetSubviews();
		if (!subviews.size()) {
			return false;
		}

		bool handled = false;

		if (e.type == MouseEventMouseWheelMove) {
			View *selectedView = mFocusedView;
			while (selectedView) {
				if (selectedView->mMouseDelegates.size() > 0 &&
					selectedView->mMouseDelegates[e.type].size() > 0) {
					std::vector<MouseEventDelegate> delegates = selectedView->mMouseDelegates[e.type];

					for (int i = 0; i < delegates.size(); i++) {
						delegates[i](selectedView, e);
					}

					handled = true;
				}

				selectedView = selectedView->GetParent();
			}
		}
		else {
			View *selectedView = this->GetSelectedView(e.position);
			if (e.type == MouseEventMouseDown) {
				if (mFocusedView) {
					mFocusedView->SetFocused(false);
				}

				mFocusedView = selectedView;
				mFocusedView->SetFocused(true);
			}


			while (selectedView) {
				if (selectedView->mMouseDelegates.size() > 0 &&
					selectedView->mMouseDelegates[e.type].size() > 0) {
					std::vector<MouseEventDelegate> delegates = selectedView->mMouseDelegates[e.type];

					for (int i = 0; i < delegates.size(); i++) {
						delegates[i](selectedView, e);
					}
				}

				selectedView = selectedView->GetParent();

				if (selectedView != this) {
					handled = true;
				}
			}
		}

		return handled;
	}
};