#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QAbstractButton>
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget {
  Q_OBJECT

public:
  explicit Login(QWidget *parent = nullptr);
  ~Login();

  static constexpr char const *NAME_STR{"Name"};
  static constexpr char const *LAST_NAME_STR{"Apellido"};
  static constexpr char const *ID_STR{"ID"};
  static constexpr char const *SALA_STR{"Sala (1-15)"};
  static constexpr char const *CAMA_STR{"Cama (1-50)"};
  static constexpr char const *EDAD_STR{"Edad"};
  static constexpr char const *MUNICIPIO_STR_STR{"Municipio"};

private slots:

  void on_ok_btn_clicked();
  void on_ID_le_textEdited(const QString &arg1);
  void on_municipio_le_textEdited(const QString &arg1);
  void on_sala_le_textEdited(const QString &arg1);
  void on_edad_le_textEdited(const QString &arg1);
  void on_last_name_le_textEdited(const QString &arg1);
  void on_cama_le_textEdited(const QString &arg1);
  void on_first_name_le_textEdited(const QString &arg1);

private:
  Ui::Login *ui;

  void setStyleSheet();
  void setPlaceHolderText();
  bool compIsalpha(std::string const &input);
};

#endif // LOGIN_HPP
