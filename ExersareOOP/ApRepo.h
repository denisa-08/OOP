//
// Created by Denisa on 18.05.2022.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Apartament.h"

using std::string;
using std::vector;

//Clasa de exceptii
class RepoException {
    string error;
public:
    RepoException(string error): error {error} {};
    string getError() {
        return this->error;
    }
};


class RepoFile {
private:
    string file;
    void loadFromFile();
    void writeToFile();
    vector<Apartament> allAp;

public:
    RepoFile(string file): file {file} {
        loadFromFile();
    }
    void adauga(const Apartament& ap);
    void sterge(const Apartament& ap);
    const Apartament& find(string strada);
    const vector<Apartament>& getAll();
};

void testeRepo();

