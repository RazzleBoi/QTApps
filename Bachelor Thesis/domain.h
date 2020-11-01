#pragma once
#include <string>
#include <sstream>

using namespace std;

class Driver {
private:
	string name, status;
	int latitude, longitude, score;
	
public:
	Driver() {};
	~Driver() {};
	Driver( string name, string status, int latitude, int longitude, int score )
		: name{ name }, status{ status }, latitude{ latitude }, longitude{longitude}, score{ score }{}
	string toString() {
		stringstream buffer;
		buffer << name << "|" << status << "|" << latitude << "|" << longitude << "|" << score;
		return buffer.str();
	}

	void fromLine(string line) {
		
		name = line.substr(0, line.find_first_of('|'));
		line = line.substr(line.find_first_of('|') + 1);
		status = line.substr(0, line.find_first_of('|'));
		line = line.substr(line.find_first_of('|') + 1);

		string latString = line.substr(0, line.find_first_of('|'));
		latitude = stoi(latString);
		line = line.substr(line.find_first_of('|') + 1);

		string longString = line.substr(0, line.find_first_of('|'));
		longitude = stoi(longString);
		line = line.substr(line.find_first_of('|') + 1);

		score = stoi(line);

	}

	string getName() { return name; }
	string getStatus() { return status; }
	int getLatitude() { return latitude; }
	int getLongitude() { return longitude; }

	void modifyLatitude(int value) { latitude += value; }
	void modifyLongitude(int value) { longitude += value; }
	int getScore() { return score; }
	
	friend bool operator==(Driver d1, Driver d2) { return d1.name == d2.name; };
	friend bool operator<(Driver const& a, Driver const& b) {
		int result = a.name.compare(b.name);
		if (result > 0)
			return 1;
		return 0;
	}

};


class Report {
private:
	string description, reporterName;
	int latitude, longitude;
	bool validated;
public:
	Report() {};
	~Report() {};
	Report(string description, string reporterName, int latitude, int longitude, bool validated) :
		description{ description }, reporterName{ reporterName }, latitude{ latitude }, longitude{ longitude }, validated{validated}{}

	string getDescription() { return description; }
	string getReporter() { return reporterName; }
	int getLatitude() { return latitude; }
	int getLongitude() { return longitude; }

	bool getValidated() { return validated; }

	string toString() {
		stringstream buffer;
		buffer << description << "|" << reporterName << "|" << latitude << "|" << longitude << "|" << validated;
		return buffer.str();
	}

	void fromLine(string line) {
		description = line.substr(0, line.find_first_of('|'));
		line = line.substr(line.find_first_of('|') + 1);
		
		reporterName = line.substr(0, line.find_first_of('|'));
		line = line.substr(line.find_first_of('|') + 1);

		string latString = line.substr(0, line.find_first_of('|'));
		latitude = stoi(latString);
		line = line.substr(line.find_first_of('|') + 1);

		string longString = line.substr(0, line.find_first_of('|'));
		longitude = stoi(longString);
		line = line.substr(line.find_first_of('|') + 1);

		validated = stoi(line);

	}
	friend bool operator==(Report p1, Report p2) { return p1.description == p2.description; };
	friend bool operator<(Report const& a, Report const& b) {
		int result = a.description.compare(b.description);
		if (result > 0)
			return 1;
		return 0;
	}
};