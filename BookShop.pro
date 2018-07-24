#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T11:01:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookShop
TEMPLATE = app


SOURCES += main.cpp\
    widgets/centerwidget.cpp \
    bookShop.cpp \
    widgets/department.cpp \
    widgets/employee.cpp \
    widgets/books.cpp \
    widgets/publishers.cpp \
    widgets/warehouse.cpp \
    widgets/statistics.cpp \
    widgets/purchase.cpp \
    widgets/clearing.cpp \
    widgets/salesreport.cpp \
    widgets/purchasereport.cpp \
    widgets/salaryreport.cpp \
    widgets/login.cpp \
    db/database.cpp

HEADERS  += bookShop.h \
    widgets/centerwidget.h \
    widgets/department.h \
    widgets/employee.h \
    widgets/books.h \
    widgets/publishers.h \
    widgets/warehouse.h \
    widgets/statistics.h \
    widgets/purchase.h \
    widgets/clearing.h \
    widgets/salesreport.h \
    widgets/purchasereport.h \
    widgets/salaryreport.h \
    widgets/login.h \
    db/database.h

FORMS    += \
    widgets/centerwidget.ui \
    widgets/department.ui \
    widgets/employee.ui \
    widgets/books.ui \
    widgets/publishers.ui \
    widgets/warehouse.ui \
    widgets/statistics.ui \
    widgets/purchase.ui \
    widgets/clearing.ui \
    widgets/salesreport.ui \
    widgets/purchasereport.ui \
    widgets/salaryreport.ui \
    widgets/login.ui

RESOURCES += \
    src.qrc
