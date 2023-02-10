#include "Service.h"

void Service::add(const string& id, const string& nume, const string& tip, const string& pret) {
	validator.validateData(id, nume, tip, pret);
	int intId = stoi(id);
	double doublePret = stod(pret);
	Produs prodNou{ intId, nume, tip, doublePret };
	repo.add(prodNou);
	notify();
}

bool cmp(Produs p1, Produs p2) {
	return p1.getPret() < p2.getPret();
}

vector<Produs> Service::getAll() {
	auto list = repo.getAll();
	sort(list.begin(), list.end(), cmp);
	return list;
}