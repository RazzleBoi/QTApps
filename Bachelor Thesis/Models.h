#pragma once
#include <QAbstractTableModel>
#include <qsortfilterproxymodel.h>
#include "repo.h"
#include "domain.h"
#include "service.h"
#include "Observer.h"

class MyTableModel : public QAbstractTableModel, public Observer
{
private:
	serviceWrapper& service;
	Driver& driver;
public:
	int &distance;
	void update() override;
	MyTableModel(serviceWrapper& service, Driver& driver, int& distance) : service{ service }, driver{ driver }, distance{ distance } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());


};

