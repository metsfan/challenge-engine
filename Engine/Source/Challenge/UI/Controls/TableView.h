#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/View.h>

#include <queue>

namespace challenge
{
	class TableView;

	class ITableViewDataSource
	{
	public:
		virtual View * GetViewForRow(TableView *table, uint32_t row) = 0;
		virtual uint32_t GetNumberOfRows(TableView *table) = 0;
	};

	class ITableViewListener
	{
	public:
		void OnRowSelected(TableView *table, uint32_t row);
	};

	class TableView : public View
	{
	public:
		TableView(Frame frame = Frame());
		virtual ~TableView();

		void SetDataSource(ITableViewDataSource *dataSource)
		{
			mDataSource = dataSource;
		}

		void SetListener(ITableViewListener *listener)
		{
			mListener = listener;
		}

		void ReloadData();

		View * GetCachedView(const std::string &key);

	private:
		ITableViewDataSource *mDataSource;
		ITableViewListener *mListener;

		std::map<std::string, std::queue<View *>> mReusableViewCache;
	};
};