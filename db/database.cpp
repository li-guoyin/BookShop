#include "database.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
dataBase::dataBase(QObject *parent) :
    QObject(parent)
{
}

bool dataBase::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    QString dsn = QString::fromLocal8Bit("testDsn");      //数据源名称
    db.setHostName("localhost");                        //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("sa");                               //登录用户
    db.setPassword("520103asd");                           //密码
    if(!db.open())                                      //打开数据库
    {
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else
        qDebug()<<"database open success!";
    return true;
}

QSqlDatabase dataBase::getDB()
{
    return db;
}
