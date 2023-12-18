#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QListWidget>
#include <QFile>
#include <QPixmap>
#include <QGraphicsView>
#include <QFileDialog>

#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlField>
#include <QtSql/QSqlRelation>

#include "taskedit.h"
//#include "tabletasks.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    QSqlDatabase sqllite3 = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery query = QSqlQuery(sqllite3);
    QSqlTableModel* modelTasks;
    QSqlTableModel *modelWorkers;

    TaskEdit task;
    //TableTasks tabletask;


    void loadTasks();
    void loadWorkers();
    void loadTasks_active();
    QString GetWorker(int i);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void showTime();
    void SetToEdit();
    //void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
};
#endif // MAINWINDOW_H
