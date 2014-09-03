#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>

namespace challenge
{
	class FrameLayout : public Layout
	{
	public:
	public:
		FrameLayout(const Size &size = Size()) : Layout(size) {}
		~FrameLayout() {}

	protected:

		virtual void PositionSubviews() {}
		virtual void PostLayout();
	};
};