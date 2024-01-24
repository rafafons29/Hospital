#include "listptients.hpp"
#include "../../../mainwindow.h"
#include "../../libraries/hospital/hospital.hpp"
#include "../login/login.hpp"
#include "ui_listptients.h"
#include <iostream>
#include <qstringview.h>
#include <qtablewidget.h>
#include <stdexcept>
#include <string>

ListPtients::ListPtients(QWidget *parent)
    : QWidget(parent), ui(new Ui::ListPtients) {
  ui->setupUi(this);

  ui->num_hward->setPlaceholderText(Login::SALA_STR);
  ui->num_hward->setStyleSheet(MainWindow::TEXT_BOX_STYLES);
  ui->list_patitents->setStyleSheet(LIS_STYLE);
}

ListPtients::~ListPtients() { delete ui; }

void ListPtients::on_ok_btn_clicked() {
  try {
    int num_hward{ui->num_hward->text().toInt()};
    int i{0};

    ui->num_hward->setStyleSheet(MainWindow::TEXT_BOX_STYLES);
    ui->list_patitents->setRowCount(MainWindow::hospital[num_hward].size());
    ui->list_patitents->setColumnCount(7);

    for (auto &patient : MainWindow::hospital[num_hward]) {
      ui->list_patitents->setItem(
          i, 0, new QTableWidgetItem(QString::fromStdString(patient.name_)));
      ui->list_patitents->setItem(
          i, 1,
          new QTableWidgetItem(QString::fromStdString(patient.last_name_)));
      ui->list_patitents->setItem(
          i, 2,
          new QTableWidgetItem(QString::fromStdString(patient.id_.c_str())));
      ui->list_patitents->setItem(
          i, 3, new QTableWidgetItem(QString::number(patient.num_bed_)));
      ui->list_patitents->setItem(
          i, 4, new QTableWidgetItem(QString::number(patient.age)));
      ui->list_patitents->setItem(
          i, 5,
          new QTableWidgetItem(QString::fromStdString(patient.municipalitie_)));

      if (patient.sex == Sex::M) {
        ui->list_patitents->setItem(i, 6,
                                    new QTableWidgetItem(QString("Masculino")));
      } else {
        ui->list_patitents->setItem(i, 6,
                                    new QTableWidgetItem(QString("Femenino")));
      }
      ++i;
    }

    if (MainWindow::hospital[num_hward].empty()) {
      ui->num_hward->setStyleSheet(MainWindow::TEXT_BOX_ERROR_STYLES);
      ui->num_hward->clear();
      ui->num_hward->setPlaceholderText(SALA_EMPTY);
    }
  } catch (std::invalid_argument const &e) {
    ui->num_hward->setStyleSheet(MainWindow::TEXT_BOX_ERROR_STYLES);
    ui->num_hward->clear();
    ui->num_hward->setPlaceholderText(e.what());
  }
}

void ListPtients::on_num_hward_textEdited(const QString &arg1) {
  ui->num_hward->setStyleSheet(MainWindow::TEXT_BOX_STYLES);
}
