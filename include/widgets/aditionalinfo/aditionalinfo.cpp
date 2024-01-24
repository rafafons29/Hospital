#include "aditionalinfo.hpp"
#include "../../../mainwindow.h"
#include "../listpatients/listptients.hpp"
#include "ui_aditionalinfo.h"

AditionalInfo::AditionalInfo(QWidget *parent)
    : QWidget(parent), ui(new Ui::AditionalInfo) {
  ui->setupUi(this);

  setStyleSheet();
  make_list();
  make_table();

  ui->t_hombres_v_le->setText(QString::number(MainWindow::hospital.cantMan()));
  ui->t_mujeres_v_le->setText(
      QString::number(MainWindow::hospital.cantWoman()));
}

AditionalInfo::~AditionalInfo() { delete ui; }

void AditionalInfo::setStyleSheet() noexcept {
  ui->t_hombres_le->setStyleSheet(LE_STYLES);
  ui->t_mujeres_le->setStyleSheet(LE_STYLES);
  ui->t_hombres_v_le->setStyleSheet(LE_STYLES);
  ui->t_mujeres_v_le->setStyleSheet(LE_STYLES);
  ui->mun_max_ing_le->setStyleSheet(LE_STYLES);
  ui->t_hombres_v_le->setStyleSheet(LE_STYLES);
  ui->pac_edad_sup_le->setStyleSheet(LE_STYLES);
  ui->municipios_listw->setStyleSheet(ListPtients::LIS_STYLE);
  ui->pac_edad_sup_inf_tw->setStyleSheet(ListPtients::LIS_STYLE);
}
void AditionalInfo::make_table() noexcept {
  ui->pac_edad_sup_inf_tw->setRowCount(
      MainWindow::hospital.getEdadEncimaMedia().size());
  ui->pac_edad_sup_inf_tw->setColumnCount(7);

  for (auto &patient : MainWindow::hospital.getEdadEncimaMedia()) {
    ui->pac_edad_sup_inf_tw->setItem(
        0, 0, new QTableWidgetItem(QString::fromStdString(patient->name_)));
    ui->pac_edad_sup_inf_tw->setItem(
        0, 1,
        new QTableWidgetItem(QString::fromStdString(patient->last_name_)));
    ui->pac_edad_sup_inf_tw->setItem(
        0, 2,
        new QTableWidgetItem(QString::fromStdString(patient->id_.c_str())));
    ui->pac_edad_sup_inf_tw->setItem(
        0, 3, new QTableWidgetItem(QString::number(patient->num_bed_)));
    ui->pac_edad_sup_inf_tw->setItem(
        0, 4, new QTableWidgetItem(QString::number(patient->age)));
    ui->pac_edad_sup_inf_tw->setItem(
        0, 5,
        new QTableWidgetItem(QString::fromStdString(patient->municipalitie_)));
  }
}
void AditionalInfo::make_list() noexcept {
  for (auto &max_ing : MainWindow::hospital.maxMunicipalitie())
    ui->municipios_listw->addItem(QString::fromStdString(max_ing->c_str()));
}