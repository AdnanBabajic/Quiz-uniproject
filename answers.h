#ifndef ANSWERS_H
#define ANSWERS_H

#include <QDialog>
#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

namespace Ui {
class answers;
}

class answers : public QDialog
{
    Q_OBJECT

public:
    explicit answers(QString id, QWidget *parent = 0);
    ~answers();
    void openDB();
    void setID(QString id);

private slots:
    void setLabelText(int QuestionID);

private:
    QString userID;
    int *querryValue;
    Ui::answers *ui;
    QSqlDatabase *db;
    database *base;
};

#endif // ANSWERS_H
