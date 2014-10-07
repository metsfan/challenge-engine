#include <Challenge/Challenge.h>
#include <Challenge/UI/Controls/TableView.h>
#include <Challenge/UI/Layout/LinearLayout.h>

namespace challenge
{
	TableView::TableView(Frame frame) :
		PanelView(frame),
		mDataSource(NULL),
		mListener(NULL),
		mReloadData(false)
	{
		this->AddMouseEvent(MouseEventMouseDown, [this](View *sender, const MouseEvent &e) {
			if (!mListener) {
				return;
			}

			auto &subviews = mTableRows->GetSubviews();

			for (View *view : subviews) {
				if (view->ContainsPoint(e.position)) {
					int row = atoi(view->GetAttribute("row").c_str());
					mListener->OnRowSelected(this, view, row);
					break;
				}
			}
		});

		mTableRows = new LinearLayout(Size(MATCH_PARENT, WRAP_CONTENT));
		this->AddSubview(mTableRows);
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
		mReloadData = true;
	}

	void TableView::ReloadDataInternal()
	{
		if (mDataSource) {
			TViewList views = mTableRows->RemoveAllSubviews();

			for (int i = 0; i < views.size(); i++) {
				View *view = views[i];
				const std::string &key = view->GetAttribute("key");
				if (key.size()) {
					view->SetVisibility(ViewGone);
					mReusableViewCache[key].push(view);
				} else {
					view->SafeDelete();
				}
			}

			int numRows = mDataSource->GetNumberOfRows(this);
			for (int i = 0; i < numRows; i++) {
				View *row = mDataSource->GetViewForRow(this, i);
				row->SetAttribute("row", std::to_string(i));
				row->SetVisibility(ViewVisible);

				mTableRows->AddSubview(row);
			}
		
			this->InvalidateLayout();
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

	void TableView::Update(int deltaMillis)
	{
		View::Update(deltaMillis);

		if (mReloadData) {
			mReloadData = false;
			this->ReloadDataInternal();
		}
	}
};