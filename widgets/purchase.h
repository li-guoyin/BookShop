#ifndef PURCHASE_H
#define PURCHASE_H

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
class purChase;
}

class purChase : public QWidget
{
    Q_OBJECT

public:
    explicit purChase(QWidget *parent = 0);
    ~purChase();
public:
    void initWidgets();
    void initLayout();
private:
    Ui::purChase *ui;
private:
    QLabel *inputName,*inputPrice,*inputNum,*inputPbs,*allPrice;
    QLineEdit *inputNameEdit,*inputPriceEdit,*inputNumEdit,*inputPbsEdit;
    QPushButton *insert,*pay;
    QTableWidget *depTable;
    int money;
private slots:
    void add();
    void paymoney();
};

#endif // PURCHASE_H
