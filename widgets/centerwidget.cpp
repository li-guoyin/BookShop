#include "centerwidget.h"
#include "ui_centerwidget.h"

centerWidget::centerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::centerWidget)
{
    QPalette p;
    p.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(p);
    setAutoFillBackground(true);//颜色要生效必须设置这句话
    ui->setupUi(this);
    initWidget();
    initLayout();
    showDataToTable();
}

centerWidget::~centerWidget()
{
    delete ui;
}

void centerWidget::initWidget()
{
    code = new QLabel(tr("中心编码:"),this);
    name = new QLabel(tr("名称:"),this);
    manager = new QLabel(tr("总经理:"),this);
    charge = new QLabel(tr("运营费用:"),this);

    codeEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    manageEdit = new QLineEdit(this);
    chargeEdit = new QLineEdit(this);

    save = new QPushButton(tr("保存"),this);
}

void centerWidget::initLayout()
{
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(code,0,0,1,1);
    layout->addWidget(codeEdit,0,1,1,2);
    layout->addWidget(name,1,0,1,1);
    layout->addWidget(nameEdit,1,1,1,2);
    layout->addWidget(manager,2,0,1,1);
    layout->addWidget(manageEdit,2,1,1,2);
    layout->addWidget(charge,3,0,1,1);
    layout->addWidget(chargeEdit,3,1,1,2);
    layout->addWidget(save,4,2,1,2);
    layout->setAlignment(Qt::AlignTop|Qt::AlignLeft);
}

void centerWidget::showDataToTable()
{
    QSqlQuery query("SELECT * FROM center");
    query.first();
    //从数据库中将数据取出
    QString id = query.value("Id").toString();
    QString namedb = query.value("name").toString();
    QString managername = query.value("managername").toString();
    QString cost = query.value("cost").toString();

    codeEdit->setText(id);
    nameEdit->setText(namedb);
    manageEdit->setText(managername);
    chargeEdit->setText(cost);

}
