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
