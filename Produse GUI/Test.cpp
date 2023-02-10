#include "Test.h"
#include <assert.h>
#include <fstream>
#include "Service.h"


void testDomain() {
	Produs produs1{ 1, "Lapte", "Lactat", 3.99 };
	assert(produs1.getId() == 1);
	assert(produs1.getNume() == "Lapte");
	Produs produs2{ 1, "Oua", "AA", 10 };
	assert(produs1 == produs2);
}

void writeToRepo() {
	ofstream fout("test.txt");
	fout << "1 Lapte Lactat 3.99\n";
	fout << "2 Oua Mancare 1.25\n";
	fout << "3 Frigider Utilitar 100.99";
}

void testRepo() {
	Repository repo{ "test.txt" };
	assert(repo.getAll().size() == 3);
	Produs prod4{ 4, "Tractor", "Masina", 90 };
	repo.add(prod4);
	assert(repo.getAll().size() == 4);
	try {
		repo.add(prod4);
		assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "Deja exista!");
	}
	writeToRepo();
}

void testValidator() {
	Validator v;
	v.validateData("1", "Lapte", "Lactat", "3.9");
	try {
		v.validateData("a", "", "", "1000");
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "Id invalid!\nNume invalid!\nTip invalid!\nPret invalid!\n");
	}
}

void testService() {
	Repository repo{ "test.txt" };
	Validator valid;
	Service service{ repo, valid };
	assert(service.getAll().size() == 3);
	auto l = service.getAll();
	assert(l.at(0).getNume() == "Oua");
	assert(l.at(2).getNume() == "Frigider");
	service.add("4", "Laptop", "Gaming", "99.9");
	assert(service.getAll().size() == 4);
	writeToRepo();
}

void testAll() {
	testDomain();
	testRepo();
	testValidator();
	testService();
}