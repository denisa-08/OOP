#pragma once
#include <QAbstractTableModel>
#include <qbrush.h>
#include <vector>
#include <qslider.h>
#include "Service.h"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
	QSlider* slider;
	vector<Produs> produse;

public:
	MyTableModel(QSlider* slider, vector<Produs> produse) : slider{ slider }, produse{ produse } {

	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return produse.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}
	
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::ForegroundRole) {
			int pretMaxim = slider->value();
			Produs pcurent = produse.at(index.row());
			if (pcurent.getPret() <= pretMaxim) return QBrush{ Qt::red };
		}
		if (role == Qt::DisplayRole) {
			Produs pCurent = produse.at(index.row());
			if (index.column() == 0) {
				return QString::number(pCurent.getId());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(pCurent.getNume());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(pCurent.getTip());
			}
			else if (index.column() == 3) {
				return QString::number(pCurent.getPret());
			}
			else if (index.column() == 4) {
				int countVocale = 0;
				string nume = pCurent.getNume();
				for (auto& litera : nume) {
					if (litera == 'A' || litera == 'a' || litera == 'E' || litera == 'e'
						|| litera == 'I' || litera == 'i' || litera == 'O' || litera == 'o'
						|| litera == 'U' || litera == 'u') countVocale++;
				}
				return QString::number(countVocale);
			}
		}
		return QVariant{};
	}
	
	void update() {
		auto stangaSus = createIndex(0, 0);
		auto dreaptaJos = createIndex(rowCount(), columnCount());
		emit dataChanged(stangaSus, dreaptaJos);
		emit layoutChanged();
	}

	void setProduse(vector<Produs> produse) {
		this->produse = produse;
		update();
	}

};

