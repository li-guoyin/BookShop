#ifndef SALESREPORT_H
#define SALESREPORT_H

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
class salesReport;
}

class salesReport : public QWidget
{
    Q_OBJECT

public:
    explicit salesReport(QWidget *parent = 0);
    ~salesReport();
    void initWidget();
    void initLayout();
    void showTable(QString datestart,QString dateend);

private:
    Ui::salesReport *ui;
    QTableWidget *depTable;
    QLabel *allPrice;
    QPushButton *shuaxin;
    int money;
    QString start;
    QString end;

private slots:
    void reflash();
};

#endif // SALESREPORT_H
