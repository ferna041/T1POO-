#include "FormularioUsuario.h"
#include "ui_FormularioUsuario.h"
#include "Usuario.h"
#include "DatabaseManager.h"
#include <QMessageBox>

FormularioUsuario::FormularioUsuario(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormularioUsuario)
{
    ui->setupUi(this);  // Conecta el .ui con el código
    
    // Configurar ventana
    setWindowTitle("Registrar Nuevo Usuario");
    
    // Crear conexión a base de datos
    db = new DatabaseManager();
    db->conectar();
}

FormularioUsuario::~FormularioUsuario()
{
    delete ui;
}

void FormularioUsuario::on_pushButtonGuardar_clicked()
{
    // Obtener datos de los campos
    QString nombre = ui->lineEditNombre->text().trimmed();
    QString email = ui->lineEditEmail->text().trimmed();
    QString telefono = ui->lineEditTelefono->text().trimmed();
    QString direccion = ui->lineEditDireccion->text().trimmed();
    
    // Validaciones básicas
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre es obligatorio");
        return;
    }
    
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Error", "El email es obligatorio");
        return;
    }
    
    // Crear objeto Usuario (el ID será asignado por la base de datos)
    Usuario nuevoUsuario(0, nombre, email, telefono, direccion, 5.0);
    
    // Guardar en base de datos
    if (db->insertarUsuario(nuevoUsuario)) {
        QMessageBox::information(this, "Éxito", "Usuario guardado correctamente");
        on_pushButtonLimpiar_clicked();  // Limpiar campos
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el usuario");
    }
}

void FormularioUsuario::on_pushButtonLimpiar_clicked()
{
    ui->lineEditNombre->clear();
    ui->lineEditEmail->clear();
    ui->lineEditTelefono->clear();
    ui->lineEditDireccion->clear();
    ui->lineEditNombre->setFocus();  // Cursor en el primer campo
}