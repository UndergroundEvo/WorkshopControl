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
    
    QT_BEGIN_NAMESPACE
    namespace Ui {class MainWindow;}
    QT_END_NAMESPACE
    class MainWindow : public QMainWindow{
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        Ui::MainWindow *ui;
        QSqlDatabase sqllite3 = QSqlDatabase::addDatabase("QSQLITE");
        QSqlQuery query = QSqlQuery(sqllite3);
        QSqlTableModel* modelTasks;
        QSqlTableModel *modelWorkers;
        QString filename;
        TaskEdit task;
        void loadTasks();
        void loadWorkers();
        void UpdateWorkers();
        void loadTasks_active();
        QString GetWorker(int i);
        QString GetWorker(QString string);
        QSqlTableModel* getModelWorkers();
    private slots:
        void on_pushButton_clicked();
        void on_pushButton_2_clicked();
        void showTime();
        void SetToEdit();
        void on_pushButton_3_clicked();
        void on_action_triggered();
        void on_action_2_triggered();
        void on_tableView_clicked(const QModelIndex &index);
        void on_pushButton_4_clicked();
        void on_pushButton_7_clicked();
        void on_pushButton_6_clicked();
        void on_action_3_triggered();
        void on_pushButton_5_clicked();
        void on_action_4_triggered();
        void on_pushButton_9_clicked();
        void on_pushButton_8_clicked();
        void on_tabWidget_tabBarClicked(int index);
    signals:
        void sendModel(QSqlTableModel*);
    };
    #endif // MAINWINDOW_H