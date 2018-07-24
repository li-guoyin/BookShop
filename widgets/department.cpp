#include "department.h"
#include "ui_department.h"
#include <QScrollBar>
#include <QHeaderView>
departMent::departMent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::departMent)
{
    ui->setupUi(this);
    initWidget();
    initLayout();
    showDataToTable();
    connect(depTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClick(QTableWidgetItem*)));
    connect(add,SIGNAL(clicked()),this,SLOT(addAction()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveAction()));

}

departMent::~departMent()
{
    delete ui;
}

void departMent::initWidget()
{
    oldName = "";
    depname = new QLabel(tr("部门名称"),this);
    supervisor = new QLabel(tr("主管"),this);
    address = new QLabel(tr("地址"),this);
    tel = new QLabel(tr("联系电话"),this);
    charge = new QLabel(tr("运营费用"),this);

    depnameEdit = new QLineEdit(this);
    supervisorEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    telEdit = new QLineEdit(this);
    chargeEdit = new QLineEdit(this);

    add = new QPushButton(tr("增加部门"),this);
    //del = new QPushButton(tr("删除部门"),this);
    save = new QPushButton(tr("保存"),this);

    depTable = new QTableWidget(0,6);
    QStringList headerInfo;
    headerInfo<<"ID"<<"部门名称"<<"主管"<<"地址"<<"联系电话"<<"运营费用";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,60);
    depTable->setColumnWidth(1,100);
    depTable->setColumnWidth(2,100);
    depTable->setColumnWidth(3,150);
    depTable->setColumnWidth(4,100);
    depTable->setColumnWidth(5,100);
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

void departMent::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(depname,0,0,1,1);
    glayout->addWidget(depnameEdit,1,0,1,2);
    glayout->addWidget(supervisor,2,0,1,1);
    glayout->addWidget(supervisorEdit,3,0,1,2);
    glayout->addWidget(address,4,0,1,1);
    glayout->addWidget(addressEdit,5,0,1,2);
    glayout->addWidget(tel,6,0,1,1);
    glayout->addWidget(telEdit,7,0,1,2);
    glayout->addWidget(charge,8,0,1,1);
    glayout->addWidget(chargeEdit,9,0,1,2);
    glayout->addWidget(add,10,0,1,1);
    //glayout->addWidget(del,10,1,1,1);
    glayout->addWidget(save,10,1,1,1);
    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}


void departMent::showDataToTable()
{
//    headerInfo<<"ID"<<"部门名称"<<"主管"<<"地址"<<"联系电话"<<"运营费用";
    QSqlQuery query("SELECT * FROM  department");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString namedb = query.value("name").toString();
        QString managername = query.value("managername").toString();
        QString addressdb = query.value("address").toString();
        QString teldb = query.value("tel").toString();
        QString costdb = query.value("cost").toString();


        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(namedb));
        depTable->setItem(i,2,new QTableWidgetItem(managername));
        depTable->setItem(i,3,new QTableWidgetItem(addressdb));
        depTable->setItem(i,4,new QTableWidgetItem(teldb));
        depTable->setItem(i,5,new QTableWidgetItem(costdb));
        i++;
    }
}

void departMent::addAction()
{
    QString depnamestr = depnameEdit->text();
    QString supervisorstr = supervisorEdit->text();
    QString addressstr = addressEdit->text();
    QString telstr = telEdit->text();
    int chargestr = chargeEdit->text().toInt();

    QSqlQuery query;
    query.prepare("INSERT INTO department(name,managername,address,tel,cost,centerid)\
                  VALUES(:name,:managername,:address,:tel,:cost,:centerid)");
    query.bindValue(":name",depnamestr);
    query.bindValue(":managername",supervisorstr);
    query.bindValue(":address",addressstr);
    query.bindValue(":tel",telstr);
    query.bindValue(":cost",chargestr);
    query.bindValue(":centerid",1);
    query.exec();
    showDataToTable();
}

void departMent::delAction()
{

}

void departMent::saveAction()
{
    if(oldName.isEmpty() == false)
    {
        QString depnamestr = depnameEdit->text();
        QString supervisorstr = supervisorEdit->text();
        QString addressstr = addressEdit->text();
        QString telstr = telEdit->text();
        int chargestr = chargeEdit->text().toInt();

        QSqlQuery query;
        query.prepare("update department set name=?,managername=?,\
                      address=?,tel=?,cost=?,centerid=? where name=?");
        query.bindValue(0,depnamestr);
        query.bindValue(1,supervisorstr);
        query.bindValue(2,addressstr);
        query.bindValue(3,telstr);
        query.bindValue(4,chargestr);
        query.bindValue(5,1);
        query.bindValue(6,oldName);
        query.exec();
        showDataToTable();
    }

}

void departMent::doubleClick(QTableWidgetItem*)
{
    //    headerInfo<<"ID"<<"部门名称"<<"主管"<<"地址"<<"联系电话"<<"运营费用";
    QString depnamestr = depTable->selectedItems().at(1)->text();
    QString managerstr = depTable->selectedItems().at(2)->text();
    QString addressstr = depTable->selectedItems().at(3)->text();
    QString telstr = depTable->selectedItems().at(4)->text();
    QString coststr = depTable->selectedItems().at(5)->text();

    depnameEdit->setText(depnamestr);
    supervisorEdit->setText(managerstr);
    addressEdit->setText(addressstr);
    telEdit->setText(telstr);
    chargeEdit->setText(coststr);
    oldName = depnamestr;
}
