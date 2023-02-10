//
// Created by Denisa on 26.03.2022.
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
    Book(const string title, const string author, const string genre, int year): title{ title }, author{author}, genre{genre}, year{year}{};
    Book(const Book& ot) :title{ ot.title }, author{ ot.author }, genre{ ot.genre }, year{ ot.year }{
        cout << "Copy constructor called." <<endl;
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