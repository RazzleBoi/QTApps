#include "myListView.h"

myListView::myListView(MyListTableModel * myListModel, QWidget *parent)
	: QWidget(parent), myListModel{ myListModel } 
{
	ui.setupUi(this);
	ui.tableView->setModel(this->myListModel);
}

myListView::~myListView()
{
}
