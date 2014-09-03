#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/FrameLayout.h>

namespace challenge
{
	void FrameLayout::PostLayout()
	{
		if (this->GetSubviews().size() > 0) {
			ViewAlignment align = this->GetLayoutParams().subviewAlignment;

			const Size &spec = this->GetLayoutParams().size;

			View *view = this->GetSubviews()[0];
			Frame frame = view->GetFrame();

			const Rect &padding = this->GetPadding();
			const Rect &viewMargin = this->GetMargin();

			if (view->GetLayoutParams().alignment != AlignmentInherit) {
				align = view->GetLayoutParams().alignment;
			}

			if (spec.width != WRAP_CONTENT) {
				if (align & AlignmentLeft) {
					frame.origin.x = padding.left;
				}
				else if (align & AlignmentRight) {
					frame.origin.x = this->GetWidth() - frame.size.width - padding.right;
				}
				else if (align & AlignmentCenterHorizontal) {
					frame.origin.x = (this->GetWidth() - frame.size.width) * 0.5;
				}
			}

			if (spec.height != WRAP_CONTENT) {
				if (align & AlignmentTop) {
					frame.origin.y = padding.top;
				}
				else if (align & AlignmentBottom) {
					frame.origin.y = this->GetHeight() - frame.size.height - padding.bottom;
				}
				else if (align & AlignmentCenterVertical) {
					frame.origin.y = (this->GetHeight() - frame.size.height) * 0.5;
				}
			}
		}
	}
}