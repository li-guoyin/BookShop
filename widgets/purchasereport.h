#ifndef PURCHASEREPORT_H
#define PURCHASEREPORT_H

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
class purchaseReport;
}

class purchaseReport : public QWidget
{
    Q_OBJECT

public:
    explicit purchaseReport(QWidget *parent = 0);
    ~purchaseReport();
    void initWidget();
    void initLayout();
    void showTable(QString datestart,QString dateend);
private:
    Ui::purchaseReport *ui;
    QTableWidget *depTable;
    QLabel *allPrice;
    QPushButton *shuaxin;
    int money;
    QString start;
    QString end;
private slots:
    void reflash();
};

#endif // PURCHASEREPORT_H
