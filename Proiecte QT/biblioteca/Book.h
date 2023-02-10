//
//  Book.hpp
//  Library Project
//
//

#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Book {
private:
    string title;
    string author;
    string genre;
    int year;

public:
    Book() = delete;

    Book(const string title, const string author, const string genre, int year): title{ title }, author{author}, genre{genre}, year{year}{};

    Book(const Book& ot) :title{ ot.title }, author{ ot.author }, genre{ ot.genre }, year{ ot.year }{
        //cout << "Copy constructor called." <<endl;
    }

    Book& operator=(const Book& ot) {
        this->title = ot.title;
        this->author = ot.author;
        this->genre = ot.genre;
        this->year = ot.year;
        return (*this);
    }

    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    int getYear() const;

    void setTitle(string newTitle);
    void setAuthor(string newAuthor);
    void setGenre(string newGenre);
    void setYear(int newYear);

};

void testeDomain();
