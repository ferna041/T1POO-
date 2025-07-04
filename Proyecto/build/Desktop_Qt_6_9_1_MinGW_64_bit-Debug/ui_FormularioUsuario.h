/********************************************************************************
** Form generated from reading UI file 'FormularioUsuario.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMULARIOUSUARIO_H
#define UI_FORMULARIOUSUARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormularioUsuario
{
public:
    QLineEdit *lineEditNombre;
    QLineEdit *lineEditEmail;
    QLineEdit *lineEditTelefono;
    QLineEdit *lineEditDireccion;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButtonGuardar;
    QPushButton *pushButtonLimpiar;

    void setupUi(QWidget *FormularioUsuario)
    {
        if (FormularioUsuario->objectName().isEmpty())
            FormularioUsuario->setObjectName("FormularioUsuario");
        FormularioUsuario->resize(539, 300);
        lineEditNombre = new QLineEdit(FormularioUsuario);
        lineEditNombre->setObjectName("lineEditNombre");
        lineEditNombre->setGeometry(QRect(40, 110, 211, 20));
        lineEditEmail = new QLineEdit(FormularioUsuario);
        lineEditEmail->setObjectName("lineEditEmail");
        lineEditEmail->setGeometry(QRect(290, 110, 211, 20));
        lineEditTelefono = new QLineEdit(FormularioUsuario);
        lineEditTelefono->setObjectName("lineEditTelefono");
        lineEditTelefono->setGeometry(QRect(40, 170, 211, 20));
        lineEditDireccion = new QLineEdit(FormularioUsuario);
        lineEditDireccion->setObjectName("lineEditDireccion");
        lineEditDireccion->setGeometry(QRect(290, 170, 211, 20));
        label = new QLabel(FormularioUsuario);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 90, 51, 16));
        label_2 = new QLabel(FormularioUsuario);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(290, 90, 37, 12));
        label_3 = new QLabel(FormularioUsuario);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 150, 51, 16));
        label_4 = new QLabel(FormularioUsuario);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(290, 150, 51, 16));
        pushButtonGuardar = new QPushButton(FormularioUsuario);
        pushButtonGuardar->setObjectName("pushButtonGuardar");
        pushButtonGuardar->setGeometry(QRect(190, 230, 80, 18));
        pushButtonLimpiar = new QPushButton(FormularioUsuario);
        pushButtonLimpiar->setObjectName("pushButtonLimpiar");
        pushButtonLimpiar->setGeometry(QRect(280, 230, 80, 18));

        retranslateUi(FormularioUsuario);

        QMetaObject::connectSlotsByName(FormularioUsuario);
    } // setupUi

    void retranslateUi(QWidget *FormularioUsuario)
    {
        FormularioUsuario->setWindowTitle(QCoreApplication::translate("FormularioUsuario", "Registro de Usuario", nullptr));
        label->setText(QCoreApplication::translate("FormularioUsuario", "Nombre", nullptr));
        label_2->setText(QCoreApplication::translate("FormularioUsuario", "Email", nullptr));
        label_3->setText(QCoreApplication::translate("FormularioUsuario", "Telefono", nullptr));
        label_4->setText(QCoreApplication::translate("FormularioUsuario", "Direccion", nullptr));
        pushButtonGuardar->setText(QCoreApplication::translate("FormularioUsuario", "Guardar", nullptr));
        pushButtonLimpiar->setText(QCoreApplication::translate("FormularioUsuario", "Limpiar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormularioUsuario: public Ui_FormularioUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMULARIOUSUARIO_H
