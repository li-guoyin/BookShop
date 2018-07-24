#include "bookShop.h"
#include "widgets/login.h"
#include "db/database.h"
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataBase db;
    bool isLogin = db.connectDB();
    if(isLogin == true)
    {
        Login *login = new Login();
        bookShop *bs = new bookShop();
        QObject::connect(login,SIGNAL(successLogin(bool)),bs,SLOT(showWidget(bool)));
        login->show();
    }
    return a.exec();
}


//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
//qDebug()<<"ODBC driver?"<<db.isValid();
//QString dsn = QString::fromLocal8Bit("testDsn");      //数据源名称
//db.setHostName("localhost");                        //选择本地主机，127.0.1.1
//db.setDatabaseName(dsn);                            //设置数据源名称
//db.setUserName("mai");                               //登录用户
//db.setPassword("123456");                           //密码
//if(!db.open())                                      //打开数据库
//{
//    qDebug()<<db.lastError().text();
//    QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
//    return false;                                   //打开失败
//}
//else
//    qDebug()<<"database open success!";
//return true;
