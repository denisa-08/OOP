#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <QTableWidget>
#include <qtablewidget.h>
#include <QGroupBox>
#include <QRadioButton>
#include <qdebug.h>
#include "BookSrv.h"
#include "Book.h"
#include <vector>
#include <qlabel.h>
#include "CartGUI.h"

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
    friend class BookCartGUI;
private:
    BookStore& ctr;
    BookCartGUI* cos;
    QHBoxLayout* lyMain = new QHBoxLayout;
    QListWidget* lst;

    //pentru sortari
    QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));//pentru alegerea tipului de sortare
    QRadioButton* radioSortTitle = new QRadioButton(QString::fromStdString("Title"));
    QRadioButton* radioSortYear = new QRadioButton(QString::fromStdString("Year"));
    QRadioButton* radioSortAuthorGenre = new QRadioButton(QString::fromStdString("Author+genre"));
    QPushButton* btnSort;

    //QPushButton* btnSortByTitle;
    //QPushButton* btnSortByYear;
    //QPushButton* btnSortByAuthorGenre;

    QPushButton* btnUndo;

    QLineEdit* txtTitle;
    QLineEdit* txtAuthor;
    QLineEdit* txtGenre;
    QLineEdit* txtYear;

    QLineEdit* newTitle;
    QLineEdit* newAuthor;
    QLineEdit* newGenre;
    QLineEdit* newYear;

    QLineEdit* txtExport;

    QPushButton* btnAdd;
    QPushButton* btnSearch;
    QPushButton* btnDelete;
    QPushButton* btnUpdate;

    QPushButton* btnAddCart;
    QPushButton* btnDeleteCart;
    QPushButton* btnGenerate;
    QLineEdit* number;

    QPushButton* btnExport;

    //QPushButton* btnSterge;

    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;

    //tabel
    //QTableWidget* tableBooks;


    QLineEdit* editFilterYear;
    QPushButton* btnFilterBooks;
    QLabel* lblFilterCriteria = new QLabel{ "The year for filter:" };
    QLabel* exportLabel = new QLabel {"File:"};

    void initGUICmps();
    void connectSignalsSlots();
    void reloadList(const std::vector<Book>& books);
    void addNewBook();
    void searchBook();
    void updateBook();
    void deleteBook();
    void undo();
    void exportFisier();

    //void adaugaButoane(const std::vector<Book>& books);

    void fereastra();
    QPushButton* btnFereastra;

    QPushButton* btnDraw;
    void desen();
public:
    BookStoreGUI(BookStore& ctr) :ctr{ ctr } {
        initGUICmps();
        connectSignalsSlots();
        reloadList(ctr.getAllBooks());
        //adaugaButoane(ctr.getAllBooks());
    }

};


//pentru fereastra noua de update
class UpdateGUI : public QWidget {
    friend class BookStoreGUI;

private:
    BookStore& ctr;
    BookStoreGUI* str;

    QHBoxLayout* lyMain = new QHBoxLayout;
    QLineEdit* Title;
    QLineEdit* Author;
    QLineEdit* Genre;
    QLineEdit* Year;

    QPushButton* bUpdate;


    void initGUICmps();
    void connectSignalsSlots();

public:

    UpdateGUI(BookStore& ctr, BookStoreGUI* str) :ctr{ ctr }, str {str }{
    initGUICmps();
    connectSignalsSlots();
    }
};
