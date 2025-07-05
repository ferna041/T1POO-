#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include <QWidget>
#include "DatabaseManager.h"
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class ListaUsuarios;
}

class ListaUsuarios : public QWidget
{
    Q_OBJECT

public:
    explicit ListaUsuarios(QWidget *parent = nullptr);
    ~ListaUsuarios();

private slots:

    void on_pushButtonActualizar_clicked();
    void cargarUsuarios();
    void ingresarCuentaUsuario();

private:
    void configurarTabla();

    Ui::ListaUsuarios *ui;
    DatabaseManager *db;
};

#endif // LISTAUSUARIOS_H
