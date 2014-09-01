#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	void Layout::Update(int deltaMillis)
	{
		View::Update(deltaMillis);

		if (this->GetParent()) {
			if (this->IsLayoutInvalid()) {
				this->Measure(this->GetParent()->GetSize());
			}
			
		}
	}

	void Layout::Measure(const Size &parentSize)
	{
		View::Measure(parentSize);

		this->PositionSubviews();

		const Size &sizeSpec = this->GetLayoutParams().size;
		if (sizeSpec.width == WRAP_CONTENT || sizeSpec.height == WRAP_CONTENT) {
			this->WrapToSubviews();
		}

		this->PostLayout();
	}

	void Layout::WrapToSubviews()
	{
		const Size &spec = this->GetLayoutParams().size;
		Size size = this->GetSize();

		const Rect &padding = this->GetPadding();
		
		// If the size is wrap content, we can now set the size with our subviews measured
		if (spec.width == WRAP_CONTENT) {
			if (this->GetSubviews().size() == 0) {
				size.width = 0;
			}
			else {
				int left = INFINITY, right = -INFINITY;

				for (View *view : this->GetSubviews()) {
					left = glm::min<real>(left, view->GetX());
					right = glm::max<real>(right, view->GetX() + view->GetWidth() + view->GetRightMargin());
				}

				size.width = (right - left) + padding.right + padding.left;
			}
		}

		if (spec.height == WRAP_CONTENT) {
			if (this->GetSubviews().size() == 0) {
				size.height = 0;
			}
			else {
				int top = INFINITY, bottom = -INFINITY;

				for (View *view : this->GetSubviews()) {
					top = glm::min<real>(top, view->GetY());
					bottom = glm::max<real>(bottom, view->GetY() + view->GetHeight() + view->GetBottomMargin());
				}

				size.height = (bottom - top) + padding.bottom + padding.top;
			}
		}

		this->SetSize(size);
	}
};