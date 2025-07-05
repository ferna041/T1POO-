#ifndef FORMULARIOUSUARIO_H
#define FORMULARIOUSUARIO_H

#include <QWidget>
#include <QMessageBox>
#include "DatabaseManager.h"
#include "Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FormularioUsuario; }
QT_END_NAMESPACE

class FormularioUsuario : public QWidget
{
    Q_OBJECT

public:
    FormularioUsuario(QWidget *parent = nullptr);
    ~FormularioUsuario();

private slots:
    void on_pushButtonGuardar_clicked();    // Qt conecta automáticamente
    void on_pushButtonLimpiar_clicked();    // por el nombre del botón

private:
    Ui::FormularioUsuario *ui;  // Conexión con el .ui
    DatabaseManager *db;
};

#endif // FORMULARIOUSUARIO_H
