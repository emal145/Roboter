#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Roboter
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    table.cpp \
    kugel.cpp \
    quader.cpp \
    rotationsmatrix.cpp \
    robotarm.cpp \
    robot.cpp \
    geoquad.cpp \
    zylinder.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    table.h \
    kugel.h \
    robotarm.h \
    quader.h \
    rotationsmatrix.h \
    robot.h \
    geoquad.h \
    zylinder.h

FORMS    += mainwindow.ui
