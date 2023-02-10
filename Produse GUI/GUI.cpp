#include "GUI.h"
#include <qheaderview.h>
#include <map>

void MainGUI::innitGUI() {
	this->setLayout(mainLayout);
	mainLayout->addWidget(slider);
	mainLayout->addWidget(sliderLabel);
	mainLayout->addLayout(formLayout);
	mainLayout->addWidget(tableView);
	formLayout->addRow(idLabel, idInput);
	formLayout->addRow(numeLabel, numeInput);
	formLayout->addRow(tipLabel, tipInput);
	formLayout->addRow(pretLabel, pretInput);
	formLayout->addWidget(addButton);
	
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	slider->setRange(1, 100);
	slider->setTickInterval(5);
}

void MainGUI::connectSignals() {
	connect(addButton, &QPushButton::pressed, this, [this]() {
		string id = idInput->text().toStdString();
		string nume = numeInput->text().toStdString();
		string tip = tipInput->text().toStdString();
		string pret = pretInput->text().toStdString();
		try {
			service.add(id, nume, tip, pret);
			loadData();
		}
		catch (Exception ex) {
			QMessageBox* errorBox = new QMessageBox;
			errorBox->setText(QString::fromStdString(ex.getMessage()));
			errorBox->show();
		}
		});
	connect(slider, &QSlider::valueChanged, this, [this]() {
		sliderLabel->setText(QString::number(slider->value()));
		loadData();
		});
}

void MainGUI::loadData() {
	model->setProduse(service.getAll());
}

void MainGUI::ferestre() {
	vector<string> tipuriDiferite;
	map<string, int> freq;
	for (auto& produs : service.getAll()) {
		if (freq[produs.getTip()] == 0) {
			freq[produs.getTip()] = 1;
			tipuriDiferite.push_back(produs.getTip());
		}
	}
	for (auto& tip : tipuriDiferite) {
		LabelGUI* label = new LabelGUI(service, tip);
		label->show();
	}
}

void LabelGUI::innitGUI() {
	this->setLayout(mainLayout);
	mainLayout->addWidget(label);
}