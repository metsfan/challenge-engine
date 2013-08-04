#include <Engine/Challenge.h>
#include "Window.h"

namespace challenge
{
	BaseWindow::BaseWindow(std::string title, Size size) :
		mSize(size),
		mTitle(title),
		mInputReader(NULL)
	{
	}

	BaseWindow::~BaseWindow()
	{
	}
};