#include "books.h"
#include "ui_books.h"
#include <QScrollBar>
#include <QHeaderView>
Books::Books(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Books)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    showDataToTable();
    connect(depTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClick(QTableWidgetItem*)));
    connect(add,SIGNAL(clicked()),this,SLOT(addAction()));
    connect(del,SIGNAL(clicked()),this,SLOT(delAction()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveAction()));
}

Books::~Books()
{
    delete ui;
}

void Books::initWidgets()
{
    name = new QLabel(tr("名称"),this);
    publishers = new QLabel(tr("出版商ID"),this);
    rule = new QLabel(tr("规格"),this);
    Wlprice = new QLabel(tr("批发价格"),this);
    Rtprice = new QLabel(tr("零售价格"),this);
    cost = new QLabel(tr("采购成本"),this);
    count = new QLabel(tr("数量"),this);

    nameEdit = new QLineEdit(this);
    ruleEdit = new QLineEdit(this);
    WlpriceEdit = new QLineEdit(this);
    RtpriceEdit = new QLineEdit(this);
    costEdit = new QLineEdit(this);
    psComBox = new QLineEdit(this);
    countEdit = new QLineEdit(this);
    add = new QPushButton(tr("增加书籍"),this);
    del = new QPushButton(tr("删除书籍"),this);
    save = new QPushButton(tr("保存"),this);

    depTable = new QTableWidget(0,8);
    QStringList headerInfo;
    headerInfo<<"ID"<<"名称"<<"出版商ID"<<"规格"<<"批发价格"<<"零售价格"<<"采购成本"<<"库存";
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

void Books::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(name,0,0,1,1);
    glayout->addWidget(nameEdit,1,0,1,2);
    glayout->addWidget(publishers,2,0,1,1);
    glayout->addWidget(psComBox,3,0,1,2);
    glayout->addWidget(rule,4,0,1,1);
    glayout->addWidget(ruleEdit,5,0,1,2);
    glayout->addWidget(Wlprice,6,0,1,1);
    glayout->addWidget(WlpriceEdit,7,0,1,2);
    glayout->addWidget(Rtprice,8,0,1,1);
    glayout->addWidget(RtpriceEdit,9,0,1,2);
    glayout->addWidget(cost,10,0,1,1);
    glayout->addWidget(costEdit,11,0,1,2);
    glayout->addWidget(count,12,0,1,1);
    glayout->addWidget(countEdit,13,0,1,2);
    glayout->addWidget(add,14,0,1,1);
    glayout->addWidget(del,14,1,1,1);
    glayout->addWidget(save,15,0,1,2);
    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}


void Books::showDataToTable()
{
//    headerInfo<<"ID"<<"名称"<<"出版商ID"<<"规格"<<"批发价格"<<"零售价格"<<"采购成本"<<"库存";
    QSqlQuery query("SELECT * FROM  book");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("Id").toString();
        QString namedb = query.value("name").toString();
        QString pubid = query.value("publisherid").toString();
        QString ruledb = query.value("model").toString();
        QString priBatch = query.value("price_batch").toString();
        QString priSale = query.value("price_sale").toString();
        QString costdb = query.value("cost").toString();
        QString countdb = query.value("count").toString();


        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(namedb));
        depTable->setItem(i,2,new QTableWidgetItem(pubid));
        depTable->setItem(i,3,new QTableWidgetItem(ruledb));
        depTable->setItem(i,4,new QTableWidgetItem(priBatch));
        depTable->setItem(i,5,new QTableWidgetItem(priSale));
        depTable->setItem(i,6,new QTableWidgetItem(costdb));
        depTable->setItem(i,7,new QTableWidgetItem(countdb));
        i++;
    }
}



void Books::addAction()
{
    QString namestr = nameEdit->text();
    QString depIDstr = psComBox->text();
    QString rulestr = ruleEdit->text();
    int wlpstr = WlpriceEdit->text().toInt();
    int rtpstr = RtpriceEdit->text().toInt();
    int coststr = costEdit->text().toInt();
    int countstr = countEdit->text().toInt();

    QSqlQuery query;
    query.prepare("INSERT INTO book(name,model,count,price_batch,price_sale,cost,publisherid,storehouseid)\
                  VALUES(:name,:model,:count,:price_batch,:price_sale,:cost,:publisherid,:storehouseid)");
    query.bindValue(":name",namestr);
    query.bindValue(":model",rulestr);
    query.bindValue(":count",countstr);
    query.bindValue(":price_batch",wlpstr);
    query.bindValue(":price_sale",rtpstr);
    query.bindValue(":cost",coststr);
    query.bindValue(":publisherid",depIDstr);
    query.bindValue(":storehouseid",1);
    query.exec();
    showDataToTable();
}

void Books::delAction()
{
    QSqlQuery query;
    query.prepare(("delete from book where Id =?"));
    query.bindValue(0,oldID.toInt());
    query.exec();
    showDataToTable();

    nameEdit->clear();
    ruleEdit->clear();
    WlpriceEdit->clear();
    RtpriceEdit->clear();
    costEdit->clear();
    psComBox->clear();
    countEdit->clear();
}

void Books::saveAction()
{
    if(oldID.isEmpty() == false)
    {
        QString namestr = nameEdit->text();
        QString depIDstr = psComBox->text();
        QString rulestr = ruleEdit->text();
        int wlpstr = WlpriceEdit->text().toInt();
        int rtpstr = RtpriceEdit->text().toInt();
        int coststr = costEdit->text().toInt();
        int countstr = countEdit->text().toInt();

        QSqlQuery query;
        query.prepare("update book set name=?,model=?,\
                      publisherid=?,price_batch=?,price_sale=?,cost=?,count=? where Id=?");
        query.bindValue(0,namestr);
        query.bindValue(1,rulestr);
        query.bindValue(2,depIDstr);
        query.bindValue(3,wlpstr);
        query.bindValue(4,rtpstr);
        query.bindValue(5,coststr);
        query.bindValue(6,countstr);
        query.bindValue(7,oldID.toInt());
        query.exec();
        showDataToTable();
    }

}

void Books::doubleClick(QTableWidgetItem*)
{
//"ID"<<"名称"<<"出版商ID"<<"规格"<<"批发价格"<<"零售价格"<<"采购成本"<<"库存";


    QString ID = depTable->selectedItems().at(0)->text();
    QString namestr = depTable->selectedItems().at(1)->text();
    QString depIDstr = depTable->selectedItems().at(2)->text();
    QString rulestr = depTable->selectedItems().at(3)->text();
    QString wlpstr = depTable->selectedItems().at(4)->text();
    QString rtpstr = depTable->selectedItems().at(5)->text();
    QString coststr = depTable->selectedItems().at(6)->text();
    QString countstr = depTable->selectedItems().at(7)->text();

    oldID = ID;
    nameEdit->setText(namestr);
    ruleEdit->setText(rulestr);
    WlpriceEdit->setText(wlpstr);
    RtpriceEdit->setText(rtpstr);
    costEdit->setText(coststr);
    psComBox->setText(depIDstr);
    countEdit->setText(countstr);
}
