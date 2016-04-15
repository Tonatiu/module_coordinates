#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T09:11:32
#
#-------------------------------------------------

QT       += core gui sql

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
    src/calculator/transforms/basics_calculations.cpp \
    src/calculator/filters/ndvi_filter.cpp \
    src/calculator/filters/pm10filter.cpp \
    src/calculator/filters/filter.cpp \
    src/search_save_services.cpp \
    ../../TT/workspace (2)/src/geographic/BoundingBox.cc \
    ../../TT/workspace (2)/src/geographic/Coords.cc \
    ../../TT/workspace (2)/src/geographic/GeoPoint.cc \
    ../../TT/workspace (2)/src/geographic/GeoPolygon.cc \
    ../../TT/workspace (2)/src/geographic/BoundingBox.cc \
    ../../TT/workspace (2)/src/geographic/Coords.cc \
    ../../TT/workspace (2)/src/geographic/GeoPoint.cc \
    ../../TT/workspace (2)/src/geographic/GeoPolygon.cc

HEADERS  += \
    src/calculator/basics_calculations.h \
    src/t_regex/t_regex.h \
    src/services/datafinder/mtl_data_collector.h \
    src/services/datafinder/coordinates/coordinatestable.h \
    src/services/datafinder/radiances/scene_rad_data.h \
    src/services/queue/pathqueue.h \
    src/ui/adminwindow.h \
    src/calculator/transforms/basics_calculations.h \
    src/calculator/filters/ndvi_filter.h \
    src/calculator/filters/pm10filter.h \
    src/calculator/filters/filter.h \
<<<<<<< HEAD
    src/services/search_save_services.h
=======
    ../../TT/workspace (2)/src/geographic/BoundingBox.h \
    ../../TT/workspace (2)/src/geographic/Coords.h \
    ../../TT/workspace (2)/src/geographic/GeoPoint.h \
    ../../TT/workspace (2)/src/geographic/GeoPolygon.h \
    ../../TT/workspace (2)/src/geographic/BoundingBox.h \
    ../../TT/workspace (2)/src/geographic/Coords.h \
    ../../TT/workspace (2)/src/geographic/GeoPoint.h \
    ../../TT/workspace (2)/src/geographic/GeoPolygon.h
>>>>>>> 8af42490c2bfe4f0da0153faf179925497dfefa3

FORMS    += adminwindow.ui

CONFIG += c++11
