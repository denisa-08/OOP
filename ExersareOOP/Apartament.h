//
// Created by Denisa on 18.05.2022.
//

#pragma once
#include <string>
#include <iostream>

using std::string;

class Apartament {
private:
    float suprafata;
    string strada;
    float pret;
public:
    Apartament() = delete;

    Apartament(float suprafata, const string strada, float pret): suprafata {suprafata}, strada {strada}, pret {pret} {};

    Apartament(const Apartament& ap): suprafata {ap.suprafata}, strada {ap.strada}, pret {ap.pret} {
        //cout<<"Copy constructor called!";
    }

    //suprascriere operator =
    Apartament& operator=(const Apartament& ot) {
        this->suprafata = ot.suprafata;
        this->strada = ot.strada;
        this->pret = ot.pret;
        return (*this);
    }

    float getSuprafata() const;
    string getStrada() const;
    float getPret() const;

};

void testeDomain();
