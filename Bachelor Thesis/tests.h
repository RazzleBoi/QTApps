#pragma once
#include "domain.h"
#include "repo.h"
#include "service.h"


class Tests {
private:
	fileRepo<Report> *repo;
public:
	void init();
	void test_repo_add_succesfull() ;
	void test_repo_add_duplicateElem_exception() ;
	void test_service_add_successfull() ;
	void test_service_add_throwException() ;
	
	void allTests() ;
};