#include "taskedit.h"
#include "ui_taskedit.h"

QSqlTableModel *modelWorkers;
//QString str = "DateEnd LIKE '%";
QString str;

TaskEdit::TaskEdit(QWidget *parent) : QDialog(parent), ui(new Ui::TaskEdit){
    ui->setupUi(this);
    ui->comboBox_2->addItem("Больше");
    ui->comboBox_2->addItem("Больше или равно");
    ui->comboBox_2->addItem("Меньше");
    ui->comboBox_2->addItem("Меньше или равно");
    ui->comboBox_2->addItem("Равно");

}
TaskEdit::~TaskEdit(){
    delete ui;
}

QString TaskEdit::ReturnFilter(){
    return str;
}


void TaskEdit::on_lineEdit_editingFinished(){
    if (ui->lineEdit->text()!="")
        QString(str)+"Name LIKE '%"+ui->lineEdit->text()+"%'";

}


void TaskEdit::on_pushButton_clicked(){
    ReturnFilter();
}

