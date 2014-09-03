#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/RelativeLayout.h>

namespace challenge
{
	RelativeLayout::RelativeLayout(const Size &size) :
		Layout(size),
		mSubviewsDirty(true)
	{

	}

	RelativeLayout::~RelativeLayout()
	{
	}

	void RelativeLayout::PositionSubviews()
	{
		// Resolve any views that are referenced by ID
		for (View *subview : this->GetSubviews()) {
			LayoutParams layoutParams = subview->GetLayoutParams();

			if (!layoutParams.leftOfView && layoutParams.leftOfViewId.length()) {
				layoutParams.leftOfView = this->FindViewById(layoutParams.leftOfViewId);
			}

			if (!layoutParams.rightOfView && layoutParams.rightOfViewId.length()) {
				layoutParams.rightOfView = this->FindViewById(layoutParams.rightOfViewId);
			}

			if (!layoutParams.belowView && layoutParams.belowViewId.length()) {
				layoutParams.belowView = this->FindViewById(layoutParams.belowViewId);
			}

			if (!layoutParams.aboveView && layoutParams.aboveViewId.length()) {
				layoutParams.aboveView = this->FindViewById(layoutParams.aboveViewId);
			}

			subview->SetLayoutParams(layoutParams);
		}

		if (mSubviewsDirty) {
			mSubviewsDirty = false;
			this->SortSubviews();
		}

		const Rect &padding = this->GetPadding();
		const Size &sizeSpec = this->GetLayoutParams().size;

		bool first = false;
		for (View *subview : mSortedSubviews) {
			Frame frame = subview->GetFrame();
			const Rect &viewMargin = subview->GetMargin();
			const Rect &viewPadding = subview->GetPadding();
			LayoutParams layoutParams = subview->GetLayoutParams();

			frame.size.width += viewPadding.left + viewPadding.right;
			frame.size.height += viewPadding.top + viewPadding.bottom;

			Rect measureBounds(frame.origin.x, frame.origin.y,
				frame.origin.x + frame.size.width, frame.origin.y + frame.size.height);

			if (layoutParams.alignParentRight && sizeSpec.width != WRAP_CONTENT) {
				measureBounds.right = this->GetWidth() - padding.right - viewMargin.right;
				measureBounds.left = measureBounds.right - frame.size.width;
			}
			else if (layoutParams.alignment & AlignmentCenterHorizontal && sizeSpec.width != WRAP_CONTENT) {
				measureBounds.left = (this->GetWidth() - frame.size.width) * 0.5;
				measureBounds.right = measureBounds.left + frame.size.width;
			}

			if (layoutParams.leftOfView) {
				measureBounds.right = layoutParams.leftOfView->GetLayoutParams().measureBounds.left;

				if (!layoutParams.rightOfView && !layoutParams.alignParentRight) {
					measureBounds.left = measureBounds.right - frame.size.width;
				}
			}

			if (layoutParams.rightOfView) {
				measureBounds.left = layoutParams.rightOfView->GetLayoutParams().measureBounds.right + 
					layoutParams.rightOfView->GetRightMargin();

				if (!layoutParams.leftOfView && !layoutParams.alignParentRight) {
					measureBounds.right = measureBounds.left + frame.size.width;
				}
			}

			int offset = viewMargin.left;
			if (!layoutParams.rightOfView && !layoutParams.alignParentRight && 
				!(layoutParams.alignment & AlignmentCenterHorizontal)) {
				offset += padding.left;
			}
			measureBounds.left += offset;
			measureBounds.right += offset;

			if (layoutParams.alignParentBottom && sizeSpec.height != WRAP_CONTENT) {
				measureBounds.bottom = this->GetHeight() - padding.bottom - viewMargin.bottom;
				measureBounds.top = measureBounds.bottom - frame.size.height;
			}
			else if (layoutParams.alignment & AlignmentCenterVertical && sizeSpec.height != WRAP_CONTENT) {
				measureBounds.top = (this->GetHeight() - frame.size.height) * 0.5;
				measureBounds.bottom = measureBounds.top + frame.size.height;
			}

			if (layoutParams.aboveView) {
				measureBounds.bottom = layoutParams.aboveView->GetLayoutParams().measureBounds.top;

				if (!layoutParams.belowView && !layoutParams.alignParentBottom) {
					measureBounds.top = measureBounds.bottom - frame.size.height;
				}
			}

			if (layoutParams.belowView) {
				const LayoutParams &belowLayoutParams = layoutParams.belowView->GetLayoutParams();
				measureBounds.top = belowLayoutParams.measureBounds.bottom + layoutParams.belowView->GetBottomMargin();

				if (!layoutParams.aboveView && !layoutParams.alignParentTop) {
					measureBounds.bottom = measureBounds.top + frame.size.height;
				}
			}

			offset = viewMargin.top;
			if (!layoutParams.belowView && !layoutParams.alignParentBottom && !(layoutParams.alignment & AlignmentCenterVertical)) {
				offset += padding.top;
			}
			measureBounds.top += offset;
			measureBounds.bottom += offset;

			//frame.origin.y += viewMargin.top;

			if (subview->GetLayoutParams().size.width == MATCH_PARENT)
				measureBounds.right = this->GetWidth() - padding.right;
			//frame.size.width = self.frame.size.width - padding.right - frame.origin.x - viewMargin.right;

			if (subview->GetLayoutParams().size.height == MATCH_PARENT)
				measureBounds.bottom = this->GetHeight() - padding.bottom;
			//frame.size.height = self.frame.size.height - padding.top - frame.origin.y - viewMargin.bottom;

			//measureBounds.right -= viewMargin.right;

			Size oldSize = frame.size;

			frame.origin.x = measureBounds.left;
			frame.origin.y = measureBounds.top;
			frame.size.width = floor(measureBounds.right - measureBounds.left);
			frame.size.height = floor(measureBounds.bottom - measureBounds.top);

			subview->SetFrame(frame);

			if (oldSize != frame.size) {
				// If our size has changed, re-measure constrained to new size
				//[subview measure:frame.size];
				layoutParams.measureSize = frame.size;
			}

			layoutParams.measureBounds = measureBounds;
			subview->SetLayoutParams(layoutParams);
		}
	}

