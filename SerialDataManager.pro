#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T21:57:27
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = SerialDataManager
TEMPLATE = app


SOURCES += main.cpp\
    connectionmanager.cpp \
    serial/serialcontroller.cpp \
    manualserialcontroller.cpp \
    serialportbrowser.cpp \
    mainwidget.cpp \
    data/product.cpp \
    api/getallproducts.cpp \
    api/postproduct.cpp \
    api/command.cpp \
    api/commandqueue.cpp \
    api/irequester.cpp \
    api/debugresponder.cpp \
    datatransfer.cpp \
    globalsettings.cpp \
    serial/serialsession.cpp \
    serial/startpacket.cpp \
    serial/serial.cpp \
    logger.cpp \
    serial/signalpacket.cpp \
    data/productsmanager.cpp \
    serial/errorpacket.cpp \
    serial/serialportparams.cpp \
    serial/serialport.cpp

HEADERS  += \
    connectionmanager.h \
    serial/serialcontroller.h \
    serial/serial.h \
    manualserialcontroller.h \
    serialportbrowser.h \
    mainwidget.h \
    data/product.h \
    api/getallproducts.h \
    api/irequester.h \
    api/postproduct.h \
    api/command.h \
    api/commandqueue.h \
    api/iresponder.h \
    api/debugresponder.h \
    datatransfer.h \
    globalsettings.h \
    settings.h \
    serial/serialsession.h \
    serial/startpacket.h \
    logger.h \
    serial/signalpacket.h \
    data/productsmanager.h \
    serial/errorpacket.h \
    api/icommand.h \
    serial/serialportparams.h \
    serial/serialport.h

FORMS    += \
    manualserialcontroller.ui \
    serialportbrowser.ui \
    mainwidget.ui \
    datatransfer.ui \
    globalsettings.ui
