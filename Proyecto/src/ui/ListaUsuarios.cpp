#include "ListaUsuarios.h"
#include "ui_ListaUsuarios.h"
#include "Usuario.h"
#include "VentanaUsuario.h"

ListaUsuarios::ListaUsuarios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaUsuarios)
{
    ui->setupUi(this);
    setWindowTitle("Lista de Usuarios");
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }
    configurarTabla();
    cargarUsuarios();
}

ListaUsuarios::~ListaUsuarios()
{
    delete ui;
}

void ListaUsuarios::configurarTabla()
{
     // Configurar columnas
     ui->tableWidgetUsuarios->setColumnCount(7);
    
     // Headers de columnas
     QStringList headers;
     headers << "ID" << "Nombre" << "Email" << "Teléfono" << "Dirección" << "Reputación" << "Accion";
     ui->tableWidgetUsuarios->setHorizontalHeaderLabels(headers);
     
     // Ajustar tamaño de columnas
     ui->tableWidgetUsuarios->horizontalHeader()->setStretchLastSection(false);
     ui->tableWidgetUsuarios->setColumnWidth(6, 100);
     ui->tableWidgetUsuarios->setAlternatingRowColors(true);
     ui->tableWidgetUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
     
     // Solo lectura
     ui->tableWidgetUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ListaUsuarios::cargarUsuarios(){
    //Limpiar tabla
    ui->tableWidgetUsuarios->setRowCount(0);

    // Obtener usuarios de la base de datos
    QList<Usuario> usuarios;
    if (!db->obtenerUsuarios(usuarios)) {
        qDebug() << "Error al obtener usuarios";
        return;
    }
    
    ui->tableWidgetUsuarios->setRowCount(usuarios.size());
    for (int i = 0; i < usuarios.size(); ++i) {
        const Usuario& usuario = usuarios[i];
        ui->tableWidgetUsuarios->setItem(i, 0, new QTableWidgetItem(QString::number(usuario.getId())));
        ui->tableWidgetUsuarios->setItem(i, 1, new QTableWidgetItem(usuario.getNombre()));
        ui->tableWidgetUsuarios->setItem(i, 2, new QTableWidgetItem(usuario.getEmail()));
        ui->tableWidgetUsuarios->setItem(i, 3, new QTableWidgetItem(usuario.getTelefono()));
        ui->tableWidgetUsuarios->setItem(i, 4, new QTableWidgetItem(usuario.getDireccion()));
        ui->tableWidgetUsuarios->setItem(i, 5, new QTableWidgetItem(QString::number(usuario.getReputacion())));

        QPushButton *btnIngresar = new QPushButton("Ingresar");
        btnIngresar->setProperty("idUsuario", usuario.getId());
        btnIngresar->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 5px; }");
        connect(btnIngresar, &QPushButton::clicked, this, &ListaUsuarios::ingresarCuentaUsuario);
        ui->tableWidgetUsuarios->setCellWidget(i, 6, btnIngresar);
    }

    // Mostrar cantidad
    setWindowTitle(QString("Lista de Usuarios (%1)").arg(usuarios.size()));
}

void ListaUsuarios::on_pushButtonActualizar_clicked()
{
    cargarUsuarios();
}

void ListaUsuarios::ingresarCuentaUsuario()
{
    // Obtener qué botón fue presionado
    QPushButton *boton = qobject_cast<QPushButton*>(sender());
    if (!boton) return;
    
    // Obtener ID del usuario desde el botón
    int idUsuario = boton->property("idUsuario").toInt();
    
    // Buscar usuario por id
    Usuario usuario;
    if (!db->obtenerUsuarioPorId(idUsuario, usuario)) {
        QMessageBox::critical(this, "Error", "No se pudo obtener el usuario");
        return;
    }
    
    VentanaUsuario *ventanaUsuario = new VentanaUsuario(usuario);
    ventanaUsuario->show();
}
