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
};

