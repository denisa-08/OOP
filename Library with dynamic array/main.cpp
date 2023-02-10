#include <iostream>
#include "Book.h"
#include "BookRepo.h"
#include "BookSrv.h"
#include "Console.h"
#include "DynamicArray.h"

using namespace std;

void testAll(){
    testeDomain();
    testeRepo();
    testeService();
    test_dynamic_vector();
}

void adaugaCateva(BookStore& str) {
    str.addBook("Baltagul", "Mihail", "realism", 1910);
    str.addBook("Enigma", "George", "realism", 1938);
    str.addBook("Ion", "Liviu", "realism", 1920);
    str.addBook("Moara", "Ioan", "nuvela", 1880);
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

