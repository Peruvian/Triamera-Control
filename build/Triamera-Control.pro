#-------------------------------------------------
#
# Project created by QtCreator 2014-04-03T15:42:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Triamera-Control
TEMPLATE = app

SOURCES += \
    ../src/api.cpp \
    ../src/core.cpp \
    ../src/main.cpp \
    ../src/core/huffman.cpp \
#    ../extlibs/QLogger/QLogger.cpp \
    ../src/core/TRI_Logger.cpp \
    ../src/core/TRI_Setting.cpp \
    ../src/core/TRI_Huffman.cpp

HEADERS  += \
    ../include/api.h \
    ../include/core.h \
    ../include/core/huffman.h \
#    ../extlibs/QLogger/QLogger.h \
    ../include/core/TRI_Logger.h \
    ../include/core/TRI_Setting.h \
    ../include/core/TRI_Huffman.h

FORMS    +=
