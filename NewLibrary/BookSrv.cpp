//
//  BookSrv.cpp
//  Library Project
//
//
//

#include "BookSrv.h"
#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>

void BookStore::addBook(const string& title, const string& author, const string& genre, const int& year) {
    Book b1{title, author, genre, year};
    val.validate(b1);
    repo.store(b1);
}

void BookStore::deleteBook(const string& title, const string& author) {
    Book b1{ title, author, "ok", 1900 };
    val.validate(b1);
    repo.delete_book(title, author);
}

void BookStore::modifyBook(const string& title, const string& author, const string& genre, const int& year, const string& new_title, const string& new_author, const string& new_genre, const int& new_year) {
    Book b1{ title, author, genre, year };
    Book new_b1{ new_title, new_author, new_genre, new_year };
    val.validate(b1);
    val.validate(new_b1);
    repo.update(b1, new_b1);
}

Book BookStore::findBook(const string& title, const string& author){
    Book b1{ title, author, "ok", 1900 };
    val.validate(b1);
    return repo.find(title, author);
}

TemplateVector<Book> BookStore::filter(function<bool(const Book&)> fct) {
    TemplateVector<Book> rez;
    for (int i=0; i<repo.getAllBooks().size(); i++) {
        if (fct(repo.getAllBooks().get(i))) {
            rez.add(repo.getAllBooks().get(i));
        }
    }
    return rez;
}

TemplateVector<Book> BookStore::generalSort(bool(*maiMicF)(const Book&, const Book&)) {
    TemplateVector<Book> v{ repo.getAllBooks() };//fac o copie
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v.get(i), v.get(j))) {
                //interschimbam
                v.exchange(i, j);
            }
        }
    }
    return v;
}

/*
Sorteaza dupa autor+gen
*/
TemplateVector<Book> BookStore::sortByAuthorGenre() {
    return generalSort([](const Book&b1, const Book&b2) {
        if (b1.getAuthor() == b2.getAuthor()) {
            return b1.getGenre() < b2.getGenre();
        }
        return b1.getAuthor() < b2.getAuthor();
    });
}


TemplateVector<Book> BookStore::filterTitle(const string& title){
    return filter([title](const Book& b) {
        return b.getTitle() == title;
    });
}

TemplateVector<Book> BookStore::filterYear(int year){
    return filter([year](const Book& b) {
        return b.getYear() == year;
    });
}

//functie de comparare titluri pentru sortare
bool cmpTitle(Book& b1, Book& b2){
    return b1.getTitle() < b2.getTitle();
}

//functie de comparare ani pentru sortare
bool cmpYear(Book& b1, Book& b2) {
    return b1.getYear() < b2.getYear();
}

/*
Sorteaza dupa titlu
*/
TemplateVector<Book> BookStore::sortByTitle() {
    auto copyAll = repo.getAllBooks();

    return generalSort(reinterpret_cast<bool (*)(const Book &, const Book &)>(cmpTitle));
}

/*
 * Sorteaza dupa anul aparitiei
 */
TemplateVector<Book> BookStore::sortByYear() {
    return generalSort(reinterpret_cast<bool (*)(const Book &, const Book &)>(cmpYear));
}



void testAddService() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei2", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei3", "George Calinescu", "realism", 1938);

    assert(testService.getAllBooks().size() == 3);
    try {
        testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
        assert(false);
    }
    catch (Exception ex) {
        assert(true);
    }

    try {
        testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
        assert(true);
    }
    catch (ValidateException&) {
        assert(false);
    }

    try {
        testService.addBook("", "Ion", "realism", 1989);
        assert(false);
    }
    catch (ValidateException&){
        assert(true);
    }

    try {
        testService.addBook("Ion", "", "realism", 1989);
        assert(false);
    }
    catch (ValidateException&){
        assert(true);
    }

    try {
        testService.addBook("Ion", "Liviu Rebreanu", "", 1989);
        assert(false);
    }
    catch (ValidateException&){
        assert(true);
    }


    try {
        testService.addBook("Ion", "Liviu Rebreanu", "realism", 100);
        assert(false);
    }
    catch (ValidateException&){
        assert(true);
    }
}

void testDeleteService(){
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);

    assert(testService.getAllBooks().size() == 3);

    testService.deleteBook("Ion", "Liviu Rebreanu");
    assert(testService.getAllBooks().size() == 2);

    try {
        testService.deleteBook("Ion", "Liviu Rebreanu");
        assert(false);
    }
    catch (Exception ex) {
        assert(true);
    }

}

void testFiltrari() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);
    testService.addBook("Moara cu noroc2", "Ioan Slavici2", "nuvela psihologica2", 1920);
    testService.addBook("Moara cu noroc3", "Ioan Slavici3", "nuvela psihologica3", 1920);

    assert(testService.filterTitle("Enigma Otiliei").size() == 2);
    assert(testService.filterTitle("Moara cu noroc").size() == 1);
    assert(testService.filterYear(1920).size() == 3);
}

void testSort() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);


    auto first = testService.sortByTitle().get(0);
    assert(first.getTitle() == "Enigma Otiliei");

    auto first_year = testService.sortByYear().get(0);
    assert(first_year.getYear() == 1880);

    testService.addBook("Acolo", "George Calinescu", "clasicism", 1938);
    auto first_author_genre = testService.sortByAuthorGenre().get(0);
    assert(first_author_genre.getAuthor() == "George Calinescu");
    assert(first_author_genre.getGenre() == "clasicism");


}

void testModify(){
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("T1", "A1", "G1", 1938);
    testService.addBook("T2", "A2", "G2", 1988);
    testService.addBook("T3", "A3", "G3", 1838);

    testService.modifyBook("T1", "A1", "G1", 1938, "T4", "A4", "G4", 1800);

    assert(testService.getAllBooks().get(0).getTitle() == "T4");
    assert(testService.getAllBooks().get(0).getAuthor() == "A4");
    assert(testService.getAllBooks().get(0).getGenre() == "G4");
    assert(testService.getAllBooks().get(0).getYear() == 1800);

    try {
        testService.findBook("T1", "A1");
        assert(false);
    }
    catch (Exception ex) {
        assert(true);
    }

    try {
        testService.modifyBook("ok", "ok", "ok", 1900, "ok2", "ok2", "ok2", 1890);
        assert(false);
    }
    catch (Exception ex){
        assert(true);
    }

}

void testFind() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);

    try {
        testService.findBook("Ion", "Liviu Rebreanu");
        assert(true);
    }
    catch (Exception ex) {
        assert(false);
    }

}


void testeService() {
    testAddService();
    testDeleteService();
    testFiltrari();
    testSort();
    testFind();
    testModify();
}
