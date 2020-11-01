#include "domain.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"

//NULL Tape is denoted by accessCount ==-1
Tape::Tape()
{
	this->accessCount = 0;
}
Tape::~Tape()
{
}
Tape::Tape(string title, string filmedLocation,  int creationDateMonth, int creationDateDay, int creationDateYear, int accessCount, string footagePreview)
{
	this->title= title;
	this->filmedAt = filmedLocation;
	this->footagePreview = footagePreview;
	this->creationDate.day = creationDateDay;
	this->creationDate.month = creationDateMonth;
	this->creationDate.year = creationDateYear;
	this->accessCount = accessCount;
}

const int Tape::getAccessCount()
{
	return accessCount;
}

const string Tape::getTitle()
{
	return this->title;
}

const string Tape::getFilmedAt()
{
	return this->filmedAt;
}

const string Tape::getFootagePreview()
{
	return footagePreview;
}
void Tape::setTitle(string newTitle)
{
	title = newTitle;
}

void Tape::setFilmedAt(string newFilmedLocation)
{
	filmedAt= newFilmedLocation;
}

void Tape::setFootagePreview(string newFootagePreview)
{
	footagePreview = newFootagePreview;
}

void Tape::setAccesCount(int newAccessCount)
{
	accessCount = newAccessCount;
}

const date Tape::getDateAsInts()
{
	return this->creationDate;
}

const string Tape::getDate()
{
	string tapeString ="";
	if (this->creationDate.month < 10)
		tapeString += "0";
	tapeString += to_string(this->creationDate.month);
	tapeString += "-";

	if (this->creationDate.day < 10)
		tapeString += "0";
	tapeString += to_string(this->creationDate.day);
	tapeString += "-";

	tapeString += to_string(this->creationDate.year);
	return tapeString;
}

void Tape::setDateFromString(string dateString)
{
	this->creationDate.month = stoi(dateString.substr(0, dateString.find_first_of("-") ));
	this->creationDate.day = stoi(dateString.substr(dateString.find_first_of("-") + 1, dateString.find_last_of("-") - dateString.find_first_of("-")));
	this->creationDate.year = stoi(dateString.substr(dateString.find_last_of("-") + 1));
}

string Tape::toString()
{
	string tapeString = "";
	tapeString += this->title;
	tapeString += ",";
	tapeString += this->filmedAt;
	tapeString += ",";

	string dayString, monthString, yearString;

	if (this->creationDate.month < 10)
		tapeString += "0";
	tapeString += to_string(this->creationDate.month);
	tapeString += "-";

	if (this->creationDate.day < 10)
		tapeString += "0";
	tapeString += to_string(this->creationDate.day);
	tapeString += "-";

	tapeString += to_string(this->creationDate.year);
	tapeString += ",";

	tapeString += to_string(this->accessCount);
	tapeString += ",";
	tapeString += this->footagePreview;
	return tapeString;
}

Tape& Tape::operator=(Tape const& sourceTape)
{
	this->title = sourceTape.title;
	this->filmedAt = sourceTape.filmedAt ;
	this->creationDate.day = sourceTape.creationDate.day ;
	this->creationDate.month = sourceTape.creationDate.month ;
	this->creationDate.year = sourceTape.creationDate.year ;
	this->accessCount = sourceTape.accessCount ;
	this->footagePreview = sourceTape.footagePreview ;
	return *this;
}


std::ostream& operator<<(std::ostream& outputStream, Tape& tapeBeingWritten)
{
	string tapeString ="";
	tapeString += tapeBeingWritten.title;
	tapeString += ",";
	tapeString += tapeBeingWritten.filmedAt;
	tapeString += ",";

	string dayString, monthString, yearString;

	if (tapeBeingWritten.creationDate.month <10)
		tapeString += "0";
	tapeString += to_string(tapeBeingWritten.creationDate.month);
	tapeString += "-";

	if (tapeBeingWritten.creationDate.day < 10)
		tapeString += "0";
	tapeString += to_string(tapeBeingWritten.creationDate.day);
	tapeString += "-";

	tapeString += to_string(tapeBeingWritten.creationDate.year);
	tapeString += ",";

	tapeString += to_string(tapeBeingWritten.accessCount);
	tapeString += ",";
	tapeString += tapeBeingWritten.footagePreview;
	outputStream << tapeString;
	return outputStream;


}

std::istream& operator>>(std::istream& inputStream, Tape& tapeBeingRead)
{
	string parametersString;
	string title, filmedLocation, footagePreview;
	int accessCount, creationDateDay, creationDateMonth, creationDateYear;

	string dateError = "Invalid date!\n";
	string accessCountError = "Invalid Access count!\n";
	std::getline(inputStream, parametersString);
	if (parametersString[0] == 0) {
		tapeBeingRead.accessCount = -1;
		return inputStream;
	}
	int startPosition = 0, endPosition =0;

	while (parametersString[startPosition] == ' ') startPosition++;
	while (parametersString[endPosition] != ',') endPosition++;
	title = parametersString.substr(startPosition, endPosition - startPosition);
	endPosition++;
	while (parametersString[endPosition] == ' ') endPosition++;
	startPosition = endPosition;
	while (parametersString[endPosition] != ',') endPosition++;
	filmedLocation = parametersString.substr(startPosition, endPosition - startPosition);
	endPosition++;
	while (parametersString[endPosition] == ' ') endPosition++;
	startPosition = endPosition;

	while (parametersString[endPosition] != '-') endPosition++;
	creationDateMonth = strToInt(parametersString.substr(startPosition, endPosition - startPosition));
	if (creationDateMonth == -1)
	{
		throw dateError;
	}
	endPosition++;
	while (parametersString[endPosition] == ' ') endPosition++;
	startPosition = endPosition;

	while (parametersString[endPosition] != '-') endPosition++;
	creationDateDay = strToInt(parametersString.substr(startPosition, endPosition - startPosition));
	if (creationDateDay == -1)
	{
		throw dateError;
	}
	endPosition++;
	while (parametersString[endPosition] == ' ') endPosition++;
	startPosition = endPosition;

	while (parametersString[endPosition] != ',') endPosition++;
	creationDateYear = strToInt(parametersString.substr(startPosition, endPosition - startPosition));
	if (creationDateYear == -1)
	{
		throw dateError;
	}
	endPosition++;
	while (parametersString[endPosition] == ' ') endPosition++;
	startPosition = endPosition;
	while (parametersString[endPosition] != ',') endPosition++;
	
	accessCount = strToInt(parametersString.substr(startPosition, endPosition - startPosition));
	if (accessCount == -1)
	{
		throw accessCountError;
	}
	endPosition++;
	startPosition = endPosition;
	while (parametersString[endPosition] != 0) endPosition++;
	footagePreview = parametersString.substr(startPosition, endPosition - startPosition);
	endPosition++;
	startPosition = endPosition;

	tapeBeingRead = Tape(title, filmedLocation, creationDateDay, creationDateMonth, creationDateYear, accessCount, footagePreview);
	return inputStream;
}
