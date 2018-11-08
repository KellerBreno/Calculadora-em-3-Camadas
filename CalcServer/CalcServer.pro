#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T11:08:11
#
#-------------------------------------------------

QT       += core gui network widgets sql

TARGET = CalcServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    databasehelperimpl.cpp \
    workerthreadimpl.cpp \
    serverimpl.cpp \
    serverdialogimpl.cpp

HEADERS += \
    databasehelper.h \
    databasehelperimpl.h \
    workerthreadimpl.h \
    workerthread.h \
    serverimpl.h \
    server.h \
    serverdialogimpl.h \
    serverdialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
