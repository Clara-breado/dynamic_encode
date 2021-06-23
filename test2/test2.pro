#-------------------------------------------------
#
# Project created by QtCreator 2021-05-31T00:12:47
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
RC_ICONS = train.ico
RESOURCES += res.qrc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
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
        lightbars.cpp \
        lights.cpp \
        logic_lb.cpp \
        logic_light.cpp \
        logic_train.cpp \
        main.cpp \
        myscene.cpp \
        train.cpp \
        widget.cpp

HEADERS += \
        lightbars.h \
        lights.h \
        logic_lb.h \
        logic_light.h \
        logic_train.h \
        myscene.h \
        setting.h \
        train.h \
        widget.h

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    static_db_1.xlsx
