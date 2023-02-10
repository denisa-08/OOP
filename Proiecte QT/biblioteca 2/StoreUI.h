#pragma once

#include "BookSrv.h"
#include <vector>

class BookUI {
private:
    BookStore& ctr;
    /*
    tipareste meniu si citeste comanda
    */
    int readCommand();
    /*
    Tipareste lista de carti
    */
    void printBooks(const std::string& title, const std::vector<Book>& v);
    /*
    citest de la tastatura si adauga pet
    */
    void addBook();
public:
    BookUI(BookStore& ctr) noexcept :ctr{ ctr } {}
    void startUI();
};
