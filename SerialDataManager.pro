#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T21:57:27
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialDataManager
TEMPLATE = app


SOURCES += main.cpp\
    connectionmanager.cpp \
    serial/serialcontroller.cpp \
    manualserialcontroller.cpp \
    serialportbrowser.cpp \
    mainwidget.cpp

HEADERS  += \
    connectionmanager.h \
    serial/serialcontroller.h \
    serial/serial.h \
    manualserialcontroller.h \
    serialportbrowser.h \
    mainwidget.h

FORMS    += \
    manualserialcontroller.ui \
    serialportbrowser.ui \
    mainwidget.ui
