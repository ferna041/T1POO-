QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    broker.cpp \
    component.cpp \
    publisher.cpp \
    subscriber.cpp \
    topic.cpp \
    videofollower.cpp \
    videopublisher.cpp \
    gpscarpublisher.cpp \
    gpscarfollower.cpp

HEADERS += \
    mainwindow.h \
    broker.h \
    component.h \
    publisher.h \
    subscriber.h \
    topic.h \
    videofollower.h \
    videopublisher.h \
    gpscarpublisher.h \
    gpscarfollower.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
