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
#include "Cart.h"
#include "Map.h"
#include "Undo.h"
#include <string>
#include <vector>

#include <functional>

using std::vector;
using std::function;


class BookStore {
private:
    BookRepo& repo;
    BookValidator& val;

    vector<ActionUndo*> undoActions;

    Cart currentCart;

    /*
    Functie generala de filtrare
    fct - poate fi o functie
    fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
    returneaza doar cartile care trec de filtru (fct(book)==true)
    */
    vector<Book> filter(function<bool(const Book&)> fct);

    /*
 Functie de sortare generala
 maiMareF - functie care compara 2 Book, verifica daca are loc relatia mai mare
          - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Book)
          - poate fi functie lambda (care nu capteaza nimic in capture list)
 returneaza o lista sortata dupa criteriu dat ca parametru
*/
    vector<Book> generalSort(bool (*maiMicF)(const Book&, const Book&));

public:
    BookStore(BookRepo& bookrepo, BookValidator& val) :repo{ bookrepo }, val{ val }{};
    //constructor de copiere

    BookStore(const BookStore& ot) = delete;

    /*
     Adaugam o carte cu titlul title, autorul author, genul genre si anul aparitiei year
     @parametrii:

     @throws:
        BookRepoException daca mai exista o carte cu titlul si autorul dat
        ValidationException daca cartea nu este valida
     */
    void addBook(string title, string author, string genre, int year);

    /*
     Sterge o carte
     */
    void deleteBook(string title, string author, string genre, int year);


    /*
     Update book
     */
    void modifyBook(string title, string author, string genre, int year, string new_title, string new_author, string new_genre, int new_year);

    /*
     * Cauta o carte in lista de carti si transmite un mesaj daca aceasta apare
     */
    bool findBook(string title, string author, string genre, int year);
    /*
     Returneaza un vector cu toate cartile disponibile
     @return: lista cu toate cartile disponibile(vector cu obiecte de tip Book)
     */

    const vector<Book>& getAllBooks(){
        return this->repo.getAllBooks();
    }

    /*
     Filtrare carti dupa titlu
     */
    vector<Book> filterTitle(string title);

    /*
     Filtrare dupa anul aparitiei
     */
    vector<Book> filterYear(int year);

    /*
     * Sortare dupa titlu
     */
    vector<Book> sortByTitle();

    /*
     * Sortare dupa anul aparitiei
     */
    vector<Book> sortByYear();

    /*
     * Sortare dupa autor si gen
     */
    vector<Book> sortByAuthorGenre();


    /*
    * Adauga o carte in cosul de inchirieri curent
    *
    * @param title: titlul cartii care se adauga (string)
    * @param author: autorul cartii care se adauga (string)
     *
    * post: cartea este adaugata in cos
    * @throws: RepoException daca nu exista cartea data
    */
    void addToCart(string title, string author);


    /*
    * Adauga un numar random de carti in cos
    *
    * @param number: cate carti se adauga (int)
    *
    * @return: numarul de carti adaugate in cos
    * post: se adauga un numar random de carti in cos
    */
    int addRandomToCart(int number);


    /*
    * Elimina toate cartile din cos
    * post: cosul nu contine nicio carte
    */
    void emptyCart();


    /*
    * Returneaza un vector cu toate cartile din cos
    */
    const vector<Book>& getCartBooks();

    /*
     * Creare raport pentru genuri de carti
     */
    int createReportGenre(const string& genre);

    /*
     * Functie pentru undo
     */
    void undo();

    /*
     * Export cos de inchirieri carti intr-un fisier
    */
    void exportFile(string file);

    std::unordered_map<string,int> reportGenre(string genre);

};

void testeService();
