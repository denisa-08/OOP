//
//
//

#include "Console.h"

#include "Book.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
//using std::getline;

using namespace std;

void ConsoleUI::print(const TemplateVector<Book>& books) {
    cout<<"Carti:\n";
    for (int i=0; i<books.size(); i++) {
        cout<<" Titlul: "<<books.get(i).getTitle()<<" | Autorul: "<<books.get(i).getAuthor()<<" | Genul: "<<books.get(i).getGenre()<<" | Anul aparitiei: "<<books.get(i).getYear()<<'\n';
    }
    cout<<"Sfarsit lista carti\n";
}

void ConsoleUI::addUI() {
    string title, author, genre;
    int year;
    cout<<"Dati titlu:";
    cin>>title;
    cout<<"Dati autor:";
    cin>>author;
    cout<<"Dati gen:";
    cin>>genre;
    cout<<"Dati an aparitie:";
    cin>>year;
    str.addBook(title, author, genre, year);
    cout<<"Adaugata cu succes!";
}


void ConsoleUI::deleteUI() {
    string title, author, genre;
    int year;
    cout<<"Dati titlu:";
    cin>>title;
    cout<<"Dati autor:";
    cin>>author;

    str.deleteBook(title, author);
    cout<<"Stearsa cu succes!";
}

void ConsoleUI::findUI() {
    string title, author, genre;
    int year;
    cout<<"Dati titlu:";
    cin>>title;
    cout<<"Dati autor:";
    cin>>author;
    cout<<"Dati gen:";
    cin>>genre;
    cout<<"Dati an aparitie:";
    cin>>year;

    try {
        Book found = str.findBook(title, author);
        cout<<"Cartea cautata exista";
    }
    catch (Exception ex){
        cout<<ex.getMessage()<<endl;
    }

}

void ConsoleUI::updateUI() {
    string title, author, genre, new_title, new_author, new_genre;
    int year, new_year;
    cout<<"Dati titlu:";
    cin>>title;
    cout<<"Dati autor:";
    cin>>author;
    cout<<"Dati gen:";
    cin>>genre;
    cout<<"Dati an aparitie:";
    cin>>year;

    cout<<"Dati noul titlu:";
    cin>>new_title;
    cout<<"Dati noul autor:";
    cin>>new_author;
    cout<<"Dati noul gen:";
    cin>>new_genre;
    cout<<"Dati noul an aparitie:";
    cin>>new_year;

    str.modifyBook(title, author, genre, year, new_title, new_author, new_genre, new_year);
    cout<<"Carte modificata cu succes!!";
}



void ConsoleUI::start() {
    while (true) {
        cout << "\nMeniu:\n";
        cout << "1 adauga\n2 tipareste\n3 sterge\n4 modificare\n5 cautare\n6 filtrare titlu\n7 filtrare an aparitie\n8 sortare titlu\n9 sortare an aparitie\n10 sortare autor+gen\n0 iesire\nDati comanda:";
        int year;
        string cmd;
        string title;
        cin >> cmd;
        try {
             if(cmd == "0")
                 break;
              else if(cmd == "1")
                    addUI();
              else if(cmd == "2")
                  print(str.getAllBooks());
              else if(cmd == "3")
                    deleteUI();
              else if(cmd == "4")
                    updateUI();
              else if(cmd == "5")
                    findUI();
              else if(cmd == "6") {
                  cout << "Dati titlul:";
                  cin >> title;
                  print(str.filterTitle(title));
              }
              else if(cmd == "7") {
                  cout << "Dati an aparitie:";
                  cin >> year;
                  print(str.filterYear(year));
              }
              else if(cmd == "8")
                   print(str.sortByTitle());
              else if(cmd == "9")
                   print(str.sortByYear());
              else if(cmd == "10")
                  print(str.sortByAuthorGenre());
              else
                    cout << "Comanda invalida\n";
            }
        catch (Exception ex) {
            cout << ex.getMessage() <<'\n';
        }
        catch (ValidateException ex) {
            cout << ex.getErrorMessages() << '\n';
        }
    }
}