//
//  BookRepo.cpp
//  Library Project
//
//
//

#include "BookRepo.h"
#include "DynamicArray.h"
#include "Errors.h"
#include <cassert>
#include <iostream>
#include <algorithm>

//adaugare
void BookRepo::store(const Book& b){
    IteratorVector<Book> i = allBooks.begin();
    while(i.valid()) {
        if(i.element().getTitle() == b.getTitle() && i.element().getAuthor() == b.getAuthor()) {
            throw Exception("Exista deja aceasta carte!\n");
        }
        i.next();
    }
    allBooks.add(b);
}


//stergere
void BookRepo::delete_book(const string& title, const string& author) {
    int i = 0;
    while(i < allBooks.size() && (allBooks.get(i).getTitle() != title || allBooks.get(i).getAuthor() != author)) {
        i++;
    }
    if(i < allBooks.size())
        allBooks.erase(i);
    else
        throw Exception("Cartea nu exista!\n");
}

//update
void BookRepo::update(const Book& b, const Book& new_b) {
    int poz = -1;
    for(int i=0; i<allBooks.size(); i++) {
        if (allBooks.get(i).getTitle() == b.getTitle() && allBooks.get(i).getAuthor() == b.getAuthor() &&
            allBooks.get(i).getGenre() == b.getGenre() && allBooks.get(i).getYear() == b.getYear()) {
            poz = i;
        }
    }

    if(poz != -1)
        allBooks.set(poz, new_b);
    else{
        throw Exception("Cartea nu a fost gasita!");
    }
}

/*
 Cauta o carte dupa titlu si autor
 Arunca exceptie daca nu exista
 */
Book BookRepo::find(const string& title, const string& author){
    int poz = -1;
    for(int i=0; i<allBooks.size(); i++){
        if(allBooks.get(i).getTitle() == title && allBooks.get(i).getAuthor() == author)
            poz = i;
    }
    if(poz != -1)
        return allBooks.get(poz);
    else
        //daca nu exista arunc exceptie
        throw Exception("Cartea nu a fost gasita!\n");
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
    catch (Exception ex) {
        assert(true);
    }

    //cauta inexistent
    try{
        rep.find("Ana", "Liviu Rebreanu");
        assert(false);
    }
    catch (Exception ex){
        assert(ex.getMessage() == "Cartea nu a fost gasita!\n");
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
    catch (Exception ex){
        assert(true);
    }
}

void testSterge(){
    BookRepo rep;
    rep.store(Book{ "Enigma Otiliei", "George Calinescu", "realism", 1938 });
    rep.store(Book{ "Ion", "Liviu Rebreanu", "realism", 1920 });
    rep.store(Book{ "Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880});

    assert(rep.getAllBooks().size() == 3);

    rep.delete_book("Ion", "Liviu Rebreanu");
    assert(rep.getAllBooks().size() == 2);

    try {
        rep.delete_book("aa", "bb");
        assert(false);
    }
    catch (Exception ex){
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
    catch (Exception ex){
        assert(true);
    }

    try {
        rep.update(Book{ "OK", "OK2", "OK3", 1900 }, Book{ "aa", "bb", "cc", 1800});
        assert(false);
    }
    catch (Exception ex){
        assert(true);
    }

}

void testeRepo(){
    testAdauga();
    testCauta();
    testSterge();
    testUpdate();
}
