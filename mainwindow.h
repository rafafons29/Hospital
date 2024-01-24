#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./include/libraries/hospital/hospital.hpp"
#include "./include/widgets/aditionalinfo/aditionalinfo.hpp"
#include "./include/widgets/hospitalward/hospitalward.hpp"
#include "./include/widgets/infopatient/infopatient.hpp"
#include "./include/widgets/listpatients/listptients.hpp"
#include "./include/widgets/login/login.hpp"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  template <typename QTYPE> static void setStyleSheet(QTYPE *, QString const &);

  static Hospital hospital;
  static constexpr char const *MENU_BAR_STYLES{
      "background-color: rgb(22, 22, 34);border: none;"};
  static constexpr char const *MENU_BOOTONS_STYLES{
      "background-color: rgb(22, 22, 34);color: rgb(223, 223, 223);"
      "border: none;"};
  static constexpr char const *TEXT_BOX_STYLES{
      "background-color: #2E2F44;color: #A599BF;"
      "padding: 3px 50px 3px 10px"};
  static constexpr char const *TEXT_BOX_ERROR_STYLES{
      "background-color: #2E2F44;color: red;"
      "padding: 3px 50px 3px 10px"};

private slots:
  void on_add_pasient_btn_clicked();
  void on_show_sala_info_btn_clicked();
  void on_show_id_info_btn_clicked();
  void on_aditional_inf_btn_clicked();

  void set_color(QPushButton *) noexcept;

private:
  Ui::MainWindow *ui;
  Login *login{nullptr};
  HospitalWard *hospital_ward{nullptr};
  ListPtients *list_patients{nullptr};
  InfoPatient *info_patient{nullptr};
  AditionalInfo *aditional_info{nullptr};
  std::array<QPushButton *, 4> buttons;

  void destroy_all();
  template <typename PTR> void showWidget(PTR *) noexcept;
};

template <typename QTYPE>
void MainWindow::setStyleSheet(QTYPE *q_element, QString const &style) {
  q_element->setStyleSheet(style);
}

template <typename PTR> void MainWindow::showWidget(PTR *ptr) noexcept {
  ptr->setGeometry(QRect(QPoint(200, 20), QSize(731, 671)));
  ptr->show();
}

#endif // MAINWINDOW_H
