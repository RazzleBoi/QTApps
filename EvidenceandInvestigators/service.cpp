#include "service.h"
#include "Repository.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <codecvt>
#include <Windows.h>

using convert_t = std::codecvt_utf8<wchar_t>;

Service::~Service()
{
	if(fieldAgentsList)
		delete fieldAgentsList;
	if(repository)
		delete[] repository;
}
void Service::configureRepo()
{
	ifstream configFile("configRepo.txt");
	string repoType,prefix;
	configFile >> prefix >> repoType;
	if (repoType == "csv") {
		repository = new csvFileRepo("csvFileRepo.csv");
		
	}
	else if (repoType == "html") {
		repository = new htmlFileRepo("fileRepo.html");
		
	}
	else
		repository = new memoryRepo();
	
	configFile >> prefix >> repoType;
	if (repoType == "csv") {
		fieldAgentsList = new csvFileRepo("myList.csv");
		
	}
	else if (repoType == "html") {
		fieldAgentsList = new htmlFileRepo("myList.html");
		
	}
	else
		fieldAgentsList = new memoryRepo();

}
void Service::setFileNameForRepo(const string fileName)
{
	//this->repository->setFileToStoreData(fileName);
}

void Service::setMyListFileType(const string fileName)
{
	string extension = fileName.substr(fileName.find_last_of(".")+1);
	if (extension == "html") {
		fieldAgentsList = new htmlFileRepo(fileName);
	}
	else {
		fieldAgentsList = new csvFileRepo(fileName);
	}
}

std::vector<Tape> Service::getListOfAllTapes()
{
	return this->repository->getAllTapes();
}

int Service::getNumberOfTapes()
{
	return this->repository->numberOfTapes();
}

void Service::openMyList()
{
	string fileName = fieldAgentsList->getFileName();
	string extension = fileName.substr(fileName.find_last_of(".") + 1);
	std::wstring_convert<convert_t, wchar_t> strconverter;
	std::wstring fullPath = strconverter.from_bytes(fileName);
	//std::wstring path = "myList";
	LPCWSTR result = fullPath.c_str();
	ShellExecute(NULL, L"open", result, NULL, NULL, SW_SHOWNORMAL);

}


void Service::addTape(Tape tapeToBeAdded)
{
	validator.validateTape(tapeToBeAdded);
	this->repository->addTape(tapeToBeAdded);
	auto pointerAction = make_unique<addAction>(tapeToBeAdded, repository);
	this->undoStack.push_back(move(pointerAction));
}

void Service::updateTape(Tape tapeToUpdate)
{
	validator.validateTape(tapeToUpdate);
	Tape oldTape = this->repository->updateTape(tapeToUpdate);
	auto pointerAction = make_unique<updateAction>(oldTape, tapeToUpdate, repository);
	this->undoStack.push_back(move(pointerAction));
	try {
		fieldAgentsList->updateTape(tapeToUpdate);
	}
	catch (repoError re) {
		//if we get a delete error that says the tape is not in myList
		//we just ignore it
		return;
	}

}

void Service::deleteTape(string title)
{
	Tape oldTape = this->repository->removeTape(title);
	auto pointerAction = make_unique<removeAction>(oldTape, repository);
	this->undoStack.push_back(move(pointerAction));

	try {
		fieldAgentsList->removeTape(title);
	}
	catch (repoError re) {
		//if we get a delete error that says the tape is not in myList
		//we just ignore it
		return;
	}
}

Tape Service::getTapeAtPosition(int position) {
	return this->repository->getTapeWithGivenPosition(position);
}

bool Service::saveToMyList(string title)
{
	int positionOfSearchedTitleTape = this->repository->searchTape(title);
	if (positionOfSearchedTitleTape == -1) {
		
		return 0;
	}
	Tape tapeToBeSaved = this->repository->getTapeWithGivenPosition(positionOfSearchedTitleTape);
	this->fieldAgentsList->addTape(tapeToBeSaved);
	auto pointerAction = make_unique<saveAction>(tapeToBeSaved, fieldAgentsList);
	this->undoSaveStack.push_back(move(pointerAction));
	return 1;
}

std::vector<Tape> Service::getFieldAgentsList()
{

	std::vector<Tape> deepCopyOfFieldAgentsList(this->fieldAgentsList->getAllTapes());
	return deepCopyOfFieldAgentsList;
}

std::vector<Tape> Service::getFilteredList(string Location, int maximumAccessCount)
{
	std::vector<Tape>  repoList = this->repository->getAllTapes();
	std::vector<Tape>  filteredList{};
	for (auto& currentTape : repoList)
		if (currentTape.getFilmedAt() == Location && currentTape.getAccessCount() < maximumAccessCount)
				filteredList.push_back(currentTape);
		
	return filteredList;
}

Tape Service::getNextTape()
{
	Tape currentTape = this->getTapeAtPosition(this->currentPositionInList);
	this->currentPositionInList++;
	if (this->currentPositionInList == this->getNumberOfTapes())
		this->currentPositionInList = 0;
	return currentTape;
}

void Service::undo()
{
	if (undoStack.size() == 0) {
		throw undoError("Nothing to undo!");
	}
	unique_ptr<Action> lastAction = move(undoStack.back());
	lastAction->executeUndo();
	undoStack.pop_back();
	redoStack.push_back(move(lastAction));
	
}

void Service::redo()
{
	if (redoStack.size() == 0) {
		throw undoError("Nothing to redo!");
	}
	unique_ptr<Action> lastAction = move(redoStack.back());
	lastAction->executeRedo();
	redoStack.pop_back();
	undoStack.push_back(move(lastAction));

}

void Service::undoSave()
{
	if (undoSaveStack.size() == 0) {
		throw undoError("Nothing to undo!");
	}
	unique_ptr<Action> lastAction = move(undoSaveStack.back());
	lastAction->executeUndo();
	undoSaveStack.pop_back();
	redoSaveStack.push_back(move(lastAction));

}

void Service::redoSave()
{
	if (redoSaveStack.size() == 0) {
		throw undoError("Nothing to redo!");
	}
	unique_ptr<Action> lastAction = move(redoSaveStack.back());
	lastAction->executeRedo();
	redoSaveStack.pop_back();
	undoSaveStack.push_back(move(lastAction));

}

void addAction::executeRedo()
{
	this->repository->addTape(tapeAdded);
}

void addAction::executeUndo()
{
	this->tapeAdded = this->repository->removeTape(this->tapeAdded.getTitle());
}

void removeAction::executeRedo()
{
	this->tapeRemoved = this->repository->removeTape(tapeRemoved.getTitle());
}

void removeAction::executeUndo()
{
	this->repository->addTape(this->tapeRemoved);
}

void updateAction::executeUndo()
{
	newTape = this->repository->updateTape(oldTape);
}
void updateAction::executeRedo()
{
	oldTape = this->repository->updateTape(newTape);
}


void saveAction::executeRedo()
{
	this->repository->addTape(tapeSaved);
}

void saveAction::executeUndo()
{
	this->tapeSaved = this->repository->removeTape(this->tapeSaved.getTitle());
}