#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T15:05:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectVMiddle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camera.cpp \
    face.cpp \
    glwidget.cpp \
    objload.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    camera.h \
    face.h \
    glwidget.h \
    objload.h \
    vertex.h

FORMS    += mainwindow.ui
