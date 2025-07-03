#include "VentanaUsuario.h"
#include "ui_VentanaUsuario.h"
#include "ListaObjetos.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "FormularioObjeto.h"

VentanaUsuario::VentanaUsuario(const Usuario& usuario, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaUsuario)
    , usuarioActual(usuario) // Inicializar con un usuario por defecto
{
    ui->setupUi(this);
    // Configurar título con nombre del usuario
    setWindowTitle(QString("Cuenta de %1").arg(usuarioActual.getNombre()));

    // Agregar ListaObjetos a la pestaña Catálogo (objetos de otros usuarios)
    ListaObjetos *catalogoWidget = new ListaObjetos(usuarioActual.getId(), false);
    QVBoxLayout *layout = new QVBoxLayout(ui->widgetCatalogo);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(catalogoWidget);

    // Agregar ListaObjetos a la pestaña Mis Objetos (solo objetos del usuario actual)
    ListaObjetos *misObjetosWidget = new ListaObjetos(usuarioActual.getId(), true);
    QVBoxLayout *misObjetosLayout = new QVBoxLayout(ui->widgetMisObjetos);
    misObjetosLayout->setContentsMargins(5, 5, 5, 5);
    misObjetosLayout->addWidget(misObjetosWidget);

    // Agregar Formulario Objeto a la pestaña publicar
    FormularioObjeto *formularioWidget = new FormularioObjeto(usuarioActual.getId());
    formularioWidget->setMaximumWidth(600);
    formularioWidget->setMaximumHeight(400);
    QHBoxLayout *formLayout = new QHBoxLayout(ui->widgetPublicar);
    formLayout->setContentsMargins(5, 5, 5, 5);
    formLayout->addWidget(formularioWidget, 0, Qt::AlignCenter);
}

VentanaUsuario::~VentanaUsuario()
{
    delete ui;
}
