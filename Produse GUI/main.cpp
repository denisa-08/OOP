#include "Produse.h"
#include <QtWidgets/QApplication>
#include "Test.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    testAll();
    QApplication a(argc, argv);
    Repository repo{ "data.txt" };
    Validator validator;
    Service service { repo, validator };
    MainGUI mainGui{ service };
    mainGui.show();
    return a.exec();
}
