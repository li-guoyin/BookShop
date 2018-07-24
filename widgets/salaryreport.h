#ifndef SALARYREPORT_H
#define SALARYREPORT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include "db/database.h"
namespace Ui {
class salaryReport;
}

class salaryReport : public QWidget
{
    Q_OBJECT

public:
    explicit salaryReport(QWidget *parent = 0);
    ~salaryReport();
    void initWidget();
    void initLayout();
    void showTable(QString datestart,QString dateend);
private:
    Ui::salaryReport *ui;
    QTableWidget *depTable;
    QLabel *allPrice;
    QPushButton *shuaxin;
    int money;
    QString start;
    QString end;
private slots:
    void reflash();
};

#endif // SALARYREPORT_H
