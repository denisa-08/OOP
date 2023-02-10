#pragma once
#include <qwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtableview.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "Service.h"
#include "MyModel.h"
#include <QAbstractTableModel>


class LabelGUI : public QWidget, public Observer {
private:
	Service& service;
	string tip;

	QLabel* label = new QLabel("Tip: " + QString::fromStdString(tip) + "Nr: ");
	QHBoxLayout* mainLayout = new QHBoxLayout;

	void update() override {
		int count = 0;
		for (auto& p : service.getAll()) {
			if (tip == p.getTip()) count++;
		}
		label->setText("Tip: " + QString::fromStdString(tip) + "\nContor: " +
			QString::number(count));
	}

	void innitGUI();

public:


	LabelGUI(Service& service, string tip) : service{ service }, tip{ tip } {
		service.addObserver(this);
		innitGUI();
		update();
	}

	~LabelGUI() {
		service.deleteObserver(this);
	}

};

class MainGUI : public QWidget {
private:
	Service& service;

	QVBoxLayout* mainLayout = new QVBoxLayout;

	//Adaugare
	QFormLayout* formLayout = new QFormLayout;
	QLabel* idLabel = new QLabel("ID:");
	QLabel* numeLabel = new QLabel("Nume:");
	QLabel* tipLabel = new QLabel("Tip:");
	QLabel* pretLabel = new QLabel("Pret:");

	QLineEdit* idInput = new QLineEdit;
	QLineEdit* numeInput = new QLineEdit;
	QLineEdit* tipInput = new QLineEdit;
	QLineEdit* pretInput = new QLineEdit;

	QPushButton* addButton = new QPushButton("Add");


	//Tabel
	QTableView* tableView = new QTableView;
	MyTableModel* model;

	//Slider
	QSlider* slider = new QSlider(Qt::Horizontal);
	QLabel* sliderLabel = new QLabel;
	
	void innitGUI();

	void connectSignals();

	void loadData();

	void ferestre();

public:

	MainGUI(Service& service) : service{ service } {
		model = new MyTableModel(slider, service.getAll());
		tableView->setModel(model);
		innitGUI();
		connectSignals();
		loadData();
		ferestre();
		this->setMinimumWidth(500);
	}

};