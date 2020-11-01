#pragma once

#include <QWidget>
#include "ui_myListView.h"
#include "MyListTableModel.h"

class myListView : public QWidget
{
	Q_OBJECT

public:
	myListView(MyListTableModel * myListModel, QWidget *parent = Q_NULLPTR);
	~myListView();

private:
	Ui::myListView ui;
	MyListTableModel * myListModel;
};
