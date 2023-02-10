#pragma once
#include <vector>
#include <algorithm>
using namespace std;
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;

public:

	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void deleteObserver(Observer* obs) {
		observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
	}

	void notify() {
		for (auto& p : observers) p->update();
	}

};