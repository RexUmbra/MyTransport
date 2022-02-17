#ifndef CREATESTRING_H
#define CREATESTRING_H
#include <QDialog>
#include "QTime"
#include "Struct.h"
#include "expanses.h"
namespace Ui {
  class CreateString;
}

class CreateString : public QDialog
{
  Q_OBJECT

public:
  explicit CreateString(QWidget *parent = nullptr);
  int n = 0; //номер строки
  ~CreateString();
  trip trp; // объект структуры для заполнения формы



private:
  Ui::CreateString *ui;
  Expanses *expansesUi;
  expenses tempExp;

signals:
  void sendData(trip tr); //сигнал для отправки строки в mainwindow
private slots:
  void on_pushButton_clicked(bool a); //обработка нажатия на кнопку для отправки формы
  void tempData(expenses exp);
  void on_Truck_currentIndexChanged(int index); //метод для смены значения прицепа и водителя при смене тягоча
  void on_trailer_currentIndexChanged(int index); //метод для смены значения тягоча и водителя при смене прицепа
  void on_Driver_currentIndexChanged(int index); //метод для смены значения прицепа и тягоча при смене водителя

  void on_ExpansesAdd_clicked();
};

#endif // CREATESTRING_H
