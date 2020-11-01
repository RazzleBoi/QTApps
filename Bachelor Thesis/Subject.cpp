#include "Subject.h"

void Subject::addObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
	auto iterator = find(this->observers.begin(), this->observers.end(), observer);
	if (iterator != this->observers.end())
	{
		this->observers.erase(iterator);
	}
}

void Subject::notify()
{
	for (auto& observer : this->observers)
	{
		observer->update();
	}
}
