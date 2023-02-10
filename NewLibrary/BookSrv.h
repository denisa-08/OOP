//
//  BookSrv.hpp
//  Library Project
//
//  Created by Denisa on 30.03.2022.
//

#pragma once
#include "BookRepo.h"
#include "Book.h"
#include "Validator.h"
#include <string>

#include <functional>

using std::vector;
using std::function;


class BookStore {
private:
    BookRepo repo;
    BookValidator val;

    /*
    Functie generala de filtrare
    fct - poate fi o functie
    fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
    returneaza doar cartile care trec de filtru (fct(book)==true)
    */
    TemplateVector<Book> filter(function<bool(const Book&)> fct);

    /*
 Functie de sortare generala
 maiMareF - functie care compara 2 Book, verifica daca are loc relatia mai mare
          - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Book)
          - poate fi functie lambda (care nu capteaza nimic in capture list)
 returneaza o lista sortata dupa criteriu dat ca parametru
*/
    TemplateVector<Book> generalSort(bool (*maiMicF)(const Book&, const Book&));

public:
    BookStore(const BookRepo& bookrepo, const BookValidator& val) :repo{ bookrepo }, val{ val }{};
    //constructor de copiere

    BookStore(const BookStore& ot) = delete;

    /*
     Adaugam o carte cu titlul title, autorul author, genul genre si anul aparitiei year
     @parametrii:

     @throws:
        BookRepoException daca mai exista o carte cu titlul si autorul dat
        ValidationException daca cartea nu este valida
     */
    void addBook(const string& title, const string& author, const string& genre, const int& year);

    /*
     Sterge o carte
     */
    void deleteBook(const string& title, const string &author);

    /*
     Update book
     */
    void modifyBook(const string& title, const string& author, const string& genre, const int& year, const string& new_title, const string& new_author, const string& new_genre, const int& new_year);

    /*
     * Cauta o carte in lista de carti si transmite un mesaj daca aceasta apare
     */
    Book findBook(const string& title, const string& author);
    /*
     Returneaza un vector cu toate cartile disponibile
     @return: lista cu toate cartile disponibile(vector cu obiecte de tip Book)
     */

    TemplateVector<Book> getAllBooks(){
        return repo.getAllBooks();
    }

    /*
     Filtrare carti dupa titlu
     */
    TemplateVector<Book> filterTitle(const string& title);

    /*
     Filtrare dupa anul aparitiei
     */
    TemplateVector<Book> filterYear(int year);

    /*
     * Sortare dupa titlu
     */
    TemplateVector<Book> sortByTitle();

    /*
     * Sortare dupa anul aparitiei
     */
    TemplateVector<Book> sortByYear();

    /*
     * Sortare dupa autor si gen
     */
    TemplateVector<Book> sortByAuthorGenre();
};

void testeService();
