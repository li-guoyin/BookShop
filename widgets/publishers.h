#ifndef PUBLISHERS_H
#define PUBLISHERS_H

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
class publiShers;
}

class publiShers : public QWidget
{
    Q_OBJECT

public:
    explicit publiShers(QWidget *parent = 0);
    ~publiShers();
public:
    void initWidgets();
    void initLayout();
    void showDataToTable();
private:
    Ui::publiShers *ui;
private:
    QLabel *name,*tel,*address;
    QLineEdit *nameEdit,*telEdit,*addressEdit;
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

#endif // PUBLISHERS_H
