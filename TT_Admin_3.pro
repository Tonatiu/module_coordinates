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
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lpqxx -lpq -pthread

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
    src/poligons_module/geographic/GeoPolygon.cc \
    src/poligons_module/geographic/GeoPoint.cc \
    src/poligons_module/geographic/Coords.cc \
    src/poligons_module/geographic/BoundingBox.cc \
    src/poligons_module/postgis/PostgisFunctions.cc \
    src/ui/statusbar.cpp \
    src/services/copy_service/copy_service.cpp \
    src/sceneprocesor/image_processor/sceneprocessor.cpp \
    src/sceneprocesor/processingthread.cpp


HEADERS  += src/ui/adminwindow.h \
    src/t_regex/t_regex.h \
    src/services/search_save_services.h\
    src/services/queue/pathqueue.h \
    src/services/datafinder/mtl_data_collector.h \
    src/services/datafinder/radiances/scene_rad_data.h \
    src/services/datafinder/coordinates/coordinatestable.h \
    src/calculator/transforms/basics_calculations.h \
    src/calculator/filters/ndvi_filter.h \
    src/calculator/filters/pm10filter.h \
    src/calculator/filters/filter.h \
    src/poligons_module/geographic/GeoPolygon.h \
    src/poligons_module/geographic/GeoPoint.h \
    src/poligons_module/geographic/Coords.h \
    src/poligons_module/geographic/BoundingBox.h \
    src/poligons_module/postgis/PostgisFunctions.h \
    src/poligons_module/postgis/postgis.h \
    src/poligons_module/postgis/entity/Municipio.h \
    src/ui/statusbar.h \
    src/services/copy_service/copy_service.h \
    src/sceneprocesor/image_processor/sceneprocessor.h \
    src/sceneprocesor/processingthread.h

FORMS    += adminwindow.ui \
    statusbar.ui

CONFIG += c++11
