#include "publishers.h"
#include "ui_publishers.h"
#include <QScrollBar>
#include <QHeaderView>
#include <QSqlQuery>
publiShers::publiShers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::publiShers)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    showDataToTable();
    connect(depTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClick(QTableWidgetItem*)));
    connect(add,SIGNAL(clicked()),this,SLOT(addAction()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveAction()));
}

publiShers::~publiShers()
{
    delete ui;
}

void publiShers::initWidgets()
{
    name = new QLabel(tr("出版商名称"),this);
    tel = new QLabel(tr("联系电话"),this);
    address = new QLabel(tr("地址"),this);

    nameEdit = new QLineEdit(this);
    telEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);

    add = new QPushButton(tr("增加出版商"),this);
    //del = new QPushButton(tr("删除出版商"),this);
    save = new QPushButton(tr("保存"),this);

    depTable = new QTableWidget(0,4);
    QStringList headerInfo;
    headerInfo<<"ID"<<"出版商名称"<<"联系电话"<<"地址";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,60);
    depTable->setColumnWidth(1,200);
    depTable->setColumnWidth(2,150);
    depTable->setColumnWidth(3,250);
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

void publiShers::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(name,0,0,1,1);
    glayout->addWidget(nameEdit,1,0,1,2);
    glayout->addWidget(tel,2,0,1,1);
    glayout->addWidget(telEdit,3,0,1,2);
    glayout->addWidget(address,4,0,1,1);
    glayout->addWidget(addressEdit,5,0,1,2);
    glayout->addWidget(add,6,0,1,1);
    //glayout->addWidget(del,6,1,1,1);
    glayout->addWidget(save,6,1,1,1);
    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}

void publiShers::showDataToTable()
{
    QSqlQuery query("SELECT * FROM  publisher");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString namedb = query.value("name").toString();
        QString tel = query.value("tel").toString();
        QString ads = query.value("address").toString();

        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(namedb));
        depTable->setItem(i,2,new QTableWidgetItem(tel));
        depTable->setItem(i,3,new QTableWidgetItem(ads));
        i++;
    }
}


void publiShers::addAction()
{
    QString nameEditstr = nameEdit->text();
    int telEditstr = telEdit->text().toInt();
    QString addressEditstr = addressEdit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO publisher(name,tel,address)\
                  VALUES(:name,:tel,:address)");
    query.bindValue(":name",nameEditstr);
    query.bindValue(":address",addressEditstr);
    query.bindValue(":tel",telEditstr);
    query.exec();
    showDataToTable();
}

void publiShers::delAction()
{

}

void publiShers::saveAction()
{
    if(oldID.isEmpty() == false)
    {
        QString namestr = nameEdit->text();
        int tel = telEdit->text().toInt();
        QString addressstr = addressEdit->text();
        QSqlQuery query;
        query.prepare("update publisher set name=?,\
                      tel=?,address=? where id=?");
        query.bindValue(0,namestr);
        query.bindValue(1,tel);
        query.bindValue(2,addressstr);
        query.bindValue(3,oldID.toInt());
        query.exec();
        showDataToTable();

    }

}

void publiShers::doubleClick(QTableWidgetItem*)
{
    //    headerInfo<<"ID"<<"部门名称"<<"主管"<<"地址"<<"联系电话"<<"运营费用";
    QString ID = depTable->selectedItems().at(0)->text();;
    QString namestr = depTable->selectedItems().at(1)->text();
    QString addressstr = depTable->selectedItems().at(3)->text();
    QString telstr = depTable->selectedItems().at(2)->text();

    nameEdit->setText(namestr);
    addressEdit->setText(addressstr);
    telEdit->setText(telstr);
    oldID = ID;
}
