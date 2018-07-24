#ifndef DEPARTMENT_H
#define DEPARTMENT_H

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
class departMent;
}

class departMent : public QWidget
{
    Q_OBJECT

public:
    explicit departMent(QWidget *parent = 0);
    ~departMent();
public:
    void initWidget();
    void initLayout();
    void showDataToTable();
private:
    Ui::departMent *ui;
private:
    QLabel *depname,*supervisor,*address,*tel,*charge;
    QLineEdit *depnameEdit,*supervisorEdit,*addressEdit,*telEdit,*chargeEdit;
    QPushButton *add,*del,*save;
    QTableWidget *depTable;
    dataBase db;
    QString oldName;
private slots:
    void addAction();
    void delAction();
    void saveAction();
    void doubleClick(QTableWidgetItem*);
};

#endif // DEPARTMENT_H
