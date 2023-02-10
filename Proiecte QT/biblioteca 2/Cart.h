#pragma once

#include "Book.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
class Cart {
private:
    vector<Book> rentedBooks;
public:
    Cart()=default;

    /*
     * Adauga o carte in cosul de inchirieri
     * @param b: cartea care se adauga (Book)
     * post: cartea va fi adaugata in cosul de inchirieri
     */
    void addBookToCart(const Book& b);

    /*
     * Elimina toate cartile din cosul de inchirieri
     * post: cosul este gol
     */
    void emptyCart();

    /*
     * Adauga un numar random de carti in cosul de inchirieri
     * @param books: cartile din care se alege
     * @param number: cate carti se adauga
     *
     * post: cartile sunt adaugate in cosul curent
     */
    void addRandomBooks(vector<Book> books, int number);

    /*
     * Returneaza un vector care contine toate cartile din cosul de inchirieri
     */
    const vector<Book>& getAllCartBooks();
};
