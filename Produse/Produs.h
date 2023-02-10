//
// Created by Denisa on 22.06.2022.
//

#pragma once
#include <string>
#include <iostream>

using namespace std;

class Produs {
private:
    int id;
    string nume;
    string tip;
    double pret;
public:
    Produs() = delete;

    Produs(int id, const string nume, const string tip, double pret): id{ id }, nume{ nume }, tip{ tip }, pret { pret }{};

    int getId() const{
        return this->id;
    }

    string getNume() const {
        return this->nume;
    }

    string getTip() const {
        return this->tip;
    }

    double getPret() const {
        return this->pret;
    }
};
