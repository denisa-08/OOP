#include "BookGUI.h"
#include "Book.h"
#include "CartGUI.h"
#include "Cart.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <qpalette.h>
#include <qbrush.h>
#include <qdebug.h>
#include <string>
#include <algorithm>

/*void UpdateGUI::initGUICmps() {
    setLayout(lyMain);

    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    Title = new QLineEdit;
    formLDetalii->addRow(new QLabel("New title:"), Title);
    Author = new QLineEdit;
    formLDetalii->addRow(new QLabel("New author:"), Author);
    Genre = new QLineEdit;
    formLDetalii->addRow(new QLabel("New genre:"), Genre);
    Year = new QLineEdit;
    formLDetalii->addRow(new QLabel("New year:"), Year);

     lyMain->addWidget(widDetalii);

     bUpdate = new QPushButton("Update book");
     lyMain->addWidget(bUpdate);
}

void UpdateGUI::connectSignalsSlots() {
    QObject::connect(bUpdate, &QPushButton::clicked, [&]() {
        ctr.modify(txtTitle);
        this->reloadList(ctr.getAllBooks());
    });
}*/


void BookStoreGUI::initGUICmps() {
    setLayout(lyMain);

    QWidget* widStanga = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    widStanga->setLayout(vl);

    lst = new QListWidget;
    vl->addWidget(lst);

    //pentru tabelul din stanga cu lista de carti
    //QWidget* left = new QWidget;

    //left->setLayout(vl);

    /*int noLines = 10;
    int noColumns = 4;
    tableBooks = new QTableWidget{noLines, noColumns};

    QStringList header;
    header << "Title" << "Author" << "Genre" << "Year";
    tableBooks->setHorizontalHeaderLabels(header);

    tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    vl->addWidget(tableBooks);*/


    //Sortare cu radio buttons
    QVBoxLayout* lyRadioBox = new QVBoxLayout;
    groupBox->setLayout(lyRadioBox);
    lyRadioBox->addWidget(radioSortTitle);
    lyRadioBox->addWidget(radioSortYear);
    lyRadioBox->addWidget(radioSortAuthorGenre);

    btnSort = new QPushButton("Sort books");
    lyRadioBox->addWidget(btnSort);

    //bag sortarile dedesubt de lista cu carti
    QWidget* widBtnStanga = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnStanga->setLayout(lyBtnsDr);
    lyBtnsDr->addWidget(groupBox);


    vl->addWidget(widBtnStanga);
    lyMain->addWidget(widStanga);

    /*QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnDreapta->setLayout(lyBtnsDr);
    btnSortByTitle = new QPushButton("Sort by title");
    lyBtnsDr->addWidget(btnSortByTitle);

    btnSortByYear = new QPushButton("Sort by year");
    lyBtnsDr->addWidget(btnSortByYear);

    btnSortByAuthorGenre = new QPushButton("Sort by author and genre");
    lyBtnsDr->addWidget(btnSortByAuthorGenre);*/

    //btnSterge = new QPushButton("Sterge");
    //lyBtnsDr->addWidget(btnSterge);
    //btnSterge->setDisabled(true);

    //fac un form pentru detalii
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    txtTitle = new QLineEdit;
    formLDetalii->addRow(new QLabel("Titles:"),txtTitle);
    txtAuthor = new QLineEdit;
    formLDetalii->addRow(new QLabel("Authors:"), txtAuthor);
    txtGenre = new QLineEdit;
    formLDetalii->addRow(new QLabel("Genres:"), txtGenre);
    txtYear = new QLineEdit;
    formLDetalii->addRow(new QLabel("Years:"), txtYear);

    btnAdd = new QPushButton("Add book");
    formLDetalii->addWidget(btnAdd);
    btnAddCart = new QPushButton("Add to cart");
    formLDetalii->addWidget(btnAddCart);

    btnSearch = new QPushButton("Search book");
    formLDetalii->addWidget(btnSearch);

    btnDelete = new QPushButton("Delete book");
    formLDetalii->addWidget(btnDelete);

    btnDeleteCart = new QPushButton("Delete from cart");
    formLDetalii->addWidget(btnDeleteCart);

    newTitle = new QLineEdit;
    formLDetalii->addRow(new QLabel("New title:"),newTitle);
    newAuthor = new QLineEdit;
    formLDetalii->addRow(new QLabel("New author:"), newAuthor);
    newGenre = new QLineEdit;
    formLDetalii->addRow(new QLabel("New genre:"), newGenre);
    newYear = new QLineEdit;
    formLDetalii->addRow(new QLabel("New year:"), newYear);

    btnUpdate = new QPushButton("Update book");
    formLDetalii->addWidget(btnUpdate);

    btnUndo = new QPushButton("Undo");
    formLDetalii->addWidget(btnUndo);

    lyMain->addWidget(widDetalii);

    btnDyn->setLayout(lyBtnDy);
    lyMain->addWidget(btnDyn);

    //pentru filtrari
    QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);

    //FEREASTRA NOUA pentru cos de cumparaturi
    btnFereastra = new QPushButton("CartCRUDGUI");
    btnFereastra->setStyleSheet("background-color:blue");
    lyFormFilter->addWidget(btnFereastra);


    //cos de inchirieri desen, fereastra noua
    btnDraw = new QPushButton("CartReadOnlyGUI");
    btnDraw->setStyleSheet("background-color: yellow");
    lyFormFilter->addWidget(btnDraw);

    //adaugare de carti random in cos
    number = new QLineEdit();
    lyFormFilter->addRow(new QLabel("How many?"), number);
    btnGenerate = new QPushButton("Add random");
    lyFormFilter->addWidget(btnGenerate);



    //filtrare
    this->editFilterYear = new QLineEdit();
    lyFormFilter->addRow(this->lblFilterCriteria, editFilterYear);

    btnFilterBooks = new QPushButton("Filter by year");
    lyFormFilter->addWidget(btnFilterBooks);


    txtExport = new QLineEdit();
    lyFormFilter->addRow(exportLabel, txtExport);
    btnExport = new QPushButton("Export file");
    lyFormFilter->addWidget(btnExport);


    lyMain->addWidget(formFilter);


}

