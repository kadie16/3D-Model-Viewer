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

#-------------------------------------------------
# CGAL LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lCGAL

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# CGAL CORE LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/cgal/4.5/lib/ -lCGAL_Core.10.0.4

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
#-------------------------------------------------
# CGAL IMAGE IO LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/cgal/4.5/lib/ -lCGAL_ImageIO.10.0.4

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
#-------------------------------------------------
# CGAL QT LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/cgal/4.5/lib/ -lCGAL_Qt4.10.0.4

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/cgal/4.5/include
#-------------------------------------------------
# BOOST THREAD LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/include
#-------------------------------------------------
# BOOST SYSTEM LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/lib/ -lboost_system

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/boost/1.57.0/include
#-------------------------------------------------
# GMP LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/lib/ -lgmp.10

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/gmp/6.0.0a/include
#-------------------------------------------------
# MPFR LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/lib/ -lmpfr.4

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/mpfr/3.1.2-p10/include


