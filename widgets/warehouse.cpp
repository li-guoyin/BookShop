#include "warehouse.h"
#include "ui_warehouse.h"
#include <QScrollBar>
#include <QHeaderView>
wareHouse::wareHouse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wareHouse)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    showDataToTable();
    connect(depTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleClick(QTableWidgetItem*)));
    connect(add,SIGNAL(clicked()),this,SLOT(addAction()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveAction()));
}

wareHouse::~wareHouse()
{
    delete ui;
}

void wareHouse::initWidgets()
{
    name = new QLabel(tr("仓库名称"),this);
    housetel = new QLabel(tr("仓库联系电话"),this);
    Admin = new QLabel(tr("仓库管理员"),this);
    charge = new QLabel(tr("仓库运营成本"),this);

    nameEdit = new QLineEdit(this);
    housetelEdit = new QLineEdit(this);
    AdminEdit = new QLineEdit(this);
    chargeEdit = new QLineEdit(this);

    add = new QPushButton(tr("增加仓库"),this);
    //del = new QPushButton(tr("删除仓库"),this);
    save = new QPushButton(tr("保存"),this);

    depTable = new QTableWidget(0,5);
    QStringList headerInfo;
    headerInfo<<"ID"<<"仓库名称"<<"仓库联系电话"<<"仓库管理员"<<"仓库运营成本";
    depTable->setHorizontalHeaderLabels(headerInfo);
    depTable->verticalHeader()->setVisible(false);
    depTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中一行
    depTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    depTable->setColumnWidth(0,60);
    depTable->setColumnWidth(1,200);
    depTable->setColumnWidth(2,150);
    depTable->setColumnWidth(3,150);
    depTable->setColumnWidth(4,150);
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

void wareHouse::initLayout()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(name,0,0,1,1);
    glayout->addWidget(nameEdit,1,0,1,2);
    glayout->addWidget(housetel,2,0,1,1);
    glayout->addWidget(housetelEdit,3,0,1,2);
    glayout->addWidget(Admin,4,0,1,1);
    glayout->addWidget(AdminEdit,5,0,1,2);
    glayout->addWidget(charge,6,0,1,1);
    glayout->addWidget(chargeEdit,7,0,1,2);
    glayout->addWidget(add,8,0,1,1);
    //glayout->addWidget(del,8,1,1,1);
    glayout->addWidget(save,8,1,1,2);
    glayout->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    layout->addLayout(glayout);
    layout->addWidget(depTable,Qt::AlignRight);
}

void wareHouse::showDataToTable()
{
//    headerInfo<<"ID"<<"仓库名称"<<"仓库联系电话"<<"仓库管理员"<<"仓库运营成本";

    QSqlQuery query("SELECT * FROM  storehouse");
    int i = 0;
    while(query.next())
    {
        //从数据库中将数据取出
        QString id = query.value("id").toString();
        QString namedb = query.value("name").toString();
        QString managername = query.value("managername").toString();
        QString teldb = query.value("tel").toString();
        QString costdb = query.value("cost").toString();


        depTable->setRowCount(i+1);
        depTable->setItem(i,0,new QTableWidgetItem(id));
        depTable->setItem(i,1,new QTableWidgetItem(namedb));
        depTable->setItem(i,2,new QTableWidgetItem(teldb));
        depTable->setItem(i,3,new QTableWidgetItem(managername));
        depTable->setItem(i,4,new QTableWidgetItem(costdb));
        i++;
    }
}

void wareHouse::addAction()
{
    QString namestr = nameEdit->text();
    QString housetel = housetelEdit->text();
    QString Adminstr = AdminEdit->text();
    QString coststr = chargeEdit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO storehouse(name,managername,tel,cost,centerid)\
                  VALUES(:name,:managername,:tel,:cost,:centerid)");
    query.bindValue(":name",namestr);
    query.bindValue(":managername",Adminstr);
    query.bindValue(":tel",housetel);
    query.bindValue(":cost",coststr);
    query.bindValue(":centerid",1);
    query.exec();
    showDataToTable();
}

void wareHouse::delAction()
{

}

void wareHouse::saveAction()
{
    if(oldID.isEmpty() == false)
    {
        QString namestr = nameEdit->text();
        QString housetel = housetelEdit->text();
        QString Adminstr = AdminEdit->text();
        int coststr = chargeEdit->text().toInt();

        QSqlQuery query;
        query.prepare("update storehouse set name=?,\
                      managername=?,tel=?,cost=?,centerid=? where id=?");
        query.bindValue(0,namestr);
        query.bindValue(1,Adminstr);
        query.bindValue(2,housetel);
        query.bindValue(3,coststr);
        query.bindValue(4,1);
        query.bindValue(5,oldID.toInt());
        query.exec();
        showDataToTable();

    }

}

void wareHouse::doubleClick(QTableWidgetItem*)
{
    //    headerInfo<<"ID"<<"仓库名称"<<"仓库联系电话"<<"仓库管理员"<<"仓库运营成本";

    QString ID = depTable->selectedItems().at(0)->text();
    QString namestr = depTable->selectedItems().at(1)->text();
    QString housetel = depTable->selectedItems().at(2)->text();
    QString Adminstr = depTable->selectedItems().at(3)->text();
    QString coststr = depTable->selectedItems().at(4)->text();

    nameEdit->setText(namestr);
    housetelEdit->setText(housetel);
    AdminEdit->setText(Adminstr);
    chargeEdit->setText(coststr);
    oldID = ID;
}
