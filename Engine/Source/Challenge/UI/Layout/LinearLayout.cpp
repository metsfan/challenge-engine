#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/LinearLayout.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	LinearLayout::LinearLayout(LinearLayoutOrientation orientation) :
		BaseLayout(),
		mOrientation(orientation)
	{
	}

	LinearLayout::~LinearLayout()
	{
	}

	void LinearLayout::PositionSubviews(View *view, bool updateSize)
	{
		if (!view->IsVisible()) {
			return;
		}

		TViewList subviews = view->GetSubviews();
		
		int currentPos = 0;
		for(int i = 0; i < subviews.size(); i++) {
			View *subview = subviews[i];
			if (subview->IsVisible()) {
				const Frame &frame = subview->GetFrame();
				const Rect &padding = subview->GetPadding();
				if (mOrientation == LinearLayoutHorizontal) {
					subview->SetX(currentPos + padding.left);
					currentPos += frame.size.width + padding.left + padding.right;
				}
				else {
					subview->SetY(currentPos + padding.top);
					currentPos += frame.size.height + padding.top + padding.bottom;
				}
				Logger::Log(LogDebug, "Current pos: %d", currentPos);
			}
		}

		BaseLayout::PositionSubviews(view, updateSize);
	}
};