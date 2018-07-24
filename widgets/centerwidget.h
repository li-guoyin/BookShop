#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "db/database.h"
namespace Ui {
class centerWidget;
}

class centerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit centerWidget(QWidget *parent = 0);
    ~centerWidget();
public:
    void initWidget();
    void initLayout();
    void showDataToTable();
private:
    Ui::centerWidget *ui;
private:
    QLabel *code,*name,*manager,*charge;
    QLineEdit *codeEdit,*nameEdit,*manageEdit,*chargeEdit;
    QPushButton *save;
    dataBase db;
};

#endif // CENTERWIDGET_H
