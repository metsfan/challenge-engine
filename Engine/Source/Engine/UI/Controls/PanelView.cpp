#include <Engine/Challenge.h>
#include <Engine/UI/Controls/PanelView.h>

namespace challenge
{
	PanelView::PanelView(Frame frame) : View(frame)
	{
		mScrollable = false;
	}

	PanelView::~PanelView(void)
	{
	}

	void PanelView::PreRender(UIManager *manager, Point origin)
	{
	}
};
