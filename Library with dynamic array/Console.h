//
//
//

#pragma once
#include "BookSrv.h"
#include "Book.h"

class ConsoleUI {
    BookStore& str;

    /*
     * Citeste datele de la tastatura si adauga Book
     * arunca exceptie daca nu se poate salva, nu e valida
     */
    void addUI();


    /*
     * Citeste datele de la tastatura si sterge Book
     * arunca exceptie daca nu exista, nu e valida
     */
    void deleteUI();

    /*
     * Cauta o carte in lista de carti
     * Arunca exceptie daca nu e valida si afiseaza un mesaj in functie de existenta acesteia
     */
    void findUI();

    /*
     * Modifica o carte cu noile date introduse
     * Arunca exceptie daca cartea nu exista in lista, nu e valida sau noile date introduse nu sunt valide
     */
    void updateUI();

    /*
     * Tipareste o lista de carti in consola
     */
    static void print(const TemplateVector<Book>& books);


public:
    ConsoleUI(BookStore& str) :str{ str } {
    }
    //nu permitem copierea obiectelor
    ConsoleUI(const ConsoleUI& ot) = delete;

    void start();
};