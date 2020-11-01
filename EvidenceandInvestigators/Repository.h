#pragma once
#include "domain.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>


using namespace std;

typedef bool exitCode;

class memoryRepo {
private:
	std::vector < Tape > listOfTapes;
public:
	virtual ~memoryRepo()
	{

	};
	virtual  string getFileName() { return "none"; };
	/// <summary>
	/// returns the number of tapes stored
	/// </summary>
	virtual int numberOfTapes();
	/// <summary>
	///returns the position of the tape corresponding to the name
	///or -1 if no such tape exists
	/// </summary>
	virtual int searchTape(string tapeTitle);

	/// <summary>
	///returns 0 and adds aTape to repo if it is not already added
	///if it is returns -1
	/// </summary>
	virtual void addTape(Tape tapeToAdd);

	/// <summary>
	///returns 0 and upgrades the Tape with the same id as aTape to aTape if it is in repo,
	///if it is not returns - 1 
	/// </summary>
	virtual Tape updateTape(Tape updateTape);
	/// <summary>
	///returns 0 and deletes the Tape with the id catalogueNumberKey if it is in repo,
	///if it is not returns - 1 
	/// </summary>
	virtual Tape removeTape(string title);

	/// <summary>
	///returns a pointer to a deep copy of the map with the given title if it exists
	/// ottherwise  returns null pointer
	/// </summary>
	virtual Tape getTapeWithGivenTitle(string title);

	/// <summary>
	///returns a pointer to a deepcopy list of all Tapes
	/// </summary>
	virtual std::vector<Tape> getAllTapes();
	virtual Tape getTapeWithGivenPosition(int position);
};

/*
class csvFileRepo: {
private:

	string fileName;

public:
	csvFileRepo();
	csvFileRepo( string fileName);

	std::vector < Tape >  readCsvFile();
	void writeToCsvFile(std::vector < Tape > listOfTapes);
	void setFileToStoreData(const string fileName);
	/// <summary>
	/// returns the number of tapes stored
	/// </summary>
	int numberOfTapes();
	/// <summary>
	///initialises repo with 10 default tapes
	/// </summary>
	void initialiseRepo();
	/// <summary>
	///returns the position of the tape corresponding to the name
	///or -1 if no such tape exists
	/// </summary>
	int searchTape(string tapeTitle);

	/// <summary>
	///returns 0 and adds aTape to repo if it is not already added
	///if it is returns -1
	/// </summary>
	void addTape(Tape tapeToAdd);

	/// <summary>
	///returns 0 and upgrades the Tape with the same id as aTape to aTape if it is in repo,
	///if it is not returns - 1
	/// </summary>
	void updateTape(Tape updateTape);
	/// <summary>
	///returns 0 and deletes the Tape with the id catalogueNumberKey if it is in repo,
	///if it is not returns - 1
	/// </summary>
	void removeTape(string title);

	/// <summary>
	///returns a pointer to a deep copy of the map with the given title if it exists
	/// ottherwise  returns null pointer
	/// </summary>
	Tape getTapeWithGivenTitle(string title);

	/// <summary>
	///returns a pointer to a deepcopy list of all Tapes
	/// </summary>
	std::vector<Tape> getAllTapes();
	Tape getTapeWithGivenPosition(int position);
};*/

class repoError : public exception
{
private:
	string message;
public:
	repoError(const std::string& message) : message(message) {}
	virtual const char* what() const noexcept override
	{
		return message.c_str();
	}
};

class fileRepo: public memoryRepo {
protected:
	string fileName;

public:
	fileRepo();

	virtual ~fileRepo() {
		//cout << "DestroyFileRepo\n"; 
	}
	string getFileName();
	virtual std::vector < Tape >  readFile() = 0;
	virtual void writeToFile(std::vector < Tape > listOfTapes) = 0;
	virtual void setFileToStoreData(const string fileName) = 0;

	/// <summary>
	/// returns the number of tapes stored
	/// </summary>
	int numberOfTapes() override;
	/// <summary>
	///returns the position of the tape corresponding to the name
	///or -1 if no such tape exists
	/// </summary>
	int searchTape(string tapeTitle) override;

	/// <summary>
	///returns 0 and adds aTape to repo if it is not already added
	///if it is returns -1
	/// </summary>
	void addTape(Tape tapeToAdd) override;

	/// <summary>
	///returns 0 and upgrades the Tape with the same id as aTape to aTape if it is in repo,
	///if it is not returns - 1 
	/// </summary>
	Tape updateTape(Tape updateTape) override;
	/// <summary>
	///returns 0 and deletes the Tape with the id catalogueNumberKey if it is in repo,
	///if it is not returns - 1 
	/// </summary>
	Tape removeTape(string title) override;

	/// <summary>
	///returns a pointer to a deep copy of the map with the given title if it exists
	/// ottherwise  returns null pointer
	/// </summary>
	Tape getTapeWithGivenTitle(string title) override;

	/// <summary>
	///returns a pointer to a deepcopy list of all Tapes
	/// </summary>
	std::vector<Tape> getAllTapes() override;
	Tape getTapeWithGivenPosition(int position) override;

	
};

class csvFileRepo: public fileRepo {
private:
	//string fileName;
public:
	csvFileRepo();
	~csvFileRepo() {
		//cout << "DestroycsvFileRepo\n";
	}
	csvFileRepo(string fileName);
	void setFileToStoreData(const string fileName) override;
	std::vector < Tape >  readFile() override;
	void writeToFile(std::vector < Tape > listOfTapes) override;
};

class htmlFileRepo : public fileRepo {
private:
	//string fileName;
public:
	htmlFileRepo();
	~htmlFileRepo() {
		//cout << "DestroyhtmlFileRepo\n";
	}
	htmlFileRepo(string fileName);
	void setFileToStoreData(const string fileName) override;
	std::vector < Tape >  readFile() override;
	void writeToFile(std::vector < Tape > listOfTapes) override;
};
