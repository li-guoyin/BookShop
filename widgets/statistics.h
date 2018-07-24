#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QTabWidget>
#include <QDateEdit>
#include "widgets/purchasereport.h"
#include "widgets/salaryreport.h"
#include "widgets/salesreport.h"
namespace Ui {
class statisTics;
}

class statisTics : public QWidget
{
    Q_OBJECT

public:
    explicit statisTics(QWidget *parent = 0);
    ~statisTics();
public:
    void initWidgets();
    void initLayout();
private:
    Ui::statisTics *ui;
private:
    QLabel *label1,*label2;
    QDateEdit *date1,*date2;
    QPushButton *look;
    QTabWidget *allReports;
    purchaseReport *purReport;
    salesReport *salReport;
    salaryReport *slryReport;
private slots:
    void lookreport();
};

#endif // STATISTICS_H
