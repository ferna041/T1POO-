#include "VentanaUsuario.h"
#include "ui_VentanaUsuario.h"
#include "ListaObjetos.h"
#include "ListaReservas.h"
#include "Notificaciones.h"
#include "../database/DatabaseManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QSizePolicy>
#include "FormularioObjeto.h"

VentanaUsuario::VentanaUsuario(const Usuario& usuario, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaUsuario)
    , usuarioActual(usuario)
    , db(new DatabaseManager())
    , widgetNotificaciones(nullptr)
{
    ui->setupUi(this);
    
    // Configurar tamaño de ventana - más grande para que el contenido se vea mejor
    setMinimumSize(1200, 700);
    resize(1300, 800);
    
    // Configurar layout principal para que el tabWidget se ajuste al tamaño de la ventana
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(ui->tabWidget);
    
    // Configurar base de datos
    if (!db->conectar()) {
        qDebug() << "Error conectando a la base de datos";
    }
    
    // Configurar título con nombre del usuario
    setWindowTitle(QString("Cuenta de %1").arg(usuarioActual.getNombre()));

    // Agregar ListaObjetos a la pestaña Catálogo (objetos de otros usuarios)
    ListaObjetos *catalogoWidget = new ListaObjetos(usuarioActual.getId(), false);
    QVBoxLayout *layout = new QVBoxLayout(ui->catalogo);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(catalogoWidget);

    // Agregar ListaObjetos a la pestaña Mis Objetos (solo objetos del usuario actual)
    ListaObjetos *misObjetosWidget = new ListaObjetos(usuarioActual.getId(), true);
    QVBoxLayout *misObjetosLayout = new QVBoxLayout(ui->tab_2);
    misObjetosLayout->setContentsMargins(0, 0, 0, 0);
    misObjetosLayout->addWidget(misObjetosWidget);

    // Agregar Formulario Objeto a la pestaña publicar
    FormularioObjeto *formularioWidget = new FormularioObjeto(usuarioActual.getId());
    
    QVBoxLayout *formLayout = new QVBoxLayout(ui->publicar);
    formLayout->setContentsMargins(50, 30, 50, 30); // Más márgenes para centrar mejor
    formLayout->setAlignment(Qt::AlignCenter); // Centrar el contenido
    formLayout->addWidget(formularioWidget);

    // Agregar ListaReservas a la pestaña Mis Reservas
    ListaReservas *reservasWidget = new ListaReservas(usuarioActual.getId());
    QVBoxLayout *reservasLayout = new QVBoxLayout(ui->reservas);
    reservasLayout->setContentsMargins(0, 0, 0, 0);
    reservasLayout->addWidget(reservasWidget);
    
    // Agregar Widget de Notificaciones a la pestaña Notificaciones
    widgetNotificaciones = new Notificaciones();
    widgetNotificaciones->setDatabaseManager(db);
    widgetNotificaciones->setUsuarioActual(usuarioActual.getId());
    QVBoxLayout *notificacionesLayout = new QVBoxLayout(ui->Notificaciones);
    notificacionesLayout->setContentsMargins(0, 0, 0, 0);
    notificacionesLayout->addWidget(widgetNotificaciones);
}

VentanaUsuario::~VentanaUsuario()
{
    delete db;
    delete ui;
}
