//
//  BookRepo.hpp
//  Library Project
//
//
//

#pragma once
#include "Book.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using std::vector;

/*
 * Clasa de exceptii specifice pentru Repository
 */
class BookRepoException {
    string errormsg;
public:
    BookRepoException(string errormsg) :errormsg{ errormsg } {};
    string getErrorMessage() {
        return this->errormsg;
    }
};

/*
 * Clasa pentru Repository
 */
class BookRepo {
private:
    vector<Book> allBooks;

public:
    BookRepo() = default;
    BookRepo(const BookRepo& ot) = delete;

    /*
 * metoda privata care verifica daca exista deja cartea b in repository
 */
    bool exist(const Book& b);


    /*
     * Adauga o carte in lista
     * @param b: cartea care se adauga (Book)
     * @return -
     * post: melodia va fi adaugata in lista
     * @throws: BookRepoException daca o carte cu acelasi titlu si acelasi autor exista deja
     */
    void store(const Book& b);

    /*
     Sterge o carte din lista
     @param b: cartea care se sterge (Book)
     @return: -
     post:cartea va fi stearsa din lista
     @throws: BookRepoException daca cartea nu a fost gasita in lista de carti
     */
    void delete_book(const Book& b);

    /*
     Modifica o carte din lista cu noile date
     @param b: cartea care se modifica (Book)
     @param new_b: cartea cu care se inlocuieste cartea b din lista
     post: cartea se va modifica cu datele date
     @throws: BookRepoException daca cartea nu a fost gasita in lista de carti
     */
    void update(const Book& b, const Book& new_b);

    /*
    Cauta
    arunca exceptie daca nu exista carte
    */
    const Book& find(string title, string author);


    /*
     * Returneaza o lista cu toate cartile
     * @return: lista cu cartile (vector of Book objects)
     */
    const vector<Book>& getAllBooks();


};

void testeRepo();