	void RelativeLayout::PostLayout()
	{
		const Size &spec = this->GetLayoutParams().size;

		if (spec.width == WRAP_CONTENT || spec.height == WRAP_CONTENT) {
			for (View *subview : mSortedSubviews) {
				Frame frame = subview->GetFrame();
				const LayoutParams &layoutParams = subview->GetLayoutParams();

				if (spec.width == WRAP_CONTENT) {
					if (layoutParams.alignParentRight) {
						frame.origin.x = this->GetWidth() - this->GetRightPadding() - frame.size.width;
					}
					else if (layoutParams.alignment & AlignmentCenterHorizontal) {
						frame.origin.x = (this->GetWidth() - this->GetRightPadding() - frame.size.width) * 0.5;
					}
				}

				if (spec.height == WRAP_CONTENT) {
					if (layoutParams.alignParentBottom) {
						frame.origin.y = this->GetHeight() - this->GetBottomPadding() - frame.size.height;
					}
					else if (layoutParams.alignment & AlignmentCenterVertical) {
						frame.origin.y = (this->GetHeight() - this->GetBottomPadding() - frame.size.height) * 0.5;
					}
				}

				subview->SetFrame(frame);
			}
		}
	}

	void RelativeLayout::SortSubviews()
	{
		auto subviews = this->GetSubviews();

		mSortedSubviews.clear();

		int dependencyMax = 0;

		std::map<View *, int> depsCount;

		for (View *subview : subviews) {
			int deps = 0;

			const LayoutParams &params = subview->GetLayoutParams();
			if (params.leftOfView) {
				deps++;
			}

			if (params.rightOfView) {
				deps++;
			}

			if (params.belowView) {
				deps++;
			}

			if (params.aboveView) {
				deps++;
			}

			depsCount[subview] = deps;
		}

		while (subviews.size() > 0) {
			auto copy = subviews;
			for (View *subview : copy) {
				int deps = depsCount[subview];
				const LayoutParams &params = subview->GetLayoutParams();
				if (params.leftOfView) {
					deps += depsCount[params.leftOfView];
				}

				if (params.rightOfView) {
					deps += depsCount[params.rightOfView];
				}

				if (params.belowView) {
					deps += depsCount[params.belowView];
				}

				if (params.aboveView) {
					deps += depsCount[params.aboveView];
				}

				if (deps <= dependencyMax) {
					mSortedSubviews.push_back(subview);
					subviews.erase(std::find(subviews.begin(), subviews.end(), subview));
				}
			}

			dependencyMax++;
		}
	}

	void RelativeLayout::AddSubview(View *view)
	{
		Layout::AddSubview(view);

		mSubviewsDirty = true;
	}

	View * RelativeLayout::RemoveSubview(View *view)
	{
		mSubviewsDirty = true;

		return Layout::RemoveSubview(view);
	}

	TViewList RelativeLayout::RemoveAllSubviews()
	{
		mSubviewsDirty = true;

		return Layout::RemoveAllSubviews();
	}
}