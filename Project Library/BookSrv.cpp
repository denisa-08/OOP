//
//  BookSrv.cpp
//  Library Project
//
//
//

#include "BookSrv.h"
#include <cassert>
#include <fstream>
#include <functional>
#include <algorithm>
#include <utility>
#include <unordered_map>

using std::ofstream;


void BookStore::addBook(string title, string author, string genre, int year) {
    Book b{title, author, genre, year};
    val.validate(b);
    repo.store(b);
    undoActions.push_back(new UndoAdd{repo, b});
}

void BookStore::undo() {
    if(undoActions.empty()) {
        throw BookRepoException{"Nu mai exista operatii!"};
    }
    ActionUndo* act = undoActions.back();
    act->doUndo();
    undoActions.pop_back();
    delete act;
}

void BookStore::deleteBook(string title, string author, string genre, int year) {
    Book b1{ title, author, genre, year };
    val.validate(b1);
    repo.delete_book(b1);
    undoActions.push_back(new UndoDelete{repo, b1});
}

void BookStore::modifyBook(string title, string author, string genre, int year, string new_title, string new_author, string new_genre, int new_year) {
    Book b1{ title, author, genre, year };
    Book new_b1{ new_title, new_author, new_genre, new_year };
    val.validate(b1);
    val.validate(new_b1);
    repo.update(b1, new_b1);
    undoActions.push_back(new UndoUpdate{repo, b1, new_b1});
}

bool BookStore::findBook(string title, string author, string genre, int year) {
    Book b1{ title, author, genre, year };
    val.validate(b1);
    return repo.exist(b1);
}

/*vector<Book> BookStore::filter(function<bool(const Book&)> fct) {
    vector<Book> rez;
    for (const auto& book : repo.getAllBooks()) {
        if (fct(book)) {
            rez.push_back(book);
        }
    }
    return rez;
}*/

vector<Book> BookStore::generalSort(bool(*maiMicF)(const Book&, const Book&)) {
    vector<Book> v{ repo.getAllBooks() };//fac o copie
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {
                //interschimbam
                Book aux = v[i];
                v[i] = v[j];
                v[j] =  aux;
            }
        }
    }
    return v;
}

vector<Book> BookStore::filterTitle(string title){
    /*return filter([title](const Book& b) {
        return b.getTitle() == title;
    });*/
    const vector<Book>& allBooks = getAllBooks();
    vector<Book> filteredBooks;
    std::copy_if(allBooks.begin(), allBooks.end(), back_inserter(filteredBooks), [title](const Book& b) {
        return b.getTitle() == title;
    });
    return filteredBooks;
}

vector<Book> BookStore::filterYear(int year){
    /*return filter([year](const Book& b) {
        return b.getYear() == year;
    });*/
    const vector<Book>& allBooks = getAllBooks();
    vector<Book> filteredBooks;
    std::copy_if(allBooks.begin(), allBooks.end(), back_inserter(filteredBooks), [year](const Book& b) {
        return b.getYear() == year;
    });
    return filteredBooks;
}

//functie de comparare titluri pentru sortare
bool cmpTitle(Book& b1, Book& b2){
    return b1.getTitle() < b2.getTitle();
}

//functie de comparare ani pentru sortare
bool cmpYear(Book& b1, Book &b2){
    return b1.getYear() < b2.getYear();
}

/*
Sorteaza dupa titlu
*/
vector<Book> BookStore::sortByTitle() {
    auto copyAll = repo.getAllBooks();
    std::sort(copyAll.begin(), copyAll.end(), cmpTitle);
    return copyAll;
    //return generalSort(cmpType);
}

/*
 * Sorteaza dupa anul aparitiei
 */
vector<Book> BookStore::sortByYear() {
    auto copyAll = repo.getAllBooks();
    std::sort(copyAll.begin(), copyAll.end(), cmpYear);
    return copyAll;
}

/*
Sorteaza dupa autor+gen
*/
vector<Book> BookStore::sortByAuthorGenre() {
    return generalSort([](const Book&b1, const Book&b2) {
        if (b1.getAuthor() == b2.getAuthor()) {
            return b1.getGenre() < b2.getGenre();
        }
        return b1.getAuthor() < b2.getAuthor();
    });
}

//adaugare in cos
void BookStore::addToCart(string title, string author) {
    const auto& book = repo.find(std::move(title), std::move(author));
    currentCart.addBookToCart(book);
}

//adaugare carti random in cos
int BookStore::addRandomToCart(int number) {
    currentCart.addRandomBooks(this->getAllBooks(), number);
    return currentCart.getAllCartBooks().size();
}

//golire cos
void BookStore::emptyCart() {
    currentCart.emptyCart();
}

//Creare raport gen
/*int BookStore::createReportGenre(const string& genre) {
    vector<string> genres = {"realism", "fantezie", "psihologica"};
    for(auto i=repo.getAllBooks().begin(); i<=repo.getAllBooks().end(); i++) {
        ReportItem rep { (*i).getGenre(), 10 };
    }
}*/
std::unordered_map<string,int> BookStore::reportGenre(string genre) {
    std::unordered_map<string, int> set;
    int count = 0;
    for(auto i=repo.getAllBooks().begin(); i!=repo.getAllBooks().end(); i++)
    {
        if((*i).getGenre() == genre)
            count++;
    }
    ReportItem r {genre, count};
    set[genre] = r.getCount();
    return set;
}



