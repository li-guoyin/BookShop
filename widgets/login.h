#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "db/database.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
public:
    void initWidget();
    void initLayout();
private:
    Ui::Login *ui;
private:
    QLabel *name,*psw,*tishi;
    QLineEdit *inputName,*inputPsw;
    QPushButton *lgbtn;
    dataBase db;
signals:
    void successLogin(bool isLogin);
private slots:
    void loginAction();
};

#endif // LOGIN_H
