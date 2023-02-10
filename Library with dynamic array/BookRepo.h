//
//  BookRepo.hpp
//  Library Project
//
//
//

#pragma once
#include "Book.h"
#include "DynamicArray.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
/*
 * Clasa de exceptii specifice pentru Repository

class BookRepoException {
    string errormsg;
public:
    BookRepoException(string errormsg) :errormsg{ errormsg } {};
    string getErrorMessage() {
        return this->errormsg;
    }
};*/

/*
 * Clasa pentru Repository
 */
class BookRepo {
private:
    TemplateVector<Book> allBooks;

public:
    //BookRepo() = default;
    //BookRepo(const BookRepo& ot) = delete;

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
    void delete_book(const string& title, const string& author);

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
    Book find(const string& title, const string& author);


    /*
     * Returneaza o lista cu toate cartile
     * @return: lista cu cartile (vector of Book objects)
     */
    TemplateVector<Book> getAllBooks() {
        return allBooks;
    }

    int length() {
        return int(allBooks.size());
    }


};

void testeRepo();
