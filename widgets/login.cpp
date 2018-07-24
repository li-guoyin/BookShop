#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QDebug>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":./img/resource/dl.jpg"));
    this->setWindowTitle(tr("用户登录"));
    this->setFixedSize(300,200);
    initWidget();
    initLayout();

    connect(lgbtn,SIGNAL(clicked()),this,SLOT(loginAction()));
}

Login::~Login()
{
    delete ui;
}

void Login::initWidget()
{
    name = new QLabel(tr("用户名:"),this);
    psw = new QLabel(tr("密 码:"),this);
    tishi = new QLabel(tr(" "),this);
    inputName = new QLineEdit(this);
    inputName->setPlaceholderText(tr("请输入用户名"));
    inputPsw = new QLineEdit(this);
    inputPsw->setPlaceholderText(tr("请输入密码"));
    inputPsw->setEchoMode(QLineEdit::Password);
    lgbtn = new QPushButton(tr("登录"),this);
}

void Login::initLayout()
{
    QGridLayout *glayout = new QGridLayout(this);
    glayout->setSpacing(15);
    glayout->addWidget(name,0,0,1,1);
    glayout->addWidget(inputName,0,1,1,1);
    glayout->addWidget(psw,1,0,1,1);
    glayout->addWidget(inputPsw,1,1,1,1);
    glayout->addWidget(lgbtn,2,0,1,2);
    glayout->addWidget(tishi,3,0,1,2);
    glayout->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);
}

void Login::loginAction()
{
    QSqlQuery query(db.getDB());
    query.prepare("SELECT password FROM users WHERE name =?");
    query.bindValue(0,inputName->text());//inputName->text().toInt()
    query.exec();
    query.first();
    QString str = query.value(0).toString();
    if(str.isEmpty())
    {
        tishi->setText(tr("用户ID或密码错误"));
    }
    else
    {
        if(str == inputPsw->text())
        {
            emit successLogin(true);
            QWidget *pWindow = this->window();
            pWindow->close();
        }
        else
        {
            tishi->setText(tr("用户ID或密码错误"));
        }
    }
}
