#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T15:17:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Control
TEMPLATE = app

HEADERS += \
    ../include/wggestion.h \
    ../ui/frmcontrol.h \
    ../include/frmcontrol.h

SOURCES += \
    ../src/wggestion.cpp \
    ../src/main.cpp \
    ../src/frmcontrol.cpp

FORMS += \
    ../ui/wggestion.ui \
    ../ui/frmcontrol.ui


