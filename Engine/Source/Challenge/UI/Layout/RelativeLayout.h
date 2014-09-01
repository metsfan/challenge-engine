#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Layout/Layout.h>

namespace challenge
{
	class RelativeLayout : public Layout
	{
	public:
		RelativeLayout(const Size &size = Size());
		~RelativeLayout();

		virtual void AddSubview(View *view);
		virtual View * RemoveSubview(View *view);
		virtual TViewList RemoveAllSubviews();

	protected:
		void PositionSubviews();
		void PostLayout();

	private:
		bool mSubviewsDirty;
		TViewList mSortedSubviews;

		void SortSubviews();
	};
};