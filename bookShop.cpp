#include "bookShop.h"
//#include "ui_widget.h"

bookShop::bookShop(QWidget *parent) :
    QWidget(parent)
{
    QPalette p;
    p.setColor(QPalette::Background,QColor(214,231,247));
    this->setFixedSize(1100,600);
    this->setWindowIcon(QIcon(":./img/resource/title.png"));
    this->setPalette(p);
    setAutoFillBackground(true);//颜色要生效必须设置这句话
    initWidgets();
    initLayout();
}

bookShop::~bookShop()
{
    delete ui;
}

void bookShop::initWidgets()
{
    allWidgets = new QTabWidget(this);
    cenWidget = new centerWidget();
    depWidgt = new departMent();
    empWidget = new emPloyee();
    bkWidget = new Books();
    pbsWidget = new publiShers();
    whWiget = new wareHouse();
    statWidget = new statisTics();
    crWidget = new cleaRing();
    pchWidget = new purChase();

    allWidgets->addTab(crWidget,tr("结算中心"));
    allWidgets->addTab(pchWidget,tr("采购中心"));
    allWidgets->addTab(depWidgt,tr("部门"));
    allWidgets->addTab(empWidget,tr("员工"));
    allWidgets->addTab(pbsWidget,tr("出版商"));
    allWidgets->addTab(bkWidget,tr("书籍"));
    allWidgets->addTab(whWiget,tr("仓库"));
    allWidgets->addTab(statWidget,tr("统计"));
    allWidgets->addTab(cenWidget,tr("关于"));
}

void bookShop::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(allWidgets);
}

void bookShop::showWidget(bool isLogin)
{
    if (isLogin == true)
        this->show();
    else
        this->deleteLater();
}
