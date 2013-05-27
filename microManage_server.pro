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
    micromanager.cpp \
    qprocessmanager_simple.cpp \
    qemuvm_qprocess.cpp \
    qemuvm_popen.cpp

HEADERS += \
    micromachine.h \
    micromanager.h \
    qprocessmanager_simple.h \
    qemuvm_qprocess.h \
    qemuvm_popen.h

