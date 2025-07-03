#ifndef USUARIO_H
#define USUARIO_H
#include <QString>
#include <QDateTime>

class Usuario {

    private:
        int id;
        QString nombre;
        QString email;
        QString telefono;
        QString direccion;
        double reputacion;
        QDateTime fechaRegistro;
        bool activo;
    public:
        Usuario() : id(0), nombre(""), email(""), telefono(""), direccion(""),
            reputacion(0.0), fechaRegistro(QDateTime::currentDateTime()), activo(true) {}

        Usuario(int id ,QString nombre, QString email, QString telefono, QString direccion, double reputacion, QDateTime fechaRegistro = QDateTime::currentDateTime() , bool activo=1)
            : id(id),nombre(nombre), email(email), telefono(telefono), direccion(direccion),
              reputacion(reputacion), fechaRegistro(fechaRegistro), activo(activo) {}
              
        ~Usuario() {};

        // Getters
        int getId() const { return id; }
        QString getNombre() const { return nombre; }
        QString getEmail() const { return email; }
        QString getTelefono() const { return telefono; }
        QString getDireccion() const { return direccion; }
        double getReputacion() const { return reputacion; }
        QDateTime getFechaRegistro() const { return fechaRegistro; }
        bool isActivo() const { return activo; }
        // Setters
        void setId(int newId) { id = newId; }
        void setNombre(const QString& newNombre) { nombre = newNombre; }
        void setEmail(const QString& newEmail) { email = newEmail; }
        void setTelefono(const QString& newTelefono) { telefono = newTelefono; }
        void setDireccion(const QString& newDireccion) { direccion = newDireccion; }
        void setReputacion(double newReputacion) { reputacion = newReputacion; }
        void setFechaRegistro(const QDateTime& newFechaRegistro) { fechaRegistro = newFechaRegistro; }
        void setActivo(bool newActivo) { activo = newActivo; }

};

#endif // USUARIO_H