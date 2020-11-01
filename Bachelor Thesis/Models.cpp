#pragma once
#include "Models.h"
#include <qdebug.h>

void MyTableModel::update()
{
	emit layoutChanged();
}

int MyTableModel::rowCount(const QModelIndex& parent) const
{
	return service.serv.getElementsOf(driver,distance).size();
}

int MyTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row(), column = index.column();
	Report currentItem = *service.serv.getElementsOf(driver, distance)[row];
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(currentItem.getDescription());
		case 1:
			return QString::fromStdString(currentItem.getReporter());
		case 2:
			return QString::fromStdString(to_string(currentItem.getLatitude()));
		case 3:
			return QString::fromStdString(to_string(currentItem.getLongitude()));
		}
	}
	//if (role == Qt::style)
	return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Description");
			case 1:
				return QString("Reporter");
			case 2:
				return QString("Latitude");
			case 3:
				return QString("Longitude");
			}
		}
	}
	return QVariant();
}

bool MyTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	beginInsertRows(parent, rowCount(), rowCount());
	endInsertRows();
	return true;
}

bool MyTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, rowCount()-1, rowCount()-1);

	endRemoveRows();
	return true;
}

