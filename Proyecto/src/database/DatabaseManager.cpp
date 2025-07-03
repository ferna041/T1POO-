#include "DatabaseManager.h"
#include "Usuario.h"
#include "Objeto.h"
#include "Reserva.h"
#include "Notificacion.h"
#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

DatabaseManager::DatabaseManager() {
    // Constructor vacío por ahora
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::conectar() {
    // Crear conexión SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    
    // Nombre del archivo de base de datos
    db.setDatabaseName("biblioteca_vecinal.db");
    
    // Intentar abrir la conexión
    if (!db.open()) {
        qDebug() << "Error al conectar base de datos:" << db.lastError().text();
        return false;
    }
    
    qDebug() << "Base de datos conectada exitosamente";
    return true;
}

bool DatabaseManager::crearTablas() {
    // Crear todas las tablas
    if (!crearTablaUsuarios()) return false;
    if (!crearTablaObjetos()) return false;
    if (!crearTablaReservas()) return false;
    if (!crearTablaNotificaciones()) return false;
    
    qDebug() << "Todas las tablas creadas exitosamente";
    return true;
}

bool DatabaseManager::crearTablaUsuarios() {
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL,
            telefono TEXT,
            direccion TEXT,
            reputacion REAL DEFAULT 5.0,
            fecha_registro DATETIME DEFAULT CURRENT_TIMESTAMP,
            activo BOOLEAN DEFAULT 1
        )
    )";
    
    if (!query.exec(sql)) {
        qDebug() << "Error creando tabla usuarios:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::crearTablaObjetos() {
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS objetos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            categoria TEXT,
            id_dueno INTEGER NOT NULL,
            estado INTEGER DEFAULT 0,
            descripcion TEXT,
            fecha_publicacion DATETIME DEFAULT CURRENT_TIMESTAMP,
            tiempo_prestamo INTEGER DEFAULT 7,
            FOREIGN KEY (id_dueno) REFERENCES usuarios(id)
        )
    )";
    
    if (!query.exec(sql)) {
        qDebug() << "Error creando tabla objetos:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::crearTablaReservas() {
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS reservas (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            id_objeto INTEGER NOT NULL,
            id_usuario INTEGER NOT NULL,
            fecha_reserva DATETIME DEFAULT CURRENT_TIMESTAMP,
            fecha_inicio DATETIME NOT NULL,
            fecha_fin DATETIME NOT NULL,
            FOREIGN KEY (id_objeto) REFERENCES objetos(id),
            FOREIGN KEY (id_usuario) REFERENCES usuarios(id)
        )
    )";
    
    if (!query.exec(sql)) {
        qDebug() << "Error creando tabla reservas:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::crearTablaNotificaciones() {
    QSqlQuery query;
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS notificaciones (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            tipo INTEGER NOT NULL,
            id_usuario INTEGER NOT NULL,
            id_reserva INTEGER,
            mensaje TEXT NOT NULL,
            fecha_creacion DATETIME DEFAULT CURRENT_TIMESTAMP,
            leida BOOLEAN DEFAULT 0,
            FOREIGN KEY (id_usuario) REFERENCES usuarios(id),
            FOREIGN KEY (id_reserva) REFERENCES reservas(id)
        )
    )";
    
    if (!query.exec(sql)) {
        qDebug() << "Error creando tabla notificaciones:" << query.lastError().text();
        return false;
    }
    return true;
}

// Métodos para manejar usuarios

bool DatabaseManager::obtenerUsuarios(QList<Usuario>& usuarios) {
    QSqlQuery query("SELECT * FROM usuarios");
    if (!query.exec()) {
        qDebug() << "Error obteniendo usuarios:" << query.lastError().text();
        return false;
    }
    
    while (query.next()) {
        Usuario usuario(
            query.value("id").toInt(),
            query.value("nombre").toString(),
            query.value("email").toString(),
            query.value("telefono").toString(),
            query.value("direccion").toString(),
            query.value("reputacion").toDouble(),
            query.value("fecha_registro").toDateTime(),
            query.value("activo").toBool()
        );
        usuarios.append(usuario);
    }
    return true;
}

