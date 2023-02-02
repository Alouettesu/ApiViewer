#-------------------------------------------------
#
# Project created by QtCreator 2023-01-28T12:29:22
#
#-------------------------------------------------

QT       += core gui sql network concurrent quick

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ApiViewer
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


SOURCES += \
        main.cpp \
#        mainwindow.cpp \
    apismodel.cpp \
    database.cpp \
    apigetter.cpp \
    apimodel.cpp \
    apiparser.cpp \
    apicacheupdatedaemon.cpp \
    elementsmodel.cpp \
    apiscontroller.cpp \
    apielementscontroller.cpp

HEADERS += \
#        mainwindow.h \
    apismodel.h \
    database.h \
    apigetter.h \
    apimodel.h \
    apiparser.h \
    apicacheupdatedaemon.h \
    elementsmodel.h \
    apiscontroller.h \
    apielementscontroller.h

FORMS += \
        mainwindow.ui

OTHER_FILES += \
    .gitignore

DISTFILES += \
    readme.md

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

RESOURCES += \
    dbresource.qrc \
    qml/qml.qrc

QMAKE_CLEAN += \
    apis.db
