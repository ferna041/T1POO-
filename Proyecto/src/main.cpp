#include "mainwindow.h"
#include "FormularioUsuario.h"
#include "ListaUsuarios.h"
#include "DatabaseManager.h"
#include "Usuario.h"
#include "FormularioObjeto.h"
#include "ListaObjetos.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configuración de la base de datos
    DatabaseManager dbManager;
    if (!dbManager.conectar()) {
        qDebug() << "Error al conectar a la base de datos.";
        return -1;
    }
    qDebug() << "Conexión a la base de datos exitosa.";
    // Crear las tablas si no existen
    if (!dbManager.crearTablas()) {
        qDebug() << "Error al crear las tablas en la base de datos.";
        return -1;
    }

    // En la función main, después de la configuración de BD:
    FormularioUsuario *formulario = new FormularioUsuario();
    formulario->show();

    ListaUsuarios *listaUsuarios = new ListaUsuarios();
    listaUsuarios->show();

    //FormularioObjeto *formularioObjeto = new FormularioObjeto();
    //formularioObjeto->show();

    //ListaObjetos *listaObjetos = new ListaObjetos();
    //listaObjetos->show();


    return a.exec();
}
