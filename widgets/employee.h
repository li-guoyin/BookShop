#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "db/database.h"
namespace Ui {
class emPloyee;
}

class emPloyee : public QWidget
{
    Q_OBJECT

public:
    explicit emPloyee(QWidget *parent = 0);
    ~emPloyee();
public:
    void initWidget();
    void initLayout();
    void showDataToTable();
private:
    Ui::emPloyee *ui;
private:
    QLabel *acinfo,*emplinfo,*account,*psw,*tel;
    QLabel *name,*dep,*title,*age,*salary;
    QLineEdit *accountEdit,*pswEdit;
    QLineEdit *nameEdit,*depEdit,*titleEdit,*ageEdit,*salaryEdit,*telEdit;
    QCheckBox *isAdmin;
    QRadioButton *man,*woman;
    //QButtonGroup *btngroup;
    QPushButton *add,*del,*save;
    QTableWidget *depTable;
    dataBase db;
    QString sexdb;
    QString oldID;
private slots:
    void addAction();
    void delAction();
    void saveAction();
    void doubleClick(QTableWidgetItem*);
    void manBtn();
    void womanBtn();
};

#endif // EMPLOYEE_H
