#ifndef BOOKSHOP_H
#define BOOKSHOP_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "widgets/centerwidget.h"
#include "widgets/department.h"
#include "widgets/employee.h"
#include "widgets/books.h"
#include "widgets/publishers.h"
#include "widgets/warehouse.h"
#include "widgets/statistics.h"
#include "widgets/clearing.h"
#include "widgets/purchase.h"
namespace Ui {
class bookShop;
}

class bookShop : public QWidget
{
    Q_OBJECT

public:
    explicit bookShop(QWidget *parent = 0);
    ~bookShop();
public:
    void initWidgets();
    void initLayout();
private:
    Ui::bookShop *ui;
    QTabWidget *allWidgets;
    centerWidget *cenWidget;
    departMent *depWidgt;
    emPloyee *empWidget;
    Books *bkWidget;
    publiShers *pbsWidget;
    wareHouse *whWiget;
    statisTics *statWidget;
    cleaRing *crWidget;
    purChase *pchWidget;
signals:

private slots:
    void showWidget(bool isLogin);
};

#endif // BOOKSHOP_H
