#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/PanelView.h>
#include "ScrollbarView.h"

namespace challenge
{
	ScrollbarView::ScrollbarView(Frame frame) :
		View(frame)
	{
		mScroller = new PanelView();
	}

	ScrollbarView::~ScrollbarView()
	{
	}
};
