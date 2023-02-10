#include "BookGUI.h"
#include "Book.h"
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

void BookStoreGUI::initGUICmps() {
    setLayout(lyMain);

    QWidget* widDreapta = new QWidget;
    QVBoxLayout* vl = new QVBoxLayout;
    widDreapta->setLayout(vl);

    //lst = new QListWidget;
    //vl->addWidget(lst);

    //pentru tabelul din stanga cu lista de carti
    //QWidget* left = new QWidget;

    //left->setLayout(vl);

    int noLines = 10;
    int noColumns = 4;
    tableBooks = new QTableWidget{noLines, noColumns};

    QStringList header;
    header << "Title" << "Author" << "Genre" << "Year";
    tableBooks->setHorizontalHeaderLabels(header);

    tableBooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    vl->addWidget(tableBooks);


    QWidget* widBtnDreapta = new QWidget;
    QHBoxLayout* lyBtnsDr = new QHBoxLayout;
    widBtnDreapta->setLayout(lyBtnsDr);
    btnSortByTitle = new QPushButton("Sort by title");
    lyBtnsDr->addWidget(btnSortByTitle);

    btnSortByYear = new QPushButton("Sort by year");
    lyBtnsDr->addWidget(btnSortByYear);

    btnSortByAuthorGenre = new QPushButton("Sort by author and genre");
    lyBtnsDr->addWidget(btnSortByAuthorGenre);

    //btnSterge = new QPushButton("Sterge");
    //lyBtnsDr->addWidget(btnSterge);
    //btnSterge->setDisabled(true);


    vl->addWidget(widBtnDreapta);
    lyMain->addWidget(widDreapta);

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

    btnSearch = new QPushButton("Search book");
    formLDetalii->addWidget(btnSearch);

    btnDelete = new QPushButton("Delete book");
    formLDetalii->addWidget(btnDelete);

    lyMain->addWidget(widDetalii);

    btnDyn->setLayout(lyBtnDy);
    lyMain->addWidget(btnDyn);

    //pentru filtrari
    QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    formFilter->setLayout(lyFormFilter);
    this->editFilterYear = new QLineEdit();
    lyFormFilter->addRow(this->lblFilterCriteria, editFilterYear);
    btnFilterBooks = new QPushButton("Filter by year");
    lyFormFilter->addWidget(btnFilterBooks);


    lyMain->addWidget(formFilter);


}

void BookStoreGUI::connectSignalsSlots() {
    //cand se emite semnalul clicked de pe buton reincarc lista
    QObject::connect(btnSortByTitle, &QPushButton::clicked, [&]() {
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
    });
    QObject::connect(btnAdd, &QPushButton::clicked, this, &BookStoreGUI::addNewBook);

    //pentru cautare o carte
    QObject::connect(btnSearch, &QPushButton::clicked, this, &BookStoreGUI::searchBook);

    //pentru stergere
    QObject::connect(btnDelete, &QPushButton::clicked, this, &BookStoreGUI::deleteBook);

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
            btnSterge->setDisabled(true);
        }
        else {
            auto selItem = sel.at(0);
            auto title = selItem->text();
            auto author = selItem->data(Qt::UserRole).toString();
            auto genre = selItem->text();
            auto year = selItem->text();
            txtTitle->setText(title);
            txtAuthor->setText(author);
            txtGenre->setText(genre);
            txtYear->setText(year);
            auto b = ctr.findBook(title.toStdString(), author.toStdString(), genre.toStdString(), year.toInt());

            //btnSterge->show();
            btnSterge->setDisabled(false);
        }
        });
}*/
}

void BookStoreGUI::addNewBook() {
    try {
        ctr.addBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt());
        reloadList(ctr.getAllBooks());
        txtTitle->clear();
        txtAuthor->clear();
        txtGenre->clear();
        txtYear->clear();

        QMessageBox::information(this, "Info", QString::fromStdString("Cartea a fost adaugata cu succes."));
    }
    catch (BookRepoException& ex) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getErrorMessage()));
    }
    catch (ValidateException& e) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.getErrorMessages()));
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

        QMessageBox::information(this, "Info", QString::fromStdString("Cartea a fost stearsa cu succes."));
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
        if(ctr.findBook(txtTitle->text().toStdString(), txtAuthor->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt()) == 1) {

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

void BookStoreGUI::adaugaButoane(const std::vector<Book>& books) {
    for (const auto& b : books) {
        if (b.getTitle() == "ok") {
            auto btn = new QPushButton{ QString::fromStdString(b.getAuthor()) };
            lyBtnDy->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [this,btn,b]() {
                QMessageBox::information(nullptr,"Info", QString::number(b.getYear()));
                delete btn;
            });
        }
    }
}

void BookStoreGUI::reloadList(const std::vector<Book>& books) {
    /*lst->clear();
    for (const auto& b : books) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(b.getTitle()));
        item->setData(Qt::UserRole, QString::fromStdString(b.getAuthor()));

        lst->addItem(item);

    }*/
    tableBooks->clearContents();
    tableBooks->setRowCount(books.size());

    int lineNumber = 0;
    for (auto& book : books) {
        tableBooks->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(book.getTitle())));
        tableBooks->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(book.getAuthor())));
        tableBooks->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(book.getGenre())));
        tableBooks->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(book.getYear())));
        lineNumber++;
    }
}

