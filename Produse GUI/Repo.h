#pragma once
#include "Produs.h"
#include "Exception.h"
#include <vector>

class Repository {
private:
	string fileName;
	vector<Produs> produse;

	void readFromFile();

	void writeToFile();

public:
	Repository(string fileName) : fileName{ fileName } {
		readFromFile();
	}

	void add(const Produs& produsNou);

	vector<Produs> getAll();
};