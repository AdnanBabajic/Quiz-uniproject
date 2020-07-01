#include "database.h"
#include <QDebug>

database::database()
{

}

bool database::connOpen()
{
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("C://Users//User//Desktop//Stuff//AdnanBabajicOP//kviz.db");

    if (base.open()){return true;}
    else {return false;}
}

void database::connClose()
{
    base.close();
    base.removeDatabase("QSqlDatabase::defaultConnection");
}

QSqlDatabase* database::getDatabase()
{
    if(connOpen()==true) return &base;
    else qDebug()<<"Baza nije otvorena.";
    return 0;
}
