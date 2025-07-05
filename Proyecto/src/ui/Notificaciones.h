#ifndef NOTIFICACIONES_H
#define NOTIFICACIONES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class Notificaciones; }
QT_END_NAMESPACE

// Forward declarations
class DatabaseManager;
class Notificacion;

class Notificaciones : public QWidget
{
    Q_OBJECT

public:
    explicit Notificaciones(QWidget *parent = nullptr);
    ~Notificaciones();
    
    // Métodos públicos para configurar el widget
    void setDatabaseManager(DatabaseManager* db);
    void setUsuarioActual(int userId);
    void actualizarNotificaciones();

private slots:
    void on_btnActualizar_clicked();
    void on_btnMarcarLeidas_clicked();
    void on_btnEliminarTodas_clicked();
    void marcarNotificacionComoLeida(int notificacionId);

private:
    Ui::Notificaciones *ui;
    DatabaseManager* db;
    int usuarioActualId;
    QList<Notificacion> notificaciones;
    
    // Métodos privados para la funcionalidad
    void configurarTabla();
    void cargarNotificaciones();
    void mostrarNotificaciones();
    void actualizarEstadisticas();
    void crearWidgetNotificacion(const Notificacion& notificacion);
    void limpiarListaNotificaciones();
    QString obtenerColorTipo(int tipo);
    QString obtenerTextoTipo(int tipo);
    QString obtenerIconoTipo(int tipo);
};

#endif // NOTIFICACIONES_H
