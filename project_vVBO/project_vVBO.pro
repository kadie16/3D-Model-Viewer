#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T11:08:37
#
#-------------------------------------------------

QT       += core gui opengl
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project_vVBO
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    camera.cpp \
    objload.cpp \
    model.cpp \

HEADERS  += mainwindow.h \
    glwidget.h \
    camera.h \
    objload.h \
    myitems.h \
    model.h \

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
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lCGAL_Core.11

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# CGAL IMAGE IO LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lCGAL_ImageIO

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# BOOST THREAD LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lboost_thread-mt

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# BOOST SYSTEM LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lboost_system-mt

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# GMP LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lgmp

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
#-------------------------------------------------
# MPFR LIBRARY
#-------------------------------------------------
macx: LIBS += -L$$PWD/../../../../../../opt/local/lib/ -lmpfr

INCLUDEPATH += $$PWD/../../../../../../opt/local/include
DEPENDPATH += $$PWD/../../../../../../opt/local/include
