#include "bonusLab11.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include "qwindow.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//bonusLab11 w;
	//w.showChart();
	GUI gui;
	gui.show();
 
	return a.exec();
}
