#-------------------------------------------------
#
# Project created by QtCreator 2014-08-07T12:53:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LecteurBinaires
TEMPLATE = app


SOURCES += main.cpp\
        mainfen.cpp \
    cparseurxml.cpp \
    cregleparsage.cpp \
    cimportexport.cpp \
    cchampbinaire.cpp \
    cdebugconsole.cpp \
    parsingthread.cpp

HEADERS  += mainfen.h \
    cparseurxml.h \
    cregleparsage.h \
    cimportexport.h \
    cchampbinaire.h \
    cdebugconsole.h \
    parsingthread.h

FORMS    += mainfen.ui \
    cdebugconsole.ui

RESOURCES += \
    resources.qrc
