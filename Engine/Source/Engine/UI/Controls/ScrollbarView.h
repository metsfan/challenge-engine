#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>

namespace challenge
{
	class PanelView;

	class ScrollbarView : View
	{
	public:
		ScrollbarView(Frame frame = Frame());
		~ScrollbarView();

	private:
		Point mScrollPosition;
		PanelView *mScroller;
	};
};