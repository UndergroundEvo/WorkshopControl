#include "tabletasks.h"
#include "ui_tabletasks.h"

TableTasks::TableTasks(QWidget *parent) : QDialog(parent), ui(new Ui::TableTasks){
    ui->setupUi(this);
}

TableTasks::~TableTasks()
{
    delete ui;
}
