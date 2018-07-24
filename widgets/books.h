#ifndef BOOKS_H
#define BOOKS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QComboBox>
#include "db/database.h"
namespace Ui {
class Books;
}

class Books : public QWidget
{
    Q_OBJECT

public:
    explicit Books(QWidget *parent = 0);
    ~Books();
public:
    void initWidgets();
    void initLayout();
    void showDataToTable();
private:
    Ui::Books *ui;
    QLabel *name,*publishers,*rule,*Wlprice,*Rtprice,*cost,*count;
    QLineEdit *nameEdit,*ruleEdit,*WlpriceEdit,*RtpriceEdit,*costEdit,*countEdit;
    QLineEdit *psComBox;
    QPushButton *add,*del,*save;
    QTableWidget *depTable;
    dataBase db;
    QString oldID;
private slots:
    void addAction();
    void delAction();
    void saveAction();
    void doubleClick(QTableWidgetItem*);
};

#endif // BOOKS_H
