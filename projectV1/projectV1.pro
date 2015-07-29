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
    objload.cpp \
    vertex.cpp \
    face.cpp \
    testqstring.cpp \
    ../../../../Qt/Examples/Qt-5.4/widgets/graphicsview/boxes/trackball.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objload.h \
    vertex.h \
    vertex.h \
    face.h \
    camera.h

FORMS    += mainwindow.ui


