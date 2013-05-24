#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T12:51:23
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = microManage_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    micromachine.cpp \
    qemuvm.cpp \
    micromanager.cpp

HEADERS += \
    micromachine.h \
    qemuvm.h \
    micromanager.h

