#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createstring.h"
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  createStringUi = new CreateString(this); //инициализация интерфейса формы заполнения
  connect(ui->create, SIGNAL(clicked()), createStringUi, SLOT(show())); //перенапрвление сигнала для создания окна формы по нажатию кнопки создания формы
  connect(createStringUi, SIGNAL(sendData(trip)), this, SLOT(recieveData(trip))); //перенапрвление сигнала для принятия данных из формы

  selectionUi = new Selection(this);
  connect(ui->selection, SIGNAL(clicked()), selectionUi, SLOT(show()));
  connect(selectionUi, SIGNAL(sendData(tripSelect)), this, SLOT(getSelectionData(tripSelect)));

  expansesUi = new Expanses(this);
  connect(this, SIGNAL(openExpanses(expenses, int)), expansesUi, SLOT(change(expenses, int)));
  connect(expansesUi, SIGNAL(sendDataUpdate(expenses, int)), this, SLOT(updateExpanses(expenses, int)));

  //ui->table->horizontalHeader()->hide(); //отключение имен строк
  ui->table->verticalHeader()->hide(); //отключение номеров столбцов
  ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет на изменение данных ячеек в самой таблице
  connect(ui->table->horizontalHeader(), SIGNAL(sectionClicked(int)), SLOT(headClicked(int))); //перенаправление сигнала нажатия на имя столбца(для сортировки)
  nB = true, trackB= true, trailerB= true, driverB= true, exitB= true, arriveB= true, dateExitB= true, dataArriveB= true, paymentB= true, expensesB= true; // инициализация переменных для сортировки в прямом и обратном порядке
}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::updateTable(QVector<trip> vec) //метод для обновления таблицы
{
  ui->table->setRowCount(0);
  for(int i = 0; i < vec.length();i++) //цикл прохода по вектору форм
    {
      if(ui->table->rowCount()==i) //если не хватает строки...
        {
          ui->table->insertRow(i); //создаем новую строку в таблице
        }
      ui->table->setItem(i,0, new QTableWidgetItem(intToString(vec[i].n))); //заполение номера в таблице
      ui->table->setItem(i,1, new QTableWidgetItem(vec[i].truck)); //заполение номера тягача в таблице
      ui->table->setItem(i,2, new QTableWidgetItem(vec[i].trailer)); //заполение номера прицепа в таблице
      ui->table->setItem(i,3, new QTableWidgetItem(vec[i].driver)); //заполение ФИ водителя в таблице
      ui->table->setItem(i,4, new QTableWidgetItem(vec[i].exit)); //заполение даты выезда в таблице
      ui->table->setItem(i,5, new QTableWidgetItem(vec[i].arrive)); //заполение даты приезда в таблице
      QString date; //переменная для создания строки даты
      date.push_front(intToString(vec[i].dataExit.year));
      date.push_front(".");
      date.push_front(intToString(vec[i].dataExit.month));
      date.push_front(".");
      date.push_front(intToString(vec[i].dataExit.day));
      ui->table->setItem(i,6, new QTableWidgetItem(date)); //добавление даты выезда в вектор
      date = "";
      date.push_front(intToString(vec[i].dataArrive.year));
      date.push_front(".");
      date.push_front(intToString(vec[i].dataArrive.month));
      date.push_front(".");
      date.push_front(intToString(vec[i].dataArrive.day));
      ui->table->setItem(i,7, new QTableWidgetItem(date));
      ui->table->setItem(i,8, new QTableWidgetItem(vec[i].payment)); //заполение оплаты в таблице
      if(vec[i].idPaymant == 0) ui->table->item(i,8)->setBackground(Qt::green); //цвет оплаты в зависимости от оплаты
      if(vec[i].idPaymant == 1) ui->table->item(i,8)->setBackground(Qt::yellow);
      if(vec[i].idPaymant == 2) ui->table->item(i,8)->setBackground(Qt::red);
      ui->table->setItem(i,9, new QTableWidgetItem(intToString(vec[i].expens.result))); //заполение расходов в таблице
    }
  tempVec.clear();
}

void MainWindow::sortN(QVector<trip> vec) //сортировка по номеру
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          if(vec[j].n > vec[j+1].n && nB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].n < vec[j+1].n && !nB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  nB = !nB;
  updateTable(vec);
}

