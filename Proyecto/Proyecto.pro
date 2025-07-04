QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Include paths para las carpetas organizadas
INCLUDEPATH += src \
               src/models \
               src/database \
               src/ui

SOURCES += \
    src/ui/FormularioObjeto.cpp \
    src/ui/ListaObjetos.cpp \
    src/ui/ListaReservas.cpp \
    src/ui/ListaUsuarios.cpp \
    src/main.cpp \
    src/ui/Notificaciones.cpp \
    src/ui/VentanaUsuario.cpp \
    src/ui/mainwindow.cpp \
    src/ui/FormularioUsuario.cpp \
    src/database/DatabaseManager.cpp

HEADERS += \
    src/ui/FormularioObjeto.h \
    src/ui/ListaObjetos.h \
    src/ui/ListaReservas.h \
    src/ui/ListaUsuarios.h \
    src/ui/Notificaciones.h \
    src/ui/VentanaUsuario.h \
    src/ui/mainwindow.h \
    src/ui/FormularioUsuario.h \
    src/database/DatabaseManager.h \
    src/models/Usuario.h \
    src/models/Objeto.h \
    src/models/Notificacion.h \
    src/models/Reserva.h

FORMS += \
    src/ui/FormularioObjeto.ui \
    src/ui/FormularioUsuario.ui \
    src/ui/ListaObjetos.ui \
    src/ui/ListaReservas.ui \
    src/ui/ListaUsuarios.ui \
    src/ui/Notificaciones.ui \
    src/ui/VentanaUsuario.ui \
    src/ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
