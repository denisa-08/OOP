#pragma once
#include <string>
#include "Exception.h"
using namespace std;

class Validator {
public:
	void validateData(const string id, const string nume, const string tip, const string pret) {
		string err = "";
		try {
			int intId = stoi(id);
		}
		catch (...) {
			err += "Id invalid!\n";
		}
		if (nume.size() == 0) err += "Nume invalid!\n";
		if (tip.size() == 0) err += "Tip invalid!\n";
		try {
			double doublePret = stod(pret);
			if (doublePret < 1.0 || doublePret > 100.0) err += "Pret invalid!\n";
		}
		catch (...) {
			err += "Pret invalid!\n";
		}
		if (err.size() > 0) throw Exception(err);
	}
};