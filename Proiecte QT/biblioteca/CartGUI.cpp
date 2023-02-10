#include "CartGUI.h"
#include "Book.h"
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

void BookCartGUI::initGUICmps() {
    setLayout(lyMain);
    //adaug lista cu cartile din cosul de cumparaturi
    //QWidget* widStanga = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    //widStanga->setLayout(vl);
    //lst = new QListWidget;
    //vl->addWidget(lst);

    //TABEL
    QWidget* left = new QWidget;

    left->setLayout(vl);

    int noLines = 10;
    int noColumns = 4;
    tableBooks = new QTableWidget{noLines, noColumns};

    QStringList header;
    header << "Title" << "Author" << "Genre" << "Year";
    tableBooks->setHorizontalHeaderLabels(header);
    tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    vl->addWidget(tableBooks);
    //TABEL



    lyMain->addWidget(left);


    //pentru carti random
    QWidget* widRandom = new QWidget;
    QFormLayout* formRandom = new QFormLayout;
    widRandom->setLayout(formRandom);
    nrRandom = new QLineEdit;
    formRandom->addRow(new QLabel("Number:"), nrRandom);

    btnRandom = new QPushButton("Add random books");
    formRandom->addWidget(btnRandom);
    lyMain->addWidget(widRandom);


    QWidget* widBtnStanga = new QWidget;
    QHBoxLayout* lyBtnsSt = new QHBoxLayout;
    widBtnStanga->setLayout(lyBtnsSt);
    btnEmpty = new QPushButton("Empty cart");
    lyBtnsSt->addWidget(btnEmpty);
    vl->addWidget(widBtnStanga);

    //fac un form pentru detalii
    QWidget* widDetalii = new QWidget;
    QFormLayout* formLDetalii = new QFormLayout;
    widDetalii->setLayout(formLDetalii);
    txtTitle = new QLineEdit;
    formLDetalii->addRow(new QLabel("Titles:"),txtTitle);
    txtAuthor = new QLineEdit;
    formLDetalii->addRow(new QLabel("Authors:"), txtAuthor);

    btnAdd = new QPushButton("Add book");
    formLDetalii->addWidget(btnAdd);

    lyMain->addWidget(widDetalii);

    btnDyn->setLayout(lyBtnDy);
    lyMain->addWidget(btnDyn);


}

void BookCartGUI::connectSignalsSlots() {
    ctr.getCart().addObserver(this);
    QObject::connect(btnAdd, &QPushButton::clicked, this, &BookCartGUI::addBook);

    QObject::connect(btnRandom, &QPushButton::clicked, this, &BookCartGUI::addRandom);

    QObject::connect(btnEmpty, &QPushButton::clicked, this, &BookCartGUI::emptyCart);

    QObject::connect(tableBooks, &QTableWidget::itemClicked, [&]() {
        auto sel = tableBooks->selectedItems();
        if (sel.isEmpty()) {
            txtTitle->setText("");
            txtAuthor->setText("");

        }
        else {
            auto selItem = sel.at(0);
            auto title = selItem->text();
            auto author = selItem->data(Qt::UserRole).toString();
            try {
            txtTitle->setText(title);
            txtAuthor->setText(author);
            }
            catch (BookRepoException& ex) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
            }

            //auto b = ctr.findBook(title.toStdString(), author.toStdString());
            //txtAuthor->setText(QString::fromStdString(b.getTitle()));
           // txtAuthor->setText(QString::fromStdString(b.getAuthor()));
        }
        });

}

void BookCartGUI::addBook() {
    try {
        ctr.addToCart(txtTitle->text().toStdString(), txtAuthor->text().toStdString());
        reloadList();
        txtTitle->clear();
        txtAuthor->clear();

        QMessageBox::information(this, "Info", QString::fromStdString("Cartea a fost adaugata cu succes in cos."));
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    catch (ValidateException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
    }
}

void BookCartGUI::addRandom() {
    try {
        ctr.addRandomToCart(nrRandom->text().toInt());
        reloadList();
        nrRandom->clear();
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
}

void BookCartGUI::emptyCart() {
    ctr.emptyCart();
    reloadList();
}

void BookCartGUI::reloadList() {
    /* lst->clear();
    for (const auto& b : books) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b.getTitle()));
        item->setData(Qt::UserRole, QString::fromStdString(b.getAuthor()));

        lst->addItem(item);

    }*/
    const vector<Book>& books = ctr.getCartBooks();
    tableBooks->clearContents();
    tableBooks->setRowCount(books.size());

    int lineNumber = 0;
    for (auto& book : books) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(book.getTitle()));
        item->setData(Qt::UserRole, QString::fromStdString(book.getAuthor()));
        tableBooks->setItem(lineNumber, 0, item);
        tableBooks->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
        //tableBooks->setData(Qt::UserRole, QString::fromStdString(b.getAuthor()));
        tableBooks->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
        tableBooks->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(book.getYear())));
        lineNumber++;
    }
}