//vector cu toate cartile din cos
const vector<Book>& BookStore::getCartBooks() {
    return currentCart.getAllCartBooks();
}


void BookStore::exportFile(string file) {
    ofstream out(file);
    if (!out.is_open()) {
        throw BookRepoException("Fisierul nu se poate deschide!\n");
    }
    out << "<!DOCTYPE html>";
    out << "<head><title> COS DE INCHIRIERI CARTI </title></head>";
    out << "<body>Cos inchirieri carti";

    for(auto& b : getCartBooks()) {
        out << "<p>";
        out << "Titlul cartii este " << b.getTitle() << " | ";

        out << "Autorul cartii este: " << b.getAuthor() << " | ";

        out << "Genul cartii este: " << b.getGenre() << " | ";

        out << "Anul aparitiei este: " << b.getYear() << endl;
        out << "</p>";
    }
    out << "</body></html>";
    out.close();
}


void testCart() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("T1", "A1", "G1", 1900);
    testService.addBook("T2", "A2", "G2", 1800);
    testService.addBook("T3", "A3", "G3", 1978);
    testService.addBook("T4", "A4", "G4", 1989);
    testService.addBook("T5", "A5", "G5", 1901);

    testService.addRandomToCart(4);
    assert(testService.getCartBooks().size() == 4);
    testService.emptyCart();
    assert(testService.getCartBooks().size() == 0);

    testService.addRandomToCart(20);
    assert(testService.getCartBooks().size() == 5);

    testService.emptyCart();
    testService.addToCart("T4", "A4");
    assert(testService.getCartBooks().size() == 1);

    try {
        testService.addToCart("T", "A");
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }
    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();
}


void testAddService() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938 );
    testService.addBook("Enigma Otiliei2", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei3", "George Calinescu", "realism", 1938);

    assert(testService.getAllBooks().size() == 3);
    try {
        testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
        assert(false);
    }
    catch (BookRepoException&) {
        assert(true);
    }

    try {
        testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
        assert(true);
    }
    catch (ValidateException&) {
        assert(false);
    }

    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();

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

    testService.deleteBook("Ion", "Liviu Rebreanu", "realism", 1920);
    assert(testService.getAllBooks().size() == 2);

    try {
        testService.deleteBook("Ion", "Liviu Rebreanu", "realism", 1920);
        assert(false);
    }
    catch (BookRepoException&) {
        assert(true);
    }

    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();

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

    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();
}

void testSort() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);


    auto first = testService.sortByTitle()[0];
    assert(first.getTitle() == "Enigma Otiliei");

    auto first_year = testService.sortByYear()[0];
    assert(first_year.getYear() == 1880);

    testService.addBook("Acolo", "George Calinescu", "clasicism", 1938);
    auto first_author_genre = testService.sortByAuthorGenre()[0];
    assert(first_author_genre.getAuthor() == "George Calinescu");
    assert(first_author_genre.getGenre() == "clasicism");

    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();


}

void testModify(){
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("T1", "A1", "G1", 1938);
    testService.addBook("T2", "A2", "G2", 1988);
    testService.addBook("T3", "A3", "G3", 1838);

    testService.modifyBook("T1", "A1", "G1", 1938, "T4", "A4", "G4", 1800);

    assert(testService.getAllBooks()[0].getTitle() == "T4");
    assert(testService.getAllBooks()[0].getAuthor() == "A4");
    assert(testService.getAllBooks()[0].getGenre() == "G4");
    assert(testService.getAllBooks()[0].getYear() == 1800);

    assert(testService.findBook("T1", "A1", "G1", 1938) == false);

    try {
        testService.modifyBook("ok", "ok", "ok", 1900, "ok2", "ok2", "ok2", 1890);
        assert(false);
    }
    catch (BookRepoException&){
        assert(true);
    }
    testService.undo();
    testService.undo();
    testService.undo();
    testService.undo();

}

void testFind() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    testService.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);

    assert(testService.findBook("Ion", "Liviu Rebreanu", "realism", 1920) == true);

    testService.undo();
    testService.undo();
    testService.undo();

}

void testUndo() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{ testRepo, testVal };

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Ion", "Liviu Rebreanu", "realism", 1920);

    assert(testService.getAllBooks().size() == 2);

    testService.undo();
    assert(testService.getAllBooks().size() == 1);
    assert(testService.getAllBooks().at(0).getTitle() == "Enigma Otiliei");

    testService.undo();

    try {
        testService.undo();
        assert(false);
    }
    catch (BookRepoException) {
        assert(true);
    }
}

void testReport() {
    BookRepo testRepo;
    BookValidator testVal;
    BookStore testService{testRepo, testVal};

    testService.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei2", "George Calinescu", "realism", 1938);
    testService.addBook("Enigma Otiliei3", "George Calinescu", "realism", 1938);

    std::unordered_map<string, int> set;
    set = testService.reportGenre("realism");
    assert(set["realism"] == 3);

    testService.undo();
    testService.undo();
    testService.undo();
}

void testeService() {
    testAddService();
    testDeleteService();
    testFiltrari();
    testSort();
    testFind();
    testModify();
    testCart();
    testUndo();
    testReport();
}
