#include "Cart.h"

using std::shuffle;

//adaugare in cosul de inchirieri
void Cart::addBookToCart(const Book &b) {
    this->rentedBooks.push_back(b);
}

//stergere carti din cosul de inchirieri
void Cart::emptyCart() {
    this->rentedBooks.clear();
}

//adaugare random de carti in cos
void Cart::addRandomBooks(vector<Book> books, int number) {
    shuffle(books.begin(), books.end(), std::default_random_engine(std::random_device{}()));
    while(rentedBooks.size() < number && !books.empty()) {
        rentedBooks.push_back(books.back());
        books.pop_back();
    }
}

//vector cu taote cartile din cos
const vector<Book>& Cart::getAllCartBooks() {
    return this->rentedBooks;
}

