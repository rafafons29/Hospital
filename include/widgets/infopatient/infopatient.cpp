#include "infopatient.hpp"
#include "../../../mainwindow.h"
#include "../listpatients/listptients.hpp"
#include "../login/login.hpp"
#include "ui_infopatient.h"
#include <stdexcept>

InfoPatient::InfoPatient(QWidget *parent)
    : QWidget(parent), ui(new Ui::InfoPatient) {
  ui->setupUi(this);

  ui->list_patitent->setRowCount(1);
  ui->list_patitent->setColumnCount(7);

  ui->id_patient->setPlaceholderText(Login::ID_STR);
  ui->id_patient->setStyleSheet(MainWindow::TEXT_BOX_STYLES);
  ui->list_patitent->setStyleSheet(ListPtients::LIS_STYLE);
}

InfoPatient::~InfoPatient() { delete ui; }

void InfoPatient::on_ok_btn_clicked() {

  try {

    auto id{ui->id_patient->text().toStdString()};
    auto patient = MainWindow::hospital.idAt(id.c_str());

    if (MainWindow::hospital.estaIngresado(id.c_str())) {
      ui->list_patitent->setItem(
          0, 0, new QTableWidgetItem(QString::fromStdString(patient->name_)));
      ui->list_patitent->setItem(
          0, 1,
          new QTableWidgetItem(QString::fromStdString(patient->last_name_)));
      ui->list_patitent->setItem(
          0, 2,
          new QTableWidgetItem(QString::fromStdString(patient->id_.c_str())));
      ui->list_patitent->setItem(
          0, 3, new QTableWidgetItem(QString::number(patient->num_bed_)));
      ui->list_patitent->setItem(
          0, 4, new QTableWidgetItem(QString::number(patient->age)));
      ui->list_patitent->setItem(0, 5,
                                 new QTableWidgetItem(QString::fromStdString(
                                     patient->municipalitie_)));
    }
  } catch (std::invalid_argument const &e) {
    ui->id_patient->setStyleSheet(MainWindow::TEXT_BOX_ERROR_STYLES);
    ui->id_patient->clear();
    ui->id_patient->setPlaceholderText(e.what());
  }
}

void InfoPatient::on_id_patient_textEdited(const QString &arg1) {
  ui->id_patient->setStyleSheet(MainWindow::TEXT_BOX_STYLES);
}
