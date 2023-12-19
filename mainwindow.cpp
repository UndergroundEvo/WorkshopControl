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
    on_action_triggered();
    //modelTasks->setEditStrategy(QSqlTableModel::OnFieldChange);


}

void MainWindow::UpdateWorkers(){
    int i = modelWorkers->rowCount();
    ui->comboBox->clear();
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
        //QDateTime start_date, end_date;
        //start_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateBegin").toInt());
        /*
        if (!modelTasks->record(selectedRow).value("DateEnd").isNull()){
            start_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateBegin").toInt());
            ui->lineEdit_2->setText(start_date.toString("hh:mm dd-MM-yyyy"));
        }
        else ui->lineEdit_2->setText(" ");

        if (!modelTasks->record(selectedRow).value("DateEnd").isNull()) {
            end_date.setSecsSinceEpoch(modelTasks->record(selectedRow).value("DateEnd").toInt());
            ui->lineEdit_3->setText(end_date.toString("hh:mm dd-MM-yyyy"));
        }
        else ui->lineEdit_3->setText(" ");*/

        ui->lineEdit_2->setText(modelTasks->record(selectedRow).value("DateBegin").toString());
        ui->lineEdit_3->setText(modelTasks->record(selectedRow).value("DateEnd").toString());

        //qDebug() << "comp= "<<modelTasks->record(selectedRow).value("Comp").toString();

        if (modelTasks->record(selectedRow).value("Comp").toString()=="1") ui->checkBox->setChecked(true);
        else ui->checkBox->setChecked(false);

        ui->plainTextEdit->setPlainText(modelTasks->record(selectedRow).value("Сontacts").toString());
        ui->plainTextEdit_2->setPlainText(modelTasks->record(selectedRow).value("Info").toString());
        ui->lineEdit_4->setText(modelTasks->record(selectedRow).value("Price").toString());

        //qDebug() << "worker= "<< modelTasks->record(selectedRow).value("WorkerKey").toInt();
        if (modelTasks->record(selectedRow).value("WorkerKey").toInt()!=0)
            ui->comboBox->setCurrentText(GetWorker(modelTasks->record(selectedRow).value("WorkerKey").toInt()-1));
        else ui->comboBox->setCurrentText(" ");


        //QPixmap img = (QString(":images/imgs/")+modelTasks->record(selectedRow).value("IMG").toString());
        QPixmap img = (modelTasks->record(selectedRow).value("IMG").toString());

        ui->label_11->setPixmap(img);
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
    qDebug() << "check today: " << QString("DateEnd LIKE '%" + QDate::currentDate().toString("dd-MM-yyyy") + "%'");
    //modelTasks->setFilter(QString("DateEnd= ")+QDateTime::currentDateTime().toString("hh:mm dd-MM-yyyy"));

    modelTasks->setFilter(QString("DateEnd LIKE '%" + QDate::currentDate().toString("dd-MM-yyyy") + "%'"));
    modelTasks->select();

    int dsd = modelTasks->rowCount();
    ui->label_14->setText(QString::number(dsd));

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




void MainWindow::on_pushButton_clicked(){
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
    loadWorkers();
    loadTasks_active();
    loadTasks();
    UpdateWorkers();
    modelTasks->select();
}

void MainWindow::on_action_2_triggered(){
    SetToEdit();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index){
    SetToEdit();
}

    QString filename;
void MainWindow::on_pushButton_4_clicked(){
    QFileDialog dialog(this, "Выберите изображение");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Изображения (*.png *.jpg)"));
    if (dialog.exec()) {
        filename = dialog.selectedFiles().first();
        QPixmap pixmap(filename);
        ui->label_11->setPixmap(pixmap);
    }
    qDebug() <<"filename= "<< filename;
    modelTasks->record(ui->tableView->currentIndex().row()).setValue("IMG",filename);

    QSqlRecord rec = modelTasks->record(ui->tableView->currentIndex().row());
    rec.setValue("IMG",filename);
    modelTasks->setRecord(ui->tableView->currentIndex().row(),rec);

    if (!modelTasks->submitAll()) {
        qDebug() << modelTasks->lastError().text();
    }
}


void MainWindow::on_pushButton_7_clicked(){
    qDebug() <<"cur ROW= "<< ui->tableView->currentIndex().row();
    qDebug() <<"else= "<< ui->lineEdit->text();
    //modelTasks->record(ui->tableView->currentIndex().row()).value("Name").setValue(ui->lineEdit->text());

    QSqlRecord rec = modelTasks->record(ui->tableView->currentIndex().row());

    QDateTime dateTime = QDateTime::fromString(ui->lineEdit_2->text(), "hh:mm dd-MM-yyyy");
    if(dateTime.isValid()) rec.setValue("DateBegin",ui->lineEdit_2->text());
    else {
        QMessageBox::information(this, "Ошибка", "Неправильный формат Времени заявки [hh:mm dd-MM-yyyy] \nБудет вставлено сегодня");
        rec.setValue("DateBegin",QDateTime::currentDateTime().toString("hh:mm dd-MM-yyyy"));
    }
    QDateTime::fromString(ui->lineEdit_3->text(), "hh:mm dd-MM-yyyy");
    if(dateTime.isValid()) rec.setValue("DateBegin",ui->lineEdit_3->text());
    else {
        QMessageBox::information(this, "Ошибка", "Неправильный формат Срок сдачи [hh:mm dd-MM-yyyy] \nБудет вставлено завтра");
        QDateTime chk = QDateTime::currentDateTime().addDays(1);
        rec.setValue("DateEnd",chk.toString("hh:mm dd-MM-yyyy"));
    }
    if (QDateTime::fromString(ui->lineEdit_2->text(),"hh:mm dd-MM-yyyy")>QDateTime::fromString(ui->lineEdit_3->text(), "hh:mm dd-MM-yyyy")){
        QMessageBox::information(this, "Ошибка", "Дата сдачи стоит раньше даты времени заявки");
        QVariant ds = ui->lineEdit_2->text(); //begin
        QVariant dfs = ui->lineEdit_3->text(); //endf
        rec.setValue("DateBegin",dfs);
        rec.setValue("DateEnd",ds);
    }

    if (ui->checkBox->isChecked()) rec.setValue("Comp","1");
    else rec.setValue("Comp","0");

    //qDebug() <<"pixmap= "<< modelTasks->record(ui->tableView->currentIndex().row()).value("IMG").toString();

    rec.setValue("Name",ui->lineEdit->text());
    rec.setValue("Info",ui->plainTextEdit_2->toPlainText());
    rec.setValue("Сontacts",ui->plainTextEdit->toPlainText());

    modelTasks->setRecord(ui->tableView->currentIndex().row(),rec);
    if (!modelTasks->submitAll()) {
        qDebug() << modelTasks->lastError().text();
    }
}


void MainWindow::on_pushButton_6_clicked(){
    qDebug() << "Вставка строки" ;
    modelWorkers->insertRows(modelWorkers->rowCount(),1);
}
void MainWindow::on_pushButton_2_clicked(){
    /*if (!query.exec("SELECT * FROM Workers")){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }
    else {
        while(query.next()){
            qDebug() << query.record();
        }
    }*/
    int selectedRow = ui->tableView_2->currentIndex().row();
    if (selectedRow >= 0){
        qDebug() << "удал. строку" << modelWorkers->removeRows(selectedRow,1);
    }
    else qDebug() << "нет выделенной строки";
}

void MainWindow::on_action_3_triggered(){
    QFileDialog dialog(this, "Выберите путь до базы");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("База (*.sqlite)"));
    if (dialog.exec()) {
        QString f2ilename = dialog.selectedFiles().first();
        sqllite3.setDatabaseName(f2ilename);
    }
}

