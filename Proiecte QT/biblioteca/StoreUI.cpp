#include "StoreUI.h"
#include <iostream>
#include "Book.h"
#include <vector>
/*
  Citeste date de la consola (int,float, double, string, etc)
  Reia citirea pana cand utilizatorul introduce corect
*/
template<typename T>
T myread(const char* msg) {
    T cmd{};
    while (true) {
        std::cout << std::endl << msg;
        std::cin >> cmd;
        const bool fail = std::cin.fail();
        std::cin.clear();//resetez failbit
        const auto& aux = std::cin.ignore(1000, '\n');
        if (!fail && aux.gcount() <= 1) {
            break; //am reusit sa citesc numar
        }
    }
    return cmd;
}
/*
tipareste meniu si citeste comanda
*/
int BookUI::readCommand() {
    std::cout << " 1 Adauga \n 2 Toate\n 3 Sterge\n 4 Modificare\n 5 Cautare\n";
    std::cout << " 6 Filtrare titlu\n 7 Filtrare an aparitie\n 8 Sortare titlu\n 9 Sortare an aparitie\n10 Adauga cos\n11 Exporta HTML\n";
    std::cout << " 0 Iesire\n";

    return myread<int>("Dati comanda:");
}

void printTableHeader() {
    std::cout.width(10);
    std::cout << "Title";
    std::cout.width(20);
    std::cout << "Author";
    std::cout.width(10);
    std::cout << "Genre";
    std::cout.width(10);
    std::cout << "Year";
    std::cout << std::endl;
}

/*
Tipareste lista de carti
*/
void BookUI::printBooks(const std::string& title,const std::vector<Book>& v) {
    std::cout << std::endl<<title<< "(" << v.size() << "):\n";
    printTableHeader();
    for (const Book& b : v) {
        std::cout.width(10);
        std::cout << b.getTitle();
        std::cout.width(20);
        std::cout << b.getAuthor();
        std::cout.width(10);
        std::cout << b.getGenre();
        std::cout.width(10);
        std::cout << b.getYear();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
/*
citeste de la tastatura si adauga carte
*/
void BookUI::addBook() {
    string title;
    string author;
    string genre;
    int year;
    std::cout << "\nTitle:";
    std::cin >> title;
    std::cout << "\nAuthor:";
    std::cin >> author;
    std::cout << "\nGenre:";
    std::cin >> genre;
    year = myread<int>("\nYear:");
    ctr.addBook(title, author, genre, year);
}


void BookUI::startUI()
{
    while (true) {
        const int cmd = readCommand();
        if (cmd == 0) {
            break;
        }
        try {
            if (cmd == 1) {
                addBook();
            }
            if (cmd == 2) {
                printBooks("Books ", ctr.getAllBooks());
            }
            /*if (cmd == 3) {
                const int price = myread<int>("Pret:");
                printPets("Pets ", ctr.getFilterByPrice(price));
            }
            if (cmd == 4) {
                printPets("Pets ", ctr.getSortByType());
            }
            if (cmd == 5) {
                printPets("Pets ", ctr.getSortByPrice());
            }
            if (cmd == 6) {
                ctr.undo();
                printPets("Pets ", ctr.getAllPets());
            }
            if (cmd == 7) {
                printPets("Cos Pets ", ctr.addToCos(myread<std::string>("Species:"), myread<std::string>("Type:")));
            }
            if (cmd == 8) {
                printPets("Cos Pets ", ctr.golesteCos());
            }
            if (cmd == 9) {
                printPets("Cos Pets ", ctr.addRandom(myread<int>("Cate:")));
            }
            if (cmd == 10) {
                ctr.exportaCosCVS(myread<string>("CVS File:"));
            }
            if (cmd == 11) {
                ctr.exportaCosHTML(myread<string>("HTML File:"));
            }*/
        }
        catch (BookRepoException& ex) {
            std::cout << ex.getErrorMessage() << std::endl;
        }
    }
}
