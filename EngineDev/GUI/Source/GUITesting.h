#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>

using namespace challenge;

class GUITesting : public IApplicationListener
{
public:
	GUITesting()
	{
	}

	~GUITesting()
	{
	}

	void OnApplicationInitialized(GameApplication *app);
	void OnApplicationDestroyed(GameApplication *app);
	void OnApplicationUpdate(GameApplication *app, uint32_t deltaMillis);
	void OnApplicationRender(GameApplication *app, IGraphicsDevice *device);
};