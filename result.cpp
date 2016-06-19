#include "result.h"
#include "ui_result.h"

Result::Result(bool success ,  QWidget *parent) :
QDialog(parent) , ui(new Ui::Result)
{

    ui->setupUi(this);

    if(success) ui->label->setText("SUCCESS");
    else ui->label->setText("FAIL");

}

Result::~Result(){delete ui;}
