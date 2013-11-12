#include <Engine/Challenge.h>
#include "GraphicsDevice.h"

namespace challenge
{
	BaseGraphicsDevice::BaseGraphicsDevice(GRAPHICS_DEVICE_DESC graphicsDesc, const Size &screenSize) :
		mDesc(graphicsDesc),
		mScreenSize(screenSize)
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

		case ScissorTest:
			this->SetScissorTest(true);
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

		case ScissorTest:
			this->SetScissorTest(false);
			break;
		};
	}
};

