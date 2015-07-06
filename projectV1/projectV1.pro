#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T11:08:37
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectV1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    objload.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objload.h \
    vertex.h \
    vertex.h

FORMS    += mainwindow.ui

#LIBS    += -L/usr/local/Cellar/cgal/4.5 -cgal
