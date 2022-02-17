#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Struct.h"
#include "createstring.h"
#include <QMainWindow>
#include "selection.h"
#include "expanses.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QVector<trip> vecTrip;
  QVector<trip> tempVec;
  void updateTable(QVector<trip> vec); //метод для обновления таблицы
  void sortTruck(QVector<trip> vec); //метод для сортировки по тягочу
  void sortN(QVector<trip> vec); //метод для сортировки по номеру формы
  void sortTrailer(QVector<trip> vec); //метод для сортировки по прицепу
  void sortDriver(QVector<trip> vec); //метод для сортировки по водителю
  void sortExit(QVector<trip> vec); //метод для сортировки по месту выезда
  void sortArrive(QVector<trip> vec); //метод для сортировки по месту приезда
  void sortDateExit(QVector<trip> vec); //метод для сортировки по по дате выезда
  void sortDateArrived(QVector<trip> vec); //метод для сортировки по дате приезда
  void sortPaymant(QVector<trip> vec); //метод для сортировки по оплате
  void sortExpenses(QVector<trip> vec); //метод для сортировки по расходам
  bool nB, trackB, trailerB, driverB, exitB, arriveB, dateExitB, dataArriveB, paymentB, expensesB; //обёявление переменных для сортировки в прямом и обратном порядке
  QString intToString(int a); //метод для преобразования числа в строку

signals:
  void openExpanses(expenses exp, int row);

private slots:
  void on_create_clicked(); //обработка нажатия кнопки для вызова окна заполнения формы

  void on_clear_clicked();

  void on_allTrip_clicked();

  void on_table_cellClicked(int row, int column);

public slots:
  void recieveData(trip trp); //метод для принятия заполненной формы
  void getSelectionData(tripSelect trp);
  void updateExpanses(expenses exp, int row);
  void headClicked(int a); // метод для отлова нажатия на название столбца
private:
  Ui::MainWindow *ui;
  CreateString *createStringUi; // интерфейс окна заполнения формы
  Selection *selectionUi;
  Expanses *expansesUi;
};
#endif // MAINWINDOW_H
