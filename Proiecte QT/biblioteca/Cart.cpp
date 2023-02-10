#include "Cart.h"

using std::shuffle;

//adaugare in cosul de inchirieri
void Cart::addBookToCart(const Book &b) {
    this->rentedBooks.push_back(b);
    notify();
}

//stergere carti din cosul de inchirieri
void Cart::emptyCart() {
    this->rentedBooks.clear();
    notify();
}

//adaugare random de carti in cos
void Cart::addRandomBooks(vector<Book> books, int number) {
    shuffle(books.begin(), books.end(), std::default_random_engine(std::random_device{}()));
    int lg = rentedBooks.size();
    while(rentedBooks.size() < (number + lg) && !books.empty()) {
        rentedBooks.push_back(books.back());
        books.pop_back();
    }
    notify();
}

//vector cu toate cartile din cos
const vector<Book>& Cart::getAllCartBooks() {
    return this->rentedBooks;
}

