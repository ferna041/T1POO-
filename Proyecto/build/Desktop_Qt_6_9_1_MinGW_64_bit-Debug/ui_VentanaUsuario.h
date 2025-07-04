/********************************************************************************
** Form generated from reading UI file 'VentanaUsuario.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAUSUARIO_H
#define UI_VENTANAUSUARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VentanaUsuario
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *catalogo;
    QWidget *publicar;
    QWidget *tab_2;
    QWidget *reservas;
    QWidget *Notificaciones;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *VentanaUsuario)
    {
        if (VentanaUsuario->objectName().isEmpty())
            VentanaUsuario->setObjectName("VentanaUsuario");
        VentanaUsuario->resize(1300, 850);
        centralwidget = new QWidget(VentanaUsuario);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 1300, 850));
        catalogo = new QWidget();
        catalogo->setObjectName("catalogo");
        catalogo->setStyleSheet(QString::fromUtf8("QWidget#catalogo {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #212529;\n"
"}"));
        tabWidget->addTab(catalogo, QString());
        publicar = new QWidget();
        publicar->setObjectName("publicar");
        publicar->setStyleSheet(QString::fromUtf8("QWidget#publicar {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #212529;\n"
"}"));
        tabWidget->addTab(publicar, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tab_2->setStyleSheet(QString::fromUtf8("QWidget#tab_2 {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #212529;\n"
"}"));
        tabWidget->addTab(tab_2, QString());
        reservas = new QWidget();
        reservas->setObjectName("reservas");
        reservas->setStyleSheet(QString::fromUtf8("QWidget#reservas {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #212529;\n"
"}"));
        tabWidget->addTab(reservas, QString());
        Notificaciones = new QWidget();
        Notificaciones->setObjectName("Notificaciones");
        Notificaciones->setStyleSheet(QString::fromUtf8("QWidget#Notificaciones {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #212529;\n"
"}"));
        tabWidget->addTab(Notificaciones, QString());
        VentanaUsuario->setCentralWidget(centralwidget);
        menubar = new QMenuBar(VentanaUsuario);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1300, 21));
        VentanaUsuario->setMenuBar(menubar);
        statusbar = new QStatusBar(VentanaUsuario);
        statusbar->setObjectName("statusbar");
        VentanaUsuario->setStatusBar(statusbar);

        retranslateUi(VentanaUsuario);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VentanaUsuario);
    } // setupUi

    void retranslateUi(QMainWindow *VentanaUsuario)
    {
        VentanaUsuario->setWindowTitle(QCoreApplication::translate("VentanaUsuario", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(catalogo), QCoreApplication::translate("VentanaUsuario", "Cat\303\241logo", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(publicar), QCoreApplication::translate("VentanaUsuario", "Publicar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("VentanaUsuario", "Mis Objetos", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(reservas), QCoreApplication::translate("VentanaUsuario", "Mis reservas", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Notificaciones), QCoreApplication::translate("VentanaUsuario", "Notificaciones", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VentanaUsuario: public Ui_VentanaUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAUSUARIO_H
