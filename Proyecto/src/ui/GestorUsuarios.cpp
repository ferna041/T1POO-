#include "GestorUsuarios.h"
#include "ui_GestorUsuarios.h"
#include "VentanaUsuario.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>

GestorUsuarios::GestorUsuarios(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GestorUsuarios)
{
    ui->setupUi(this);
    setWindowTitle("Gestor de Usuarios");
    setMinimumSize(1000, 550);
    resize(1200, 600);
    
    // Estilo del fondo de la ventana principal - blanco con gris
    setStyleSheet("QWidget#GestorUsuarios { background-color: #f5f5f5; }");
    
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }
    
    configurarInterfaz();
    configurarTabla();
    cargarUsuarios();
}

GestorUsuarios::~GestorUsuarios()
{
    delete ui;
    delete db;
}

void GestorUsuarios::configurarInterfaz()
{
    // Configurar el título de la sección de registro
    ui->labelTituloRegistro->setText("Registrar Nuevo Usuario");
    ui->labelTituloRegistro->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: #2c3e50; }");
    
    // Configurar el título de la lista
    ui->labelTituloLista->setText("Lista de Usuarios Registrados");
    ui->labelTituloLista->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: #2c3e50; }");
    
    // Estilo para los botones
    ui->pushButtonRegistrar->setStyleSheet("QPushButton { background-color: #27ae60; color: white; padding: 8px; font-weight: bold; border-radius: 5px; }");
    ui->pushButtonLimpiar->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; padding: 8px; font-weight: bold; border-radius: 5px; }");
    ui->pushButtonActualizar->setStyleSheet("QPushButton { background-color: #3498db; color: white; padding: 8px; font-weight: bold; border-radius: 5px; }");
    
    // Placeholder text para los campos
    ui->lineEditNombre->setPlaceholderText("Ingrese el nombre completo");
    ui->lineEditEmail->setPlaceholderText("ejemplo@correo.com");
    ui->lineEditTelefono->setPlaceholderText("+56 9 XXXX XXXX");
    ui->lineEditDireccion->setPlaceholderText("Dirección completa");
}

void GestorUsuarios::configurarTabla()
{
    // Configurar columnas
    ui->tableWidgetUsuarios->setColumnCount(7);
    
    // Headers de columnas
    QStringList headers;
    headers << "ID" << "Nombre" << "Email" << "Teléfono" << "Dirección" << "Reputación" << "Acción";
    ui->tableWidgetUsuarios->setHorizontalHeaderLabels(headers);
    
    // Ajustar tamaño de columnas para evitar scroll horizontal
    ui->tableWidgetUsuarios->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetUsuarios->setColumnWidth(0, 40);   // ID
    ui->tableWidgetUsuarios->setColumnWidth(1, 140);  // Nombre
    ui->tableWidgetUsuarios->setColumnWidth(2, 180);  // Email
    ui->tableWidgetUsuarios->setColumnWidth(3, 110);  // Teléfono
    ui->tableWidgetUsuarios->setColumnWidth(4, 180);  // Dirección
    ui->tableWidgetUsuarios->setColumnWidth(5, 80);   // Reputación
    // La última columna (Acción) se estira automáticamente
    
    // Configurar comportamiento de la tabla
    ui->tableWidgetUsuarios->setAlternatingRowColors(true);
    ui->tableWidgetUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Política de scroll - mostrar scroll solo cuando sea necesario
    ui->tableWidgetUsuarios->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableWidgetUsuarios->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    // Ajustar el header para que se distribuya el espacio disponible
    ui->tableWidgetUsuarios->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidgetUsuarios->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch); // Columna Acción se estira
    
    // Estilo de la tabla - esquema blanco/gris
    ui->tableWidgetUsuarios->setStyleSheet(
        "QTableWidget { "
        "   gridline-color: #e0e0e0; "
        "   background-color: white; "
        "   border: 1px solid #e0e0e0; "
        "   border-radius: 5px; "
        "   color: black; "
        "} "
        "QHeaderView::section { "
        "   background-color: #f8f9fa; "
        "   color: #2c3e50; "
        "   padding: 8px; "
        "   font-weight: bold; "
        "   border: 1px solid #e0e0e0; "
        "} "
        "QTableWidget::item { "
        "   padding: 5px; "
        "   border-bottom: 1px solid #f0f0f0; "
        "   color: black; "
        "} "
        "QTableWidget::item:selected { "
        "   background-color: #e3f2fd; "
        "   color: #1976d2; "
        "} "
        "QTableWidget::item:alternate { "
        "   background-color: #fafafa; "
        "   color: black; "
        "} "
        "QTableCornerButton::section { "
        "   background-color: #f8f9fa; "
        "   border: 1px solid #e0e0e0; "
        "} "
        "QScrollBar:vertical { "
        "   background-color: #f0f0f0; "
        "   width: 12px; "
        "   border: none; "
        "} "
        "QScrollBar::handle:vertical { "
        "   background-color: #c0c0c0; "
        "   border-radius: 6px; "
        "} "
        "QScrollBar:horizontal { "
        "   background-color: #f0f0f0; "
        "   height: 12px; "
        "   border: none; "
        "}"
    );
}

