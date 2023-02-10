//
//  Book.cpp
//  Library Project
//
//
//

#include "Book.h"
#include <cassert>

Book::Book(const string& title, const string& author, const string& genre, const int& year) {
    this->title = title;
    this->author = author;
    this->genre = genre;
    this->year = year;
}
string Book::getTitle() const {
    return this->title;
}
string Book::getAuthor() const {
    return this->author;
}
string Book::getGenre() const {
    return this->genre;
}
int Book::getYear() const {
    return this->year;
}

void Book::setTitle(const string& newTitle) {
    this->title = newTitle;
}
void Book::setAuthor(const string& newAuthor) {
    this->author = newAuthor;
}
void Book::setGenre(const string& newGenre) {
    this->genre = newGenre;
}
void Book::setYear(int newYear) noexcept{
    this->year = newYear;
}

bool Book::operator==(const Book& other) {
    return (this->title == other.getTitle() && this->author == other.getAuthor());
}


void testGetSet() {
    Book b1{ "Enigma Otiliei", "George Calinescu", "realism", 1938 };
    assert(b1.getTitle() == "Enigma Otiliei");
    assert(b1.getAuthor() == "George Calinescu");
    assert(b1.getGenre() == "realism");
    assert(b1.getYear() == 1938);

    Book b2{ "Ion", "Liviu Rebreanu", "realism", 1920 };
    assert(b2.getTitle() == "Ion");
    assert(b2.getAuthor() == "Liviu Rebreanu");
    assert(b2.getGenre() == "realism");
    assert(b2.getYear() == 1920);

    b2.setTitle("Moara cu noroc");
    b2.setAuthor("Ioan Slavici");
    b2.setGenre("nuvela psihologica");
    b2.setYear(1881);

    assert(b2.getTitle() == "Moara cu noroc");
    assert(b2.getAuthor() == "Ioan Slavici");
    assert(b2.getGenre() == "nuvela psihologica");
    assert(b2.getYear() == 1881);

}

void test_operator() {
    Book b1{ "Enigma Otiliei", "George Calinescu", "realism", 1938 };
    Book b2{ "Enigma Otiliei", "George Calinescu", "realism2", 1900 };
    assert(b1 == b2);
}

void testeDomain() {
    testGetSet();
    test_operator();
}
