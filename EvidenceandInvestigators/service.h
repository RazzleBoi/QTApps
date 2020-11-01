#pragma once
#include "domain.h"
#include "Repository.h"
#include "Validator.h"
#include <string.h>

class Action {
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() {};
};
class addAction: public Action {
private:
	Tape tapeAdded;
	memoryRepo* repository;
public:
	addAction(Tape tapeAdded, memoryRepo* repository) :tapeAdded{ tapeAdded }, repository{ repository }{};
	void executeRedo() override;
	void executeUndo() override;
	~addAction() {};
};
class removeAction : public Action {
private:
	Tape tapeRemoved;
	memoryRepo* repository;
public:
	removeAction(Tape tapeRemoved, memoryRepo* repository) :tapeRemoved{ tapeRemoved }, repository{ repository }{};
	void executeRedo() override;
	void executeUndo() override;
	~removeAction() {} ;
};
class updateAction : public Action {
	
private:
	Tape oldTape, newTape;
	memoryRepo* repository;

public:
	updateAction(Tape oldTape, Tape newTape, memoryRepo* repository) : oldTape{ oldTape }, newTape{newTape}, repository{ repository }{};
	void executeRedo() override;
	void executeUndo() override;
	~updateAction() {};
	
};
class undoError : public exception
{
private:
	string message;
public:
	undoError(const std::string& message) : message(message) {}
	virtual const char* what() const noexcept override
	{
		return message.c_str();
	}
};

class saveAction : public Action {
private:
	Tape tapeSaved;
	memoryRepo* repository;
public:
	saveAction(Tape tapeSaved, memoryRepo* repository) :tapeSaved{ tapeSaved }, repository{ repository }{};
	void executeRedo() override;
	void executeUndo() override;
	~saveAction() {};
};

class Service {
private:
	memoryRepo *repository = nullptr;
	memoryRepo *fieldAgentsList = nullptr;
	vector <unique_ptr<Action>> undoStack{}, redoStack{};

	vector <unique_ptr<Action>> undoSaveStack{}, redoSaveStack{};
	int currentPositionInList = 0;
	tapeValidator validator;

	friend class MyListTableModel;
public:
	Service() {
	}
	~Service();
	/// <summary>
	/// returns the a deep copy of a list of all tapes
	/// </summary>

	void configureRepo();
	void setFileNameForRepo(const string fileName);
	void setMyListFileType(const string fileName);
	std::vector<Tape> getListOfAllTapes();

	int getNumberOfTapes();

	void openMyList();
	
	/// <summary>
	///adds aTape to repo if it is not already added and is the tape is valid 
	///throws error if tape is already in repo or not valid
	/// </summary>
	void addTape(Tape tapeToBeAdded);
	
	/// <summary>
	/// updates aTape to repo if it is not already added and is the tape is valid 
	///throws error if tape is not in repo or not valid
	/// </summary>
	void updateTape(Tape tapeToUpdate);

	/// <summary>
	/// deletes the tape from repo with the given title if it exists
	///throws error if tape is not in repo
	/// </summary>
	void deleteTape(string title);

	Tape getTapeAtPosition(int position);

	bool saveToMyList(string title);



	std::vector<Tape> getFieldAgentsList();
	std::vector<Tape> getFilteredList(string Location, int maximumAccessCount);
	Tape getNextTape();
	void undo();
	void redo();

	void undoSave();
	void redoSave();

	int undoSaveSize() { return this->undoSaveStack.size(); };
	int redoSaveSize() { return this->redoSaveStack.size(); };
};