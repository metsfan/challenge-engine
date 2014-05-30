#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class View;

	class Controller
	{
	public:
		Controller();
		Controller(const std::string &layout);
		Controller(View *view);
		virtual ~Controller();

		virtual void OnLoad();
		virtual void OnAppear();
		virtual void OnDisappear();

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state) {}

		View * GetView() { return mView; }	

	private:
		View *mView;
	};
};