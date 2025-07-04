#ifndef VENTANAUSUARIO_H
#define VENTANAUSUARIO_H

#include <QMainWindow>
#include "Usuario.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaUsuario; }
QT_END_NAMESPACE

// Forward declarations
class DatabaseManager;
class Notificaciones;

class VentanaUsuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaUsuario(const Usuario& usuario, QWidget *parent = nullptr);
    ~VentanaUsuario();

private:
    Ui::VentanaUsuario *ui;
    Usuario usuarioActual;
    DatabaseManager* db;
    Notificaciones* widgetNotificaciones;
};

#endif // VENTANAUSUARIO_H
