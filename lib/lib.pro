#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T14:06:09
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): Qt += widgets

TARGET = libdeepin-font-installer
TEMPLATE = lib
CONFIG += create_pc c++11 link_pkgconfig
PKGCONFIG += glib-2.0 freetype2 fontconfig

SOURCES += \
        dfontinfo.cpp

HEADERS += \
        dfontinfo.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
