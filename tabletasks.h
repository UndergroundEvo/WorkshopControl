#ifndef TABLETASKS_H
#define TABLETASKS_H

#include <QDialog>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>

namespace Ui {
class TableTasks;
}

class TableTasks : public QDialog{
    Q_OBJECT

public:
    explicit TableTasks(QWidget *parent = nullptr);
    ~TableTasks();


private:
    Ui::TableTasks *ui;

};

#endif // TABLETASKS_H
