#include "login.hpp"
#include "../../../mainwindow.h"
#include "../../libraries/hospital/hospital.hpp"
#include "ui_login.h"

#include <algorithm>
#include <ios>
#include <iostream>
#include <qpushbutton.h>
#include <stdexcept>
#include <string>
#include <tuple>

Login::Login(QWidget *parent) : QWidget(parent), ui(new Ui::Login) {
  ui->setupUi(this);

  setStyleSheet();
  setPlaceHolderText();
}

Login::~Login() { delete ui; }

void Login::setStyleSheet() {
  MainWindow::setStyleSheet(ui->first_name_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->last_name_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->ID_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->sala_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->cama_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->edad_le, MainWindow::TEXT_BOX_STYLES);
  MainWindow::setStyleSheet(ui->municipio_le, MainWindow::TEXT_BOX_STYLES);
}

void Login::setPlaceHolderText() {
  ui->first_name_le->clear();
  ui->last_name_le->clear();
  ui->ID_le->clear();
  ui->sala_le->clear();
  ui->cama_le->clear();
  ui->edad_le->clear();
  ui->municipio_le->clear();

  ui->first_name_le->setPlaceholderText(NAME_STR);
  ui->last_name_le->setPlaceholderText(LAST_NAME_STR);
  ui->ID_le->setPlaceholderText(ID_STR);
  ui->sala_le->setPlaceholderText(SALA_STR);
  ui->cama_le->setPlaceholderText(CAMA_STR);
  ui->edad_le->setPlaceholderText(EDAD_STR);
  ui->municipio_le->setPlaceholderText(MUNICIPIO_STR_STR);
}

void Login::on_ok_btn_clicked() {
  if (!ui->first_name_le->text().isEmpty() &&
      !ui->last_name_le->text().isEmpty() && !ui->ID_le->text().isEmpty() &&
      !ui->sala_le->text().isEmpty() && !ui->cama_le->text().isEmpty() &&
      !ui->edad_le->text().isEmpty() && !ui->municipio_le->text().isEmpty() &&
      (ui->M_rbtn->isChecked() || ui->F_rbtn->isChecked())) {

    Sex sex;
    (ui->M_rbtn->isChecked()) ? sex = Sex::M : sex = Sex::F;
    h_parameters data{ui->first_name_le->text().toStdString(),
                      ui->last_name_le->text().toStdString(),
                      ui->municipio_le->text().toStdString(),
                      ui->sala_le->text().toInt(),
                      ui->cama_le->text().toInt(),
                      ui->edad_le->text().toInt(),
                      sex,
                      ui->ID_le->text().toStdString().c_str()};

    try {
      MainWindow::hospital.setPaciente(std::move(data));
      setPlaceHolderText();
      ui->ok_btn->setEnabled(true);
    } catch (std::invalid_argument const &e) {
      auto errorMessage = [](QLineEdit *line, QString const &message) {
        QString style{MainWindow::TEXT_BOX_ERROR_STYLES};
        line->setText("");
        line->setPlaceholderText(message);
        line->setStyleSheet(style);
      };

      if (std::string(e.what()) == std::string(Hospital::SAME_ID))
        errorMessage(ui->ID_le, Hospital::SAME_ID);
      else if (std::string(e.what()) == std::string(Hospital::SAME_SALA_BED))
        errorMessage(ui->cama_le, Hospital::SAME_SALA_BED);
      else if (std::string(e.what()) == std::string(Hospital::SALA_ERROR))
        errorMessage(ui->sala_le, Hospital::SALA_ERROR);
      else if (std::string(e.what()) == std::string(Hospital::BED_ERROR))
        errorMessage(ui->cama_le, Hospital::BED_ERROR);
      else if (std::string(e.what()) == std::string(Hospital::ID_ERROR))
        errorMessage(ui->ID_le, Hospital::ID_ERROR);
      else
        return;
    }
  }
}

bool Login::compIsalpha(std::string const &input) {
  // Comprobar que el string pasado no contiene letras
  for (auto c : input)
    if (std::isalpha(c))
      return false;

  return true;
}

void Login::on_ID_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (!compIsalpha(arg1.toStdString()))
    ui->ID_le->setText("");
}

void Login::on_municipio_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (arg1 == QString(MUNICIPIO_STR_STR))
    ui->municipio_le->setText("");
}

void Login::on_sala_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (!compIsalpha(arg1.toStdString()))
    ui->sala_le->setText("");
}

void Login::on_edad_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (!compIsalpha(arg1.toStdString()))
    ui->edad_le->setText("");
}

void Login::on_last_name_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (arg1 == QString(NAME_STR))
    ui->last_name_le->setText("");
}

void Login::on_cama_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (!compIsalpha(arg1.toStdString()))
    ui->cama_le->setText("");
}

void Login::on_first_name_le_textEdited(const QString &arg1) {
  setStyleSheet();

  if (arg1 == QString(NAME_STR))
    ui->first_name_le->setText("");
}
