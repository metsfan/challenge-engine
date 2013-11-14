#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/View.h>

namespace challenge
{
	class PanelView : public View
	{
	public:
		PanelView(Frame frame = Frame());
		virtual ~PanelView(void);

		void SetScrollable(bool scrollable);
		
		void SetContentSize(Size size) { mContentSize = size; }
		Size GetContentSize() { return mContentSize; }

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		virtual Point GetPositionInView(const Point &position, View *other);

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		Size mContentSize;
		bool mScrollable;
		Point mScrollPosition;
		PanelView *mHorizontalScrollbar;
		PanelView *mHorizontalScroller;
		PanelView *mVerticalScrollbar;
		PanelView *mVerticalScroller;
		bool mVertScrollPressed;

		virtual Frame CalculateChildFrame();
	};
};