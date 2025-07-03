#ifndef NOTIFICACION_H
#define NOTIFICACION_H

#include <QString>
#include <QDateTime>

class Notificacion {
public:
    enum Tipo {
        SOLICITUD_RECIBIDA,
        SOLICITUD_ENVIADA, 
        RECORDATORIO_DEVOLUCION,
        PRESTAMO_CONFIRMADO,
        PRESTAMO_RECHAZADO,
        OBJETO_DEVUELTO
    };

private:
    int id;
    Tipo tipo;
    int idUsuario; // ID del usuario que recibe la notificación
    int idReserva; // ID de la reserva asociada, si aplica
    QString mensaje; // Mensaje de la notificación
    QDateTime fechaCreacion; // Fecha y hora de creación de la notificación
    bool leida; // Indica si la notificación ha sido leída

public:
    Notificacion(int id, Tipo tipo, int idUsuario, int idReserva, 
                 const QString& mensaje, QDateTime fechaCreacion = QDateTime::currentDateTime(), bool leida = false)
        : id(id), tipo(tipo), idUsuario(idUsuario), idReserva(idReserva), mensaje(mensaje),
          fechaCreacion(fechaCreacion), leida(leida) {}
    
    ~Notificacion() {}
    
    // Getters
    int getId() const { return id; }
    Tipo getTipo() const { return tipo; }
    int getIdUsuario() const { return idUsuario; }
    int getIdReserva() const { return idReserva; }
    QString getMensaje() const { return mensaje; }
    QDateTime getFechaCreacion() const { return fechaCreacion; }
    bool isLeida() const { return leida; }
    
    // Setters
    void setId(int newId) { id = newId; }
    void setTipo(Tipo newTipo) { tipo = newTipo; }
    void setIdUsuario(int newIdUsuario) { idUsuario = newIdUsuario; }
    void setIdReserva(int newIdReserva) { idReserva = newIdReserva; }
    void setMensaje(const QString& newMensaje) { mensaje = newMensaje; }
    void setFechaCreacion(const QDateTime& newFechaCreacion) { fechaCreacion = newFechaCreacion; }
    void setLeida(bool newLeida) { leida = newLeida; }
};

#endif // NOTIFICACION_H