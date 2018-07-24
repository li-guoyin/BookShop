#include "employee.h"
#include "ui_employee.h"
#include <QScrollBar>
#include <QHeaderView>
emPloyee::emPloyee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emPloyee)
{
    ui->setupUi(this);
    initWidget();
    initLayout();
    showDataToTable();
    connect(depTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClick(QTableWidgetItem*)));
    connect(add,SIGNAL(clicked()),this,SLOT(addAction()));
    connect(del,SIGNAL(clicked()),this,SLOT(delAction()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveAction()));
    connect(man,SIGNAL(clicked()),this,SLOT(manBtn()));
    connect(woman,SIGNAL(clicked()),this,SLOT(womanBtn()));

}

emPloyee::~emPloyee()
{
    delete ui;
}

void emPloyee::initWidget()
{
    sexdb= "男";
    oldID = "";
    acinfo = new QLabel(tr("账号信息"),this);
    account = new QLabel(tr("账号:"),this);
    psw = new QLabel(tr("密码:"),this);

    emplinfo = new QLabel(tr("基础信息"),this);
    name = new QLabel(tr("姓名:"),this);
    dep = new QLabel(tr("部门:"),this);
    title = new QLabel(tr("职位:"),this);
    age = new QLabel(tr("年龄:"),this);
    salary = new QLabel(tr("工资:"),this);
    tel = new QLabel(tr("电话:"),this);

    accountEdit = new QLineEdit(this);
//    accountEdit->setFocusPolicy(Qt::NoFocus);
    accountEdit->setPlaceholderText("注册不需要ID,系统自动分配");
    pswEdit = new QLineEdit(this);
    pswEdit->setEchoMode(QLineEdit::Password);
    nameEdit = new QLineEdit(this);
    depEdit = new QLineEdit(this);
    titleEdit = new QLineEdit(this);
    ageEdit = new QLineEdit(this);
    salaryEdit = new QLineEdit(this);
    telEdit = new QLineEdit(this);

    isAdmin = new QCheckBox(tr("是否开通管理员权限"),this);
    man = new QRadioButton(tr("男"),this);
    woman = new QRadioButton(tr("女"),this);

    add = new QPushButton(tr("增加员工"),this);
    del = new QPushButton(tr("删除员工"),this);
    save = new QPushButton(tr("保存"),this);

    depTable = new QTableWidget(0,8);
    QStringList headerInfo;
    headerInfo<<"ID"<<"部门ID"<<"姓名"<<"工资"<<"职位"<<"年龄"<<"性别"<<"电话";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,60);
    depTable->setColumnWidth(1,60);
    depTable->setColumnWidth(2,100);
    depTable->setColumnWidth(3,100);
    depTable->setColumnWidth(4,100);
    depTable->setColumnWidth(5,100);
    depTable->setColumnWidth(6,100);
    depTable->setColumnWidth(7,100);
    //设置背景色透明
    QPalette pll = depTable->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    depTable->setPalette(pll);
    //设置表头透明
    depTable->horizontalHeader()->setStyleSheet("QHeaderView::section {background:transparent}");
    //消除格子线
    depTable->setShowGrid(false);
    //消除虚线框
//    depTable->setItemDelegate(new NoFocusDelegate());
    depTable->setStyleSheet("QTableWidget{\
                                    font-size:13px; \
                                    font-weight:300;\
                                    color: rgb(60,60,60);\
                                    gridline-color: white;\
                                    \
                                    selection-background-color: rgb(210,210,210);\
                                    selection-color:rgb(60,60,60);\
                                    border: 2px groove gray;\
                                    border-radius: 0px;\
                                    border:1px solid rgb(220,220,220);}\
                               ");
    depTable->verticalScrollBar()->setStyleSheet("QScrollBar{background:rgb(230,230,230); width:12px;}\
                                                    QScrollBar::handle:vertical {\
                                                    background-color:rgb(200,200,200);\
                                                    border-radius: 6px;\
                                                    min-height: 5px;\
                                                    }\
                                                     ");
}

void emPloyee::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    //glayout->setSpacing(0);
    glayout->addWidget(acinfo,0,0,1,2);
    glayout->addWidget(account,1,0,1,1);
    glayout->addWidget(accountEdit,1,1,1,1);
    glayout->addWidget(psw,2,0,1,1);
    glayout->addWidget(pswEdit,2,1,1,1);
    glayout->addWidget(isAdmin,3,1,1,1);
    glayout->addWidget(emplinfo,4,0,1,2);
    glayout->addWidget(name,5,0,1,1);
    glayout->addWidget(nameEdit,5,1,1,1);
    glayout->addWidget(dep,6,0,1,1);
    glayout->addWidget(depEdit,6,1,1,1);
    glayout->addWidget(title,7,0,1,1);
    glayout->addWidget(titleEdit,7,1,1,1);
    glayout->addWidget(age,8,0,1,1);
    glayout->addWidget(ageEdit,8,1,1,1);
    glayout->addWidget(salary,9,0,1,1);
    glayout->addWidget(salaryEdit,9,1,1,1);
//    glayout->addWidget(btngroup,10,1,1,1);
    glayout->addWidget(man,10,0,1,1);
    glayout->addWidget(woman,10,1,1,1);
    glayout->addWidget(tel,11,0,1,1);
    glayout->addWidget(telEdit,11,1,1,1);

    glayout->addWidget(add,12,0,1,1);
    glayout->addWidget(del,12,1,1,1);
    glayout->addWidget(save,13,0,1,2);

    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}

