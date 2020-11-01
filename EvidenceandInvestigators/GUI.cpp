#include <qwindow.h>
#include <qmainwindow.h>
#include "GUI.h"
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include "utilities.h"
GUI::GUI()
{
	service.configureRepo();
	initGUI();
	populateRepoList();
	populateMyList();
	connectSignalsAndSlots();
}
void GUI::initGUI()
{
	tapeListWidget = new QListWidget{};
	fieldAgentsWidget = new QListWidget{};
	titleLineEdit = new QLineEdit{};
	filmedLocationLineEdit = new QLineEdit{};
	dateLineEdit = new QLineEdit{};
	accessCountLineEdit = new QLineEdit{};
	footagePreviewLineEdit = new QLineEdit{};
	addButton = new QPushButton{"Add"};
	deleteButton = new QPushButton{"Delete"};
	updateButton = new QPushButton{"Update"};

	undoButton = new QPushButton{"Undo"};
	redoButton = new QPushButton{"Redo"};

	saveButton = new QPushButton{"Save"};
	nextButton = new QPushButton{"Next"};
	filterButton = new QPushButton{"Filter"};
	openButton = new QPushButton{"Open"};
	fieldAgentModeButton = new QPushButton{"Agent Mode"};
	QKeySequence *ctrlZ = new QKeySequence(Qt::CTRL + Qt::Key_Z);
	undoKeyCombination = new QShortcut(this);
	undoKeyCombination->setKey(*ctrlZ);
	QKeySequence* ctrlY = new QKeySequence(Qt::CTRL + Qt::Key_Z);
	redoKeyCombination = new QShortcut(this);
	undoKeyCombination->setKey(*ctrlY);

	QVBoxLayout *leftLayout = new QVBoxLayout{ };
	QLabel* repoList = new QLabel("List of tapes");
	leftLayout->addWidget(repoList);
	leftLayout->addWidget(this->tapeListWidget);

	QFormLayout *tapeAttributes = new QFormLayout{};
	tapeAttributes->addRow("Title", this->titleLineEdit);
	tapeAttributes->addRow("Filmed Location", this->filmedLocationLineEdit);
	tapeAttributes->addRow("Date", this->dateLineEdit);
	tapeAttributes->addRow("Access count", this->accessCountLineEdit);
	tapeAttributes->addRow("Footage Preview", this->footagePreviewLineEdit);
	leftLayout->addLayout(tapeAttributes);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(addButton, 0, 0);
	buttonsLayout->addWidget(updateButton, 0, 1);
	buttonsLayout->addWidget(deleteButton, 0, 2);
	buttonsLayout->addWidget(undoButton, 1, 1);
	buttonsLayout->addWidget(redoButton, 1, 2);

	buttonsLayout->addWidget(saveButton, 2, 0);
	buttonsLayout->addWidget(nextButton, 2, 1);
	buttonsLayout->addWidget(filterButton, 2, 2);
	buttonsLayout->addWidget(openButton, 2, 3);
	buttonsLayout->addWidget(fieldAgentModeButton, 2, 4);
	leftLayout->addLayout(buttonsLayout);

	QVBoxLayout* rightLayout = new QVBoxLayout{ };
	QLabel* myListLabel = new QLabel("Field Agents list");
	rightLayout->addWidget(myListLabel);
	rightLayout->addWidget(this->fieldAgentsWidget);

	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	mainLayout->addLayout(leftLayout);
	//mainLayout->addLayout(rightLayout);


	fieldAgentsList = new MyListTableModel{ service };
	fieldAgentView = new myListView{ fieldAgentsList};

	filterButton->setEnabled(0);
	saveButton->setEnabled(0);
	nextButton->setEnabled(0);
	openButton->setEnabled(0);

}

void GUI::populateRepoList()
{
	this->tapeListWidget->clear();
	vector<Tape> tapesFromRepo = service.getListOfAllTapes();
	for (Tape currentTape : tapesFromRepo) {
		this->tapeListWidget->addItem(QString::fromStdString(currentTape.toString()));
	}
}

