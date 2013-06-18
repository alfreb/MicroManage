#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T12:51:23
#
#-------------------------------------------------
QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64

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
    experiment.cpp \
    sampler.cpp \
    ../perfdata/perfSampler.cpp \
    ../perfdata/memDataPoint.cpp \
    ../perfdata/cpuSample2.cpp \
    ../perfdata/scalingSample.cpp \
    qemuvm_microcore.cpp
    #qemuvm_popen.cpp

HEADERS += \
    micromachine.h \
    micromanager.h \
    qprocessmanager_simple.h \
    qemuvm_qprocess.h \
    experiment.h \
    sampler.h \
    ../perfdata/perfSampler.h \
    ../perfdata/memDataPoint.h \
    ../perfdata/cpuSample2.h \
    outstream.h \
    ../perfdata/scalingSample.h \
    ../perfdata/globals.h \
    qemuvm_microcore.h
    #qemuvm_popen.h

