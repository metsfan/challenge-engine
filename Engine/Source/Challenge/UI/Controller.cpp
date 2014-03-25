#include <Challenge/Challenge.h>
#include <Challenge/UI/Controller.h>

namespace challenge
{
	Controller::Controller() :
		Controller(new View())
	{
	}

	Controller::Controller(const std::string &layout) :
		Controller(View::CreateFromResource(layout))
	{
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