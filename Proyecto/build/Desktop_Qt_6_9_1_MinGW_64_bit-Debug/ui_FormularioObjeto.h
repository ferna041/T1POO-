/********************************************************************************
** Form generated from reading UI file 'FormularioObjeto.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMULARIOOBJETO_H
#define UI_FORMULARIOOBJETO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormularioObjeto
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitulo;
    QWidget *widgetContenedor;
    QVBoxLayout *verticalLayoutContenedor;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditNombre;
    QLabel *label_2;
    QLineEdit *lineEditCategoria;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_tiempo;
    QSpinBox *spinBoxTiempo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QTextEdit *textEditDescripcion;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_botones;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonLimpiar;
    QPushButton *pushButtonGuardar;

    void setupUi(QWidget *FormularioObjeto)
    {
        if (FormularioObjeto->objectName().isEmpty())
            FormularioObjeto->setObjectName("FormularioObjeto");
        FormularioObjeto->resize(700, 600);
        FormularioObjeto->setMinimumSize(QSize(600, 500));
        FormularioObjeto->setStyleSheet(QString::fromUtf8("QWidget#FormularioObjeto {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    border: none;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QLabel {\n"
"    font: 600 12pt \"Segoe UI\";\n"
"    color: #495057;\n"
"    background: transparent;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    padding: 10px 12px;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #212529;\n"
"    selection-background-color: #e3f2fd;\n"
"    selection-color: #1976d2;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #80bdff;\n"
"    box-shadow: 0 0 0 3px rgba(0, 123, 255, 0.25);\n"
"}\n"
"\n"
"QTextEdit {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    padding: 10px 12px;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #212529;\n"
"    selection-background-color: #e3f2fd;\n"
"    select"
                        "ion-color: #1976d2;\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border-color: #80bdff;\n"
"    box-shadow: 0 0 0 3px rgba(0, 123, 255, 0.25);\n"
"}\n"
"\n"
"QSpinBox {\n"
"    background-color: #ffffff;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font: 11pt \"Segoe UI\";\n"
"    color: #212529;\n"
"    min-height: 25px;\n"
"}\n"
"\n"
"QSpinBox:focus {\n"
"    border-color: #80bdff;\n"
"    box-shadow: 0 0 0 2px rgba(0, 123, 255, 0.25);\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #007bff, stop: 1 #0056b3);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    font: bold 12pt \"Segoe UI\";\n"
"    padding: 12px 20px;\n"
"    min-width: 100px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #0056b3, stop: 1 #004085);\n"
"}\n"
"\n"
"QPushButton:pressed "
                        "{\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #004085, stop: 1 #002752);\n"
"}\n"
"\n"
"QPushButton#pushButtonLimpiar {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6c757d, stop: 1 #495057);\n"
"}\n"
"\n"
"QPushButton#pushButtonLimpiar:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #5a6268, stop: 1 #343a40);\n"
"}\n"
"\n"
"QPushButton#pushButtonLimpiar:pressed {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #495057, stop: 1 #212529);\n"
"}"));
        verticalLayout = new QVBoxLayout(FormularioObjeto);
        verticalLayout->setSpacing(30);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(40, 40, 40, 40);
        labelTitulo = new QLabel(FormularioObjeto);
        labelTitulo->setObjectName("labelTitulo");
        labelTitulo->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font: 700 20pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"    background: transparent;\n"
"    padding: 10px;\n"
"    border-radius: 8px;\n"
"}"));
        labelTitulo->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitulo);

        widgetContenedor = new QWidget(FormularioObjeto);
        widgetContenedor->setObjectName("widgetContenedor");
        widgetContenedor->setStyleSheet(QString::fromUtf8("QWidget#widgetContenedor {\n"
"    background-color: rgba(255, 255, 255, 250);\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 15px;\n"
"    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n"
"}"));
        verticalLayoutContenedor = new QVBoxLayout(widgetContenedor);
        verticalLayoutContenedor->setSpacing(30);
        verticalLayoutContenedor->setObjectName("verticalLayoutContenedor");
        verticalLayoutContenedor->setContentsMargins(40, 40, 40, 40);
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::ExpandingFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setLabelAlignment(Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        formLayout->setHorizontalSpacing(20);
        formLayout->setVerticalSpacing(25);
        label = new QLabel(widgetContenedor);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setAlignment(Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineEditNombre = new QLineEdit(widgetContenedor);
        lineEditNombre->setObjectName("lineEditNombre");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditNombre);

        label_2 = new QLabel(widgetContenedor);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        lineEditCategoria = new QLineEdit(widgetContenedor);
        lineEditCategoria->setObjectName("lineEditCategoria");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditCategoria);

        label_4 = new QLabel(widgetContenedor);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_4);

        horizontalLayout_tiempo = new QHBoxLayout();
        horizontalLayout_tiempo->setObjectName("horizontalLayout_tiempo");
        spinBoxTiempo = new QSpinBox(widgetContenedor);
        spinBoxTiempo->setObjectName("spinBoxTiempo");
        spinBoxTiempo->setMinimum(1);
        spinBoxTiempo->setMaximum(365);
        spinBoxTiempo->setValue(7);

        horizontalLayout_tiempo->addWidget(spinBoxTiempo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_tiempo->addItem(horizontalSpacer_2);


        formLayout->setLayout(2, QFormLayout::ItemRole::FieldRole, horizontalLayout_tiempo);

        label_3 = new QLabel(widgetContenedor);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_3);

        textEditDescripcion = new QTextEdit(widgetContenedor);
        textEditDescripcion->setObjectName("textEditDescripcion");
        textEditDescripcion->setMinimumSize(QSize(0, 100));
        textEditDescripcion->setMaximumSize(QSize(16777215, 150));

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, textEditDescripcion);


        verticalLayoutContenedor->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutContenedor->addItem(verticalSpacer);

        horizontalLayout_botones = new QHBoxLayout();
        horizontalLayout_botones->setObjectName("horizontalLayout_botones");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_botones->addItem(horizontalSpacer);

        pushButtonLimpiar = new QPushButton(widgetContenedor);
        pushButtonLimpiar->setObjectName("pushButtonLimpiar");
        pushButtonLimpiar->setMinimumSize(QSize(140, 45));

        horizontalLayout_botones->addWidget(pushButtonLimpiar);

        pushButtonGuardar = new QPushButton(widgetContenedor);
        pushButtonGuardar->setObjectName("pushButtonGuardar");
        pushButtonGuardar->setMinimumSize(QSize(140, 45));

        horizontalLayout_botones->addWidget(pushButtonGuardar);


        verticalLayoutContenedor->addLayout(horizontalLayout_botones);


        verticalLayout->addWidget(widgetContenedor);


        retranslateUi(FormularioObjeto);

        pushButtonGuardar->setDefault(true);


        QMetaObject::connectSlotsByName(FormularioObjeto);
    } // setupUi

    void retranslateUi(QWidget *FormularioObjeto)
    {
        FormularioObjeto->setWindowTitle(QCoreApplication::translate("FormularioObjeto", "Publicar Objeto", nullptr));
        labelTitulo->setText(QCoreApplication::translate("FormularioObjeto", "Publicar Nuevo Objeto", nullptr));
        label->setText(QCoreApplication::translate("FormularioObjeto", "Nombre del objeto:", nullptr));
        lineEditNombre->setPlaceholderText(QCoreApplication::translate("FormularioObjeto", "Ej: Taladro el\303\251ctrico, Libro de cocina...", nullptr));
        label_2->setText(QCoreApplication::translate("FormularioObjeto", "Categor\303\255a:", nullptr));
        lineEditCategoria->setPlaceholderText(QCoreApplication::translate("FormularioObjeto", "Ej: Herramientas, Libros, Electrodom\303\251sticos...", nullptr));
        label_4->setText(QCoreApplication::translate("FormularioObjeto", "Tiempo disponible:", nullptr));
        spinBoxTiempo->setSuffix(QCoreApplication::translate("FormularioObjeto", " d\303\255as", nullptr));
        label_3->setText(QCoreApplication::translate("FormularioObjeto", "Descripci\303\263n:", nullptr));
        textEditDescripcion->setPlaceholderText(QCoreApplication::translate("FormularioObjeto", "Describe el objeto, su estado, cuidados especiales, etc.", nullptr));
        pushButtonLimpiar->setText(QCoreApplication::translate("FormularioObjeto", "Limpiar", nullptr));
        pushButtonGuardar->setText(QCoreApplication::translate("FormularioObjeto", "Guardar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormularioObjeto: public Ui_FormularioObjeto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMULARIOOBJETO_H
