#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Produse.h"

class Produse : public QMainWindow
{
    Q_OBJECT

public:
    Produse(QWidget *parent = nullptr);
    ~Produse();

private:
    Ui::ProduseClass ui;
};
