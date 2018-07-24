#include "statistics.h"
#include "ui_statistics.h"

statisTics::statisTics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statisTics)
{
    ui->setupUi(this);
    initWidgets();
    initLayout();
    connect(look,SIGNAL(clicked()),this,SLOT(lookreport()));
}

statisTics::~statisTics()
{
    delete ui;
}

void statisTics::initWidgets()
{
    label1 = new QLabel(tr("报表时间范围: "),this);
    label2 = new QLabel(tr("至"),this);
    date1 = new QDateEdit(this);
    date2 = new QDateEdit(this);
    look = new QPushButton(tr("查看分析报表"),this);
    purReport = new purchaseReport();
    salReport = new salesReport();
    slryReport = new salaryReport();

    allReports = new QTabWidget(this);
    allReports->addTab(purReport,tr("销售报表"));
    allReports->addTab(salReport,tr("采购报表"));
    allReports->addTab(slryReport,tr("员工工资报表"));

}

void statisTics::initLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(label1);
    hlayout->addWidget(date1);
    hlayout->addWidget(label2);
    hlayout->addWidget(date2);
    hlayout->addWidget(look);
    hlayout->addStretch();

    layout->addLayout(hlayout,Qt::AlignTop);
    layout->addWidget(allReports);
}

void statisTics::lookreport()
{
    QString datestart = date1->text();
    QString dateend = date2->text();
    purReport->showTable(datestart,dateend);
    salReport->showTable(datestart,dateend);
    slryReport->showTable(datestart,dateend);
}
