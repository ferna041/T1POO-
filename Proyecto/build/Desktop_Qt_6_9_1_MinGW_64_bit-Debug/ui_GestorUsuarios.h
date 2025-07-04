/********************************************************************************
** Form generated from reading UI file 'GestorUsuarios.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTORUSUARIOS_H
#define UI_GESTORUSUARIOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestorUsuarios
{
public:
    QVBoxLayout *verticalLayout_main;
    QGroupBox *groupBoxRegistro;
    QVBoxLayout *verticalLayout_registro;
    QLabel *labelTituloRegistro;
    QGridLayout *gridLayout_formulario;
    QLabel *labelNombre;
    QLineEdit *lineEditNombre;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QLabel *labelTelefono;
    QLineEdit *lineEditTelefono;
    QLabel *labelDireccion;
    QLineEdit *lineEditDireccion;
    QHBoxLayout *horizontalLayout_botones;
    QSpacerItem *horizontalSpacer_left;
    QPushButton *pushButtonRegistrar;
    QPushButton *pushButtonLimpiar;
    QSpacerItem *horizontalSpacer_right;
    QGroupBox *groupBoxLista;
    QVBoxLayout *verticalLayout_lista;
    QHBoxLayout *horizontalLayout_titulo;
    QLabel *labelTituloLista;
    QSpacerItem *horizontalSpacer_titulo;
    QPushButton *pushButtonActualizar;
    QTableWidget *tableWidgetUsuarios;

    void setupUi(QWidget *GestorUsuarios)
    {
        if (GestorUsuarios->objectName().isEmpty())
            GestorUsuarios->setObjectName("GestorUsuarios");
        GestorUsuarios->resize(1200, 600);
        GestorUsuarios->setMinimumSize(QSize(1000, 550));
        verticalLayout_main = new QVBoxLayout(GestorUsuarios);
        verticalLayout_main->setSpacing(20);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        groupBoxRegistro = new QGroupBox(GestorUsuarios);
        groupBoxRegistro->setObjectName("groupBoxRegistro");
        verticalLayout_registro = new QVBoxLayout(groupBoxRegistro);
        verticalLayout_registro->setSpacing(15);
        verticalLayout_registro->setObjectName("verticalLayout_registro");
        labelTituloRegistro = new QLabel(groupBoxRegistro);
        labelTituloRegistro->setObjectName("labelTituloRegistro");
        labelTituloRegistro->setAlignment(Qt::AlignCenter);

        verticalLayout_registro->addWidget(labelTituloRegistro);

        gridLayout_formulario = new QGridLayout();
        gridLayout_formulario->setObjectName("gridLayout_formulario");
        gridLayout_formulario->setHorizontalSpacing(15);
        gridLayout_formulario->setVerticalSpacing(10);
        labelNombre = new QLabel(groupBoxRegistro);
        labelNombre->setObjectName("labelNombre");

        gridLayout_formulario->addWidget(labelNombre, 0, 0, 1, 1);

        lineEditNombre = new QLineEdit(groupBoxRegistro);
        lineEditNombre->setObjectName("lineEditNombre");

        gridLayout_formulario->addWidget(lineEditNombre, 0, 1, 1, 1);

        labelEmail = new QLabel(groupBoxRegistro);
        labelEmail->setObjectName("labelEmail");

        gridLayout_formulario->addWidget(labelEmail, 0, 2, 1, 1);

        lineEditEmail = new QLineEdit(groupBoxRegistro);
        lineEditEmail->setObjectName("lineEditEmail");

        gridLayout_formulario->addWidget(lineEditEmail, 0, 3, 1, 1);

        labelTelefono = new QLabel(groupBoxRegistro);
        labelTelefono->setObjectName("labelTelefono");

        gridLayout_formulario->addWidget(labelTelefono, 1, 0, 1, 1);

        lineEditTelefono = new QLineEdit(groupBoxRegistro);
        lineEditTelefono->setObjectName("lineEditTelefono");

        gridLayout_formulario->addWidget(lineEditTelefono, 1, 1, 1, 1);

        labelDireccion = new QLabel(groupBoxRegistro);
        labelDireccion->setObjectName("labelDireccion");

        gridLayout_formulario->addWidget(labelDireccion, 1, 2, 1, 1);

        lineEditDireccion = new QLineEdit(groupBoxRegistro);
        lineEditDireccion->setObjectName("lineEditDireccion");

        gridLayout_formulario->addWidget(lineEditDireccion, 1, 3, 1, 1);


        verticalLayout_registro->addLayout(gridLayout_formulario);

        horizontalLayout_botones = new QHBoxLayout();
        horizontalLayout_botones->setObjectName("horizontalLayout_botones");
        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_botones->addItem(horizontalSpacer_left);

        pushButtonRegistrar = new QPushButton(groupBoxRegistro);
        pushButtonRegistrar->setObjectName("pushButtonRegistrar");
        pushButtonRegistrar->setMinimumSize(QSize(120, 35));

        horizontalLayout_botones->addWidget(pushButtonRegistrar);

        pushButtonLimpiar = new QPushButton(groupBoxRegistro);
        pushButtonLimpiar->setObjectName("pushButtonLimpiar");
        pushButtonLimpiar->setMinimumSize(QSize(80, 35));

        horizontalLayout_botones->addWidget(pushButtonLimpiar);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_botones->addItem(horizontalSpacer_right);


        verticalLayout_registro->addLayout(horizontalLayout_botones);


        verticalLayout_main->addWidget(groupBoxRegistro);

        groupBoxLista = new QGroupBox(GestorUsuarios);
        groupBoxLista->setObjectName("groupBoxLista");
        groupBoxLista->setMinimumSize(QSize(0, 280));
        verticalLayout_lista = new QVBoxLayout(groupBoxLista);
        verticalLayout_lista->setSpacing(15);
        verticalLayout_lista->setObjectName("verticalLayout_lista");
        horizontalLayout_titulo = new QHBoxLayout();
        horizontalLayout_titulo->setObjectName("horizontalLayout_titulo");
        labelTituloLista = new QLabel(groupBoxLista);
        labelTituloLista->setObjectName("labelTituloLista");

        horizontalLayout_titulo->addWidget(labelTituloLista);

        horizontalSpacer_titulo = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_titulo->addItem(horizontalSpacer_titulo);

        pushButtonActualizar = new QPushButton(groupBoxLista);
        pushButtonActualizar->setObjectName("pushButtonActualizar");
        pushButtonActualizar->setMinimumSize(QSize(120, 30));

        horizontalLayout_titulo->addWidget(pushButtonActualizar);


        verticalLayout_lista->addLayout(horizontalLayout_titulo);

        tableWidgetUsuarios = new QTableWidget(groupBoxLista);
        tableWidgetUsuarios->setObjectName("tableWidgetUsuarios");
        tableWidgetUsuarios->setMinimumSize(QSize(0, 200));
        tableWidgetUsuarios->setMaximumSize(QSize(16777215, 250));
        tableWidgetUsuarios->setAlternatingRowColors(true);
        tableWidgetUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetUsuarios->setGridStyle(Qt::SolidLine);
        tableWidgetUsuarios->setSortingEnabled(true);

        verticalLayout_lista->addWidget(tableWidgetUsuarios);


        verticalLayout_main->addWidget(groupBoxLista);


        retranslateUi(GestorUsuarios);

        QMetaObject::connectSlotsByName(GestorUsuarios);
    } // setupUi

    void retranslateUi(QWidget *GestorUsuarios)
    {
        GestorUsuarios->setWindowTitle(QCoreApplication::translate("GestorUsuarios", "Gestor de Usuarios", nullptr));
        GestorUsuarios->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QWidget#GestorUsuarios {\n"
"    background-color: #f5f5f5;\n"
"}", nullptr));
        groupBoxRegistro->setTitle(QString());
        groupBoxRegistro->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QGroupBox {\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"    background-color: #ffffff;\n"
"}", nullptr));
        labelTituloRegistro->setText(QCoreApplication::translate("GestorUsuarios", "Registrar Nuevo Usuario", nullptr));
        labelNombre->setText(QCoreApplication::translate("GestorUsuarios", "Nombre:", nullptr));
        labelNombre->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLabel { font-weight: bold; }", nullptr));
        lineEditNombre->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 5px;\n"
"    font-size: 12px;\n"
"    background-color: white;\n"
"    color: black;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"}", nullptr));
        labelEmail->setText(QCoreApplication::translate("GestorUsuarios", "Email:", nullptr));
        labelEmail->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLabel { font-weight: bold; }", nullptr));
        lineEditEmail->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 5px;\n"
"    font-size: 12px;\n"
"    background-color: white;\n"
"    color: black;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"}", nullptr));
        labelTelefono->setText(QCoreApplication::translate("GestorUsuarios", "Tel\303\251fono:", nullptr));
        labelTelefono->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLabel { font-weight: bold; }", nullptr));
        lineEditTelefono->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 5px;\n"
"    font-size: 12px;\n"
"    background-color: white;\n"
"    color: black;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"}", nullptr));
        labelDireccion->setText(QCoreApplication::translate("GestorUsuarios", "Direcci\303\263n:", nullptr));
        labelDireccion->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLabel { font-weight: bold; }", nullptr));
        lineEditDireccion->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 5px;\n"
"    font-size: 12px;\n"
"    background-color: white;\n"
"    color: black;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"}", nullptr));
        pushButtonRegistrar->setText(QCoreApplication::translate("GestorUsuarios", "Registrar Usuario", nullptr));
        pushButtonLimpiar->setText(QCoreApplication::translate("GestorUsuarios", "Limpiar", nullptr));
        groupBoxLista->setTitle(QString());
        groupBoxLista->setStyleSheet(QCoreApplication::translate("GestorUsuarios", "QGroupBox {\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"    background-color: #ffffff;\n"
"}", nullptr));
        labelTituloLista->setText(QCoreApplication::translate("GestorUsuarios", "Lista de Usuarios Registrados", nullptr));
        pushButtonActualizar->setText(QCoreApplication::translate("GestorUsuarios", "Actualizar Lista", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestorUsuarios: public Ui_GestorUsuarios {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTORUSUARIOS_H
