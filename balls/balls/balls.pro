#-------------------------------------------------
#
# Project created by QtCreator 2016-06-12T00:30:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = balls
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    view.cpp \
    ball.cpp \
    move.cpp

HEADERS  += \
    view.h \
    ball.h \
    move.h \
    include/config.h

FORMS    +=
