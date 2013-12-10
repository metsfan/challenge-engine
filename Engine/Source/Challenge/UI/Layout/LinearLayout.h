#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>

namespace challenge
{
	enum LinearLayoutOrientation
	{
		LinearLayoutVertical,
		LinearLayoutHorizontal
	};

	class LinearLayout : public BaseLayout
	{
	public:
		LinearLayout(LinearLayoutOrientation orientation = LinearLayoutVertical);
		~LinearLayout();

		void PositionSubviews(View *view, bool updateSize);

	private:
		LinearLayoutOrientation mOrientation;


	};
};