#ifndef RESERVA_H
#define RESERVA_H
#include <QDateTime>

class Reserva {
    private:
        int id;
        int idObjeto; // ID del objeto reservado
        int idUsuario; // ID del usuario que reserva
        QDateTime fechaReserva; // Fecha y hora de la reserva
        QDateTime fechaInicio; // Fecha y hora de inicio del préstamo
        QDateTime fechaFin; // Fecha y hora de finalización del préstamo
    public:
        Reserva(int id, int idObjeto, int idUsuario, QDateTime fechaInicio, QDateTime fechaFin, 
                QDateTime fechaReserva = QDateTime::currentDateTime())
            : id(id), idObjeto(idObjeto), idUsuario(idUsuario), fechaReserva(fechaReserva),
              fechaInicio(fechaInicio), fechaFin(fechaFin) {}

        ~Reserva() {}

        // Getters
        int getId() const { return id; }
        int getIdObjeto() const { return idObjeto; }
        int getIdUsuario() const { return idUsuario; }
        QDateTime getFechaReserva() const { return fechaReserva; }
        QDateTime getFechaInicio() const { return fechaInicio; }
        QDateTime getFechaFin() const { return fechaFin; }

        // Setters
        void setId(int newId) { id = newId; }
        void setIdObjeto(int newIdObjeto) { idObjeto = newIdObjeto; }
        void setIdUsuario(int newIdUsuario) { idUsuario = newIdUsuario; }
        void setFechaReserva(const QDateTime& newFechaReserva) { fechaReserva = newFechaReserva; }
        void setFechaInicio(const QDateTime& newFechaInicio) { fechaInicio = newFechaInicio; }
        void setFechaFin(const QDateTime& newFechaFin) { fechaFin = newFechaFin; }
};

#endif // RESERVA_H