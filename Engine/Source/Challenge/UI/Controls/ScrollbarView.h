#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	class PanelView;

	class ScrollbarView : View
	{
	public:
		ScrollbarView(Frame frame = Frame());
		virtual ~ScrollbarView();

	private:
		Point mScrollPosition;
		PanelView *mScroller;
	};
};