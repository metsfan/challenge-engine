#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class StaticBlock
	{
	public:
		StaticBlock(std::function<void()> func)
		{
			func();
		}

		~StaticBlock() {}
	};
}