bool DatabaseManager::insertarUsuario(const Usuario& usuario) {
    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nombre, email, telefono, direccion, reputacion, fecha_registro, activo) "
                  "VALUES (:nombre, :email, :telefono, :direccion, :reputacion, :fecha_registro, :activo)");
    query.bindValue(":nombre", usuario.getNombre());
    query.bindValue(":email", usuario.getEmail());
    query.bindValue(":telefono", usuario.getTelefono());
    query.bindValue(":direccion", usuario.getDireccion());
    query.bindValue(":reputacion", usuario.getReputacion());
    query.bindValue(":fecha_registro", usuario.getFechaRegistro());
    query.bindValue(":activo", usuario.isActivo());

    if (!query.exec()) {
        qDebug() << "Error insertando usuario:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::actualizarUsuario(const Usuario& usuario) {
    QSqlQuery query;
    query.prepare("UPDATE usuarios SET nombre = :nombre, email = :email, telefono = :telefono, "
                  "direccion = :direccion, reputacion = :reputacion, fecha_registro = :fecha_registro, "
                  "activo = :activo WHERE id = :id");
    query.bindValue(":id", usuario.getId());
    query.bindValue(":nombre", usuario.getNombre());
    query.bindValue(":email", usuario.getEmail());
    query.bindValue(":telefono", usuario.getTelefono());
    query.bindValue(":direccion", usuario.getDireccion());
    query.bindValue(":reputacion", usuario.getReputacion());
    query.bindValue(":fecha_registro", usuario.getFechaRegistro());
    query.bindValue(":activo", usuario.isActivo());

    if (!query.exec()) {
        qDebug() << "Error actualizando usuario:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::eliminarUsuario(int idUsuario) {
    QSqlQuery query;
    // soft delete
    query.prepare("UPDATE usuarios SET activo = 0 WHERE id = :id");
    query.bindValue(":id", idUsuario);
    if (!query.exec()) {
        qDebug() << "Error eliminando usuario:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::obtenerUsuarioPorId(int idUsuario, Usuario& usuario) {
    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE id = :id");
    query.bindValue(":id", idUsuario);
    
    if (!query.exec()) {
        qDebug() << "Error obteniendo usuario por ID:" << query.lastError().text();
        return false;
    }
    
    if (query.next()) {
        usuario = Usuario(
            query.value("id").toInt(),
            query.value("nombre").toString(),
            query.value("email").toString(),
            query.value("telefono").toString(),
            query.value("direccion").toString(),
            query.value("reputacion").toDouble(),
            query.value("fecha_registro").toDateTime(),
            query.value("activo").toBool()
        );
        return true;
    }
    
    qDebug() << "Usuario no encontrado con ID:" << idUsuario;
    return false;
}

// Metodos para manejar objetos

bool DatabaseManager::obtenerObjetos(QList<Objeto>& objetos) {
    QSqlQuery query("SELECT * FROM objetos");
    if (!query.exec()) {
        qDebug() << "Error obteniendo objetos:" << query.lastError().text();
        return false;
    }
    
    while (query.next()) {
        Objeto objeto(
            query.value("id").toInt(),
            query.value("nombre").toString(),
            query.value("categoria").toString(),
            query.value("id_dueno").toInt(),
            query.value("estado").toInt(),
            query.value("descripcion").toString(),
            query.value("tiempo_prestamo").toInt(),
            query.value("fecha_publicacion").toDateTime()
        );
        objetos.append(objeto);
    }
    return true;
}

bool DatabaseManager::insertarObjeto(const Objeto& objeto) {
    QSqlQuery query;
    query.prepare("INSERT INTO objetos (nombre, categoria, id_dueno, estado, descripcion, fecha_publicacion, tiempo_prestamo) "
                  "VALUES (:nombre, :categoria, :id_dueno, :estado, :descripcion, :fecha_publicacion, :tiempo_prestamo)");
    query.bindValue(":nombre", objeto.getNombre());
    query.bindValue(":categoria", objeto.getCategoria());
    query.bindValue(":id_dueno", objeto.getIdDueno());
    query.bindValue(":estado", objeto.getEstado());
    query.bindValue(":descripcion", objeto.getDescripcion());
    query.bindValue(":fecha_publicacion", objeto.getFechaPublicacion());
    query.bindValue(":tiempo_prestamo", objeto.getTiempoPrestamo());

    if (!query.exec()) {
        qDebug() << "Error insertando objeto:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::actualizarObjeto(const Objeto& objeto) {
    QSqlQuery query;
    query.prepare("UPDATE objetos SET nombre = :nombre, categoria = :categoria, id_dueno = :id_dueno, "
                  "estado = :estado, descripcion = :descripcion, fecha_publicacion = :fecha_publicacion, "
                  "tiempo_prestamo = :tiempo_prestamo WHERE id = :id");
    query.bindValue(":id", objeto.getId());
    query.bindValue(":nombre", objeto.getNombre());
    query.bindValue(":categoria", objeto.getCategoria());
    query.bindValue(":id_dueno", objeto.getIdDueno());
    query.bindValue(":estado", objeto.getEstado());
    query.bindValue(":descripcion", objeto.getDescripcion());
    query.bindValue(":fecha_publicacion", objeto.getFechaPublicacion());
    query.bindValue(":tiempo_prestamo", objeto.getTiempoPrestamo());

    if (!query.exec()) {
        qDebug() << "Error actualizando objeto:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::eliminarObjeto(int idObjeto) {
    QSqlQuery query;
    // soft delete
    query.prepare("UPDATE objetos SET estado = -1 WHERE id = :id");
    query.bindValue(":id", idObjeto);
    if (!query.exec()) {
        qDebug() << "Error eliminando objeto:" << query.lastError().text();
        return false;
    }
    return true;
}

// Métodos para manejar reservas

bool DatabaseManager::obtenerReservas(QList<Reserva>& reservas) {
    QSqlQuery query("SELECT * FROM reservas");
    if (!query.exec()) {
        qDebug() << "Error obteniendo reservas:" << query.lastError().text();
        return false;
    }
    
    while (query.next()) {
        Reserva reserva(
            query.value("id").toInt(),
            query.value("id_objeto").toInt(),
            query.value("id_usuario").toInt(),
            query.value("fecha_reserva").toDateTime(),
            query.value("fecha_inicio").toDateTime(),
            query.value("fecha_fin").toDateTime()
        );
        reservas.append(reserva);
    }
    return true;
}

bool DatabaseManager::insertarReserva(const Reserva& reserva) {
    QSqlQuery query;
    query.prepare("INSERT INTO reservas (id_objeto, id_usuario, fecha_reserva, fecha_inicio, fecha_fin) "
                  "VALUES (:id_objeto, :id_usuario, :fecha_reserva, :fecha_inicio, :fecha_fin)");
    query.bindValue(":id_objeto", reserva.getIdObjeto());
    query.bindValue(":id_usuario", reserva.getIdUsuario());
    query.bindValue(":fecha_reserva", reserva.getFechaReserva());
    query.bindValue(":fecha_inicio", reserva.getFechaInicio());
    query.bindValue(":fecha_fin", reserva.getFechaFin());

    if (!query.exec()) {
        qDebug() << "Error insertando reserva:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::actualizarReserva(const Reserva& reserva) {
    QSqlQuery query;
    query.prepare("UPDATE reservas SET id_objeto = :id_objeto, id_usuario = :id_usuario, "
                  "fecha_reserva = :fecha_reserva, fecha_inicio = :fecha_inicio, fecha_fin = :fecha_fin "
                  "WHERE id = :id");
    query.bindValue(":id", reserva.getId());
    query.bindValue(":id_objeto", reserva.getIdObjeto());
    query.bindValue(":id_usuario", reserva.getIdUsuario());
    query.bindValue(":fecha_reserva", reserva.getFechaReserva());
    query.bindValue(":fecha_inicio", reserva.getFechaInicio());
    query.bindValue(":fecha_fin", reserva.getFechaFin());

    if (!query.exec()) {
        qDebug() << "Error actualizando reserva:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::eliminarReserva(int idReserva) {
    QSqlQuery query;
    // soft delete
    query.prepare("UPDATE reservas SET fecha_fin = NULL WHERE id = :id");
    query.bindValue(":id", idReserva);
    if (!query.exec()) {
        qDebug() << "Error eliminando reserva:" << query.lastError().text();
        return false;
    }
    return true;
}

// Métodos para manejar notificaciones

bool DatabaseManager::obtenerNotificaciones(QList<Notificacion>& notificaciones) {
    QSqlQuery query("SELECT * FROM notificaciones");
    if (!query.exec()) {
        qDebug() << "Error obteniendo notificaciones:" << query.lastError().text();
        return false;
    }
    
    while (query.next()) {
        Notificacion notificacion(
            query.value("id").toInt(),
            static_cast<Notificacion::Tipo>(query.value("tipo").toInt()),
            query.value("id_usuario").toInt(),
            query.value("id_reserva").toInt(),
            query.value("mensaje").toString(),
            query.value("fecha_creacion").toDateTime(),
            query.value("leida").toBool()
        );
        notificaciones.append(notificacion);
    }
    return true;
}

bool DatabaseManager::insertarNotificacion(const Notificacion& notificacion) {
    QSqlQuery query;
    query.prepare("INSERT INTO notificaciones (tipo, id_usuario, id_reserva, mensaje, fecha_creacion, leida) "
                  "VALUES (:tipo, :id_usuario, :id_reserva, :mensaje, :fecha_creacion, :leida)");
    query.bindValue(":tipo", static_cast<int>(notificacion.getTipo()));
    query.bindValue(":id_usuario", notificacion.getIdUsuario());
    query.bindValue(":id_reserva", notificacion.getIdReserva());
    query.bindValue(":mensaje", notificacion.getMensaje());
    query.bindValue(":fecha_creacion", notificacion.getFechaCreacion());
    query.bindValue(":leida", notificacion.isLeida());

    if (!query.exec()) {
        qDebug() << "Error insertando notificación:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::actualizarNotificacion(const Notificacion& notificacion) {
    QSqlQuery query;
    query.prepare("UPDATE notificaciones SET tipo = :tipo, id_usuario = :id_usuario, "
                  "id_reserva = :id_reserva, mensaje = :mensaje, fecha_creacion = :fecha_creacion, "
                  "leida = :leida WHERE id = :id");
    query.bindValue(":id", notificacion.getId());
    query.bindValue(":tipo", static_cast<int>(notificacion.getTipo()));
    query.bindValue(":id_usuario", notificacion.getIdUsuario());
    query.bindValue(":id_reserva", notificacion.getIdReserva());
    query.bindValue(":mensaje", notificacion.getMensaje());
    query.bindValue(":fecha_creacion", notificacion.getFechaCreacion());
    query.bindValue(":leida", notificacion.isLeida());

    if (!query.exec()) {
        qDebug() << "Error actualizando notificación:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::eliminarNotificacion(int idNotificacion) {
    QSqlQuery query;
    // soft delete
    query.prepare("UPDATE notificaciones SET leida = 1 WHERE id = :id");
    query.bindValue(":id", idNotificacion);
    if (!query.exec()) {
        qDebug() << "Error eliminando notificación:" << query.lastError().text();
        return false;
    }
    return true;
}

// Métodos auxiliares para reservas

bool DatabaseManager::crearReserva(int idObjeto, int idUsuario, int tiempoPrestamo) {
    // Verificar si el objeto ya está reservado
    if (objetoEstaReservado(idObjeto)) {
        qDebug() << "El objeto ya está reservado";
        return false;
    }
    
    // Calcular fechas
    QDateTime fechaInicio = QDateTime::currentDateTime();
    QDateTime fechaFin = fechaInicio.addDays(tiempoPrestamo);
    
    // Crear reserva
    Reserva nuevaReserva(0, idObjeto, idUsuario, fechaInicio, fechaFin);
    
    // Insertar la reserva
    if (!insertarReserva(nuevaReserva)) {
        return false;
    }
    
    // Actualizar el estado del objeto a "prestado" (estado = 1)
    QSqlQuery query;
    query.prepare("UPDATE objetos SET estado = 1 WHERE id = :id");
    query.bindValue(":id", idObjeto);
    
    if (!query.exec()) {
        qDebug() << "Error actualizando estado del objeto:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool DatabaseManager::objetoEstaReservado(int idObjeto) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as count FROM reservas WHERE id_objeto = :id_objeto AND fecha_fin > :fecha_actual");
    query.bindValue(":id_objeto", idObjeto);
    query.bindValue(":fecha_actual", QDateTime::currentDateTime());
    
    if (!query.exec()) {
        qDebug() << "Error verificando reserva del objeto:" << query.lastError().text();
        return true; // En caso de error, asumimos que está reservado para evitar conflictos
    }
    
    if (query.next()) {
        int count = query.value("count").toInt();
        return count > 0;
    }
    
    return false;
}