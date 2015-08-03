#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T11:08:37
#
#-------------------------------------------------

QT       += core gui opengl
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectV1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    vertex.cpp \
    face.cpp \
    testqstring.cpp \
    ../../../../Qt/Examples/Qt-5.4/widgets/graphicsview/boxes/trackball.cpp \
    camera.cpp \
    points_and_segment.cpp \
    objload.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    vertex.h \
    vertex.h \
    face.h \
    camera.h \
    objload.h

FORMS    += mainwindow.ui

#LIBS    += -L/usr/local/Cellar/cgal/4.5/include/ -cgal

macx: LIBS += -L$$PWD/../../4.5/lib/ -lCGAL.10.0.4

INCLUDEPATH += $$PWD/../../4.5/include
DEPENDPATH += $$PWD/../../4.5/include



macx: LIBS += -L$$PWD/../../1.57.0/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../1.57.0/include
DEPENDPATH += $$PWD/../../1.57.0/include

macx: LIBS += -L$$PWD/../../1.57.0/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../1.57.0/include
DEPENDPATH += $$PWD/../../1.57.0/include
