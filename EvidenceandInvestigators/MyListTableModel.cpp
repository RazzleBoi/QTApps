#pragma once
#include "MyListTableModel.h"

int MyListTableModel::rowCount(const QModelIndex& parent) const
{
	return repo.numberOfTapes();
}

int MyListTableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant MyListTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row(), column = index.column();
	Tape currentTape = repo.getAllTapes()[row];
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0:
			return QString::fromStdString(currentTape.getTitle());
		case 1:
			return QString::fromStdString(currentTape.getFilmedAt());
		case 2:
			return QString::fromStdString(currentTape.getDate());
		case 3:
			return QString::fromStdString(to_string(currentTape.getAccessCount()));
		case 4:
			return QString::fromStdString(currentTape.getFootagePreview());
		}
	}
	return QVariant();
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Title");
			case 1:
				return QString("Filmed Location");
			case 2:
				return QString("Date");
			case 3:
				return QString("Access count");
			case 4:
				return QString("Footage preview");
			}
		}
	}
	return QVariant();
}

bool MyListTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	beginInsertRows(parent, rowCount(), rowCount());
	
	endInsertRows();
	return true;
}

bool MyListTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, rowCount()-1, rowCount()-1);

	endRemoveRows();
	return true;
}
