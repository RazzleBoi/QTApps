#include "Repository.h"
#include <string.h>
using namespace std;

fileRepo::fileRepo()
{
    this->fileName = "fileRepo.txt";
    ofstream writefile(fileName);
    writefile.close();
}
string fileRepo::getFileName()
{
    return fileName;
}


int fileRepo::numberOfTapes()
{

    std::vector < Tape > listOfTapes = readFile();
    
    return listOfTapes.size();
}


int fileRepo::searchTape(string tapeTitle)
{
    std::vector < Tape > listOfTapes = readFile();
    for (auto iterator = listOfTapes.begin(); iterator != listOfTapes.end(); ++iterator) {

        string currentTitle = (*iterator).getTitle();
        if (currentTitle == tapeTitle)
        {
            int position =std::distance(listOfTapes.begin(), iterator);
            return position;
        }
    }
    return -1;
}

void fileRepo::addTape(Tape tapeToAdd)
{

    std::vector < Tape > listOfTapes = readFile();
    string tapeToAddTitle = tapeToAdd.getTitle();
    if (this->searchTape(tapeToAddTitle) != -1)
        throw repoError("Tape already in repo!");

    listOfTapes.push_back(tapeToAdd);
    writeToFile(listOfTapes);
}

Tape fileRepo::updateTape(Tape updateTape)
{

    std::vector < Tape > listOfTapes = readFile();
    string updateTapeTitle = updateTape.getTitle();
    int positionOfTape = searchTape(updateTapeTitle);
    if (positionOfTape == -1)
        throw repoError("Tape not found!");
    Tape oldTape = listOfTapes[positionOfTape];
    listOfTapes[positionOfTape] = updateTape;
    writeToFile(listOfTapes);
    return oldTape;
}

Tape fileRepo::removeTape(string title)
{

    std::vector < Tape > listOfTapes = readFile();
    int positionOfTape = this->searchTape(title);
    if (positionOfTape == -1)
        throw repoError("Tape not found!");

    Tape oldTape = listOfTapes[positionOfTape];
    listOfTapes.erase(listOfTapes.begin() +  positionOfTape);
    writeToFile(listOfTapes);
    return oldTape;
}
Tape fileRepo::getTapeWithGivenTitle(string title)
{

    std::vector < Tape > listOfTapes =readFile();
    int position = searchTape(title);
    Tape currentElement = listOfTapes[position];
    return currentElement;
    
}

std::vector<Tape> fileRepo::getAllTapes()
{

    std::vector < Tape > listOfTapes = readFile();
    return listOfTapes;
}

Tape fileRepo::getTapeWithGivenPosition(int position)
{

    std::vector < Tape > listOfTapes = readFile();
    Tape elementAtPosition = listOfTapes[position];
    return elementAtPosition;
}


csvFileRepo::csvFileRepo()
{
    this->fileName = "csvfileRepo.csv";
    ifstream readFile(fileName);
    if (readFile.is_open() == 1) {
        readFile.close();
        return;
    }
    readFile.close();
    ofstream writefile(fileName);
    writefile.close();
}
csvFileRepo::csvFileRepo(string fileName)
{
    this->fileName = fileName;
    ifstream readFile(fileName);
    if (readFile.is_open() == 1) {
        readFile.close();
        return;
    }
    readFile.close();
    ofstream writefile(fileName);
    writefile.close();
}

void csvFileRepo::setFileToStoreData(const string fileName)
{
    this->fileName = fileName;
    ifstream readFile(fileName);
    if (readFile.is_open() == 1) {
        readFile.close();
        return;
    }
    readFile.close();
    ofstream writefile(fileName);
    writefile.close();
}

std::vector<Tape> csvFileRepo::readFile()
{
    std::vector < Tape > listOfTapes;
    ifstream readFile(fileName);
    listOfTapes.clear();
    Tape aTape;
    while (!readFile.fail() && !readFile.eof()) {
        readFile >> aTape;
        if (aTape.getAccessCount() == -1)
            break;
        listOfTapes.push_back(aTape);
    }
    readFile.close();
    return listOfTapes;
}

void csvFileRepo::writeToFile(std::vector<Tape> listOfTapes)
{
    ofstream writeFile(fileName);
    for (auto currentTape : listOfTapes) {
        writeFile << currentTape << endl;
    }
    writeFile.close();
}


htmlFileRepo::htmlFileRepo()
{
    this->fileName = "htmlfileRepo.txt";
    ofstream writefile(fileName);
    writefile.close();
}

htmlFileRepo::htmlFileRepo(string fileName)
{
    this->fileName = fileName;
    ifstream readFile(fileName);
    if (readFile.is_open() == 1) {
        readFile.close();
        return;
    }
    readFile.close();
    ofstream writefile(fileName);
    writefile.close();
}

void htmlFileRepo::setFileToStoreData(const string fileName)
{
    this->fileName = fileName;
    ifstream readFile(fileName);
    if (readFile.is_open() == 1) {
        readFile.close();
        return;
    }
    readFile.close();
    ofstream writefile(fileName);
    writefile.close();
}

