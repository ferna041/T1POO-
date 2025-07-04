/********************************************************************************
** Form generated from reading UI file 'ListaReservas.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTARESERVAS_H
#define UI_LISTARESERVAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListaReservas
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitulo;
    QWidget *widgetContenedor;
    QVBoxLayout *verticalLayoutTabla;
    QTableWidget *tableWidgetReservas;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonActualizar;

    void setupUi(QWidget *ListaReservas)
    {
        if (ListaReservas->objectName().isEmpty())
            ListaReservas->setObjectName("ListaReservas");
        ListaReservas->resize(800, 600);
        ListaReservas->setStyleSheet(QString::fromUtf8("QWidget#ListaReservas {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    border: none;\n"
"    color: #212529;\n"
"}"));
        verticalLayout = new QVBoxLayout(ListaReservas);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        labelTitulo = new QLabel(ListaReservas);
        labelTitulo->setObjectName("labelTitulo");
        labelTitulo->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font: 700 18pt \"Segoe UI\";\n"
"    color: #2c3e50;\n"
"    background: transparent;\n"
"    padding: 5px 10px;\n"
"    border-radius: 8px;\n"
"}"));

        verticalLayout->addWidget(labelTitulo);

        widgetContenedor = new QWidget(ListaReservas);
        widgetContenedor->setObjectName("widgetContenedor");
        widgetContenedor->setStyleSheet(QString::fromUtf8("QWidget#widgetContenedor {\n"
"    background-color: rgba(255, 255, 255, 240);\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 12px;\n"
"    box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n"
"}"));
        verticalLayoutTabla = new QVBoxLayout(widgetContenedor);
        verticalLayoutTabla->setSpacing(0);
        verticalLayoutTabla->setObjectName("verticalLayoutTabla");
        verticalLayoutTabla->setContentsMargins(15, 15, 15, 15);
        tableWidgetReservas = new QTableWidget(widgetContenedor);
        tableWidgetReservas->setObjectName("tableWidgetReservas");
        tableWidgetReservas->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #ffffff;\n"
"    alternate-background-color: #f8f9fa;\n"
"    selection-background-color: #e3f2fd;\n"
"    selection-color: #1976d2;\n"
"    border: none;\n"
"    gridline-color: #e9ecef;\n"
"    font: 11pt \"Segoe UI\";\n"
"    outline: none;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QTableWidget QHeaderView {\n"
"    background-color: #ffffff;\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget QHeaderView::section {\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 12px 10px;\n"
"    border: none;\n"
"    border-bottom: 1px solid #f1f3f4;\n"
"    color: #212529;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QTableWidget::item:alternate {\n"
"    background-color: #f8f9fa;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #e8f4fd;\n"
"    color: #1565c0;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: #f5f5f5;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QTableWidget::item:"
                        "selected:hover {\n"
"    background-color: #e3f2fd;\n"
"    color: #1565c0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"    color: #495057;\n"
"    padding: 15px 10px;\n"
"    border: none;\n"
"    font: bold 11pt \"Segoe UI\";\n"
"    border-right: 1px solid #dee2e6;\n"
"    border-bottom: 2px solid #dee2e6;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QHeaderView::section:last {\n"
"    border-right: none;\n"
"}\n"
"\n"
"QHeaderView::section:first {\n"
"    border-top-left-radius: 8px;\n"
"}\n"
"\n"
"QHeaderView::section:last {\n"
"    border-top-right-radius: 8px;\n"
"}\n"
"\n"
"QHeaderView::section:vertical {\n"
"    background-color: #f8f9fa;\n"
"    color: #6c757d;\n"
"    border: none;\n"
"    border-bottom: 1px solid #dee2e6;\n"
"    padding: 8px;\n"
"    font: 10pt \"Segoe UI\";\n"
"    text-align: center;\n"
"    min-width: 40px;\n"
"}\n"
"\n"
"QTableWidget::corner-button {"
                        "\n"
"    background-color: #ffffff;\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget QTableCornerButton::section {\n"
"    background-color: #ffffff;\n"
"    border: none;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    background: #f8f9fa;\n"
"    width: 12px;\n"
"    border-radius: 6px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #dee2e6;\n"
"    border-radius: 6px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #adb5bd;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    background: #f8f9fa;\n"
"    height: 12px;\n"
"    border-radius: 6px;\n"
"    margin: 2px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background: #dee2e6;\n"
"    border-radius: 6px;\n"
"    min-width: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background: #adb5bd;\n"
"}"));
        tableWidgetReservas->setAlternatingRowColors(true);
        tableWidgetReservas->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetReservas->setSortingEnabled(true);

        verticalLayoutTabla->addWidget(tableWidgetReservas);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonActualizar = new QPushButton(widgetContenedor);
        pushButtonActualizar->setObjectName("pushButtonActualizar");
        pushButtonActualizar->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #6c757d, stop: 1 #495057);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px;\n"
"    font: bold 11pt \"Segoe UI\";\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #5a6268, stop: 1 #343a40);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #495057, stop: 1 #212529);\n"
"}"));
        pushButtonActualizar->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(pushButtonActualizar);


        verticalLayoutTabla->addLayout(horizontalLayout);


        verticalLayout->addWidget(widgetContenedor);


        retranslateUi(ListaReservas);

        QMetaObject::connectSlotsByName(ListaReservas);
    } // setupUi

    void retranslateUi(QWidget *ListaReservas)
    {
        ListaReservas->setWindowTitle(QCoreApplication::translate("ListaReservas", "Mis Reservas", nullptr));
        labelTitulo->setText(QCoreApplication::translate("ListaReservas", "Mis Reservas", nullptr));
        pushButtonActualizar->setText(QCoreApplication::translate("ListaReservas", "Actualizar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListaReservas: public Ui_ListaReservas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTARESERVAS_H
