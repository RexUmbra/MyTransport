#include "selection.h"
#include "ui_selection.h"

Selection::Selection(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Selection)
{
  ui->setupUi(this);
  ui->dateExitFrom->setDate(QDate::currentDate());
  ui->dateExitBefore->setDate(QDate::currentDate());
  ui->dateArriveFrom->setDate(QDate::currentDate());
  ui->dateArriveBefore->setDate(QDate::currentDate());
}

Selection::~Selection()
{
  delete ui;
}


void Selection::on_pushButton_clicked()
{
  tripSelect trp;
  trp.truck = ui->Truck->currentText(); //сбор данных тягача
  trp.trailer = ui->trailer->currentText(); //сбор данных прицепа
  trp.n = ui->no->value(); //сбор номера формы
  trp.driver = ui->Driver->currentText(); //сбор данных водителя
  trp.exit = ui->exit->text(); //сбор данных места выезда
  trp.arrive = ui->arrival->text(); //сбор данных места приезда

  trp.exitAgg = ui->dataExitAgg->checkState();
  trp.ArriveAgg = ui->dataArriveAgg->checkState();

  trp.dataExitFrom.day = ui->dateExitFrom->date().day();  //сбор данных дня выезда
  trp.dataExitFrom.month = ui->dateExitFrom->date().month();//сбор данных месяца выезда
  trp.dataExitFrom.year = ui->dateExitFrom->date().year(); //сбор данных года выезда

  trp.dataExitBefore.day = ui->dateExitBefore->date().day();  //сбор данных дня выезда
  trp.dataExitBefore.month = ui->dateExitBefore->date().month();//сбор данных месяца выезда
  trp.dataExitBefore.year = ui->dateExitBefore->date().year(); //сбор данных года выезда

  trp.dataArriveFrom.day = ui->dateArriveFrom->date().day();  //сбор данных дня выезда
  trp.dataArriveFrom.month = ui->dateArriveFrom->date().month();//сбор данных месяца выезда
  trp.dataArriveFrom.year = ui->dateArriveFrom->date().year(); //сбор данных года выезда

  trp.dataArriveBefore.day = ui->dateArriveBefore->date().day();  //сбор данных дня выезда
  trp.dataArriveBefore.month = ui->dateArriveBefore->date().month();//сбор данных месяца выезда
  trp.dataArriveBefore.year = ui->dateArriveBefore->date().year(); //сбор данных года выезда

  trp.payment = ui->payment->currentText(); //сбор данных об оплате
  trp.idPaymant = ui->payment->currentIndex(); //сбор id об оплаты
  //trp.expenses = ui->expenses->text().toInt(); //сбор данных расходах
  emit sendData(trp); //эмитация сигнала отправки
  QWidget::close(); //закрытие формы
}




void Selection::on_Truck_currentIndexChanged(int index)
{
  ui->trailer->setCurrentIndex(index);
  ui->Driver->setCurrentIndex(index);
}


void Selection::on_trailer_currentIndexChanged(int index)
{
  ui->Truck->setCurrentIndex(index);
  ui->Driver->setCurrentIndex(index);
}


void Selection::on_Driver_currentIndexChanged(int index)
{
  ui->trailer->setCurrentIndex(index);
  ui->Truck->setCurrentIndex(index);
}

