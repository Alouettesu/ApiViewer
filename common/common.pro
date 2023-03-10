#-------------------------------------------------
#
# Project created by QtCreator 2023-02-04T16:22:28
#
#-------------------------------------------------

QT       += sql network concurrent core

QT       -= gui

TARGET = ApiViewerCommon
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apicacheupdatedaemon.cpp \
    apigetter.cpp \
    apimodel.cpp \
    apiparser.cpp \
    apismodel.cpp \
    database.cpp \
    elementsmodel.cpp


HEADERS += \
    apicacheupdatedaemon.cpp \
    apicacheupdatedaemon.h \
    apigetter.h \
    apimodel.h \
    apiparser.h \
    apismodel.h \
    database.h \
    elementsmodel.h

RESOURCES += \
    dbresource.qrc \

QMAKE_CLEAN += \
    apis.db

unix {
    target.path = /usr/lib
    INSTALLS += target
}
