#include <iostream>
#include "Book.h"
#include "BookRepo.h"
#include "BookSrv.h"
#include "Console.h"

using namespace std;

void testAll(){
    testeDomain();
    testeRepo();
    testeService();
}

void adaugaCateva(BookStore& str) {
    str.addBook("Baltagul", "Mihail Sadoveanu", "realism", 1910);
    str.addBook("Enigma Otiliei", "George Calinescu", "realism", 1938);
    str.addBook("Ion", "Liviu Rebreanu", "realism", 1920);
    str.addBook("Moara cu noroc", "Ioan Slavici", "nuvela psihologica", 1880);
    str.addBook("Cum eram candva", "Allan Hampson", "fictiune", 1990);
}

int main(int argc, const char * argv[]) {
    testAll();
    cout << "Toate testele au trecut!\n";

    BookRepo repo;
    BookValidator val;
    BookStore str{ repo, val};
    adaugaCateva(str);
    ConsoleUI ui{ str };
    ui.start();

    return 0;
}

