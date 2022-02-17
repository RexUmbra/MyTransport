#include "expanses.h"
#include "ui_expanses.h"

Expanses::Expanses(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Expanses)
{
  ui->setupUi(this);
  ui->row->setValue(-1);
}

Expanses::~Expanses()
{
  delete ui;
}

void Expanses::change(expenses exp, int row)
{
  this->show();
  ui->dT->setValue(exp.dT);
  ui->BelTol->setValue(exp.belTol);
  ui->Platon->setValue(exp.Platon);
  ui->Parking->setValue(exp.parking);
  ui->Zp->setValue(exp.pay);
  ui->Dif->setValue(exp.dif);
  ui->row->setValue(row);
}

void Expanses::on_dT_valueChanged(int arg1)
{
    ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_BelTol_valueChanged(int arg1)
{
     ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_Platon_valueChanged(int arg1)
{
     ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_Parking_valueChanged(int arg1)
{
     ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_Zp_valueChanged(int arg1)
{
     ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_Dif_valueChanged(int arg1)
{
     ui->res->setValue(ui->dT->value()+ui->BelTol->value()+ui->Platon->value()+ui->Parking->value()+ui->Zp->value()+ui->Dif->value());
}


void Expanses::on_pushButton_clicked()
{
  if(ui->row->value()!=-1)
    {
    expenses exp;
    int row = ui->row->value();
    exp.dT = ui->dT->value();
    exp.belTol = ui->BelTol->value();
    exp.Platon = ui->Platon->value();
    exp.parking = ui->Parking->value();
    exp.pay = ui->Zp->value();
    exp.dif = ui->Dif->value();
    exp.result = ui->res->value();
    emit sendDataUpdate(exp, row);
    this->close();
    }
  else
    {
      expenses exp;
      exp.dT = ui->dT->value();
      exp.belTol = ui->BelTol->value();
      exp.Platon = ui->Platon->value();
      exp.parking = ui->Parking->value();
      exp.pay = ui->Zp->value();
      exp.dif = ui->Dif->value();
      exp.result = ui->res->value();
      emit sendDataNew(exp);
      this->close();
    }
}

