#pragma once
#include <vector>
#include "Observer.h"

using namespace std;

class Subject
{
private:
	vector<Observer*> observers;

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify();
};

