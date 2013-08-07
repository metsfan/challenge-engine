#include <Engine/Challenge.h>
#include "GraphicsDevice.h"

namespace challenge
{
	BaseGraphicsDevice::BaseGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, IWindow *window) :
		mDesc(graphicsDesc),
		mWindow(window)
	{
	}

	BaseGraphicsDevice::~BaseGraphicsDevice()
	{
	}

	void BaseGraphicsDevice::EnableState(GraphicsState state)
	{
		switch(state)
		{
		case DepthTest:
			this->SetDepthTest(true);
			break;

		case AlphaBlending:
			this->SetAlphaBlending(true);
			break;
		};
	}

	void BaseGraphicsDevice::DisableState(GraphicsState state)
	{
		switch(state)
		{
		case DepthTest:
			this->SetDepthTest(false);
			break;

		case AlphaBlending:
			this->SetAlphaBlending(false);
			break;
		};
	}
};

