#ifndef WAREHOUSE_H
#define WAREHOUSE_H

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
class wareHouse;
}

class wareHouse : public QWidget
{
    Q_OBJECT

public:
    explicit wareHouse(QWidget *parent = 0);
    ~wareHouse();
public:
    void initWidgets();
    void initLayout();
    void showDataToTable();
private:
    Ui::wareHouse *ui;
private:
    QLabel *name,*housetel,*Admin,*charge;
    QLineEdit *nameEdit,*housetelEdit,*AdminEdit,*chargeEdit;
    QPushButton *add,*del,*save;
    QTableWidget *depTable;
    QString oldID;
    dataBase db;
private slots:
    void addAction();
    void delAction();
    void saveAction();
    void doubleClick(QTableWidgetItem*);
};

#endif // WAREHOUSE_H
