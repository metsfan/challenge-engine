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

	class LinearLayout : public Layout
	{
	public:
		LinearLayout(const Size &size = Size(), LinearLayoutOrientation orientation = LinearLayoutVertical);
		~LinearLayout();

		void ParseFromXML(XMLNode &node);

	protected:
		void PositionSubviews();
		void PostLayout();

	private:
		LinearLayoutOrientation mOrientation;


	};
};