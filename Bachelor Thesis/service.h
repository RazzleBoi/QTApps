#pragma once
#include <math.h>
#include "domain.h"
#include "repo.h"
#include <algorithm>
#include <functional>
#include <set>
#include <assert.h>
#include "Subject.h"



template<typename element>
class service: public Subject{
	friend class serviceWrapper;
private:
	fileRepo<element> repoElements;
public:
	~service()
	{

	};
	void setStoringFile(string filePath) { repoElements.setStoringfile(filePath); };
	void writeToFile();
	void readFromFile();
	int size() { return repoElements.size(); };
	/*tries to add element to repo and if succesfull notifies its observers
	(if add is not succesfull) repo will throw an exception so notify(0 wont be apelated*/
	void addElement(element* elementAdded) { repoElements.addElement(elementAdded); this->notify(); };
	void updateElement(element* elementUpdated) { repoElements.updateElement(elementUpdated); this->notify(); };
	void deleteElement(element* elementDeleted) { repoElements.deleteElement(elementDeleted); };
	vector<element*> getElements() ;
	vector<element*> getSearchedElements(string key) ;
	vector<element*> getElementsOf(Driver driver, int dist) ;

};

class serviceWrapper {
public:
	service<Report> serv;
	serviceWrapper(fileRepo<Report> repo) {
		serv.repoElements = repo;
	};
};

template<typename element>
inline void service<element>::writeToFile()
{
	repoElements->writeToFile();
}
template<typename element>
inline void service<element>::readFromFile()
{
	repoElements->readFromFile();
}


template<typename element>
inline vector<element*> service<element>::getElements()
{
	vector<element*> list = repoElements.getList();
	return list;
}

template<typename element>
inline vector<element*> service<element>::getSearchedElements(string key)
{
	vector<element*> list = repoElements.getList();
	vector<element*> filteredList{};
	for (auto currentElement : list) {
		if ( key!="" && currentElement->getName().find( key) != string::npos)
			filteredList.push_back(currentElement);
	}
	return filteredList;
}

template<typename element>
inline vector<element*> service<element>::getElementsOf(Driver driver, int dist)
{
	vector<element*> list = repoElements.getList();
	vector<element*> filteredList{};
	for (auto currentElement : list) {
		double distance = sqrt((currentElement->getLatitude() - driver.getLatitude()) * (currentElement->getLatitude() - driver.getLatitude()) + (currentElement->getLongitude() - driver.getLongitude()) * (currentElement->getLongitude() - driver.getLongitude()));
		if (distance <= dist)
			filteredList.push_back(currentElement);
	}

	for(int i=0; i<filteredList.size(); i++)
		for (int j = i + 1; j < filteredList.size(); j++)
		{
			double distance1 = sqrt((filteredList[i]->getLatitude() - driver.getLatitude()) * (filteredList[i]->getLatitude() - driver.getLatitude()) + (filteredList[i]->getLongitude() - driver.getLongitude()) * (filteredList[i]->getLongitude() - driver.getLongitude()));
			double distance2 = sqrt((filteredList[j]->getLatitude() - driver.getLatitude()) * (filteredList[j]->getLatitude() - driver.getLatitude()) + (filteredList[j]->getLongitude() - driver.getLongitude()) * (filteredList[j]->getLongitude() - driver.getLongitude()));
			if (distance1 > distance2)
			{
				element* aux = filteredList[i];
				filteredList[i] = filteredList[j];
				filteredList[j] = aux;
			}
		}
	return filteredList;
}


