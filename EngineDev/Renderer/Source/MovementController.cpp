#include "MovementController.h"

MovementController::MovementController() :
	mAngle(0),
	mPosition(0.0)
{
}

MovementController::~MovementController()
{
}


void MovementController::OnKeyDown(const KeyboardEvent &e)
{
}

void MovementController::OnKeyUp(const KeyboardEvent &e)
{
}

void MovementController::OnKeyPress(const KeyboardEvent &e)
{
	float factor = 0.25;

	switch(e.keyCode) {
	case 'Q':
		mPosition.x += cos(mAngle*DEG2RAD) * factor;
		mPosition.z += sin(mAngle*DEG2RAD) * factor;
		break;

	case 'E':
		mPosition.x -= cos(mAngle*DEG2RAD) * factor;
		mPosition.z -= sin(mAngle*DEG2RAD) * factor;
		break;

	case 'W':
		mPosition.x -= sin(mAngle*DEG2RAD) * factor;
		mPosition.z += cos(mAngle*DEG2RAD) * factor;
		break;

	case 'S':
		mPosition.x += sin(mAngle*DEG2RAD) * factor;
		mPosition.z -= cos(mAngle*DEG2RAD) * factor;
		break;

	case 'A':
		mAngle -= 1;
		break;

	case 'D':
		mAngle += 1;
		break;

	case 'Z':
		mPosition.y -= factor;
		break;

	case 'X':
		mPosition.y += factor;
		break;
	}
}