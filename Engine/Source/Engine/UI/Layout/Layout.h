#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class ILayout
	{
	public:
		virtual void PositionSubviews(View *view, bool updateSize) = 0;
	};

	class BaseLayout : public ILayout
	{
	public:
		BaseLayout() {}
		~BaseLayout() {}

		void PositionSubviews(View *view, bool updateSize);
	};
};