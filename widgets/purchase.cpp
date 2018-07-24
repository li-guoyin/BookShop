#include "purchase.h"
#include "ui_purchase.h"
#include <QScrollBar>
#include <QHeaderView>
#include <QDate>
purChase::purChase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purChase)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    connect(insert,SIGNAL(clicked()),this,SLOT(add()));
    connect(pay,SIGNAL(clicked()),this,SLOT(paymoney()));
}

purChase::~purChase()
{
    delete ui;
}

void purChase::initWidgets()
{
    inputName = new QLabel(tr("书名"),this);
    inputPrice = new QLabel(tr("批发价格"),this);
    inputNum = new QLabel(tr("批发数量"),this);
    inputPbs = new QLabel(tr("所属出版商"),this);
    allPrice = new QLabel(tr("总价: 0￥"),this);

    inputNameEdit = new QLineEdit(this);
    inputPriceEdit = new QLineEdit(this);
    inputNumEdit = new QLineEdit(this);
    inputPbsEdit = new QLineEdit(this);

    insert = new QPushButton(tr("添加"),this);
    pay = new QPushButton(tr("结算"),this);

    depTable = new QTableWidget(0,5);
    QStringList headerInfo;
    headerInfo<<"ID"<<"书名"<<"所属出版商"<<"批发价格"<<"批发数量";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,60);
    depTable->setColumnWidth(1,300);
    depTable->setColumnWidth(2,300);
    depTable->setColumnWidth(3,100);
    depTable->setColumnWidth(4,100);
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

void purChase::initLayout()
{
    //QLabel *inputName,*inputPrice,*inputNum,*inputPbs,*allPrice;
    //QLineEdit *inputNameEdit,*inputPriceEdit,*inputNumEdit,*inputPbsEdit;
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(inputName,0,0,1,1);
    glayout->addWidget(inputNameEdit,1,0,1,2);
    glayout->addWidget(inputPrice,2,0,1,1);
    glayout->addWidget(inputPriceEdit,3,0,1,2);
    glayout->addWidget(inputNum,4,0,1,1);
    glayout->addWidget(inputNumEdit,5,0,1,2);
    glayout->addWidget(inputPbs,6,0,1,1);
    glayout->addWidget(inputPbsEdit,7,0,1,2);
    glayout->addWidget(insert,8,0,1,2);
    glayout->addWidget(allPrice,10,0,1,2);
    glayout->addWidget(pay,11,1,1,1);
    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}


void purChase::add()
{

    QString name = inputNameEdit->text();
    QString price_batch = inputPriceEdit->text();
    QString num = inputNumEdit->text();
    QString puber = inputPbsEdit->text();

    int i = depTable->rowCount();
    depTable->setRowCount(i+1);
    depTable->setItem(i,0,new QTableWidgetItem(i));
    depTable->setItem(i,1,new QTableWidgetItem(name));
    depTable->setItem(i,2,new QTableWidgetItem(puber));
    depTable->setItem(i,3,new QTableWidgetItem(price_batch));
    depTable->setItem(i,4,new QTableWidgetItem(num));

    QSqlQuery query1;
    query1.prepare("INSERT INTO purchase(name,count,addtime,price_batch,puber)\
                   VALUES(:name,:count,:addtime,:price_batch,:puber)");
    query1.bindValue(":name",name);
    query1.bindValue(":count",num.toInt());
    QDate *date=new QDate();
    query1.bindValue(":addtime",date->currentDate().toString("yyyy-MM-dd"));
    query1.bindValue(":price_batch",price_batch.toInt());
    query1.bindValue(":puber",puber);
    query1.exec();


    money += (price_batch.toInt()*num.toInt() );
    QString s = QString::number(money, 10);
    QString str = "总价: "+ s + "￥";
    allPrice->setText(str);

    inputPriceEdit->clear();
    inputNameEdit->clear();
    inputNumEdit->clear();
    inputPbsEdit->clear();
}

void purChase::paymoney()
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    money = 0;
    QString s = QString::number(money, 10);
    QString str = "总价: "+ s + "￥";
    allPrice->setText(str);

    inputPriceEdit->clear();
    inputNameEdit->clear();
    inputNumEdit->clear();
    inputPbsEdit->clear();
}
