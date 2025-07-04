/********************************************************************************
** Form generated from reading UI file 'Notificaciones.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICACIONES_H
#define UI_NOTIFICACIONES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notificaciones
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitulo;
    QHBoxLayout *layoutControles;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnActualizar;
    QPushButton *btnMarcarLeidas;
    QPushButton *btnEliminarTodas;
    QScrollArea *scrollAreaNotificaciones;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *layoutNotificaciones;
    QLabel *labelSinNotificaciones;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Notificaciones)
    {
        if (Notificaciones->objectName().isEmpty())
            Notificaciones->setObjectName("Notificaciones");
        Notificaciones->resize(800, 600);
        Notificaciones->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #f8f9fa;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #333;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #007bff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 8px 16px;\n"
"    font-weight: 500;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #0056b3;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #004085;\n"
"}\n"
"\n"
"QPushButton#btnMarcarLeidas {\n"
"    background-color: #28a745;\n"
"}\n"
"\n"
"QPushButton#btnMarcarLeidas:hover {\n"
"    background-color: #1e7e34;\n"
"}\n"
"\n"
"QPushButton#btnEliminarTodas {\n"
"    background-color: #dc3545;\n"
"}\n"
"\n"
"QPushButton#btnEliminarTodas:hover {\n"
"    background-color: #c82333;\n"
"}\n"
"\n"
"QScrollArea {\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QScrollArea QWidget {\n"
""
                        "    background-color: white;\n"
"}\n"
"\n"
"QFrame.notificacion-item {\n"
"    background-color: white;\n"
"    border: 1px solid #e9ecef;\n"
"    border-radius: 8px;\n"
"    margin: 4px;\n"
"    padding: 12px;\n"
"}\n"
"\n"
"QFrame.notificacion-item:hover {\n"
"    background-color: #f8f9fa;\n"
"    border-color: #007bff;\n"
"}\n"
"\n"
"QFrame.notificacion-nueva {\n"
"    background-color: #e3f2fd;\n"
"    border-color: #2196f3;\n"
"}\n"
"\n"
"QLabel.titulo-notificacion {\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"    color: #2c3e50;\n"
"    margin-bottom: 4px;\n"
"}\n"
"\n"
"QLabel.mensaje-notificacion {\n"
"    font-size: 13px;\n"
"    color: #555;\n"
"    line-height: 1.4;\n"
"}\n"
"\n"
"QLabel.fecha-notificacion {\n"
"    font-size: 11px;\n"
"    color: #6c757d;\n"
"    font-style: italic;\n"
"}\n"
"\n"
"QLabel.tipo-notificacion {\n"
"    font-size: 10px;\n"
"    font-weight: 600;\n"
"    padding: 2px 8px;\n"
"    border-radius: 12px;\n"
"    color: white;\n"
"}"));
        verticalLayout = new QVBoxLayout(Notificaciones);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        labelTitulo = new QLabel(Notificaciones);
        labelTitulo->setObjectName("labelTitulo");
        labelTitulo->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: 700;\n"
"    color: #2c3e50;\n"
"    margin-bottom: 8px;\n"
"}"));
        labelTitulo->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitulo);

        layoutControles = new QHBoxLayout();
        layoutControles->setSpacing(12);
        layoutControles->setObjectName("layoutControles");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutControles->addItem(horizontalSpacer);

        btnActualizar = new QPushButton(Notificaciones);
        btnActualizar->setObjectName("btnActualizar");
        btnActualizar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #6c757d;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #545b62;\n"
"}"));

        layoutControles->addWidget(btnActualizar);

        btnMarcarLeidas = new QPushButton(Notificaciones);
        btnMarcarLeidas->setObjectName("btnMarcarLeidas");

        layoutControles->addWidget(btnMarcarLeidas);

        btnEliminarTodas = new QPushButton(Notificaciones);
        btnEliminarTodas->setObjectName("btnEliminarTodas");

        layoutControles->addWidget(btnEliminarTodas);


        verticalLayout->addLayout(layoutControles);

        scrollAreaNotificaciones = new QScrollArea(Notificaciones);
        scrollAreaNotificaciones->setObjectName("scrollAreaNotificaciones");
        scrollAreaNotificaciones->setWidgetResizable(true);
        scrollAreaNotificaciones->setStyleSheet(QString::fromUtf8("QScrollArea {\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background-color: #f8f9fa;\n"
"    width: 12px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background-color: #ced4da;\n"
"    border-radius: 6px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background-color: #adb5bd;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}"));
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 758, 69));
        layoutNotificaciones = new QVBoxLayout(scrollAreaWidgetContents);
        layoutNotificaciones->setSpacing(0);
        layoutNotificaciones->setObjectName("layoutNotificaciones");
        layoutNotificaciones->setContentsMargins(0, 0, 0, 0);
        labelSinNotificaciones = new QLabel(scrollAreaWidgetContents);
        labelSinNotificaciones->setObjectName("labelSinNotificaciones");
        labelSinNotificaciones->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-size: 16px;\n"
"    color: #6c757d;\n"
"    padding: 40px;\n"
"    text-align: center;\n"
"}"));
        labelSinNotificaciones->setAlignment(Qt::AlignCenter);

        layoutNotificaciones->addWidget(labelSinNotificaciones);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutNotificaciones->addItem(verticalSpacer);

        scrollAreaNotificaciones->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollAreaNotificaciones);


        retranslateUi(Notificaciones);

        QMetaObject::connectSlotsByName(Notificaciones);
    } // setupUi

    void retranslateUi(QWidget *Notificaciones)
    {
        Notificaciones->setWindowTitle(QCoreApplication::translate("Notificaciones", "Notificaciones", nullptr));
        labelTitulo->setText(QCoreApplication::translate("Notificaciones", "Centro de Notificaciones", nullptr));
        btnActualizar->setText(QCoreApplication::translate("Notificaciones", "\360\237\224\204 Actualizar", nullptr));
        btnMarcarLeidas->setText(QCoreApplication::translate("Notificaciones", "\342\234\223 Marcar como le\303\255das", nullptr));
        btnEliminarTodas->setText(QCoreApplication::translate("Notificaciones", "\360\237\227\221\357\270\217 Eliminar todas", nullptr));
        labelSinNotificaciones->setText(QCoreApplication::translate("Notificaciones", "\360\237\223\255 No hay notificaciones disponibles", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Notificaciones: public Ui_Notificaciones {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICACIONES_H
