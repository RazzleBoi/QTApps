#pragma once
#include "service.h"
#include "myListView.h"
#include "domain.h"
#include "MyListTableModel.h"

#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qshortcut.h>
#include <qkeysequence.h>
#include <vector>

using namespace std;
class GUI :
	public QWidget
{
private:
	Service service;
	MyListTableModel* fieldAgentsList;
	//graphical
	myListView* fieldAgentView;
	QShortcut* undoKeyCombination, * redoKeyCombination;
	QListWidget* tapeListWidget, *fieldAgentsWidget;
	QLineEdit* titleLineEdit, * filmedLocationLineEdit, * dateLineEdit, * accessCountLineEdit, * footagePreviewLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, * saveButton, * filterButton, * nextButton, * openButton, *fieldAgentModeButton, *undoButton, *redoButton;

public:
	GUI();
	void initGUI();
	void populateRepoList();
	void populateMyList();
	void connectSignalsAndSlots();

	int getSelectedIndex() const;
	void addTape();
	void deleteTape();
	void saveTape();
	void filterTape();
	void updateTape();

	void undoAction();
	void redoAction();

	void nextTape();
	void openFieldAgent();
	void enableFieldAgent();
};

