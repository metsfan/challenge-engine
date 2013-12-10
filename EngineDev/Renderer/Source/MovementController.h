#pragma once

#include <Engine/Core/Globals.h>
#include <Engine/Input/KeyboardListener.h>

using namespace challenge;

class MovementController : public IKeyboardListener
{
public:
	MovementController();
	~MovementController();

	void OnKeyDown(const KeyboardEvent &e);
	void OnKeyUp(const KeyboardEvent &e);
	void OnKeyPress(const KeyboardEvent &e);

	glm::vec3& GetPosition() { return mPosition; }
	float GetAngle() { return mAngle; }

private:
	glm::vec3 mPosition;
	float mAngle;
};