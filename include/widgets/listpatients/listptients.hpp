#ifndef LISTPTIENTS_HPP
#define LISTPTIENTS_HPP

#include <QTableWidgetItem>
#include <QWidget>
#include <memory>
#include <qtablewidget.h>

namespace Ui {
class ListPtients;
}

class ListPtients : public QWidget {
  Q_OBJECT

public:
  explicit ListPtients(QWidget *parent = nullptr);
  ~ListPtients();

  static constexpr char const *LIS_STYLE{"color: rgb(0, 0, 0);"};
  static constexpr char const *SALA_EMPTY{"Esta sala no tiene pacientes"};

private slots:
  void on_ok_btn_clicked();

  void on_num_hward_textEdited(const QString &arg1);

private:
  Ui::ListPtients *ui;
};

#endif // LISTPTIENTS_HPP
