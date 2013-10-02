#include <Engine/Challenge.h>
#include <Engine/UI/Controls/PanelView.h>

namespace challenge
{
	static const int kScrollbarSize = 20;
	static const glm::vec4 kScrollbarBackgroundColor(240, 240, 240, 255);
	static const glm::vec4 kScrollbarFillColor(200, 200, 200, 255);

	PanelView::PanelView(Frame frame) : 
		View(frame),
		mHorizontalScrollbar(NULL),
		mVerticalScrollbar(NULL)
	{
		mScrollable = false;
		mScrollPosition.y = 0;
	}

	PanelView::~PanelView(void)
	{
	}

	void PanelView::SetScrollable(bool scrollable) 
	{ 
		mScrollable = scrollable; 
		this->ClipSubviews(scrollable);

		const Frame &frame = this->GetFrame();
		/*if(!mHorizontalScrollbar) {
			Frame horizontalScrollbarFrame(
				0, 
				frame.origin.y + frame.size.height - kScrollbarSize,
				frame.size.width - kScrollbarSize,
				kScrollbarSize
			);
			mHorizontalScrollbar = new PanelView(horizontalScrollbarFrame);
			mHorizontalScrollbar->SetBackgroundColor(kScrollbarBackgroundColor);

			mHorizontalScroller = new PanelView(horizontalScrollbarFrame);
			mHorizontalScroller->SetBackgroundColor(kScrollbarFillColor);
		}*/

		if(!mVerticalScrollbar) {
			Frame verticalScrollbarFrame(
				frame.size.width - kScrollbarSize, 
				0,
				kScrollbarSize,
				frame.size.height - kScrollbarSize
			);
			mVerticalScrollbar = new PanelView(verticalScrollbarFrame);
			mVerticalScrollbar->SetBackgroundColor(kScrollbarBackgroundColor);
			mVerticalScrollbar->SetZPosition(100000);
			this->AddInternalSubview(mVerticalScrollbar);

			mVerticalScroller = new PanelView(verticalScrollbarFrame);
			mVerticalScroller->SetBackgroundColor(kScrollbarFillColor);
			mVerticalScrollbar->AddInternalSubview(mVerticalScroller);
			
			mVertScrollPressed = false;

			auto moveScroller = [this](View *sender, const MouseEvent &e) {
				if(this->mVertScrollPressed) {
					real relativeY = e.position.y - this->GetAdjustedFrame().origin.y;
					real scrollerRatio = (mContentSize.height / this->GetFrame().size.height);
					mScrollPosition.y = glm::clamp<real>(relativeY * scrollerRatio, 0, mContentSize.height - this->GetHeight());
				}
			};

			mVerticalScrollbar->AddMouseDownDelegate([this, moveScroller](View *sender, const MouseEvent &e) {
				this->mVertScrollPressed = true;
				moveScroller(sender, e);
			});

			mVerticalScrollbar->AddMouseMoveDelegate(moveScroller);

			this->AddMouseWheelMoveDelegate([this](View *sender, const MouseEvent &e) {
				mScrollPosition.y = glm::clamp<real>(mScrollPosition.y - e.wheelDelta, 0, mContentSize.height - this->GetHeight());
			});

			//mVerticalScroller->SetPosition(0, 35);

			mVerticalScrollbar->AddMouseUpDelegate([this](View *sender, const MouseEvent &e) {
				this->mVertScrollPressed = false;
			});
		}
	}

	void PanelView::Update(int deltaMillis)
	{
		const TViewList &subviews = this->GetSubviews();
		const Frame &frame = this->GetFrame();

		mContentSize.width = 0;
		mContentSize.height = 0;

		for(View *view : subviews) {
			const Frame &childFrame = view->GetFrame();

			mContentSize.width = std::max(mContentSize.width, childFrame.origin.x + childFrame.size.width);
			mContentSize.height = std::max(mContentSize.height, childFrame.origin.y + childFrame.size.height);

			if(mScrollable) {
				if(childFrame.origin.y > mScrollPosition.y + frame.size.height ||
					childFrame.origin.y + childFrame.size.height < mScrollPosition.y) {
					view->SetVisible(false);
				} else {
					view->SetVisible(true);
				}
			}
		}

		if(this->IsVisible() && mScrollable) {
			const Frame &adjustedFrame = this->GetAdjustedFrame();
			/*if(mContentSize.width > this->GetFrame().size.width) {
				mHorizontalScrollbar->SetPosition(adjustedFrame.origin.x, mHorizontalScrollbar->GetFrame().origin.y);
				mHorizontalScrollbar->Render(device, state, parentFrame);

				real scrollerSize = (adjustedFrame.size.width / mContentSize.width) * adjustedFrame.size.width;
				mHorizontalScroller->SetSize(scrollerSize, kScrollbarSize);
				mHorizontalScroller->Render(device, state, parentFrame);
			}*/
			
			if(mContentSize.height > this->GetHeight()) {
				mVerticalScrollbar->SetY(mScrollPosition.y);
				mVerticalScrollbar->SetSize(kScrollbarSize, adjustedFrame.size.height);

				real scrollPositionRatio = mScrollPosition.y / mContentSize.height;
				real scrollY = scrollPositionRatio * mVerticalScrollbar->GetHeight();
				mVerticalScroller->SetPosition(0, scrollY);

				real scrollerRatio = (this->GetHeight() / mContentSize.height);
				real scrollerSize = scrollerRatio * mVerticalScrollbar->GetHeight();
				mVerticalScroller->SetSize(kScrollbarSize, scrollerSize);
			}
		}

		View::Update(deltaMillis);
	}

	void PanelView::Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame)
	{
		View::Render(device, state, parentFrame);
	}

	Frame PanelView::CalculateChildFrame()
	{
		if(mScrollable) {
			const Frame &currentFrame = this->GetAdjustedFrame();

			return Frame(
				currentFrame.origin.x,
				currentFrame.origin.y - mScrollPosition.y,
				currentFrame.size.width,
				currentFrame.size.height
			);
		} else {
			return this->GetAdjustedFrame();
		}
	}
};