void emPloyee::showDataToTable()
{
    QSqlQuery query("SELECT * FROM  users");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString depid = query.value("departmentid").toString();
        QString namedb = query.value("name").toString();
        QString sly = query.value("salary").toString();
        QString titl = query.value("postion").toString();
        QString agedb = query.value("age").toString();
        QString sexdb = query.value("sex").toString();
        QString teldb = query.value("tel").toString();


        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(depid));
        depTable->setItem(i,2,new QTableWidgetItem(namedb));
        depTable->setItem(i,3,new QTableWidgetItem(sly));
        depTable->setItem(i,4,new QTableWidgetItem(titl));
        depTable->setItem(i,5,new QTableWidgetItem(agedb));
        depTable->setItem(i,6,new QTableWidgetItem(sexdb));
        depTable->setItem(i,7,new QTableWidgetItem(teldb));
        i++;
    }
}



void emPloyee::addAction()
{
    QString pswstr = pswEdit->text();
    QString namestr = nameEdit->text();
    int depstr = depEdit->text().toInt();
    QString titlestr = titleEdit->text();
    int agestr = ageEdit->text().toInt();
    int salarystr = salaryEdit->text().toInt();
    bool ischecked = isAdmin->isChecked();
    int ischeck ;
    if(ischecked== true)
        ischeck = 1;
    else
        ischeck = 0;
    QString telstr = telEdit->text();


    QSqlQuery query;
    query.prepare("INSERT INTO users(name,password,tel,sex,age,postion,degree,salary,departmentid)\
                  VALUES(:name,:password,:tel,:sex,:age,:postion,:degree,:salary,:departmentid)");
    query.bindValue(":name",namestr);
    query.bindValue(":password",pswstr);
    query.bindValue(":tel",telstr);
    query.bindValue(":sex",sexdb);
    query.bindValue(":age",agestr);
    query.bindValue(":postion",titlestr);
    query.bindValue(":degree",ischeck);
    query.bindValue(":salary",salarystr);
    query.bindValue(":departmentid",depstr);
    query.exec();
    showDataToTable();
}

void emPloyee::delAction()
{
    QString Id = accountEdit->text();
    QSqlQuery query;
    query.prepare(("delete from users where id =?"));
    query.bindValue(0,Id);
    query.exec();
    showDataToTable();

    accountEdit->clear();
    pswEdit->clear();
    nameEdit->clear();
    depEdit->clear();
    titleEdit->clear();
    ageEdit->clear();
    salaryEdit->clear();
    telEdit->clear();
    isAdmin->setChecked(false);

}

void emPloyee::saveAction()
{
    if(oldID.isEmpty() == false)
    {
        QString pswstr = pswEdit->text();
        QString namestr = nameEdit->text();
        int depstr = depEdit->text().toInt();
        QString titlestr = titleEdit->text();
        int agestr = ageEdit->text().toInt();
        int salarystr = salaryEdit->text().toInt();
        QString telstr = telEdit->text();
        bool ischecked = isAdmin->isChecked();
        int ischeck ;
        if(ischecked== true)
            ischeck = 1;
        else
            ischeck = 0;
        QSqlQuery query;
        query.prepare("update users set name=?,password=?,\
                      tel=?,sex=?,age=?,postion=?,degree=?,salary=?,departmentid=? where id=?");
        query.bindValue(0,namestr);
        query.bindValue(1,pswstr);
        query.bindValue(2,telstr);
        query.bindValue(3,sexdb);
        query.bindValue(4,agestr);
        query.bindValue(5,titlestr);
        query.bindValue(6,ischeck);
        query.bindValue(7,salarystr);
        query.bindValue(8,depstr);
        query.bindValue(9,oldID.toInt());
        query.exec();
        showDataToTable();
    }

}

void emPloyee::doubleClick(QTableWidgetItem*)
{
    QString ID = depTable->selectedItems().at(0)->text();
    QString depstr = depTable->selectedItems().at(1)->text();
    QString namestr = depTable->selectedItems().at(2)->text();
    QString salarystr = depTable->selectedItems().at(3)->text();
    QString titlestr = depTable->selectedItems().at(4)->text();
    QString agestr = depTable->selectedItems().at(5)->text();
    sexdb = depTable->selectedItems().at(6)->text();
    QString telstr = depTable->selectedItems().at(7)->text();

    QSqlQuery query;
    query.prepare("select password from users where ID=?");
    query.bindValue(0,ID.toInt());
    query.exec();
    query.first();

    QSqlQuery query1;
    query1.prepare("select degree from users where ID=?");
    query1.bindValue(0,ID.toInt());
    query1.exec();
    query1.first();

    accountEdit->setText(ID);
    pswEdit->setText(query.value(0).toString());
    nameEdit->setText(namestr);
    depEdit->setText(depstr);
    titleEdit->setText(titlestr);
    ageEdit->setText(agestr);
    salaryEdit->setText(salarystr);
    telEdit->setText(telstr);
    oldID = ID;

    if(sexdb == "男")
    {
        man->setChecked(true);
        woman->setChecked(false);
    }
    else if(sexdb == "女")
    {
        man->setChecked(false);
        woman->setChecked(true);
    }

    if(query1.value(0).toInt() == 1)
        isAdmin->setChecked(true);
    else
        isAdmin->setChecked(false);
}

void emPloyee::manBtn()
{
    sexdb = "男";
}

void emPloyee::womanBtn()
{
    sexdb = "女";
}
