#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	struct InputElement
	{
		std::string name;
		int numComponents;
		int offset;
	};
	
	typedef std::vector<InputElement> TInputElementList;

	class InputLayout
	{
	public:
		InputLayout();
		~InputLayout();

		void AddElement(std::string name, int numComponents, int offset);
		const TInputElementList& GetElements() { return mElements; }

	private:
		TInputElementList mElements;
	};
};