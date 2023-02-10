#include "widget.h"
#include "BookGUI.h"
#include "Book.h"
#include "StoreUI.h"
#include "BookSrv.h"

#include <QApplication>

void runGUI(int argc, char* argv[]) {
    QApplication a(argc, argv);
    BookRepo rep;
    BookValidator val;
    BookStore ctr { rep, val };

    BookStoreGUI gui { ctr };
    gui.show();
    a.exec();

}

void testAll() {
    testeRepo();
    testeDomain();
    testeService();
}

int main(int argc, char *argv[])
{
    testAll();
    runGUI(argc, argv);
    return 0;
}
