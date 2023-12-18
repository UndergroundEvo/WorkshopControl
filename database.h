#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QWidget>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QListWidget>
#include <QFile>

#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>


#define DATABASE_NAME "D:\\Qt\\WorkshopControlpro\\WorkshopControlpro\\mydatabase.sqlite"

#define TABLE_WORKERS "Workers"

#define TABLE_WORKERS_KEY "key"
#define TABLE_WORKERS_NAME "Name"

#define TABLE_TASKS "Tasks"

#define T1 "Key"
#define T2 "Name"
#define T3 "DateBegin"
#define T4 "DateEnd"
#define T5 "IMG"
#define T6 "Price"
#define T7 "Info"
#define T8 "Genres"
#define T9 "WorkerKey"
#define T10 "Contacts"

/*
#define TABLE_KEY "Key"
#define TABLE_NAME "Name"
#define TABLE_DATE_START "DateBegin"
#define TABLE_DATE_END "DateEnd"
#define TABLE_IMAGE "IMG"
#define TABLE_PRICE "Price"
#define TABLE_INFO "Info"
#define TABLE_GENRES "Genres"
#define TABLE_WKEY "WorkerKey"
#define TABLE_CONT "Contacts" */

class Database : public QObject{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    void connectToDataBase();
    bool insertIntoTable(const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear);
    bool insertIntoTable(const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type,  const QString &genres,  const QDate &viewDate, const qint8 &score, const QString &comment);
    bool editInTable(const int &id, const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type,  const QString &genres,  const QDate &viewDate, const qint8 &score, const QString &comment);
    bool deleteFromDatabase(const int id);
private:
    QSqlDatabase db;
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable_Tasks();
    bool createTable_Workers();
signals:
};

#endif // DATABASE_H
