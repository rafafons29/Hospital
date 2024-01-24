#include "hospitalward.hpp"
#include "ui_hospitalward.h"

#include "../../../mainwindow.h"
#include <qpushbutton.h>
#include <string>

HospitalWard::HospitalWard(QWidget *parent)
    : QWidget(parent), ui(new Ui::HospitalWard) {
  ui->setupUi(this);
}

HospitalWard::~HospitalWard() { delete ui; }
