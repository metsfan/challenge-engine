#include <Engine/Challenge.h>
#include <Engine/UI/Window.h>
#include <Engine/UI/View.h>
#include <Engine/UI/ViewManager.h>

namespace challenge
{
	BaseWindow::BaseWindow(std::string title, Size size, IWindowListener *listener) :
		mSize(size),
		mTitle(title),
		mInputReader(NULL),
		mListener(listener),
		mViewManager(new ViewManager(size))
	{
	}

	BaseWindow::~BaseWindow()
	{
		this->WindowDestroyed();

		delete mListener;
	}

	void BaseWindow::SetRootView(View *rootView)
	{
		mViewManager->SetRootView(rootView);
		rootView->SetWindow(this);
	}

	void BaseWindow::SetFocusedView(View *focusedView)
	{
		mViewManager->SetFocusedView(focusedView);
	}

	void BaseWindow::UnfocusView(View *view)
	{
		mViewManager->UnfocusView(view);
	}

	void BaseWindow::WindowInitialized(GameApplication *app)
	{
		mApplication = app;

		if (mListener) {
			mListener->OnWindowInitialized(this, app);
		}
	}

	void BaseWindow::WindowDestroyed()
	{
		if (mListener) {
			mListener->OnWindowDestroyed(this, mApplication);
		}
	}

	void BaseWindow::WindowUpdate(uint32_t deltaMillis)
	{
		if (mListener) {
			mListener->OnWindowUpdate(this, mApplication, deltaMillis);
		}

		mViewManager->Update(deltaMillis);
	}

	void BaseWindow::WindowDraw()
	{
		// Render frame from listener

		mApplication->PreRender();

		if (mListener) {
			mListener->OnWindowDraw(this, mApplication, mApplication->GetGraphicsDevice());
		}

		// Render GUI after

		mViewManager->Render(mApplication->GetGraphicsDevice());

		mApplication->PostRender();
	}
};