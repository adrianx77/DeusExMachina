#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T13:26:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeusExMachina
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logicform.cpp \
    productdialog.cpp \
    product.cpp \
    productlist.cpp \
    pronounceNum.cpp

HEADERS  += mainwindow.h \
    logicform.h \
    productdialog.h \
    product.h \
    productlist.h \
    pronounceNum.h

FORMS    += mainwindow.ui \
    logicform.ui \
    productdialog.ui
