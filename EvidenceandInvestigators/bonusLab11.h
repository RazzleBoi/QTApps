#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include "service.h"
#include "domain.h"
#include <qpushbutton.h>
#include <qlayout.h>
#include <vector>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class bonusLab11 :
	public QWidget
{
private:
	Service service;
	QChartView *mainChartView;
	//graphical

public:
	bonusLab11();
	void generateChart();
	void showChart() { mainChartView->show(); };
};
