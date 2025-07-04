/********************************************************************************
** Form generated from reading UI file 'ListaUsuarios.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTAUSUARIOS_H
#define UI_LISTAUSUARIOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListaUsuarios
{
public:
    QTableWidget *tableWidgetUsuarios;
    QPushButton *pushButtonActualizar;

    void setupUi(QWidget *ListaUsuarios)
    {
        if (ListaUsuarios->objectName().isEmpty())
            ListaUsuarios->setObjectName("ListaUsuarios");
        ListaUsuarios->resize(697, 324);
        tableWidgetUsuarios = new QTableWidget(ListaUsuarios);
        tableWidgetUsuarios->setObjectName("tableWidgetUsuarios");
        tableWidgetUsuarios->setGeometry(QRect(10, 20, 671, 251));
        pushButtonActualizar = new QPushButton(ListaUsuarios);
        pushButtonActualizar->setObjectName("pushButtonActualizar");
        pushButtonActualizar->setGeometry(QRect(600, 280, 80, 18));

        retranslateUi(ListaUsuarios);

        QMetaObject::connectSlotsByName(ListaUsuarios);
    } // setupUi

    void retranslateUi(QWidget *ListaUsuarios)
    {
        ListaUsuarios->setWindowTitle(QCoreApplication::translate("ListaUsuarios", "Form", nullptr));
        pushButtonActualizar->setText(QCoreApplication::translate("ListaUsuarios", "Actualizar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListaUsuarios: public Ui_ListaUsuarios {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTAUSUARIOS_H
