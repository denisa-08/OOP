#include "Repo.h"
#include <fstream>


void Repository::readFromFile() {
	ifstream fin(fileName);
	produse.clear();
	int id;
	string nume, tip;
	double pret;
	while (fin >> id >> nume >> tip >> pret) {
		Produs pNou{ id, nume, tip, pret };
		produse.push_back(pNou);
	}
	fin.close();
}

void Repository::writeToFile() {
	ofstream fout(fileName);
	for (auto& prod : produse) {
		fout << prod.getId() << " " << prod.getNume() << " "
			<< prod.getTip() << " " << prod.getPret() << endl;
	}
}

void Repository::add(const Produs& pNou) {
	readFromFile();
	for (auto& prod : produse) {
		if (prod == pNou) throw Exception("Deja exista!");
	}
	produse.push_back(pNou);
	writeToFile();
}

vector<Produs> Repository::getAll() {
	readFromFile();
	return produse;
}