#include "tests.h"

void Tests::init()
{
	this->repo = new fileRepo<Report>{};
	repo->setStoringfile("testFile.txt");
}

void Tests::test_repo_add_succesfull()
{
	Report* report = new Report("a", "baby", 12, 23, 0);
	Report* report2 = new Report("a", "advanced", 12, 23,0);
	repo->addElement(report);
	assert(repo->size() == 1);
	repo->deleteElement(report2);
}

void Tests::test_repo_add_duplicateElem_exception()
{
	Report* report = new Report("a", "John", 12, 23, 0);
	Report* report2 = new Report("a", "Bon", 12, 23, 1);
	Report* report3 = new Report("a", "Badonk", 12, 23,1);
	repo->addElement(report);
	try {
		repo->addElement(report2);
		assert(false);
	}
	catch (exception re) {
		assert(true);
		repo->deleteElement(report3);
	}
}

void Tests::test_service_add_successfull()
{
	serviceWrapper service{ *repo };
	Report* report = new Report("a", "Bdscb", 12, 23, 0);
	Report* report2 = new Report("a", "Bsdcdsb", 12, 23, 0);
	service.serv.addElement(report);
	vector<Report*> list = service.serv.getElements();
	assert(list[0]->getDescription() == "a");
	service.serv.deleteElement(report2);
}

void Tests::test_service_add_throwException()
{
	serviceWrapper service{ *repo };
	Report* report = new Report("a", "Bbzcvb", 12, 23, 0);
	Report* report2 = new Report("a", "sdadBb", 12, 23,0);
	Report* report3 = new Report("a", "AVEE", 12, 23, 0);
	service.serv.addElement(report);
	try {
		service.serv.addElement(report2);
		assert(false);
	}
	catch (exception re) {
		assert(true);
		service.serv.deleteElement(report3);
	}
}

void Tests::allTests()
{
	init();
	test_repo_add_succesfull();
	test_repo_add_duplicateElem_exception();
	test_service_add_successfull();
	test_service_add_throwException();
}
