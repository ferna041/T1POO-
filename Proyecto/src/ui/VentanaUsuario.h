#ifndef VENTANAUSUARIO_H
#define VENTANAUSUARIO_H

#include <QMainWindow>
#include "Usuario.h"

namespace Ui {
class VentanaUsuario;
}

class VentanaUsuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaUsuario(const Usuario& usuario,QWidget *parent = nullptr);
    ~VentanaUsuario();

private:
    Ui::VentanaUsuario *ui;
    Usuario usuarioActual;
};

#endif // VENTANAUSUARIO_H
