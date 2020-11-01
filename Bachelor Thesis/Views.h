#pragma once

#include <QWidget>
#include <qslider.h>
#include <qwindow.h>
#include <qlayout.h>
#include <qlabel.h>
#include <QtWidgets/QListView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <qtableview.h>
#include <qheaderview.h>
#include <qcheckbox.h>
#include "Models.h"
#include "domain.h"
#include "Observer.h"


class myListView : public QWidget
{
		QOBJECT_H
public:
	myListView(MyTableModel* myTableModel, serviceWrapper& service ,Driver& driver, QWidget *parent = Q_NULLPTR);
	~myListView();
	void ChangeDistance();
	void AddReport();
	void North();
	void South();
	void East();
	void West();

private:
	serviceWrapper& service;
	Driver& driver;

	MyTableModel* myTableModel;
	QTableView * reports;
	QSlider* slider;

	int distance=10;

	QLabel* scoreLabel, * latitudeLabel, * statusLabel, *longitudeLabel;

	QLineEdit * longitudeLineEdit, *latitudeLineEdit, *descriptionLineEdit;
	QPushButton *addButton, *northButton, *southButton, *eastButton, *westButton;
};