void BookStoreGUI::connectSignalsSlots() {
    //cand se emite semnalul clicked de pe buton reincarc lista
    /*QObject::connect(btnSortByTitle, &QPushButton::clicked, [&]() {
        qDebug() << "am ajuns aici!";
        reloadList(ctr.sortByTitle());
    });
    //cand se emite semnalul clicked de pe buton reincarc lista
    QObject::connect(btnSortByYear, &QPushButton::clicked, [&]() {
        reloadList(ctr.sortByYear());
    });
    //cand se emite semnalul clicked de pe buton reincarc lista
    QObject::connect(btnSortByAuthorGenre, &QPushButton::clicked, [&]() {
        reloadList(ctr.sortByAuthorGenre());
    });*/
    QObject::connect(btnAddCart, &QPushButton::clicked, this, [&]() {
        try {
            ctr.addToCart(txtTitle->text().toStdString(), txtAuthor->text().toStdString());
            txtTitle->clear();
            txtAuthor->clear();
            txtGenre->clear();
            txtYear->clear();
            cos->reloadList();
        }
        catch (BookRepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
        }
        catch (ValidateException& e) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
        }
    });

    QObject::connect(btnDeleteCart, &QPushButton::clicked, this, [&]() {
        ctr.emptyCart();
        cos->reloadList();
        //reloadList(ctr.getCartBooks());
    });

    QObject::connect(btnGenerate, &QPushButton::clicked, this, [&]() {
        int nr = this->number->text().toInt();
        ctr.addRandomToCart(nr);
        cos->reloadList();
        //reloadList(ctr.getCartBooks());
    });







    QObject::connect(btnDraw, &QPushButton::clicked, this, [&]() {
        auto drawWindow = new CartGUIDraw{ ctr.getCart() };
        drawWindow->show();
    });

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try{
            ctr.undo();
            this->reloadList(ctr.getAllBooks());
        }
        catch (BookRepoException& ex) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    });

    QObject::connect(btnExport, &QPushButton::clicked, this, &BookStoreGUI::exportFisier);

    //sortari
    QObject::connect(btnSort, &QPushButton::clicked, [&]() {
          if(this->radioSortTitle->isChecked()) {
               this->reloadList(ctr.sortByTitle());
               QHBoxLayout* lySecond = new QHBoxLayout;
               this->setLayout(lySecond);
          }
          else if(this->radioSortYear->isChecked())
                this->reloadList(ctr.sortByYear());
          else if(this->radioSortAuthorGenre->isChecked())
                this->reloadList(ctr.sortByAuthorGenre());
    });

    QObject::connect(btnAdd, &QPushButton::clicked, this, &BookStoreGUI::addNewBook);

    //pentru cautare o carte
    QObject::connect(btnSearch, &QPushButton::clicked, this, &BookStoreGUI::searchBook);

    //pentru stergere
    QObject::connect(btnDelete, &QPushButton::clicked, this, &BookStoreGUI::deleteBook);

    //pentru update
    QObject::connect(btnUpdate, &QPushButton::clicked, this, &BookStoreGUI::updateBook);

    //fereastra noua
    QObject::connect(btnFereastra, &QPushButton::clicked, this, &BookStoreGUI::fereastra);

    QObject::connect(btnFilterBooks, &QPushButton::clicked, [&]() {
        int filterC = this->editFilterYear->text().toInt();
        this->reloadList(ctr.filterYear(filterC));
        });

    /*QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = lst->selectedItems();
        if (sel.isEmpty()) {
            txtTitle->setText("");
            txtAuthor->setText("");
            txtGenre->setText("");
            txtYear->setText("");

            //btnSterge->hide();
            //btnSterge->setDisabled(true);
        }
        else {
            auto selItem = sel.at(0);
            auto title = selItem->text();
            auto author = selItem->data(Qt::UserRole).toString();
            //auto genre = selItem->text();
            //auto year = selItem->text();
            txtTitle->setText(title);
            txtAuthor->setText(author);
            //txtGenre->setText(genre);
            //txtYear->setText(year);
            auto b = ctr.findBook(title.toStdString(), author.toStdString());
            txtGenre->setText(QString::fromStdString(b.getGenre()));
            txtYear->setText(QString::number(b.getYear()));
            //btnSterge->show();
            //btnSterge->setDisabled(false);
        }
        });*/


    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        if (lst->selectedItems().isEmpty()) {
            txtTitle->setText("");
            txtAuthor->setText("");
            txtGenre->setText("");
            txtYear->setText("");
            return;
            //btnSterge->hide();
            //btnSterge->setDisabled(true);
        }

        QListWidgetItem* selItem = lst->selectedItems().at(0);
        QString title = selItem->text();
        txtTitle->setText(title);
        QString author = selItem->data(Qt::UserRole).toString();
        txtAuthor->setText(author);

        try {
            //cautam carte
            Book b = ctr.findBook(title.toStdString(), author.toStdString());
            txtGenre->setText(QString::fromStdString(b.getGenre()));
            txtYear->setText(QString::number(b.getYear()));
        }
        catch (BookRepoException& ex) {
            QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getErrorMessage()));
        }
        });

}

