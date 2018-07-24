#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class dataBase : public QObject
{
    Q_OBJECT
public:
    explicit dataBase(QObject *parent = 0);
public:
    bool connectDB();
    QSqlDatabase getDB();
private:
    QSqlDatabase db;

};

#endif // DATABASE_H
