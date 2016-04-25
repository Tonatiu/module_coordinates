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
    src/services/datafinder/mtl_data_collector.cpp \
    src/services/datafinder/radiances/scene_rad_data.cpp \
    src/services/datafinder/coordinates/coordinatestable.cpp \
    src/calculator/transforms/basics_calculations.cpp \
    src/calculator/filters/ndvi_filter.cpp \
    src/calculator/filters/pm10filter.cpp \
    src/services/copy_service/copy_service.cpp \
    src/sceneprocesor/image_processor/sceneprocessor.cpp \
    src/sceneprocesor/processingthread.cpp \
    src/services/copy_service/copythread.cpp \
    src/services/filter/datafilter.cpp \
    src/postgis/postgis/PostgisFunctions.cc \
    src/postgis/geographic/GeoPolygon.cc \
    src/postgis/geographic/GeoPoint.cc \
    src/postgis/geographic/Coords.cc \
    src/postgis/geographic/BoundingBox.cc \
    src/calculator/filters/filter.cpp \
    src/sceneprocesor/scene_cutter/infoobjetivo.cpp \
    src/relations/scenedatarelations.cpp \
    src/sceneprocesor/image_processor/areaprocesor.cpp \
    src/sceneprocesor/image_processor/bandscontainer.cpp \
    src/sceneprocesor/scene_cutter/cutter.cpp \
    src/ui/copybar.cpp


HEADERS  += src/ui/adminwindow.h \
    src/t_regex/t_regex.h \
    src/services/search_save_services.h\
    src/services/datafinder/mtl_data_collector.h \
    src/services/datafinder/radiances/scene_rad_data.h \
    src/services/datafinder/coordinates/coordinatestable.h \
    src/calculator/transforms/basics_calculations.h \
    src/calculator/filters/ndvi_filter.h \
    src/calculator/filters/pm10filter.h \
    src/services/copy_service/copy_service.h \
    src/sceneprocesor/image_processor/sceneprocessor.h \
    src/sceneprocesor/processingthread.h \
    src/services/datafinder/mtl_header_regex.h \
    src/services/copy_service/copythread.h \
    src/services/filter/datafilter.h \
    src/postgis/postgis/PostgisFunctions.h \
    src/postgis/postgis/postgis.h \
    src/postgis/postgis/entity/AreaObjetivo.h \
    src/postgis/geographic/GeoPolygon.h \
    src/postgis/geographic/GeoPoint.h \
    src/postgis/geographic/Coords.h \
    src/postgis/geographic/BoundingBox.h \
    src/calculator/filters/filter.h \
    src/sceneprocesor/scene_cutter/infoobjetivo.h \
    src/relations/scenedatarelations.h \
    src/sceneprocesor/image_processor/areaprocesor.h \
    src/sceneprocesor/image_processor/bandscontainer.h \
    src/sceneprocesor/scene_cutter/cutter.h \
    src/ui/copybar.h

FORMS    += adminwindow.ui \
    src/ui/copybar.ui

CONFIG += c++11
