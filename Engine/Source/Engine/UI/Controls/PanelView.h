#include <Engine/Challenge.h>
#include <Engine/UI/View.h>

namespace challenge
{
	class PanelView : public View
	{
	public:
		PanelView(void);
		PanelView(Frame frame);
		virtual ~PanelView(void);

		void SetScrollable(bool scrollable);
		
		void SetContentSize(Size size) { mContentSize = size; }
		Size GetContentSize() { return mContentSize; }

	private:
		Size mContentSize;
		bool mScrollable;

		virtual void PreRender(UIManager *manager, Point origin);
	};
};