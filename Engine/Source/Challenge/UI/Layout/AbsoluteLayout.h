#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>

namespace challenge
{
	class AbsoluteLayout : public Layout
	{
	public:
	public:
		AbsoluteLayout(const Size &size = Size()) : Layout(size) {}
		~AbsoluteLayout() {}

	protected:
		// Do nothing special
		virtual void PositionSubviews() {}
		virtual void PostLayout() {}
	};
};