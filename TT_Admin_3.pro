#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T09:11:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TT_Admin_3
TEMPLATE = app


SOURCES += main.cpp\
        adminwindow.cpp \
    search_save_services.cpp \
    pathqueue.cpp \
    coordinatestable.cpp

HEADERS  += adminwindow.h \
    search_save_services.h \
    pathqueue.h \
    coordinatestable.h

FORMS    += adminwindow.ui
