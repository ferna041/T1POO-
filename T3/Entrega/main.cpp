#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    a.setApplicationName("Simulador Publicador-Suscriptor");
    a.setApplicationVersion("1.0 - Entrega Final");
    a.setOrganizationName("ELO329 - USM");
    
    MainWindow w;
    w.show();
    return a.exec();
}
