#ifndef OBJETO_H
#define OBJETO_H
#include <QString>
#include <QDateTime>

class Objeto{
    private:
        int id;
        QString nombre;
        QString categoria;
        int idDueno;
        int estado; // 0: disponible, 1: prestado, 2: no disponible
        QString descripcion;
        QDateTime fechaPublicacion;
        int tiempoPrestamo; // en días
    public:
        Objeto(int id, QString nombre, QString categoria, int idDueno, int estado, QString descripcion, 
               int tiempoPrestamo, QDateTime fechaPublicacion = QDateTime::currentDateTime())
            : id(id), nombre(nombre), categoria(categoria), idDueno(idDueno), estado(estado), descripcion(descripcion),
              fechaPublicacion(fechaPublicacion), tiempoPrestamo(tiempoPrestamo) {}

        ~Objeto() {};

        // Getters
        int getId() const { return id; }
        QString getNombre() const { return nombre; }
        QString getCategoria() const { return categoria; }
        int getIdDueno() const { return idDueno; }
        int getEstado() const { return estado; }
        QString getDescripcion() const { return descripcion; }
        QDateTime getFechaPublicacion() const { return fechaPublicacion; }
        int getTiempoPrestamo() const { return tiempoPrestamo; }
        // Setters
        void setId(int newId) { id = newId; }
        void setNombre(const QString& newNombre) { nombre = newNombre; }
        void setCategoria(const QString& newCategoria) { categoria = newCategoria; }
        void setIdDueno(int newIdDueno) { idDueno = newIdDueno; }
        void setEstado(int newEstado) { estado = newEstado; }
        void setDescripcion(const QString& newDescripcion) { descripcion = newDescripcion; }
        void setFechaPublicacion(const QDateTime& newFechaPublicacion) { fechaPublicacion = newFechaPublicacion; }
        void setTiempoPrestamo(int newTiempoPrestamo) { tiempoPrestamo = newTiempoPrestamo; }
};

#endif // OBJETO_H