std::vector<Tape> htmlFileRepo::readFile()
{
    std::vector < Tape > listOfTapes;
    string currentLine, startColumn, endColumn, title, filmedLocation, footagePreview, theDateString;
    int accessCount;
    ifstream readFile(fileName);
    
    std::getline(readFile, currentLine);
    if (currentLine == "")
        return vector <Tape>();
    while(currentLine != "</tr>")
        std::getline(readFile, currentLine); //read everything till the first row of info
    std::getline(readFile, currentLine);
    Tape aTape;
    while (currentLine != "</table>" && currentLine != "") {
        std::getline(readFile, currentLine);
        title = currentLine.substr(currentLine.find_first_of(">")+1, currentLine.find_last_of("<") - currentLine.find_first_of(">") - 1);
        aTape.setTitle(title);

        std::getline(readFile, currentLine);
        filmedLocation = currentLine.substr(currentLine.find_first_of(">") + 1, currentLine.find_last_of("<") - currentLine.find_first_of(">") - 1);
        aTape.setFilmedAt(filmedLocation);

        std::getline(readFile, currentLine);
        theDateString = currentLine.substr(currentLine.find_first_of(">") + 1, currentLine.find_last_of("<") - currentLine.find_first_of(">") - 1);
        aTape.setDateFromString(theDateString);

        std::getline(readFile, currentLine);
        accessCount = stoi(currentLine.substr(currentLine.find_first_of(">") + 1, currentLine.find_last_of("<") - currentLine.find_first_of(">") - 1));
        aTape.setAccesCount(accessCount);
        std::getline(readFile, currentLine);
        footagePreview = currentLine.substr(currentLine.find_first_of(">") + 1, currentLine.find_last_of("<") - currentLine.find_first_of(">") - 1);
        aTape.setFootagePreview(footagePreview);
        listOfTapes.push_back(aTape);
        std::getline(readFile, currentLine); //reads </tr>
        std::getline(readFile, currentLine); //reads <tr> or </table> 
    }
    readFile.close();
    return listOfTapes;
}

void htmlFileRepo::writeToFile(std::vector<Tape> listOfTapes)
{
    ofstream writeFile(fileName);
    writeFile << "<!DOCTYPE html>"<<"\n";
    writeFile << "<html> "<<"\n";
    writeFile << "<head> "<<"\n";
    writeFile << "<title> "<<"TapesList "<<"</title>"<<"\n";
    writeFile << "</head>"<<"\n";
    writeFile << "<body>"<<"\n";
    writeFile << "<table border = \"1\">" << "\n";

    writeFile << "<tr>" << "\n";

    writeFile << "<td>" << " ";
    writeFile << "Title" << " ";
    writeFile << "</td>" << "\n";

    writeFile << "<td>" << " ";
    writeFile << "Location" << " ";
    writeFile << "</td>" << "\n";

    writeFile << "<td>" << " ";
    writeFile << "Date" << " ";
    writeFile << "</td>" << "\n";

    writeFile << "<td>" << " ";
    writeFile << "AccessCount" << " ";
    writeFile << "</td>" << "\n";

    writeFile << "<td>" << " ";
    writeFile << "Footage preview" << " ";
    writeFile << "</td>" << "\n";

    writeFile << "</tr>" << "\n";
    for (auto currentTape : listOfTapes) {
        writeFile << "<tr>" << "\n";

        writeFile << "<td>";
        writeFile << currentTape.getTitle();
        writeFile << "</td>" << "\n";

        writeFile << "<td>";
        writeFile << currentTape.getFilmedAt();
        writeFile << "</td>" << "\n";

        writeFile << "<td>";
        writeFile << currentTape.getDate();
        writeFile << "</td>" << "\n";

        writeFile << "<td>";
        writeFile << currentTape.getAccessCount();
        writeFile << "</td>" << "\n";

        writeFile << "<td>";
        writeFile << currentTape.getFootagePreview();
        writeFile << "</td>" << "\n";

        writeFile << "</tr>" << "\n";
    }

    writeFile << "</table>" << "\n";
    writeFile << "</body>" << "\n";
    writeFile << "</html>" << "\n";
    writeFile.close();
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int memoryRepo::numberOfTapes()
{
    return listOfTapes.size();
}


int memoryRepo::searchTape(string tapeTitle)
{
    for (auto iterator = listOfTapes.begin(); iterator != listOfTapes.end(); ++iterator) {

        string currentTitle = (*iterator).getTitle();
        if (currentTitle == tapeTitle)
        {
            int position = std::distance(listOfTapes.begin(), iterator);
            return position;
        }
    }
    return -1;
}

void memoryRepo::addTape(Tape tapeToAdd)
{
    string tapeToAddTitle = tapeToAdd.getTitle();
    if (this->searchTape(tapeToAddTitle) != -1)
        throw repoError("Tape already in repo!");

    listOfTapes.push_back(tapeToAdd);
}

Tape memoryRepo::updateTape(Tape updateTape)
{
    string updateTapeTitle = updateTape.getTitle();
    int positionOfTape = searchTape(updateTapeTitle);
    if (positionOfTape == -1)
        throw repoError("Tape not found!");
    Tape oldTape = listOfTapes[positionOfTape];
    listOfTapes[positionOfTape] = updateTape;
    return oldTape;
}

Tape memoryRepo::removeTape(string title)
{
    int positionOfTape = this->searchTape(title);
    if (positionOfTape == -1)
        throw repoError("Tape not found!");

    Tape oldTape = listOfTapes[positionOfTape];
    listOfTapes.erase(listOfTapes.begin() + positionOfTape);
    return oldTape;
}
Tape memoryRepo::getTapeWithGivenTitle(string title)
{
    int position = searchTape(title);
    Tape currentElement = listOfTapes[position];
    return currentElement;

}

std::vector<Tape> memoryRepo::getAllTapes()
{
    return listOfTapes;
}

Tape memoryRepo::getTapeWithGivenPosition(int position)
{

    Tape elementAtPosition = listOfTapes[position];
    return elementAtPosition;
}