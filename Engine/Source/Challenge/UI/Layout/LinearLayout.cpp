#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/LinearLayout.h>
#include <Challenge/UI/View.h>

namespace challenge
{
	LinearLayout::LinearLayout(const Size &size, LinearLayoutOrientation orientation) :
		Layout(size),
		mOrientation(orientation)
	{
	}

	LinearLayout::~LinearLayout()
	{
	}

	void LinearLayout::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);

		const std::string &orientation = node.GetAttributeString("orientation");
		if (orientation == "horizontal") {
			mOrientation = LinearLayoutHorizontal;
		}
		else {
			mOrientation = LinearLayoutVertical;
		}
	}

	void LinearLayout::PositionSubviews()
	{
		const Rect &padding = this->GetPadding();
		const Rect &margin = this->GetMargin();
		const LayoutParams &layoutParams = this->GetLayoutParams();

		

		Point offset(padding.left, padding.top);
		auto &subviews = this->GetSubviews();

		for (View *view : subviews) {
			if (view->GetVisibility() != ViewVisible) {
				continue;
			}

			const Rect &viewMargin = view->GetMargin();
			const Rect &viewPadding = view->GetPadding();
			Point viewOffset = offset;

			const LayoutParams &viewLayoutParams = view->GetLayoutParams();

			const Frame &frame = view->GetFrame();
			Rect measureBounds(frame.origin.x, frame.origin.y,
				frame.origin.x + frame.size.width, frame.origin.y + frame.size.height);

			measureBounds.left = viewOffset.x + viewMargin.left;
			measureBounds.right = measureBounds.left + frame.size.width + viewPadding.right + viewPadding.left;
			measureBounds.top = viewOffset.y + viewMargin.top;
			measureBounds.bottom = measureBounds.top + frame.size.height + viewPadding.top + viewPadding.bottom;

			if (measureBounds.right + measureBounds.left > this->GetWidth()) {
				measureBounds.right = this->GetWidth();
			}

			Size newSize(measureBounds.right - measureBounds.left, measureBounds.bottom - measureBounds.top);
			view->SetFrame(Frame(measureBounds.left, measureBounds.top, newSize.width, newSize.height));

			if (mOrientation == LinearLayoutHorizontal) {
				offset.x = measureBounds.right + viewMargin.right;
			}
			else {
				offset.y = measureBounds.bottom + viewMargin.bottom;
			}
		}

		// Calculate weighted views


	}

	void LinearLayout::PostLayout()
	{
		if (this->GetVisibility() != ViewVisible) {
			return;
		}

		ViewAlignment defaultAlign = this->GetLayoutParams().subviewAlignment;
		auto &subviews = this->GetSubviews();

		if (mOrientation == LinearLayoutHorizontal) {
			//int rightOffset = [self measureSize].width;
			int rightOffset = this->GetWidth();
			

			int left = INFINITY, right = -INFINITY;
			for (View *view : subviews) {
				left = glm::min<real>(left, view->GetX());
				right = glm::max<real>(right, view->GetX() + view->GetWidth());
			}

			int wrappedWidth = right - left;
			int wrappedOffset = (rightOffset - wrappedWidth) * 0.5;

			

			for (int i = subviews.size() - 1; i >= 0; i--) {
				View *view = subviews[i];

				ViewAlignment align = view->GetLayoutParams().alignment;
				if (align == AlignmentInherit) {
					align = defaultAlign;
				}

				Frame frame = view->GetFrame();

				// We only need to make adjustments for right and center, since left is default
				if (align & AlignmentBottom) {
					frame.origin.y = this->GetHeight() - frame.origin.y - frame.size.height;
				}
				else if (align & AlignmentCenterVertical) {
					frame.origin.y = (this->GetHeight() - frame.origin.y - frame.size.height) * 0.5;
				}

				// We only need to make adjustments for bottom and center, since top is default
				if (align & AlignmentRight) {
					frame.origin.x = rightOffset - frame.size.width;
				}
				else if (align & AlignmentCenterHorizontal) {
					frame.origin.x += wrappedOffset;
				}

				rightOffset -= frame.size.width;

				view->SetFrame(frame);
			}
		}
		else {
			//int bottomOffset = [self measureSize].height;
			int bottomOffset = this->GetHeight();

			int wrappedHeight = 0;
			for (View *view : subviews) {
				wrappedHeight += view->GetHeight();
			}

			int wrappedOffset = (bottomOffset - wrappedHeight) * 0.5;

			for (int i = subviews.size() - 1; i >= 0; i--) {
				View *view = subviews[i];

				ViewAlignment align = view->GetLayoutParams().alignment;
				if (align == AlignmentInherit) {
					align = defaultAlign;
				}

				Frame frame = view->GetFrame();


				// We only need to make adjustments for right and center, since left is default
				if (align & AlignmentRight) {
					frame.origin.x = this->GetWidth() - frame.origin.x - frame.size.width;
				}
				else if (align & AlignmentCenterHorizontal) {
					frame.origin.x = (this->GetWidth() - frame.origin.x - frame.size.width) * 0.5;
				}

				// We only need to make adjustments for bottom and center, since top is default
				if (align & AlignmentBottom) {
					frame.origin.y = bottomOffset - frame.size.height;
				}
				else if (align & AlignmentCenterVertical) {
					frame.origin.y += wrappedOffset;
				}

				bottomOffset -= frame.size.height;
				view->SetFrame(frame);
			}
		}
	}
};