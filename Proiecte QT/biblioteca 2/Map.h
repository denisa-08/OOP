#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Book.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

/*class ReportItem{
private:
    std::unordered_map<string, int> report;

public:
    void constructor_gen(vector<Book> books);

    int getNumber(const string& genre);

};*/
class ReportItem {
private:
    string genre;
    int count;

public:
    ReportItem() = delete;

    ReportItem(string genre, int count): genre { genre }, count { count }{}

    int getCount() {
        return this->count;
    }

};








