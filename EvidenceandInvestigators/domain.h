#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct date {
	int year, month, day;
};
class Tape {
private:
	string title, filmedAt, footagePreview;
	date creationDate; 
	int accessCount;

public:
	Tape();
	~Tape();
	Tape(int accessCount);
	Tape(string title, string filmedLocation, int creationDateDay, int creationDateMonth, int creationDateYear, int accessCount, string footagePreview);
	const int getAccessCount();
	const string getTitle();
	const string getFilmedAt();
	const string getFootagePreview();
	void setTitle(string newTitle);
	void setFilmedAt(string newFilmedLocation);
	void setFootagePreview(string newFootagePreview);
	void setAccesCount(int newAccessCount);
	const date getDateAsInts();
	const string getDate();
	void setDateFromString(string dateString);
	string toString();
	Tape& operator=(Tape const  &sourceTape);
	friend std::istream& operator>>(std::istream& inputStream, Tape& tapeBeingRead);
	friend std::ostream& operator<<(std::ostream& outputStream, Tape& tapeBeingWritten);
};