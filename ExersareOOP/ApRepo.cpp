//
// Created by Denisa on 18.05.2022.
//

#include "ApRepo.h"
#include <assert.h>
#include <fstream>

using namespace std;

void RepoFile::loadFromFile() {
    ifstream fin(file);
    if(!fin.is_open())
        throw RepoException("Problem with file");
    while(!fin.eof()){
        float suprafata;
        fin >> suprafata;
        string strada;
        fin >> strada;
        float pret;
        fin >> pret;

        Apartament a{suprafata, strada.c_str(), pret};
        adauga(a);
    }
    fin.close();
}

void RepoFile::adauga(const Apartament &ap) {
    allAp.push_back(ap);
}


const Apartament& RepoFile::find(string strada) {
    for(const auto& a: this->allAp) {
        if(a.getStrada() == strada)
            return a;
    }
}

const vector<Apartament>& RepoFile::getAll() {
    return this->allAp;
}

void testeRepo(){
    std::ofstream ofs;
    ofs.open("tests.txt", std::ofstream::out | std::ofstream::trunc);
    ofs << "123 da 78\n";
    ofs << "2345 nu 90";
    ofs.close();
    RepoFile repf {"tests.txt"};
    auto a = repf.find("da");
    assert(a.getPret() == 78);
    assert(a.getSuprafata() == 123);

    assert(repf.getAll().size() == 2);
}

