//
// Created by Denisa on 22.06.2022.
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Produs.h"

using namespace std;

/*
 * Clasa de exceptii
 */
class RepoException {
    string error;
public:
    RepoException(string error): error { error } {};
    string getError() {
        return this->getError();
    }
};

class RepoFile {
private:
    void loadFromFile();
    vector<Produs> produse;

public:
    RepoFile() = default;
    void adauga(const Produs& p);
    const vector<Produs>& getAll();
};