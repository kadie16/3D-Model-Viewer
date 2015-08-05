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
    testqstring.cpp \
    ../../../../Qt/Examples/Qt-5.4/widgets/graphicsview/boxes/trackball.cpp \
    camera.cpp \
    objload.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    camera.h \
    objload.h \
    myitems.h

FORMS    += mainwindow.ui

macx: LIBS += -L$$PWD/../../4.5/lib/ -lCGAL.10.0.4

INCLUDEPATH += $$PWD/../../4.5/include
DEPENDPATH += $$PWD/../../4.5/include



macx: LIBS += -L$$PWD/../../1.57.0/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../1.57.0/include
DEPENDPATH += $$PWD/../../1.57.0/include

macx: LIBS += -L$$PWD/../../1.57.0/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../1.57.0/include
DEPENDPATH += $$PWD/../../1.57.0/include



macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/lib/ -lgmp.10

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/lib/ -lmpfr.4

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/include
