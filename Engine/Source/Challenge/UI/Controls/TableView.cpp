#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/TableView.h>

namespace challenge
{
	TableView::TableView(Frame frame) :
		View(frame)
	{
		this->SetLayoutType(LayoutTypeLinear);
	}

	TableView::~TableView()
	{
		for (auto &pair : mReusableViewCache) {
			auto &queue = pair.second;
			while (!queue.empty()) {
				View *top = queue.front();
				if (!this->FindView(top)) {
					delete top;
				}

				queue.pop();
			}
		}
	}

	void TableView::ReloadData()
	{
		if (mDataSource) {
			TViewList views = this->RemoveAllSubviews();
			for (int i = 0; i < views.size(); i++) {
				View *view = views[i];
				const std::string &key = view->GetAttribute("key");
				if (key.size()) {
					mReusableViewCache[key].push(view);
				} else {
					view->SafeDelete();
				}
			}

			int numRows = mDataSource->GetNumberOfRows(this);
			for (int i = 0; i < numRows; i++) {
				View *row = mDataSource->GetViewForRow(this, i);

				this->AddInternalSubview(row);
			}
		}
	}

	View * TableView::GetCachedView(const std::string &key)
	{
		auto &queue = mReusableViewCache[key];
		if (queue.size() > 0) {
			View *top = queue.front();
			queue.pop();

			return top;
		}
		
		return NULL;
	}
};