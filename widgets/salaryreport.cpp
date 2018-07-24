#include "salaryreport.h"
#include "ui_salaryreport.h"
#include <QScrollBar>
#include <QHeaderView>
salaryReport::salaryReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::salaryReport)
{
    ui->setupUi(this);
    initWidget();
    initLayout();
    //showTable();
    connect(shuaxin,SIGNAL(clicked()),this,SLOT(reflash()));
}

salaryReport::~salaryReport()
{
    delete ui;
}

void salaryReport::initWidget()
{
    start = "1990-1-1";
    end = "1990-1-1";
    money= 0;
    allPrice = new QLabel(tr("总发工资: 0￥"),this);
    allPrice->setFixedSize(300,30);
    shuaxin = new QPushButton(tr("刷新"),this);
    depTable = new QTableWidget(0,6);
    QStringList headerInfo;
    headerInfo<<"ID"<<"姓名"<<"职位"<<"性别"<<"年龄"<<"工资";
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

void salaryReport::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(depTable);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(allPrice);
    hlayout->addStretch();
    hlayout->addWidget(shuaxin);
    layout->addLayout(hlayout);
}

void salaryReport::showTable(QString datestart,QString dateend)
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    start = datestart;
    end = dateend;
    money= 0;
    QSqlQuery query("SELECT * FROM  users");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString namedb = query.value("name").toString();
        QString postion = query.value("postion").toString();
        QString sex = query.value("sex").toString();
        QString age = query.value("age").toString();
        QString salary = query.value("salary").toString();


        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(namedb));
        depTable->setItem(i,2,new QTableWidgetItem(postion));
        depTable->setItem(i,3,new QTableWidgetItem(sex));
        depTable->setItem(i,4,new QTableWidgetItem(age));
        depTable->setItem(i,5,new QTableWidgetItem(salary));
        i++;
        money += salary.toInt();
    }

    QString s = QString::number(money, 10);
    QString str = "总发工资: "+ s + "￥";
    allPrice->setText(str);
}

void salaryReport::reflash()
{
    int rows = depTable->rowCount();
    for(int j=0;j<rows;j++)
    {
        depTable->removeRow(0);
    }
    showTable(start,end);
}
