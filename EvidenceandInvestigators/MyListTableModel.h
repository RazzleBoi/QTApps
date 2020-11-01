#pragma once
#include <QAbstractTableModel>
#include "Repository.h"
#include "domain.h"
#include "service.h"

class MyListTableModel : public QAbstractTableModel
{
private:
	memoryRepo& repo;

public:
	MyListTableModel(memoryRepo &repo) : repo{ repo} {};
	MyListTableModel(Service &service) : repo{ (*service.fieldAgentsList) } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
};
