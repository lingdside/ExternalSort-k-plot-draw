#include "maxkinput.h"
#include "ui_maxkinput.h"
#include<string>
#include "WriteMaxk.h"
#include "PrintGragh.h"
#include "global.h"
#include<iostream>

Maxkinput::Maxkinput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Maxkinput)
{
    ui->setupUi(this);
}

Maxkinput::~Maxkinput()
{
    delete ui;
}

void Maxkinput::on_pushButton_clicked()
{
    std::string mthfilename = ui->lineEdit_mth->text().toStdString();
    int datanum=ui->lineEdit_k->text().toInt();
    WriteMaxk(mthfilename,datanum);
}

void Maxkinput::on_CLOSE_clicked()
{
    this->close();
}

void Maxkinput::on_pushButton_2_clicked()
{
    year_s= ui->lineEdit_yr ->text().toStdString();std::cout<<(&year_s)<<endl;
    readyear=1;
}
