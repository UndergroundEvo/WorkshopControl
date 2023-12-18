#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    sqllite3.setDatabaseName("D:\\Qt\\WorkshopControlpro\\WorkshopControlpro\\mydatabase.sqlite");
    if (!sqllite3.open()) QMessageBox::information(this, "База", "База не подключилась");
    else QMessageBox::information(this, "База", "База работает");

    QDate dateToday = QDate::currentDate();
    ui->label->setText(dateToday.toString("dd MMMM yyyy"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    loadWorkers();
    loadTasks_active();
    loadTasks();

    int i = modelWorkers->rowCount();
    while(i--){
        ui->comboBox->addItem(modelWorkers->record(i).value("Name").toString());
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::SetToEdit(){
    /*modelTasks = new QSqlTableModel(this, sqllite3);
    modelTasks->setTable("Tasks");
    modelTasks->select();*/
    //int selectedRow = ui->tableView->currentIndex().row();

    int selectedRow = ui->tableView->currentIndex().row();
    qDebug() << selectedRow;
    if (selectedRow < 0){
        ui->lineEdit->setText(" ");
        ui->lineEdit_2->setText(" ");
        ui->lineEdit_3->setText(" ");
        ui->checkBox->setChecked(0);
        ui->plainTextEdit->setPlainText(" ");
        ui->plainTextEdit_2->setPlainText(" ");
        ui->lineEdit_4->setText(" ");
    }
    else {
        ui->lineEdit->setText(modelTasks->record(selectedRow).value("Name").toString());
        QDateTime start_date, end_date;
        //start_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateBegin").toInt());

        if (!modelTasks->record(selectedRow).value("DateEnd").isNull()){
            start_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateBegin").toInt());
            ui->lineEdit_2->setText(start_date.toString("hh:mm dd-MM-yyyy"));
        }
        else ui->lineEdit_2->setText(" ");

        if (!modelTasks->record(selectedRow).value("DateEnd").isNull()) {
            end_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateEnd").toInt());
            ui->lineEdit_3->setText(end_date.toString("hh:mm dd-MM-yyyy"));
        }
        else ui->lineEdit_3->setText(" ");

        //qDebug() << "comp= "<<modelTasks->record(selectedRow).value("Comp").toString();

        if (modelTasks->record(selectedRow).value("Comp").toString()=="1") ui->checkBox->setChecked(true);
        else ui->checkBox->setChecked(false);

        ui->plainTextEdit->setPlainText(modelTasks->record(selectedRow).value("Сontacts").toString());
        ui->plainTextEdit_2->setPlainText(modelTasks->record(selectedRow).value("Info").toString());
        ui->lineEdit_4->setText(modelTasks->record(selectedRow).value("Price").toString());

        qDebug() << "worker= "<< modelTasks->record(selectedRow).value("WorkerKey").toInt();
        ui->comboBox->setCurrentText(GetWorker(modelTasks->record(selectedRow).value("WorkerKey").toInt()-1));
    }
}
QString MainWindow::GetWorker(int i){
    return modelWorkers->record(i).value("Name").toString();
}



void MainWindow::loadWorkers(){
    //QSqlTableModel *modelWorkers;
    modelWorkers = new QSqlTableModel(this, sqllite3);
    modelWorkers->setTable("Workers");
    modelWorkers->select();
    ui->tableView_2->setModel(modelWorkers);
}
void MainWindow::loadTasks(){
    modelTasks = new QSqlTableModel(this, sqllite3);
    modelTasks->setTable("Tasks");
    modelTasks->select();
    ui->tableView->setModel(modelTasks);
}
void MainWindow::loadTasks_active(){
    modelTasks = new QSqlTableModel(this, sqllite3);
    modelTasks->setTable("Tasks");
    modelTasks->setFilter("Comp= 0");
    modelTasks->select();
    int ids = modelTasks->rowCount();
    ui->label_10->setText(QString::number(ids));
    ui->tableView_3->setModel(modelTasks);
}
void MainWindow::showTime(){
    QTime time = QTime::currentTime();
    ui->label_2->setText(time.toString("hh : mm : ss"));
}


void MainWindow::on_pushButton_2_clicked(){
    if (!query.exec("SELECT * FROM Workers")){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }
    else {
        while(query.next()){
            qDebug() << query.record();
        }
    }
}

void MainWindow::on_pushButton_clicked(){
    //task.show();
    qDebug() << "Вставка строки" ;
    modelTasks->insertRows(modelTasks->rowCount(),1);
}

void MainWindow::on_pushButton_3_clicked(){
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0){
        qDebug() << "удал. строку" << modelTasks->removeRows(selectedRow,1);
    }
    else qDebug() << "нет выделенной строки";
}


void MainWindow::on_action_triggered(){
    modelTasks->select();
}

void MainWindow::on_action_2_triggered(){
    SetToEdit();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index){
    SetToEdit();
}

