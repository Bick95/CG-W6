#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T12:26:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_transformations
TEMPLATE = app
CONFIG += c++11 -std=libc++

SOURCES += main.cpp\
    mainwindow.cpp \
    mainview.cpp \
    user_input.cpp \
    model.cpp \
    utility.cpp

HEADERS  += mainwindow.h \
    mainview.h \
    model.h \
    triangle.h \
    material.h \
    vertex.h \
    light.h

FORMS    += mainwindow.ui

QMAKE_MAC_SDK = macosx10.14

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc
