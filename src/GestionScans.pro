#-------------------------------------------------
#
# Project created by QtCreator 2016-06-15T10:38:42
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GestionScans
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    add.cpp \
    setting.cpp \
    seriesbox.cpp

HEADERS  += mainwindow.h \
    add.h \
    setting.h \
    seriesbox.h

FORMS    += mainwindow.ui \
    add.ui \
    setting.ui