#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "include/libraries/hospital/hospital.hpp"
#include "include/widgets/aditionalinfo/aditionalinfo.hpp"
#include "include/widgets/hospitalward/hospitalward.hpp"
#include "include/widgets/infopatient/infopatient.hpp"
#include "include/widgets/listpatients/listptients.hpp"
#include "include/widgets/login/login.hpp"

#include <iostream>

Hospital MainWindow::hospital{};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  buttons.at(0) = ui->add_pasient_btn;
  buttons.at(1) = ui->aditional_inf_btn;
  buttons.at(2) = ui->show_id_info_btn;
  buttons.at(3) = ui->show_sala_info_btn;

  setStyleSheet(ui->menu, MENU_BAR_STYLES);
  setStyleSheet(ui->add_pasient_btn, MENU_BOOTONS_STYLES);
  setStyleSheet(ui->aditional_inf_btn, MENU_BOOTONS_STYLES);
  setStyleSheet(ui->show_id_info_btn, MENU_BOOTONS_STYLES);
  setStyleSheet(ui->show_sala_info_btn, MENU_BOOTONS_STYLES);
}

MainWindow::~MainWindow() {
  delete ui;
  destroy_all();
}

void MainWindow::on_add_pasient_btn_clicked() {
  destroy_all();
  set_color(ui->add_pasient_btn);

  login = new Login(this);
  showWidget(login);
}

void MainWindow::set_color(QPushButton *btn) noexcept {
  static constexpr char const *style_active{
      "background-color: #58587C;color: #ffffff; border: 0px;"};

  btn->setStyleSheet(style_active);
  for (auto *button : buttons) {
    if (button->styleSheet().toStdString() == style_active && btn != button) {
      button->setStyleSheet(MENU_BOOTONS_STYLES);
      return;
    }
  }
}

void MainWindow::on_show_sala_info_btn_clicked() {
  destroy_all();
  set_color(ui->show_sala_info_btn);

  list_patients = new ListPtients(this);
  showWidget(list_patients);
}

void MainWindow::on_show_id_info_btn_clicked() {
  destroy_all();
  set_color(ui->show_id_info_btn);

  info_patient = new InfoPatient(this);
  showWidget(info_patient);
}

void MainWindow::on_aditional_inf_btn_clicked() {
  destroy_all();
  set_color(ui->aditional_inf_btn);

  aditional_info = new AditionalInfo(this);
  showWidget(aditional_info);
}

void MainWindow::destroy_all() {

  if (login != nullptr) {
    delete login;
    login = nullptr;
  } else if (hospital_ward != nullptr) {
    delete hospital_ward;
    hospital_ward = nullptr;
  } else if (list_patients != nullptr) {
    delete list_patients;
    list_patients = nullptr;
  } else if (info_patient != nullptr) {
    delete info_patient;
    info_patient = nullptr;
  } else if (aditional_info != nullptr) {
    delete aditional_info;
    aditional_info = nullptr;
  } else
    return;
}
