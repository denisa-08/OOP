#include "Console.h"
#include "BookSrv.h"
#include "Book.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using std::cin;
using std::cout;

using namespace std;

void ConsoleUI::printCartMenu() {
    cout<<"Meniu Cos inchirieri"<<endl;
    cout<<"1. Adauga carte in cos"<<endl;
    cout<<"2. Adauga carti random in cos"<<endl;
    cout<<"3. Goleste cos"<<endl;
    cout<<"4. Afiseaza cos curent"<<endl;
    cout<<"5. Inapoi la meniul principal"<<endl;
}
void ConsoleUI::print(const vector<Book>& books) {
    cout<<"Carti:\n";
    for (const auto& book : books) {
        cout<<" Titlul: "<<book.getTitle()<<" | Autorul: "<<book.getAuthor()<<" | Genul: "<<book.getGenre()<<" | Anul aparitiei: "<<book.getYear()<<'\n';
    }
    cout<<"Sfarsit lista carti\n";
}

void ConsoleUI::addUI() {
    string title, author, genre;
    int year;
    cout<<"Dati titlu:";
    getline(cin >> ws, title);
    cout<<"Dati autor:";
    getline(cin >> ws, author);
    cout<<"Dati gen:";
    getline(cin >> ws, genre);
    cout<<"Dati an aparitie:";
    cin>>year;
    str.addBook(title, author, genre, year);
    cout<<"Adaugata cu succes!";
}


void ConsoleUI::deleteUI() {
    string title, genre, author;
    int year;
    cout<<"Dati titlu:";
    getline(cin >> ws, title);

    cout<<"Dati autor:";
    getline(cin >> ws, author);

    cout<<"Dati gen:";
    getline(cin >> ws, genre);

    cout<<"Dati an aparitie:";
    cin>>year;

    str.deleteBook(title, author, genre, year);
    cout<<"Stearsa cu succes!";
}

void ConsoleUI::findUI() {
    string title, author, genre;
    int year;
    cout<<"Dati titlu:";
    getline(cin >> ws, title);
    cout<<"Dati autor:";
    getline(cin >> ws, author);
    cout<<"Dati gen:";
    getline(cin >> ws, genre);
    cout<<"Dati an aparitie:";
    cin>>year;

    if(str.findBook(title, author, genre, year)) {
        cout << "Cartea cautata exista.\n";
    }
    else {
        cout << "Cartea cautata nu exista.\n";
    }
}

void ConsoleUI::updateUI() {
    string title, author, genre, new_title, new_author, new_genre;
    int year, new_year;
    cout<<"Dati titlu:";
    getline(cin >> ws, title);
    cout<<"Dati autor:";
    getline(cin >> ws, author);
    cout<<"Dati gen:";
    getline(cin >> ws, genre);
    cout<<"Dati an aparitie:";
    cin>>year;

    cout<<"Dati noul titlu:";
    getline(cin >> ws, new_title);
    cout<<"Dati noul autor:";
    getline(cin >> ws, new_author);
    cout<<"Dati noul gen:";
    getline(cin >> ws, new_genre);
    cout<<"Dati noul an aparitie:";
    cin>>new_year;

    str.modifyBook(title, author, genre, year, new_title, new_author, new_genre, new_year);
    cout<<"Carte modificata cu succes!!";
}

void ConsoleUI::addToCartUI() {
    string title, author;
    cout<<"Titlul cartii este:";
    getline(cin >> ws, title);

    cout<<"Autorul cartii este:";
    getline(cin>>ws, author);

    try {
        str.addToCart(title, author);
        cout<<"Cartea s-a adaugat cu succes in cos.";
    }
    catch (BookRepoException& e)  {
        cout<<e.getErrorMessage();
    }
    catch (ValidateException& ve) {
        cout<<"Cartea nu este valida."<<endl;
        cout<<ve.getErrorMessages();
    }
}

void ConsoleUI::addRandomUI() {
    int number;
    cout<<"Numarul de carti care sa se adauge:";
    cin>>number;

    try {
        int nr = str.addRandomToCart(number);
        cout<<"S-au adaugat "<<nr<<" carti in cos."<<endl;
    }
    catch (BookRepoException& re) {
        cout<<re.getErrorMessage();
    }
}

void ConsoleUI::emptyCartUI() {
    str.emptyCart();
    cout<<"S-au sters toate cartile din cosul curent."<<endl;
}

void ConsoleUI::CartUI() {
    int cmd;
    int cart = 1;
    while(cart) {
        printCartMenu();
        cout<<"Comanda este: ";
        cin>>cmd;
        switch (cmd) {
            case 1:
                addToCartUI();
                break;
            case 2:
                addRandomUI();
                break;
            case 3:
                emptyCartUI();
                break;
            case 4:
                print(str.getCartBooks());
                break;
            case 5:
                cart=0;
                break;
            default:
                break;
        }
    }
}


void ConsoleUI::printReport() {
    cout<<"Raport genuri de carti\n";
    cout<<"Introduceti genul pentru care se doreste raportul:";
    string genre;
    getline(cin >> ws, genre);
    int count = str.reportGenre(genre)[genre];
    cout<<"Numarul de carti de genul "<<genre<<" este "<<count;
}

void ConsoleUI::UndoUI() {
    try {
        str.undo();
        cout<<"Operatia de undo s-a efectuat cu succes!\n";
    }
    catch (BookRepoException& re) {
        cout<<re.getErrorMessage()<<endl;
    }
}

void ConsoleUI::ExportUI() {
    string file;
    cout << "Exportul se doreste in fisierul: ";
    cin >> file;
    try {
        str.exportFile(file);
    }
    catch (BookRepoException& re) {
        cout << re.getErrorMessage()<<endl;
    }
}


void ConsoleUI::start() {
    while (true) {
        cout << "\nMeniu:\n";
        cout << "1 adauga\n2 tipareste\n3 sterge\n4 modificare\n5 cautare\n6 filtrare titlu\n7 filtrare an aparitie\n8 sortare titlu\n9 sortare an aparitie\n10 sortare autor+gen\n11 meniu cos de inchirieri\n12 raport gen\n13 undo\n14 export fisier\n0 iesire\nDati comanda:";
        int cmd, year;
        string title;
        cin >> cmd;
        try {
            switch (cmd) {
                case 1:
                    addUI();
                    break;
                case 2:
                    print(str.getAllBooks());
                    break;
                case 3:
                    deleteUI();
                    break;
                case 4:
                    updateUI();
                    break;
                case 5:
                    findUI();
                    break;
                case 6:
                    cout << "Dati titlul:";
                    cin >> title;
                    print(str.filterTitle(title));
                    break;
                case 7:
                    cout << "Dati an aparitie:";
                    cin >> year;
                    print(str.filterYear(year));
                    break;
                case 8:
                    print(str.sortByTitle());
                    break;
                case 9:
                    print(str.sortByYear());
                    break;
                case 10:
                    print(str.sortByAuthorGenre());
                    break;
                case 11:
                    CartUI();
                    break;
                case 12:
                    printReport();
                    break;
                case 13:
                    UndoUI();
                    break;
                case 14:
                    ExportUI();
                    break;
                case 0:
                    return;
                default:
                    cout << "Comanda invalida\n";
            }
        }
        catch (BookRepoException ex) {
            cout << ex.getErrorMessage() <<'\n';
        }
        catch (ValidateException ex) {
            cout << ex.getErrorMessages() << '\n';
        }
    }
}