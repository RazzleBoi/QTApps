
#include <QtWidgets/QApplication>
#include "repo.h"
#include "domain.h"
#include "Views.h"
#include "Models.h"
#include <qdebug.h>
#include "tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Tests test;
    test.allTests();

    fileRepo<Report> Repo1;
    Repo1.setStoringfile("Reports.txt");
    fileRepo<Driver> Repo2;
    Repo2.setStoringfile("Drivers.txt");

    serviceWrapper service(Repo1);
    

    
    for (auto driver : Repo2.getList()) {
        int* ten = new int();
        *ten = 10;
        MyTableModel* reportsTable = new MyTableModel(service, *driver, *ten);
        service.serv.addObserver(reportsTable);
        myListView* currentDriver = new myListView(reportsTable, service, *driver);
        currentDriver->show();
        
    }
    return a.exec();
}
