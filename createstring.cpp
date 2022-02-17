#include "createstring.h"
#include "ui_createstring.h"

CreateString::CreateString(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CreateString)
{
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked())); //сигнал на обработку нажатия на кнопку для отправки формы
  ui->dateExit->setDate(QDate::currentDate()); //установка сегоднешней даты в строку отправки
  ui->dateArrive->setDate(QDate::currentDate()); //установка сегоднешней даты в строку приезда

  expansesUi = new Expanses(this);
  connect(ui->ExpansesAdd, SIGNAL(clicked()), expansesUi, SLOT(show()));
  connect(expansesUi, SIGNAL(sendDataNew(expenses)), this, SLOT(tempData(expenses)));
}

CreateString::~CreateString()
{
  delete ui;
}



void CreateString::on_pushButton_clicked(bool a) //метод для сбора и отправки формы
{
    n++; // переменная для номера формы
    trp.truck = ui->Truck->currentText(); //сбор данных тягача
    trp.trailer = ui->trailer->currentText(); //сбор данных прицепа
    trp.n = n; //сбор номера формы
    trp.driver = ui->Driver->currentText(); //сбор данных водителя
    trp.exit = ui->exit->text(); //сбор данных места выезда
    trp.arrive = ui->arrival->text(); //сбор данных места приезда
    trp.dataExit.day = ui->dateExit->date().day();  //сбор данных дня выезда
    trp.dataExit.month = ui->dateExit->date().month();//сбор данных месяца выезда
    trp.dataExit.year = ui->dateExit->date().year(); //сбор данных года выезда
    trp.dataArrive.day = ui->dateArrive->date().day(); //сбор данных дня приезда
    trp.dataArrive.month = ui->dateArrive->date().month(); //сбор данных месяца приезда
    trp.dataArrive.year = ui->dateArrive->date().year(); //сбор данных года приезда
    trp.payment = ui->payment->currentText(); //сбор данных об оплате
    trp.idPaymant = ui->payment->currentIndex(); //сбор id об оплаты

    trp.expens = tempExp; //сбор данных расходах
    emit sendData(trp); //эмитация сигнала отправки
    QWidget::close(); //закрытие формы
}

void CreateString::tempData(expenses exp)
{
  tempExp = exp;
}





void CreateString::on_Truck_currentIndexChanged(int index) //метод для смены значения прицепа и водителя при смене тягоча
{
    ui->trailer->setCurrentIndex(index);
    ui->Driver->setCurrentIndex(index);
}


void CreateString::on_trailer_currentIndexChanged(int index) //метод для смены значения тягоча и водителя при смене прицепа
{
  ui->Truck->setCurrentIndex(index);
  ui->Driver->setCurrentIndex(index);
}


void CreateString::on_Driver_currentIndexChanged(int index) //метод для смены значения прицепа и тягоча при смене водителя
{
  ui->trailer->setCurrentIndex(index);
  ui->Truck->setCurrentIndex(index);
}



void CreateString::on_ExpansesAdd_clicked()
{

}

