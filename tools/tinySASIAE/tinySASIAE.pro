#-------------------------------------------------
#
# Project created by QtCreator 2014-09-22T10:39:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tinySASIAE
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp \
    physicsengine.cpp \
    robotbin.cpp

HEADERS  += \
    mainwindow.hpp\
    robot.hpp \
    physicsengine.hpp \
    robotbin.hpp

FORMS    += mainwindow.ui

target.path = /usr/local/bin
INSTALLS += target