void MainWindow::sortTrailer(QVector<trip> vec) //сортировка по прицепу
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          int n = 0;
          while(vec[j].trailer[n] == vec[j+1].trailer[n])
            {
              n++;
            }
          if(vec[j].trailer[n] > vec[j+1].trailer[n] && trailerB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].trailer[n] < vec[j+1].trailer[n] && !trailerB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  trailerB = !trailerB;
  updateTable(vec);
}

void MainWindow::sortDriver(QVector<trip> vec) //сортировка по водителю
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          int n = 0;
          while(vec[j].driver[n] == vec[j+1].driver[n])
            {
              n++;
            }
          if(vec[j].driver[n] > vec[j+1].driver[n] && driverB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].driver[n] < vec[j+1].driver[n] && !driverB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  driverB = !driverB;
  updateTable(vec);
}

void MainWindow::sortExit(QVector<trip> vec) //сортировка по месту выезда
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          int n = 0;
          while(vec[j].exit[n] == vec[j+1].exit[n])
            {
              n++;
            }
          if(vec[j].exit[n] > vec[j+1].exit[n] && exitB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].exit[n] < vec[j+1].exit[n] && !exitB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  exitB = !exitB;
  updateTable(vec);
}

void MainWindow::sortArrive(QVector<trip> vec) //сортировка по месту приезда
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          int n = 0;
          while(vec[j].arrive[n] == vec[j+1].arrive[n])
            {
              n++;
            }
          if(vec[j].arrive[n] > vec[j+1].arrive[n] && arriveB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].arrive[n] < vec[j+1].arrive[n] && !arriveB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  arriveB = !arriveB;
  updateTable(vec);
}

