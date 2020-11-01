#include "bonusLab11.h"
#include <qchart.h>
#include <set>
bonusLab11::bonusLab11()
{
	generateChart();
}


void bonusLab11::generateChart()
{
	vector<Tape> repoList = service.getListOfAllTapes();
	QBarSeries* seriesOfLocations = new QBarSeries();

	//Access Count per filmed location


	//std::set <string> filmedLocations;
	std::map <string, int> accessCountForSpecificLocation;
	for (auto tape : repoList) {
		string currentTapesLocation = tape.getFilmedAt();
		if (accessCountForSpecificLocation.find(currentTapesLocation) == accessCountForSpecificLocation.end()) {
			accessCountForSpecificLocation.emplace(currentTapesLocation, tape.getAccessCount());
		}
		else {
			accessCountForSpecificLocation.at(currentTapesLocation) += tape.getAccessCount();
		}
	}
	QStringList locations;
	int position = 0;
	for (auto locationAccessCountPair : accessCountForSpecificLocation) {
		QBarSet* newLocationSet = new QBarSet(QString::fromStdString(locationAccessCountPair.first));
		for (int i = 0; i < position; i++)
			*newLocationSet << 0;
		*newLocationSet << locationAccessCountPair.second;
		seriesOfLocations->append(newLocationSet);
		locations << QString::fromStdString(locationAccessCountPair.first) ;
		position++;
	}

	QChart* mainChart = new QChart();
	mainChart->addSeries(seriesOfLocations);
	mainChart->setTitle("AcessCount for FilmedLocation");
	
	QBarCategoryAxis* axis = new QBarCategoryAxis();
	axis->append(locations);
	mainChart->createDefaultAxes();
	mainChart->setAxisX(axis, seriesOfLocations);

	mainChart->axisX()->setTitleText("Location");
	mainChart->axisY()->setTitleText("Access Count");

	mainChart->legend()->setVisible(true);
	mainChart->legend()->setAlignment(Qt::AlignBottom);

	this->mainChartView = new QChartView(mainChart);
	mainChartView->setRenderHint(QPainter::Antialiasing);

	QPalette pal = mainChartView->palette();
	pal.setColor(QPalette::Window, QRgb(0xf5f5f5));
	pal.setColor(QPalette::WindowText, QRgb(0x404040));

	mainChartView->setPalette(pal);
	

}
