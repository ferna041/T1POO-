#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QList>

// Forward declarations para evitar includes circulares
class Usuario;
class Objeto;
class Reserva;
class Notificacion;


class DatabaseManager {
    private:
        QSqlDatabase db;    // Base de datos SQLite

        // Métodos privados para crear las tablas
        bool crearTablaUsuarios();
        bool crearTablaObjetos();
        bool crearTablaReservas();
        bool crearTablaNotificaciones();

    public:
        DatabaseManager();
        ~DatabaseManager();

        bool conectar();
        bool crearTablas();
        // Métodos para manejar usuarios
        bool obtenerUsuarios(QList<Usuario>& usuarios);
        bool insertarUsuario(const Usuario& usuario);
        bool actualizarUsuario(const Usuario& usuario);
        bool eliminarUsuario(int idUsuario);
        bool obtenerUsuarioPorId(int idUsuario, Usuario& usuario);
        // Métodos para manejar objetos
        bool obtenerObjetos(QList<Objeto>& objetos);
        bool insertarObjeto(const Objeto& objeto);
        bool actualizarObjeto(const Objeto& objeto);
        bool eliminarObjeto(int idObjeto);
        // Métodos para manejar reservas
        bool obtenerReservas(QList<Reserva>& reservas);
        bool insertarReserva(const Reserva& reserva);
        bool actualizarReserva(const Reserva& reserva);
        bool eliminarReserva(int idReserva);
        // Métodos auxiliares para reservas
        bool crearReserva(int idObjeto, int idUsuario, int tiempoPrestamo);
        bool objetoEstaReservado(int idObjeto);
        bool obtenerReservasPorUsuario(int idUsuario, QList<Reserva>& reservas);
        bool obtenerObjetoPorId(int idObjeto, Objeto& objeto);
        bool cancelarReserva(int idReserva);
        int obtenerUltimoIdReserva();
        // Método para recrear la base de datos
        bool recrearBaseDatos();
        // Métodos para manejar notificaciones
        bool obtenerNotificaciones(QList<Notificacion>& notificaciones);
        bool insertarNotificacion(const Notificacion& notificacion);
        bool actualizarNotificacion(const Notificacion& notificacion);
        bool eliminarNotificacion(int idNotificacion);
};

#endif // DATABASEMANAGER_H