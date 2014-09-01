#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	class Layout : public View
	{
	public:
		Layout(const Size &size = Size()) : View(size) {}
		~Layout() {}

		virtual void Update(int deltaMillis);
		virtual void Measure(const Size &parentSize);

	protected:
		virtual void PositionSubviews() = 0;
		virtual void PostLayout() = 0;

	private:
		void WrapToSubviews();
	};
};