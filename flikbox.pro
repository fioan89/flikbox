#-------------------------------------------------
#
# Project created by QtCreator 2013-08-04T18:26:16
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flikbox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    flickrauth.cpp \
    crypto.cpp \
    httpmanager.cpp

HEADERS  += mainwindow.h \
    flickrauth.h \
    crypto.h \
    httpmanager.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../../Documents/flikbox mockups/flikbox_logo_70x50.png \
    ../../Documents/flikbox mockups/flikbox_logo_70x50.png

RESOURCES += \
    resources/flikbox.qrc
