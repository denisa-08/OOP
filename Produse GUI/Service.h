#pragma once
#include "Repo.h"
#include "Validator.h"
#include "Observer.h"
#include <algorithm>

class Service : public Observable {
private:

	Repository& repo;
	Validator& validator;

public:

	Service(Repository& repo, Validator& validator) : repo{ repo }, validator{ validator } {

	}

	void add(const string& id, const string& nume, const string& tip, const string& pret);

	vector<Produs> getAll();

};
