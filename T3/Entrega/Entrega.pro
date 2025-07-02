QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Entrega

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    broker.cpp \
    component.cpp \
    publisher.cpp \
    subscriber.cpp \
    topic.cpp \
    videofollower.cpp \
    videopublisher.cpp

HEADERS += \
    mainwindow.h \
    broker.h \
    component.h \
    publisher.h \
    subscriber.h \
    topic.h \
    videofollower.h \
    videopublisher.h

FORMS += \
    mainwindow.ui
