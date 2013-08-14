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

		void SetScrollable(bool scrollable) { mScrollable = scrollable; }
		
		void SetContentSize(Size size) { mContentSize = size; }
		Size GetContentSize() { return mContentSize; }

	private:
		Size mContentSize;
		bool mScrollable;

		virtual void PreRender(UIManager *manager, Point origin);
	};
};