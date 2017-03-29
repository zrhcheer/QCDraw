#-------------------------------------------------
#
# Project created by QtCreator 2016-02-26T14:53:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L../../lib -lUsrControl
INCLUDEPATH +=  ../../UsrDefineControl /usr/local/include


DESTDIR += ../../../bin

TARGET = QCDraw
TEMPLATE = app

LIBS += -L../../../lib  -lQCDraw
INCLUDEPATH += ../QCDraw

SOURCES += main.cpp\
        qcdrawmainwin.cpp \
    eletoolitem.cpp \
    toolwidget.cpp \
    controltoolwidget.cpp \
    specialtoolwidget.cpp \
    specieletoolitem.cpp

HEADERS  += qcdrawmainwin.h \
    eletoolitem.h \
    toolwidget.h \
    controltoolwidget.h \
    specialtoolwidget.h \
    specieletoolitem.h

FORMS    += qcdrawmainwin.ui

RESOURCES   +=	tool.qrc
