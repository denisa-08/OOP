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
#include "Observer.h"
#include "Cart.h"
#include <QPainter>

class BookCartGUI : public QWidget, public Observer{
private:
    BookStore& ctr;

    QHBoxLayout* lyMain = new QHBoxLayout;
    //QListWidget* lst;

    //pentru tabel cu carti din cos de cumparaturi
    QTableWidget* tableBooks;

    QLineEdit* txtTitle;
    QLineEdit* txtAuthor;
    QLineEdit* nrRandom;

    QPushButton* btnAdd;
    QPushButton* btnRandom;
    QPushButton* btnEmpty;

    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;

    void initGUICmps();
    void connectSignalsSlots();
    void addBook();
    void addRandom();
    void emptyCart();

    void update() override {
        reloadList();
    }

    ~BookCartGUI() {
        ctr.getCart().removeObserver(this);
    }

public:
    void reloadList();
    BookCartGUI(BookStore& ctr) :ctr{ ctr } {
        initGUICmps();
        connectSignalsSlots();
        reloadList();
    }

};

class CartGUIDraw: public QWidget, public Observer {
private:
    Cart& cart;
    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
        int x = 0;
        int y = 0;
        for(auto book : cart.getAllCartBooks()) {
            p.drawRect(x,y,10,book.getYear());
            x = rand() % 400 + 1;
            y = rand() % 400 + 1;
            qDebug() << x << " " << y;
            QRectF target(x,y,100,94);
            QRectF source(0,0,732,720);
            QImage image(": /Users/denisa/Documents/FACULTATE/book.jpg");
            p.drawImage(target, image, source);

            x+=40;
        }
    }

    void update() override {
        repaint();
    };

    ~CartGUIDraw() {
        cart.removeObserver(this);
    }

public:
    CartGUIDraw(Cart& cart) :cart { cart } {
        cart.addObserver(this);
    };
};