void MainWindow::sortDateExit(QVector<trip> vec) //сортировка по дате выезда
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          if(vec[j].dataExit.year != vec[j+1].dataExit.year)
            {
              if(vec[j].dataExit.year > vec[j+1].dataExit.year && dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataExit.year < vec[j+1].dataExit.year && !dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
          else if(vec[j].dataExit.month != vec[j+1].dataExit.month)
            {
              if(vec[j].dataExit.month > vec[j+1].dataExit.month && dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataExit.month < vec[j+1].dataExit.month && !dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
          else
            {
              if(vec[j].dataExit.day > vec[j+1].dataExit.day && dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataExit.day < vec[j+1].dataExit.day && !dateExitB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
        }
    }
  dateExitB = !dateExitB;
  updateTable(vec);
}

void MainWindow::sortDateArrived(QVector<trip> vec) //сортировка по дате приезда
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          if(vec[j].dataArrive.year != vec[j+1].dataArrive.year)
            {
              if(vec[j].dataArrive.year > vec[j+1].dataArrive.year && dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataArrive.year < vec[j+1].dataArrive.year && !dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
          else if(vec[j].dataArrive.month != vec[j+1].dataArrive.month)
            {
              if(vec[j].dataArrive.month > vec[j+1].dataArrive.month && dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataArrive.month < vec[j+1].dataArrive.month && !dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
          else
            {
              if(vec[j].dataArrive.day > vec[j+1].dataArrive.day && dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
              if(vec[j].dataArrive.day < vec[j+1].dataArrive.day && !dataArriveB)
                {
                  qSwap(vec[j],vec[j+1]);
                }
            }
        }
    }
  dataArriveB = !dataArriveB;
  updateTable(vec);
}

void MainWindow::sortPaymant(QVector<trip> vec) //сортировка по оплате
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          if(vec[j].idPaymant > vec[j+1].idPaymant && paymentB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].idPaymant < vec[j+1].idPaymant && !paymentB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  paymentB = !paymentB;
  updateTable(vec);
}

void MainWindow::sortExpenses(QVector<trip> vec) //сортировка по расходам
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          if(vec[j].expens.result > vec[j+1].expens.result && expensesB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].expens.result < vec[j+1].expens.result && !expensesB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  expensesB = !expensesB;
  updateTable(vec);
}

void MainWindow::sortTruck(QVector<trip> vec) // сортировка по тягачу
{
  for(int i = 0; i < vec.length()-1;i++)
    {
      for(int j = 0; j < vec.length()-i-1;j++)
        {
          int n = 0;
          while(vec[j].truck[n] == vec[j+1].truck[n])
            {
              n++;
            }
          if(vec[j].truck[n] > vec[j+1].truck[n] && trackB)
            {
              qSwap(vec[j],vec[j+1]);
            }
          if(vec[j].truck[n] < vec[j+1].truck[n] && !trackB)
            {
              qSwap(vec[j],vec[j+1]);
            }
        }
    }
  trackB = !trackB;
  updateTable(vec);
}



void MainWindow::on_create_clicked() //метод для отлова нажатия на кнопку добавления формы
{

}

void MainWindow::recieveData(trip trp) //метод для приема данных с окна формы
{
  vecTrip.push_back(trp);
  updateTable(vecTrip);
}

void MainWindow::getSelectionData(tripSelect trp)
{
  for(int i = 0; i < vecTrip.length();i++)
    {
      if((vecTrip[i].n == trp.n || trp.n == 0) && (vecTrip[i].truck == trp.truck || trp.truck == "-") && (vecTrip[i].trailer == trp.trailer || trp.trailer == "-") &&
          (vecTrip[i].driver == trp.driver || trp.driver == "-") && (vecTrip[i].exit == trp.exit || trp.exit == "") && (vecTrip[i].arrive == trp.arrive || trp.arrive == "") &&
            ( ( (trp.dataExitFrom.day <= vecTrip[i].dataExit.day  && vecTrip[i].dataExit.day <= trp.dataExitBefore.day) &&
                (trp.dataExitFrom.month <= vecTrip[i].dataExit.month  && vecTrip[i].dataExit.month <= trp.dataExitBefore.month) &&
                (trp.dataExitFrom.year <= vecTrip[i].dataExit.year  && vecTrip[i].dataExit.year <= trp.dataExitBefore.year) ) || !trp.exitAgg) &&
            ( ( (trp.dataArriveFrom.day <= vecTrip[i].dataArrive.day  && vecTrip[i].dataArrive.day <= trp.dataArriveBefore.day) &&
                (trp.dataArriveFrom.month <= vecTrip[i].dataArrive.month  && vecTrip[i].dataArrive.month <= trp.dataArriveBefore.month) &&
                (trp.dataArriveFrom.year <= vecTrip[i].dataArrive.year  && vecTrip[i].dataArrive.year <= trp.dataArriveBefore.year) ) || !trp.ArriveAgg) &&
          (vecTrip[i].payment == trp.payment || trp.payment == "-"))
        {
          tempVec.push_back(vecTrip[i]);
        }
    }
  updateTable(tempVec);
}

void MainWindow::updateExpanses(expenses exp, int row)
{
  vecTrip[row].expens = exp;
  ui->table->setItem(row,9, new QTableWidgetItem(intToString(exp.result)));
}

QString MainWindow::intToString(int a) //метод для преобразования инт в стринг
{
  QString str;
  while(a!=0)
    {
      if(a%10 == 0)
        str.push_front("0");
      else if(a%10 == 1)
        str.push_front("1");
      else if(a%10 == 2)
        str.push_front("2");
      else if(a%10 == 3)
        str.push_front("3");
      else if(a%10 == 4)
        str.push_front("4");
      else if(a%10 == 5)
        str.push_front("5");
      else if(a%10 == 6)
        str.push_front("6");
      else if(a%10 == 7)
        str.push_front("7");
      else if(a%10 == 8)
        str.push_front("8");
      else if(a%10 == 9)
        str.push_front("9");
      a/=10;
    }
  return str;
}

void MainWindow::headClicked(int a) //обработка нажатий на название колонок для сортировки
{
  if(a == 0) sortN(vecTrip);
  if(a == 1) sortTruck(vecTrip);
  if(a == 2) sortTrailer(vecTrip);
  if(a == 3) sortDriver(vecTrip);
  if(a == 4) sortExit(vecTrip);
  if(a == 5) sortArrive(vecTrip);
  if(a == 6) sortDateExit(vecTrip);
  if(a == 7) sortDateArrived(vecTrip);
  if(a == 8) sortPaymant(vecTrip);
}

void MainWindow::on_clear_clicked()
{
    ui->table->setRowCount(0);
}


void MainWindow::on_allTrip_clicked()
{
    ui->table->setRowCount(0);
    updateTable(vecTrip);
}


void MainWindow::on_table_cellClicked(int row, int column)
{
    if(column == 9)
      {
        emit openExpanses(vecTrip[row].expens, row);
      }
}

