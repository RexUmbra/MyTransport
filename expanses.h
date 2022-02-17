#ifndef EXPANSES_H
#define EXPANSES_H
#include "Struct.h"
#include <QDialog>

namespace Ui {
  class Expanses;
}

class Expanses : public QDialog
{
  Q_OBJECT

public:
  explicit Expanses(QWidget *parent = nullptr);
  ~Expanses();

signals:
  void sendDataUpdate(expenses exp, int row);
  void sendDataNew(expenses exp);

public slots:
  void change(expenses exp, int row);

private slots:
  void on_dT_valueChanged(int arg1);

  void on_BelTol_valueChanged(int arg1);

  void on_Platon_valueChanged(int arg1);

  void on_Parking_valueChanged(int arg1);

  void on_Zp_valueChanged(int arg1);

  void on_Dif_valueChanged(int arg1);

  void on_pushButton_clicked();

private:
  Ui::Expanses *ui;
};

#endif // EXPANSES_H
