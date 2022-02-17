#ifndef STRUCT_H
#define STRUCT_H
#include <QApplication>
struct data //структура дата
{
  int day, month, year;
};

struct tripSelect
{
  int n = 0, idPaymant; //n - номер формы //expenses - расходы(переделать в отдельную структуру) //idPaymant - id оплаты(для сортировки)
  QString truck, trailer,exit,arrive,driver, payment; //truck - номер тягача // trailer - номер прицепа //exit - место выезда //arrive - место приезда //driver - ФИ водителя //payment - строка оплаты
  data dataExitFrom, dataExitBefore, dataArriveFrom, dataArriveBefore;
  bool exitAgg,ArriveAgg;
};

struct expenses
{
  int dT, belTol, Platon, parking, pay, dif, result;
  expenses();
};

struct trip
  {
    int n = 0, idPaymant; //n - номер формы //expenses - расходы(переделать в отдельную структуру) //idPaymant - id оплаты(для сортировки)
    QString truck, trailer,exit,arrive,driver, payment; //truck - номер тягача // trailer - номер прицепа //exit - место выезда //arrive - место приезда //driver - ФИ водителя //payment - строка оплаты
    data dataExit, dataArrive; //переменные даты выезда и приезда
    expenses expens;
};




#endif // STRUCT_H
