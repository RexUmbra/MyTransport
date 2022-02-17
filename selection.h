#ifndef SELECTION_H
#define SELECTION_H
#include "Struct.h"
#include <QDialog>

namespace Ui {
  class Selection;
}

class Selection : public QDialog
{
  Q_OBJECT

public:
  explicit Selection(QWidget *parent = nullptr);
  ~Selection();

private slots:

  void on_pushButton_clicked();

  void on_Truck_currentIndexChanged(int index);

  void on_trailer_currentIndexChanged(int index);

  void on_Driver_currentIndexChanged(int index);

signals:
  void sendData(tripSelect tr); //сигнал для отправки строки в mainwindow

private:
  Ui::Selection *ui;

};

#endif // SELECTION_H
