#include "Views.h"
#include <string>
#include <qformlayout.h>


myListView::myListView(MyTableModel* myTableModel, serviceWrapper& service, Driver& driver, QWidget *parent)
	: QWidget(parent), myTableModel{ myTableModel }, service{ service }, driver{ driver }
{
	myTableModel->distance = distance;
	this->setWindowTitle(driver.getName().c_str());
	QVBoxLayout* layout = new QVBoxLayout{ this };
	reports = new QTableView(this);
	layout->addWidget(reports);
	reports->setModel(myTableModel);
	reports->resizeColumnsToContents();
	reports->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	this->resize(400,500);
	reports->setSelectionBehavior(QAbstractItemView::SelectRows);
	reports->setSelectionMode(QAbstractItemView::SingleSelection);

	slider = new QSlider(Qt::Horizontal);
	slider->setTickInterval(1);
	slider->setValue(10);
	slider->setMaximum(20);
	layout->addWidget(slider);
	QFormLayout* labels = new QFormLayout{  };
	scoreLabel = new QLabel();
	statusLabel = new QLabel();
	latitudeLabel = new QLabel();
	longitudeLabel = new QLabel();
	scoreLabel->setText(QString::fromStdString(to_string( driver.getScore())));
	statusLabel->setText(QString::fromStdString( driver.getStatus()));
	latitudeLabel->setText(QString::fromStdString(to_string(driver.getLatitude())));
	longitudeLabel->setText(QString::fromStdString(to_string(driver.getLongitude())));
	labels->addRow("Status", statusLabel);
	labels->addRow("Score", scoreLabel);
	labels->addRow("Latitude", latitudeLabel);
	labels->addRow("Longitude", longitudeLabel);
	layout->addLayout(labels);

	QFormLayout *reportAttributes = new QFormLayout{};
	descriptionLineEdit = new QLineEdit();
	latitudeLineEdit = new QLineEdit();
	longitudeLineEdit = new QLineEdit();

	reportAttributes->addRow("Description", descriptionLineEdit);
	reportAttributes->addRow("Report Latitude", latitudeLineEdit);
	reportAttributes->addRow("Report Longitude", longitudeLineEdit);
	layout->addLayout(reportAttributes);

	addButton = new QPushButton("Add Report");
	QFormLayout* directions = new QFormLayout{  };
	northButton = new QPushButton("North");
	southButton = new QPushButton("South");
	eastButton = new QPushButton("East");
	westButton = new QPushButton("West");
	directions->addWidget(northButton);
	directions->addWidget(southButton);
	directions->addWidget(eastButton );
	directions->addWidget(westButton);
	layout->addWidget(addButton);
	layout->addLayout(directions);

	QObject::connect(this->addButton, &QPushButton::clicked, this, &myListView::AddReport);
	QObject::connect(this->northButton, &QPushButton::clicked, this, &myListView::North);
	QObject::connect(this->southButton, &QPushButton::clicked, this, &myListView::South);
	QObject::connect(this->eastButton, &QPushButton::clicked, this, &myListView::East);
	QObject::connect(this->westButton, &QPushButton::clicked, this, &myListView::West);


	QObject::connect(this->slider, &QSlider::valueChanged, this, &myListView::ChangeDistance);

	this->setLayout(layout);
	
}

myListView::~myListView()
{
}

void myListView::ChangeDistance()
{
	distance = slider->value();
	this->myTableModel->distance = distance;
	this->service.serv.notify();
}


void myListView::AddReport()
{
	string description = descriptionLineEdit->text().toStdString();
	int latitude = latitudeLineEdit->text().toInt();
	int longitude = longitudeLineEdit->text().toInt();
	double distance = sqrt((latitude - driver.getLatitude()) * (latitude - driver.getLatitude()) + (longitude - driver.getLongitude()) * (longitude - driver.getLongitude()));
	if (description == "") {
		QMessageBox::critical(this, "Report description error", "Description can't be empty!");
		return;
	}
	if (distance > 20) {
		QMessageBox::critical(this, "Distance error", "Distance too great!");
		return;
	}
	try {
		Report* report = new Report(description, driver.getName(), latitude, longitude, 0);
		this->service.serv.addElement(report);
	}
	catch (exception re) {
		QMessageBox::critical(this, "Repo error", "Report description already taken!");
		return;
	}
}

void myListView::North()
{
	this->driver.modifyLongitude(1);
	longitudeLabel->setText(QString::fromStdString(to_string(driver.getLongitude())));
	this->service.serv.notify();
}
void myListView::South()
{
	this->driver.modifyLongitude(-1);
	longitudeLabel->setText(QString::fromStdString(to_string(driver.getLongitude())));
	this->service.serv.notify();
}
void myListView::East()
{
	this->driver.modifyLatitude(1);
	latitudeLabel->setText(QString::fromStdString(to_string(driver.getLatitude())));
	this->service.serv.notify();
}
void myListView::West()
{
	this->driver.modifyLatitude(-1);
	latitudeLabel->setText(QString::fromStdString(to_string(driver.getLatitude())));
	this->service.serv.notify();
}