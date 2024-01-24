#ifndef HOSPITALWARD_HPP
#define HOSPITALWARD_HPP

#include <vector>

#include <QPushButton>
#include <QWidget>

namespace Ui {
class HospitalWard;
}

class HospitalWard : public QWidget {
  Q_OBJECT

public:
  explicit HospitalWard(QWidget *parent = nullptr);
  ~HospitalWard();

private:
  Ui::HospitalWard *ui;
  std::vector<QPushButton> buttons;
};

#endif // HOSPITALWARD_HPP
