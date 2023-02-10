#include "BookRepo.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using std::ostream;


void BookRepo::store(const Book& b){
    if(exist(b)) {
        throw BookRepoException("Exista deja cartea cu titlul:" + b.getTitle() + " si autorul:" + b.getAuthor());
    }
    this->allBooks.push_back(b);
}


//stergere
void BookRepo::delete_book(const Book& b) {
    if(exist(b)){
        /*for(auto i = allBooks.begin(); i<= allBooks.end();i++){
            if((*i).getTitle() == b.getTitle() && (*i).getAuthor() == b.getAuthor()){
                allBooks.erase(i);
            }
        }*/
        auto f = std::find_if(this->allBooks.begin(), this->allBooks.end(), [=](const Book& b1) {
            return b.getTitle() == b1.getTitle() && b.getAuthor() == b1.getAuthor();
        });
        allBooks.erase(f);
    }
    else{
        throw BookRepoException("Cartea cu titlul: " + b.getTitle() + " si cu autorul: " + b.getAuthor() + " nu exista.");
    }
}

//update
void BookRepo::update(const Book& b, const Book& new_b) {
    if(exist(b)) {
        for(auto i = allBooks.begin(); i!= allBooks.end();i++){
            if((*i).getTitle() == b.getTitle() && (*i).getAuthor() == b.getAuthor())
            {
                *i = new_b;
            }
        }
        /*vector<Book>::iterator f = std::find_if(this->allBooks.begin(), this->allBooks.end(), [=](const Book &b) {
            return b.getTitle() == new_b.getTitle() && b.getAuthor() == new_b.getAuthor();
        });
        *f = new_b;*/
    }
    else{
        throw BookRepoException("Cartea cu titlul: " + b.getTitle() + "si cu autorul: " + b.getAuthor() + " nu exista.");
    }
}


//Verifica daca o carte exista in lista de carti
bool BookRepo::exist(const Book& b) {
    try {
        find(b.getTitle(), b.getAuthor());
        return true;
    }
    catch (BookRepoException) {
        return false;
    }
}

/*
 Cauta o carte dupa titlu si autor
 Arunca exceptie daca nu exista
 */
const Book& BookRepo::find(string title, string author) {

    /*for(const auto& b : this->allBooks){
        if(b.getTitle() == title && b.getAuthor() == author)
            return b;
    }*/
    vector<Book>::iterator f = std::find_if(this->allBooks.begin(), this->allBooks.end(), [=](const Book& b) {
        return b.getTitle() == title && b.getAuthor() == author;
    });

    if(f != this->allBooks.end())
        return (*f);
    else
    //daca nu exista arunc exceptie
        throw BookRepoException("Nu exista carte cu titlul: " + title + " si cu autorul: " + author);
}

/*
 returneaza toate cartile salvate
 */
const vector<Book>& BookRepo::getAllBooks() {
    return this->allBooks;
}


void testAdauga() {
    BookRepo rep;
    rep.store(Book{ "Enigma Otiliei", "George Calinescu", "realism", 1938 });
    assert(rep.getAllBooks().size() == 1);
    assert(rep.find("Enigma Otiliei", "George Calinescu").getYear() == 1938);

    rep.store(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });
    assert(rep.getAllBooks().size() == 2);

    //nu pot adauga 2 cu acelasi titlu si acelasi autor
    try {
        rep.store(Book{ "Enigma Otiliei", "George Calinescu", "romantism", 1898 });
        assert(false);
    }
    catch (const BookRepoException&) {
        assert(true);
    }

    //cauta inexistent
    try{
        rep.find("Ana", "Liviu Rebreanu");
        assert(false);
    }
    catch (BookRepoException& e){
        assert(e.getErrorMessage() == "Nu exista carte cu titlul: Ana si cu autorul: Liviu Rebreanu");
    }
}

void testCauta(){
    BookRepo rep;
    rep.store(Book{ "Enigma Otiliei", "George Calinescu", "realism", 1938 });
    rep.store(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });

    auto b = rep.find("Enigma Otiliei", "George Calinescu");
    assert(b.getTitle() == "Enigma Otiliei");
    assert(b.getAuthor() == "George Calinescu");

    //arunca exceptie daca nu gaseste
    try {
        rep.find("Enigma Otiliei", "Liviu Rebreanu");
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }
}

void testSterge(){
    BookRepo rep;
    rep.store(Book{ "Enigma Otiliei", "George Calinescu", "realism", 1938 });
    rep.store(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });
    rep.store(Book{ "Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880});

    assert(rep.getAllBooks().size() == 3);

    rep.delete_book(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });
    assert(rep.getAllBooks().size() == 2);

    try {
        rep.delete_book(Book{ "aa", "bb", "cc", 1880});
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }

    assert(rep.getAllBooks().size() == 2);
}

void testUpdate() {
    BookRepo rep;
    rep.store(Book{ "Enigma Otiliei", "George Calinescu", "realism", 1938 });
    rep.store(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });
    rep.store(Book{ "Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880});

    rep.update(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 }, Book{ "Hello", "Pop George", "romantism", 1978 });

    try {
        rep.find("Ion", "Liviu Rebreanu");
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }

    try {
        rep.update(Book{ "OK", "OK2", "OK3", 1900 }, Book{ "aa", "bb", "cc", 1800});
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }

}

void testeRepo(){
    testAdauga();
    testCauta();
    testSterge();
    testUpdate();
}
