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

class Book{
private:
    string title;
    string author;
    string genre;
    int year;

public:

    Book(const string& title, const string& author, const string& genre, const int& year);

    Book() = default;

    Book(const Book& ot) : title{ ot.getTitle() }, author{ ot.getAuthor() }, genre{ ot.getGenre() }, year{ ot.getYear() } {
        //cout<<"Copy constructor called!";
    }

    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    int getYear() const;

    void setTitle(const string& newTitle);
    void setAuthor(const string& newAuthor);
    void setGenre(const string& newGenre);
    void setYear(int newYear) noexcept;

    //bool operator==(const Book& b1);

};

void testeDomain();
