#ifndef CLEARING_H
#define CLEARING_H

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
class cleaRing;
}

class cleaRing : public QWidget
{
    Q_OBJECT

public:
    explicit cleaRing(QWidget *parent = 0);
    ~cleaRing();
public:
    void initWidgets();
    void initLayout();
private:
    Ui::cleaRing *ui;
private:
    QLabel *inputId,*inputNum,*allPrice;
    QLineEdit *input,*num;
    QPushButton *insert,*pay;
    QTableWidget *depTable;
    dataBase db;
    int money;
private slots:
    void add();
    void paymoney();
};

#endif // CLEARING_H