void GestorUsuarios::cargarUsuarios()
{
    // Limpiar tabla
    ui->tableWidgetUsuarios->setRowCount(0);

    // Obtener usuarios de la base de datos
    QList<Usuario> usuarios;
    if (!db->obtenerUsuarios(usuarios)) {
        qDebug() << "Error al obtener usuarios";
        QMessageBox::warning(this, "Error", "No se pudieron cargar los usuarios.");
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
        ui->tableWidgetUsuarios->setItem(i, 5, new QTableWidgetItem(QString::number(usuario.getReputacion(), 'f', 1)));

        QPushButton *btnIngresar = new QPushButton("Ingresar");
        btnIngresar->setProperty("idUsuario", usuario.getId());
        btnIngresar->setStyleSheet(
            "QPushButton { "
            "   background-color: #e74c3c; "
            "   color: white; "
            "   padding: 6px 12px; "
            "   border: none; "
            "   border-radius: 4px; "
            "   font-weight: bold; "
            "   font-size: 12px; "
            "} "
            "QPushButton:hover { "
            "   background-color: #c0392b; "
            "} "
            "QPushButton:pressed { "
            "   background-color: #a93226; "
            "}"
        );
        connect(btnIngresar, &QPushButton::clicked, this, &GestorUsuarios::ingresarCuentaUsuario);
        ui->tableWidgetUsuarios->setCellWidget(i, 6, btnIngresar);
        
        // Ajustar altura de fila para que los botones se vean proporcionados
        ui->tableWidgetUsuarios->setRowHeight(i, 40);
    }

    // Actualizar título con cantidad
    ui->labelTituloLista->setText(QString("Lista de Usuarios Registrados (%1)").arg(usuarios.size()));
}

bool GestorUsuarios::validarFormulario()
{
    if (ui->lineEditNombre->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error de Validación", "El nombre es obligatorio.");
        ui->lineEditNombre->setFocus();
        return false;
    }
    
    if (ui->lineEditEmail->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error de Validación", "El email es obligatorio.");
        ui->lineEditEmail->setFocus();
        return false;
    }
    
    // Validación básica de email
    QString email = ui->lineEditEmail->text().trimmed();
    if (!email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Error de Validación", "Ingrese un email válido.");
        ui->lineEditEmail->setFocus();
        return false;
    }
    
    if (ui->lineEditTelefono->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error de Validación", "El teléfono es obligatorio.");
        ui->lineEditTelefono->setFocus();
        return false;
    }
    
    if (ui->lineEditDireccion->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error de Validación", "La dirección es obligatoria.");
        ui->lineEditDireccion->setFocus();
        return false;
    }
    
    return true;
}

void GestorUsuarios::limpiarFormulario()
{
    ui->lineEditNombre->clear();
    ui->lineEditEmail->clear();
    ui->lineEditTelefono->clear();
    ui->lineEditDireccion->clear();
    ui->lineEditNombre->setFocus();
}

void GestorUsuarios::on_pushButtonRegistrar_clicked()
{
    if (!validarFormulario()) {
        return;
    }
    
    // Crear objeto Usuario con los datos del formulario
    Usuario usuario(
        0, // ID se genera automáticamente
        ui->lineEditNombre->text().trimmed(),
        ui->lineEditEmail->text().trimmed(),
        ui->lineEditTelefono->text().trimmed(),
        ui->lineEditDireccion->text().trimmed(),
        0.0, // Reputación inicial
        QDateTime::currentDateTime(),
        true // Activo
    );
    
    // Intentar guardar en la base de datos
    if (db->insertarUsuario(usuario)) {
        QMessageBox::information(this, "Éxito", "Usuario registrado correctamente.");
        limpiarFormulario();
        cargarUsuarios(); // Recargar la lista
    } else {
        QMessageBox::critical(this, "Error", "No se pudo registrar el usuario.\nVerifique que el email no esté duplicado.");
    }
}

void GestorUsuarios::on_pushButtonLimpiar_clicked()
{
    limpiarFormulario();
}

void GestorUsuarios::on_pushButtonActualizar_clicked()
{
    cargarUsuarios();
}

void GestorUsuarios::ingresarCuentaUsuario()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    
    int idUsuario = btn->property("idUsuario").toInt();
    
    // Obtener el usuario completo de la base de datos
    Usuario usuario;
    if (!db->obtenerUsuarioPorId(idUsuario, usuario)) {
        QMessageBox::warning(this, "Error", "No se pudo obtener la información del usuario.");
        return;
    }
    
    // Crear y mostrar la ventana de usuario
    VentanaUsuario *ventana = new VentanaUsuario(usuario);
    ventana->show();
    
    // Opcional: cerrar la ventana actual
    // this->close();
}
