#include <Challenge/Challenge.h>
#include <Challenge/UI/Window.h>
#include <Challenge/UI/View.h>
#include <Challenge/UI/UI.h>
#include <Challenge/UI/Controller.h>

namespace challenge
{
	Window::Window(Size size) :
		View(Frame(0, 0, size.width, size.height)),
		mFocusedView(NULL),
		mHoveredView(NULL)
	{
		mCamera = new OrthoCamera(0.0f, size.width, size.height, 0.0f, -1000.0f, 1000.0f, size);

		this->RegisterCoreUIClasses();

		this->ClipSubviews(true);

		mWindow = this;
	}

	Window::~Window()
	{
		delete mCamera;
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
		mControllerStack.top()->Update(deltaMillis);

		View::Update(deltaMillis);
	}

	void Window::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		mControllerStack.top()->Render(device, state);

		state.SetProjection(mCamera->GetProjectionMatrix());

		//state.PushTransform(mCamera->GetViewMatrix());
		device->DisableState(DepthTest);
		device->EnableState(AlphaBlending);
		device->EnableState(ScissorTest);

		View::Render(device, state, parentFrame);

		device->DisableState(ScissorTest);

		Cursor::Render(device, state);

		device->EnableState(DepthTest);
	}

	void Window::AddSubview(View *view)
	{
		View::AddSubview(view);

		view->SetWindow(this);
	}

	View * Window::RemoveSubview(View *view)
	{
		view->SetWindow(NULL);

		if (view->FindView(mHoveredView)) {
			mHoveredView = NULL;
		}

		if (view->FindView(mFocusedView)) {
			mFocusedView = NULL;
		}

		return View::RemoveSubview(view);
	}

	void Window::PushController(Controller *controller)
	{
		if (mControllerStack.size() > 0) {
			Controller *top = mControllerStack.top();
			this->RemoveSubview(top->GetView());

			top->OnDisappear();
		}

		mControllerStack.push(controller);
		
		View *controllerView = controller->GetView();
		controllerView->SetFrame(this->GetFrame());
		this->AddSubview(controllerView);

		controller->OnAppear();
	}

	void Window::PopController()
	{
		if (mControllerStack.size() > 0) { 
			Controller *top = mControllerStack.top();
			this->RemoveSubview(top->GetView());
			mControllerStack.pop();

			top->OnDisappear();
		}

		if (mControllerStack.size() > 0) {
			Controller *controller = mControllerStack.top();
			View *controllerView = controller->GetView();
			controllerView->SetFrame(this->GetFrame());
			this->AddSubview(controllerView);

			controller->OnAppear();
		}
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
		View::RegisterViewClass("Hidden", [](Frame frame) { return new HiddenView(); });
		View::RegisterViewClass("Model3D", [](Frame frame) { return new Model3DView(frame); });
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
			handled |= selectedView->View::OnKeyboardEvent(e);

			if (handled) {
				break;
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
				if (selectedView->View::OnMouseEvent(e)) {
					break;
				}

				handled = true;

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

			if (e.type == MouseEventMouseMove) {
				if (mHoveredView) {
					if (selectedView != mHoveredView) {
						View *currentView = mHoveredView;

						MouseEvent mouseLeaveEvt = e;
						mouseLeaveEvt.type = MouseEventMouseLeave;

						while (currentView) {
							if (currentView->View::OnMouseEvent(mouseLeaveEvt)) {
								break;
							}

							currentView = currentView->GetParent();
						}
					}

					mHoveredView = NULL;
				}

				if (selectedView) {
					mHoveredView = selectedView;

					View *currentView = selectedView;

					MouseEvent mouseEnterEvt = e;
					mouseEnterEvt.type = MouseEventMouseEnter;

					while (currentView) {
						if (currentView->View::OnMouseEvent(mouseEnterEvt)) {
							break;
						}

						currentView = currentView->GetParent();
					}
				}
			}


			if (e.type == MouseEventMouseDown) {
				int x = 0;
			}

			while (selectedView) {
				if (selectedView != this) {
					if (selectedView->View::OnMouseEvent(e)) {
						handled = true;
						break;
					}
				}
				
				selectedView = selectedView->GetParent();	
			}
		}

		return handled;
	}
};