void BookStoreGUI::addNewBook() {
    try {
        ctr.addBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt());
        reloadList(ctr.getAllBooks());
        txtTitle->clear();
        txtAuthor->clear();
        txtGenre->clear();
        txtYear->clear();

        //QMessageBox::information(this, "Info", QString::fromStdString("Cartea a fost adaugata cu succes."));
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    catch (ValidateException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
    }
}

void BookStoreGUI::exportFisier() {
    try {
        ctr.exportFile(txtExport->text().toStdString());
        reloadList(ctr.getAllBooks());
        txtExport->clear();

    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
}
void BookStoreGUI::deleteBook() {
    try {
        ctr.deleteBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt());
        reloadList(ctr.getAllBooks());
        txtTitle->clear();
        txtAuthor->clear();
        txtGenre->clear();
        txtYear->clear();

        //QMessageBox::information(this, "Info", QString::fromStdString("Cartea a fost stearsa cu succes."));
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    catch (ValidateException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
    }
}

void BookStoreGUI::searchBook() {
    try {
        auto b = ctr.findBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString());
        if(b.getTitle() == txtTitle->text().toStdString() && b.getAuthor() == txtAuthor->text().toStdString()){

        QMessageBox::information(this, "Info", QString::fromStdString("Cartea cautata exista."));
        }
        else {
              QMessageBox::information(this, "Info", QString::fromStdString("Cartea cautata nu exista!"));
        }
        txtTitle->clear();
        txtAuthor->clear();
        txtGenre->clear();
        txtYear->clear();
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    catch (ValidateException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
    }
}

void BookStoreGUI::updateBook() {
    try {
         ctr.modifyBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt(),
                        newTitle->text().toStdString(), newAuthor->text().toStdString(), newGenre->text().toStdString(), newYear->text().toInt());
         reloadList(ctr.getAllBooks());
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }

}

/*void BookStoreGUI::adaugaButoane(const std::vector<Book>& books) {
    for (const auto& b : books) {
        if (b.getTitle() == "ok") {
            auto btn = new QPushButton{ QString::fromStdString(b.getAuthor()) };
            lyBtnDy->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [btn,b]() {
                QMessageBox::information(nullptr,"Info", QString::number(b.getYear()));
                delete btn;
            });
        }
    }
}*/

void BookStoreGUI::reloadList(const std::vector<Book>& books) {
    lst->clear();
    for (const auto& b : books) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b.getTitle()));
        item->setData(Qt::UserRole, QString::fromStdString(b.getAuthor()));

        lst->addItem(item);

    }
    /*tableBooks->clearContents();
    tableBooks->setRowCount(books.size());

    int lineNumber = 0;
    for (auto& book : books) {
        tableBooks->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
        tableBooks->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
        tableBooks->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
        tableBooks->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(book.getYear())));
        lineNumber++;
    }*/
}

void BookStoreGUI::fereastra() {
    //BookCartGUI* f = new BookCartGUI { ctr };
    //UpdateGUI* f = new UpdateGUI ();

    //BookCartGUI* f = new BookCartGUI { ctr };
    this->cos = new BookCartGUI { ctr };
    cos->show();
}


/*BookCartGUI* BookStoreGUI::cos() {
    BookCartGUI* f = new BookCartGUI {ctr};
    //f->show();
    return f;
}*/



