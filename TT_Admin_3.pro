#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T09:11:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TT_Admin_3
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
               /usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

SOURCES += main.cpp\
    src/ui/adminwindow.cpp \
    src/t_regex/t_regex.cpp \
    src/services/search_save_services.cpp \
    src/services/queue/pathqueue.cpp \
    src/services/datafinder/mtl_data_collector.cpp \
    src/services/datafinder/radiances/scene_rad_data.cpp \
    src/services/datafinder/coordinates/coordinatestable.cpp \
    src/calculator/basics_calculations.cpp

HEADERS  += \
    src/calculator/basics_calculations.h \
    src/t_regex/t_regex.h \
    src/services/search_save_services.h \
    src/services/datafinder/mtl_data_collector.h \
    src/services/datafinder/coordinates/coordinatestable.h \
    src/services/datafinder/radiances/scene_rad_data.h \
    src/services/queue/pathqueue.h \
    src/ui/adminwindow.h

FORMS    += adminwindow.ui

CONFIG += c++11
