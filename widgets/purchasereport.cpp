﻿#include "purchasereport.h"
#include "ui_purchasereport.h"
#include <QScrollBar>
#include <QHeaderView>
purchaseReport::purchaseReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::purchaseReport)
{
    ui->setupUi(this);
    initWidget();
    initLayout();
//    showTable();
    connect(shuaxin,SIGNAL(clicked()),this,SLOT(reflash()));
}

purchaseReport::~purchaseReport()
{
    delete ui;
}

void purchaseReport::initWidget()
{
    start = "1990-1-1";
    end = "1990-1-1";
    money= 0;
    allPrice = new QLabel(tr("总利润: 0￥"),this);
    allPrice->setFixedSize(300,30);
    shuaxin = new QPushButton(tr("刷新"),this);
    depTable = new QTableWidget(0,8);
    QStringList headerInfo;
    headerInfo<<"序号"<<"书名"<<"出版商"<<"销售数量"<<"采购价格"<<"销售价格"<<"利润"<<"结算时间";
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

void purchaseReport::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(depTable);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(allPrice);
    hlayout->addStretch();
    hlayout->addWidget(shuaxin);
    layout->addLayout(hlayout);
}

void purchaseReport::showTable(QString datestart,QString dateend)
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    start = datestart;
    end = dateend;
    money= 0;
    QSqlQuery query;
    query.prepare("SELECT * FROM  orderbook where addtime between ? and ?");
    query.bindValue(0,datestart);
    query.bindValue(1,dateend);
    query.exec();
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString namedb = query.value("name").toString();
        QString bookid = query.value("bookid").toString();
        QString count = query.value("count").toString();
        QString price_batch = query.value("price_batch").toString();
        QString price_sale = query.value("price_sale").toString();
        QString date = query.value("addtime").toString();
        int lireun = price_sale.toInt() - price_batch.toInt();
        QString s = QString::number(lireun,10);
        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(bookid));
        depTable->setItem(i,2,new QTableWidgetItem(namedb));
        depTable->setItem(i,3,new QTableWidgetItem(count));
        depTable->setItem(i,4,new QTableWidgetItem(price_batch));
        depTable->setItem(i,5,new QTableWidgetItem(price_sale));
        depTable->setItem(i,6,new QTableWidgetItem(s));
        depTable->setItem(i,7,new QTableWidgetItem(date));
        i++;
        money += (  lireun*count.toInt());
    }

    QString s = QString::number(money, 10);
    QString str = "总利润: "+ s + "￥";
    allPrice->setText(str);
}

void purchaseReport::reflash()
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    showTable(start,end);
}
