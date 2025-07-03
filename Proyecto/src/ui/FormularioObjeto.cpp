#include "FormularioObjeto.h"
#include "ui_FormularioObjeto.h"
#include "Objeto.h"
#include "DatabaseManager.h"
#include <QMessageBox>

FormularioObjeto::FormularioObjeto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormularioObjeto)
    , usuarioActualId(1) // ID por defecto
{
    ui->setupUi(this);

    // Configurar ventana
    setWindowTitle("Registrar Nuevo Objeto");
    // Crear conexión a base de datos
    db = new DatabaseManager();
    if (!db->conectar()) {
        QMessageBox::critical(this, "Error", "No se pudo conectar a la base de datos");
        return;
    }
}

FormularioObjeto::FormularioObjeto(int usuarioId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormularioObjeto)
    , usuarioActualId(usuarioId)
{
    ui->setupUi(this);

    // Configurar ventana
    setWindowTitle("Registrar Nuevo Objeto");
    // Crear conexión a base de datos
    db = new DatabaseManager();
    if (!db->conectar()) {
        QMessageBox::critical(this, "Error", "No se pudo conectar a la base de datos");
        return;
    }
}

FormularioObjeto::~FormularioObjeto()
{
    delete ui;
}

void FormularioObjeto::on_pushButtonGuardar_clicked(){

    QString nombre = ui->lineEditNombre->text().trimmed();
    QString categoria = ui->lineEditCategoria->text().trimmed();
    QString descripcion = ui->textEditDescripcion->toPlainText().trimmed();
    int tiempoPrestamo = ui->spinBoxTiempo->value();

    // validaciones básicas
    if (nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre es obligatorio");
        return;
    }
    if (categoria.isEmpty()) {
        QMessageBox::warning(this, "Error", "La categoría es obligatoria");
        return;
    }
    if (descripcion.isEmpty()) {
        QMessageBox::warning(this, "Error", "La descripción es obligatoria");
        return;
    }
    if (tiempoPrestamo <= 0) {
        QMessageBox::warning(this, "Error", "El tiempo de préstamo debe ser mayor a 0");
        return;
    }

    // Crear objeto Objeto (el ID será asignado por la base de datos)
    Objeto nuevoObjeto(0, nombre, categoria, usuarioActualId, 0, descripcion, tiempoPrestamo);

    //Guardar en base de datos
    if (db->insertarObjeto(nuevoObjeto)) {
        QMessageBox::information(this, "Éxito", "Objeto guardado correctamente");
        on_pushButtonLimpiar_clicked();  // Limpiar campos
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el objeto");
    }
}

void FormularioObjeto::on_pushButtonLimpiar_clicked()
{
    ui->lineEditNombre->clear();
    ui->lineEditCategoria->clear();
    ui->textEditDescripcion->clear();
    ui->spinBoxTiempo->setValue(7);  // Valor por defecto
    ui->lineEditNombre->setFocus();  // Cursor en el primer campo
}
