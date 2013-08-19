#include <Engine/Challenge.h>
#include <Engine/UI/Controls/PanelView.h>
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