void GUI::populateMyList()
{/*
	this->fieldAgentsWidget->clear();
	vector<Tape> tapesFromRepo = service.getFieldAgentsList();
	for (Tape currentTape : tapesFromRepo) {
		this->fieldAgentsWidget->addItem(QString::fromStdString(currentTape.toString()));
	}*/
}

void GUI::connectSignalsAndSlots()
{
	
	QObject::connect(this->tapeListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Tape selectedTape = service.getListOfAllTapes()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(selectedTape.getTitle()));
		this->filmedLocationLineEdit->setText(QString::fromStdString(selectedTape.getFilmedAt()));
		this->dateLineEdit->setText(QString::fromStdString(selectedTape.getDate()));
		this->accessCountLineEdit->setText(QString::fromStdString(to_string(selectedTape.getAccessCount())));
		this->footagePreviewLineEdit->setText(QString::fromStdString(selectedTape.getFootagePreview()));
		});
	QObject::connect(this->addButton, &QPushButton::clicked,this,  &GUI::addTape);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateTape);
	QObject::connect(this->deleteButton, &QPushButton::clicked,this,  &GUI::deleteTape);

	QObject::connect(this->undoButton, &QPushButton::clicked,this,  &GUI::undoAction);
	QObject::connect(this->redoButton, &QPushButton::clicked,this,  &GUI::redoAction);

	QObject::connect(undoKeyCombination, &QShortcut::activated,this,  &GUI::undoAction);
	QObject::connect(redoKeyCombination, &QShortcut::activated,this,  &GUI::redoAction);


	QObject::connect(this->saveButton, &QPushButton::clicked,this,  &GUI::saveTape);
	QObject::connect(this->filterButton, &QPushButton::clicked,this,  &GUI::filterTape);
	QObject::connect(this->nextButton, &QPushButton::clicked,this,  &GUI::nextTape);
	QObject::connect(this->openButton, &QPushButton::clicked,this,  &GUI::openFieldAgent);
	QObject::connect(this->fieldAgentModeButton, &QPushButton::clicked,this,  &GUI::enableFieldAgent);
}


int GUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->tapeListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->titleLineEdit->clear();
		this->filmedLocationLineEdit->clear();
		this->dateLineEdit->clear();
		this->accessCountLineEdit->clear();
		this->footagePreviewLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::addTape()
{
	string title = this->titleLineEdit->text().toStdString();
	string filmedLocation = this->filmedLocationLineEdit->text().toStdString();
	date adate = stringToDate(this->dateLineEdit->text().toStdString());
	int accessCount = this->accessCountLineEdit->text().toInt();
	string footagePreview = this->footagePreviewLineEdit->text().toStdString();
	Tape tapeToAdd(title, filmedLocation, adate.day, adate.month, adate.year, accessCount, footagePreview);
	try {
		service.addTape(tapeToAdd);
	}
	catch (repoError re) {
		QMessageBox::critical(this, "Repo Error", re.what());
		return;
	}
	catch (validatorError ve) {
		QMessageBox::critical(this, "Validator Error", ve.what());
		return;
	}
	populateRepoList();
}

void GUI::deleteTape()
{
	string title = this->titleLineEdit->text().toStdString();
	if (title == "")
	{
		QMessageBox::critical(this, "Error", "Song title cant be empty");
		return;
	}
	try {
		service.deleteTape(title);
	}
	catch (repoError re) {
		QMessageBox::critical(this, "Repo Error", re.what());
		return;
	}
	populateRepoList();
}

void GUI::saveTape()
{
	string title = this->titleLineEdit->text().toStdString();
	if (title == "")
	{
		QMessageBox::critical(this, "Error", "Song title cant be empty");
		return;
	}
	try {
		exitCode eCode = service.saveToMyList(title);
		if (eCode == 0) {
			QMessageBox::critical(this, "Repo Error", "Tape not in Repo");
			return;
		}
		else {
			fieldAgentsList->insertRows(fieldAgentsList->rowCount(), 1);
		}
	}
	catch (repoError re) {
		QMessageBox::critical(this, "Repo Error", re.what());
		return;
	}
	populateMyList();
}


