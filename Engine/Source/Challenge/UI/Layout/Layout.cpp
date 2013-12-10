#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	void BaseLayout::PositionSubviews(View *view, bool updateSize)
	{
		if (updateSize) {
			int width = view->GetWidth(), height = view->GetHeight();

			TViewList subviews = view->GetSubviews();
			for (View *view : subviews) {
				const Frame &frame = view->GetFrame();
				const Rect &padding = view->GetPadding();

				int farX = frame.origin.x + frame.size.width + padding.left + padding.right;
				int farY = frame.origin.y + frame.size.height + padding.top + padding.bottom;
				width = std::max(width, farX);
				height = std::max(height, farY);
			}

			view->SetSize(width, height);
		}
	}
};