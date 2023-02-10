#pragma once

#include <string>

using namespace std;

class Produs {
private:
	int id;
	string nume;
	string tip;
	double pret;

public:

	Produs(const int& id, const string& nume, const string& tip, const double pret) : id{ id }, nume{ nume }, tip{ tip }, pret{ pret } {

	}

	int getId() { return id; }
	string getNume() { return nume; }
	string getTip() { return tip; }
	double getPret() { return pret; }

	bool operator==(const Produs& other) {
		return this->id == other.id;
	}

};