void GUI::updateTape()
{
	string title = this->titleLineEdit->text().toStdString();
	string filmedLocation = this->filmedLocationLineEdit->text().toStdString();
	date adate;
	int accessCount;
	try {
		adate = stringToDate(this->dateLineEdit->text().toStdString());
		accessCount = this->accessCountLineEdit->text().toInt();
	}
	catch (exception error) {
		QMessageBox::critical(this, "Repo Error", "Date  and access Count must be of type int-int-int  and int, respectively");
		return;
	}
	string footagePreview = this->footagePreviewLineEdit->text().toStdString();
	Tape tapeToUpdate(title, filmedLocation, adate.day, adate.month, adate.year, accessCount, footagePreview);
	try {
		service.updateTape(tapeToUpdate);
	}
	catch (repoError re) {
		QMessageBox::critical(this, "Repo Error", re.what());
		return;
	}
	catch (validatorError ve) {
		QMessageBox::critical(this, "Validator Error", ve.what());
		return;
	}
	populateRepoList();
}

void GUI::undoAction()
{
	try {
		if (this->saveButton->isEnabled()){
			if(service.undoSaveSize())
				fieldAgentsList->removeRows(fieldAgentsList->rowCount(), 1);
			service.undoSave();
			//
		}
		else {
			service.undo();
			populateRepoList();
		}
	}
	catch (undoError ue) {
		QMessageBox::critical(this, "Undo error", ue.what());
	}
}

void GUI::redoAction()
{
	try {
		if (this->saveButton->isEnabled()) {
			if (service.redoSaveSize())
				fieldAgentsList->insertRows(fieldAgentsList->rowCount(), 1);
			service.redoSave();
			
		}
		else {
			service.redo();
			populateRepoList();
		}
	}
	catch (undoError ue) {
		QMessageBox::critical(this, "Edo error", ue.what());
	}
}

void GUI::nextTape()
{
	int size = tapeListWidget->count()-1;
	if (size == -1)
		return;
	if (tapeListWidget->item(size)->isSelected())
	{
		tapeListWidget->item(size)->setSelected(0);
		tapeListWidget->item(0)->setSelected(1);
		return;
	}
	for (int i = 0; i < size-1; ++i)
	{
		if (tapeListWidget->item(i)->isSelected())
		{
			tapeListWidget->item(i)->setSelected(0);
			tapeListWidget->item(i+1)->setSelected(1);
			return;
		}
	}
	tapeListWidget->item(0)->setSelected(1);
}


void GUI::filterTape()
{

	QListWidget* fiteredListWidget = new QListWidget{};
	string filmedLocation = this->filmedLocationLineEdit->text().toStdString();
	int accessCount = this->accessCountLineEdit->text().toInt();
	vector<Tape> tapesFromRepo = service.getFilteredList(filmedLocation, accessCount);
	for (Tape currentTape : tapesFromRepo) {

		fiteredListWidget->addItem(QString::fromStdString(currentTape.toString()));
	}
	QWidget* newWindow = new QWidget;
	newWindow->setWindowTitle("Filter result");
	QVBoxLayout* filterLabel = new QVBoxLayout{};
	filterLabel->addWidget(fiteredListWidget);
	//newWindow->setCentralWidget(*filterLabel);
	newWindow->setLayout(filterLabel);
	newWindow->show();

}

void GUI::enableFieldAgent()
{
	fieldAgentView->show();
	if (this->filterButton->isEnabled())
		filterButton->setEnabled(0);
	else
		filterButton->setEnabled(1);
	if (nextButton->isEnabled())
		nextButton->setEnabled(0);
	else
		nextButton->setEnabled(1);
	if (saveButton->isEnabled())
		saveButton->setEnabled(0);
	else
		saveButton->setEnabled(1);
	if (openButton->isEnabled())
		openButton->setEnabled(0);
	else
		openButton->setEnabled(1);
	if (this->addButton->isEnabled())
		addButton->setEnabled(0);
	else
		addButton->setEnabled(1);
	if (deleteButton->isEnabled())
		deleteButton->setEnabled(0);
	else
		deleteButton->setEnabled(1);
	if (updateButton->isEnabled())
		updateButton->setEnabled(0);
	else
		updateButton->setEnabled(1);
			
}

void GUI::openFieldAgent()
{
	service.openMyList();
}
