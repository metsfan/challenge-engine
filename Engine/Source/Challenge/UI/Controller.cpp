#include <Challenge/Challenge.h>
#include <Challenge/UI/Controller.h>

namespace challenge
{
	Controller::Controller() :
		mView(new View())
	{
		Dispatch::PushTask(Dispatch::MainQueue, [this]() {
			this->OnLoad();
		});
	}

	Controller::Controller(const std::string &layout) :
		mView(View::CreateFromResource(layout))
	{
		Dispatch::PushTask(Dispatch::MainQueue, [this]() {
			this->OnLoad();
		});
	}

	Controller::Controller(View *view) :
		mView(view)
	{
		Dispatch::PushTask(Dispatch::MainQueue, [this]() {
			this->OnLoad();
		});
		
	}

	Controller::~Controller()
	{
	}

	void Controller::OnLoad()
	{
	}

	void Controller::OnAppear()
	{
	}

	void Controller::OnDisappear()
	{
	}

	void Controller::Update(int deltaMillis)
	{
	}
}