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
    str.addBook("T1", "A1", "g1", 1910);
    str.addBook("T2", "A2", "g2", 1938);
    str.addBook("T3", "A3", "g3", 1920);
    str.addBook("T4", "A4", "g4", 1880);
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

