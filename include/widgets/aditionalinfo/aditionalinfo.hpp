#ifndef ADITIONALINFO_HPP
#define ADITIONALINFO_HPP

#include <QWidget>

namespace Ui {
class AditionalInfo;
}

class AditionalInfo : public QWidget {
  Q_OBJECT

public:
  explicit AditionalInfo(QWidget *parent = nullptr);
  ~AditionalInfo();

  static constexpr char const *LE_STYLES{"color: black"};

private:
  Ui::AditionalInfo *ui;

  void setStyleSheet() noexcept;
  void make_table() noexcept;
  void make_list() noexcept;
};

#endif // ADITIONALINFO_HPP
