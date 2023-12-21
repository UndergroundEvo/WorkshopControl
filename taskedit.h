#ifndef TASKEDIT_H
#define TASKEDIT_H

#include <QDialog>
#include <QAbstractButton>

#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlIndex>
#include <QtSql/QSqlField>
#include <QtSql/QSqlRelation>

namespace Ui {
class TaskEdit;
}

class TaskEdit : public QDialog
{
    Q_OBJECT

public:
    QString ReturnFilter();
    explicit TaskEdit(QWidget *parent = nullptr);
    ~TaskEdit();

private slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::TaskEdit *ui;

};

#endif // TASKEDIT_H
