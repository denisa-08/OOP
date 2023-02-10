#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <QTableWidget>
#include <qtablewidget.h>

#include <qdebug.h>
#include "BookSrv.h"
#include "Book.h"
#include <vector>
#include <qlabel.h>

class SmallGUI : public QWidget {
private:
    QLabel* lbl = new QLabel("Nimic");
public:
    SmallGUI() {
        QHBoxLayout* ly = new QHBoxLayout;
        setLayout(ly);
        ly->addWidget(lbl);
    }

    void setBook(const Book&b) {
        lbl->setText(QString::fromStdString( b.getTitle()));
    }
};


class BookStoreGUI : public QWidget{
private:
    BookStore& ctr;
    QHBoxLayout* lyMain = new QHBoxLayout;
    QListWidget* lst;

    QPushButton* btnSortByTitle;
    QPushButton* btnSortByYear;
    QPushButton* btnSortByAuthorGenre;

    QLineEdit* txtTitle;
    QLineEdit* txtAuthor;
    QLineEdit* txtGenre;
    QLineEdit* txtYear;

    QPushButton* btnAdd;
    QPushButton* btnSearch;
    QPushButton* btnDelete;

    //QPushButton* btnSterge;

    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;

    //tabel
    QTableWidget* tableBooks;

    QLineEdit* editFilterYear;
    QPushButton* btnFilterBooks;
    QLabel* lblFilterCriteria = new QLabel{ "The year for filter:" };

    void initGUICmps();
    void connectSignalsSlots();
    void reloadList(const std::vector<Book>& books);
    void addNewBook();
    void searchBook();
    void deleteBook();
    void adaugaButoane(const std::vector<Book>& books);
public:
    BookStoreGUI(BookStore& ctr) :ctr{ ctr } {
        initGUICmps();
        connectSignalsSlots();
        reloadList(ctr.getAllBooks());
        adaugaButoane(ctr.getAllBooks());
    }
};
