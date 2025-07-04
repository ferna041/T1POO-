#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include "DatabaseManager.h"
#include "Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GestorUsuarios; }
QT_END_NAMESPACE

class GestorUsuarios : public QWidget
{
    Q_OBJECT

public:
    explicit GestorUsuarios(QWidget *parent = nullptr);
    ~GestorUsuarios();

private slots:
    void on_pushButtonRegistrar_clicked();
    void on_pushButtonLimpiar_clicked();
    void on_pushButtonActualizar_clicked();
    void cargarUsuarios();
    void ingresarCuentaUsuario();
    void limpiarFormulario();

private:
    void configurarTabla();
    void configurarInterfaz();
    bool validarFormulario();

    Ui::GestorUsuarios *ui;
    DatabaseManager *db;
};

#endif // GESTORUSUARIOS_H
