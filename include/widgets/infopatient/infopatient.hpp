#ifndef INFOPATIENT_HPP
#define INFOPATIENT_HPP

#include <QWidget>

namespace Ui {
class InfoPatient;
}

class InfoPatient : public QWidget {
  Q_OBJECT

public:
  explicit InfoPatient(QWidget *parent = nullptr);
  ~InfoPatient();

private slots:
  void on_ok_btn_clicked();
  void on_id_patient_textEdited(const QString &arg1);

private:
  Ui::InfoPatient *ui;
};

#endif // INFOPATIENT_HPP
