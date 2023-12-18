#include "database.h"

Database::Database(QObject *parent): QObject{parent}{}
Database::~Database(){}

void Database::connectToDataBase(){
    if(!QFile(DATABASE_NAME).exists()) this->restoreDataBase();
    else this->openDataBase();
}
/*
bool Database::restoreDataBase(){
    if(this->openDataBase()){
        if(!this->createTable()) return false;
         else return true;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
}*/

bool Database::openDataBase(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open())return true;
    else return false;
}

void Database::closeDataBase(){
    db.close();
}
/*
bool Database::createTable_Tasks(){
    формирование sql запросов
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_TASKS " ("
                    T1 " INTEGER PRIMARY KEY AUTOINCREMENT, "
                    T5       " BLOB            NOT NULL,"
                    T2          " TINYTEXT        NOT NULL,"
                    TABLE_AUTHOR        " TINYTEXT        NOT NULL,"
                    TABLE_RELEASE_YEAR  " INT             NOT NULL,"
                    TABLE_DESCRIPTION   " TEXT            NOT NULL,"
                    TABLE_TYPE          " TINYTEXT        NOT NULL,"
                    TABLE_GENRES        " TINYTEXT        NOT NULL,"
                    TABLE_VIEWDATE      " DATE            NOT NULL,"
                    TABLE_SCORE         " TINYINT         NOT NULL,"
                    TABLE_COMMENT        " TEXT           NOT NULL"
                    " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}*/
