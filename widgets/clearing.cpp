#include "clearing.h"
#include "ui_clearing.h"
#include <QScrollBar>
#include <QHeaderView>
#include <QDateTime>
#include <QDate>
#include <QDebug>
cleaRing::cleaRing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cleaRing)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    connect(insert,SIGNAL(clicked()),this,SLOT(add()));
    connect(pay,SIGNAL(clicked()),this,SLOT(paymoney()));
}

cleaRing::~cleaRing()
{
    delete ui;
}

void cleaRing::initWidgets()
{
    money = 0;
    inputId = new QLabel(tr("ID:"),this);
    inputNum = new QLabel(tr("数量:"),this);
    allPrice = new QLabel(tr("总价: 0￥"),this);
    allPrice->setFixedSize(300,30);
    input = new QLineEdit(this);
    input->setPlaceholderText(tr("请输入书籍ID号"));
    num = new QLineEdit(this);
    num->setPlaceholderText(tr("请输入书籍数量"));
    insert = new QPushButton(tr("添加"),this);
    pay = new QPushButton(tr("结算"),this);

    depTable = new QTableWidget(0,4);
    QStringList headerInfo;
    headerInfo<<"ID"<<"书名"<<"价格"<<"数量";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,80);
    depTable->setColumnWidth(1,400);
    depTable->setColumnWidth(2,200);
    depTable->setColumnWidth(3,200);
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

void cleaRing::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout->addWidget(inputId);
    hlayout->addWidget(input);
    hlayout->addWidget(inputNum);
    hlayout->addWidget(num);
    hlayout->addWidget(insert);

    hlayout1->addWidget(allPrice);
    hlayout1->addStretch();
    hlayout1->addWidget(pay);
    layout->addLayout(hlayout,Qt::AlignTop);
    layout->addWidget(depTable);
    layout->addLayout(hlayout1,Qt::AlignBottom);
}

void cleaRing::add()
{
    QString id = input->text();
    QString numstr = num->text();

    QSqlQuery query;
    query.prepare("select *from book where Id=?");
    query.bindValue(0,id.toInt());
    query.exec();
    query.first();
    QString namedb = query.value("name").toString();
    QString price_batch = query.value("price_batch").toString();
    QString price_sale = query.value("price_sale").toString();


    int i = depTable->rowCount();
    depTable->setRowCount(i+1);
    depTable->setItem(i,0,new QTableWidgetItem(id));
    depTable->setItem(i,1,new QTableWidgetItem(namedb));
    depTable->setItem(i,2,new QTableWidgetItem(price_sale));
    depTable->setItem(i,3,new QTableWidgetItem(numstr));

    QSqlQuery query1;
    query1.prepare("INSERT INTO orderbook(name,bookid,count,addtime,price_batch,price_sale)\
                   VALUES(:name,:bookid,:count,:addtime,:price_batch,:price_sale)");
    query1.bindValue(":name",namedb);
    query1.bindValue(":bookid",id.toInt());
    query1.bindValue(":count",numstr.toInt());
    QDate *date=new QDate();
    query1.bindValue(":addtime",date->currentDate().toString("yyyy-MM-dd"));
    query1.bindValue(":price_batch",price_batch.toInt());
    query1.bindValue(":price_sale",price_sale.toInt());
    query1.exec();



    money += (price_sale.toInt()*numstr.toInt() );
    QString s = QString::number(money, 10);
    QString str = "总价: "+ s + "￥";
    allPrice->setText(str);
    input->clear();
    num->clear();

}

void cleaRing::paymoney()
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    input->clear();
    num->clear();
    money = 0;
    QString s = QString::number(money, 10);
    QString str = "总价: "+ s + "￥";
    allPrice->setText(str);
}
