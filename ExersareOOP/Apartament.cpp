//
// Created by Denisa on 18.05.2022.
//

#include "Apartament.h"
#include <assert.h>

float Apartament::getSuprafata() const {
    return this->suprafata;
}

string Apartament::getStrada() const {
    return this->strada;
}

float Apartament::getPret() const {
    return this->pret;
}

void testeDomain() {
    Apartament a1{123, "feasfs", 145};
    assert(a1.getSuprafata() == 123);
    assert(a1.getStrada() == "feasfs");
    assert(a1.getPret() ==145);
}
