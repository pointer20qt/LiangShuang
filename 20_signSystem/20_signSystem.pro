#-------------------------------------------------
#
# Project created by QtCreator 2020-02-06T16:54:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 20_signSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    person.cpp \
    login.cpp \
    formregister.cpp

HEADERS  += widget.h \
    person.h \
    login.h \
    formregister.h

FORMS    += widget.ui \
    person.ui \
    login.ui \
    formregister.ui

RESOURCES += \
    Resources/resources.qrc

DISTFILES +=
