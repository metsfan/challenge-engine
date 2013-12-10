#include <Challenge/Challenge.h>
#include "InputLayout.h"

namespace challenge
{
	InputLayout::InputLayout()
	{
	}

	InputLayout::~InputLayout()
	{
	}

	void InputLayout::AddElement(std::string name, int numComponents, int offset)
	{
		InputElement element = { name, numComponents, offset };
		mElements.push_back(element);
	}
};