#pragma once
#include "domain.h"
#include <string>
#include <vector>
#include <fstream>


template<typename element>
class fileRepo
{
private:
	string storingFile = "None";
public:
	~fileRepo()
	{
		vector<element*> list =this->readFromFile();
		writeToFile(list);
	}
	void addElement(element* elementAdded) ;
	void updateElement(element* elementUpdated) ;
	void deleteElement(element* elementDeleted) ;
	vector<element*>getList() ;
	int size() ;

	void setStoringfile(string path)  { storingFile = path; };
	void writeToFile( vector<element*> list) ;
	vector<element*> readFromFile() ;
};


/*adds an element to the repo if its not already there
if it is throws exception*/
template<typename element>
inline void fileRepo<element>::addElement(element* elementAdded)
{
	vector<element*> list=this->readFromFile();

	for (auto element : list) {
		if (*elementAdded == *element) {
			delete elementAdded;
			for (auto currentElement : list) {
				delete currentElement;
			}
			throw exception("Add error: Object already in repo");
		}
	}
	list.push_back(elementAdded);
	writeToFile(list);
	for (auto currentElement : list) {
		delete currentElement;
	}
}

template<typename element>
inline void fileRepo<element>::updateElement(element* elementUpdated)
{
	vector<element*> list = this->readFromFile();

	for (int i = 0; i < list.size(); i++) {
		if (*list[i] == *elementUpdated) {
			delete list[i];
			list[i] = elementUpdated;
			writeToFile(list);
			for (auto currentElement : list) {
				delete currentElement;
			}
			return;
		}
	}
	delete elementUpdated;
	throw exception("Update error : Object not in repo");
	
}

template<typename element>
inline void fileRepo<element>::deleteElement(element* elementDeleted)
{

	vector<element*> list = this->readFromFile();

	for (int i = 0; i < list.size(); i++) {
		if (*list[i] == *elementDeleted) {
			list.erase(list.begin() + i);
			writeToFile(list);
			for (auto currentElement : list) {
				delete currentElement;
			}
			return;
		}
	}
	delete elementDeleted;
	throw exception("Delete error : Object not in repo");

}

template<typename element>
inline vector<element*> fileRepo<element>::getList()
{
	vector<element*> list = this->readFromFile();
	return list;
}

template<typename element>
inline int fileRepo<element>::size()
{
	vector<element*> list = this->readFromFile();
	return list.size();
}

template<typename element>
inline void fileRepo<element>::writeToFile(vector<element*> list)
{
	if (storingFile == "None")
		return;
	element* aux;
	for (int i = 0; i < list.size(); i++)
		for (int j = i + 1; j < list.size(); j++)
			if (*list[j] < *list[i]) {
				aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}
	ofstream writeFile(storingFile);
	for (auto element : list) {
		writeFile << (*element).toString() << "\n";
	}
	writeFile.close();
}

template<typename element>
inline vector<element*> fileRepo<element>::readFromFile()
{
	vector<element*> list;
	if (storingFile == "None")
		return list;
	ifstream readFile(storingFile);
	string line;
	while (getline(readFile, line)) {
		
		if (line == "")
			break;
		element* currentElement = new element();
		(*currentElement).fromLine(line);
		list.push_back(currentElement);
	}
	
	readFile.close();
	return list;
}





