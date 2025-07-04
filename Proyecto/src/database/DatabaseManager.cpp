#include "DatabaseManager.h"
#include "Usuario.h"
#include "Objeto.h"
#include "Reserva.h"
#include "Notificacion.h"
#include <QDebug>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

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
            estado INTEGER DEFAULT 0,
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
            query.value("fecha_inicio").toDateTime(),
            query.value("fecha_fin").toDateTime(),
            query.value("fecha_reserva").toDateTime(),
            query.value("estado").toInt()
        );
        reservas.append(reserva);
    }
    return true;
}

bool DatabaseManager::insertarReserva(const Reserva& reserva) {
    QSqlQuery query;
    QString sql = "INSERT INTO reservas (id_objeto, id_usuario, fecha_reserva, fecha_inicio, fecha_fin, estado) "
                  "VALUES (:id_objeto, :id_usuario, :fecha_reserva, :fecha_inicio, :fecha_fin, :estado)";
    
    qDebug() << "SQL a ejecutar:" << sql;
    qDebug() << "Valores - idObjeto:" << reserva.getIdObjeto() 
             << "idUsuario:" << reserva.getIdUsuario()
             << "fechaReserva:" << reserva.getFechaReserva()
             << "fechaInicio:" << reserva.getFechaInicio()
             << "fechaFin:" << reserva.getFechaFin()
             << "estado:" << reserva.getEstado();
    
    query.prepare(sql);
    query.bindValue(":id_objeto", reserva.getIdObjeto());
    query.bindValue(":id_usuario", reserva.getIdUsuario());
    query.bindValue(":fecha_reserva", reserva.getFechaReserva());
    query.bindValue(":fecha_inicio", reserva.getFechaInicio());
    query.bindValue(":fecha_fin", reserva.getFechaFin());
    query.bindValue(":estado", reserva.getEstado());

    if (!query.exec()) {
        qDebug() << "Error insertando reserva:" << query.lastError().text();
        qDebug() << "Query SQL ejecutado:" << query.lastQuery();
        return false;
    }
    return true;
}

bool DatabaseManager::actualizarReserva(const Reserva& reserva) {
    QSqlQuery query;
    query.prepare("UPDATE reservas SET id_objeto = :id_objeto, id_usuario = :id_usuario, "
                  "fecha_reserva = :fecha_reserva, fecha_inicio = :fecha_inicio, fecha_fin = :fecha_fin, "
                  "estado = :estado WHERE id = :id");
    query.bindValue(":id", reserva.getId());
    query.bindValue(":id_objeto", reserva.getIdObjeto());
    query.bindValue(":id_usuario", reserva.getIdUsuario());
    query.bindValue(":fecha_reserva", reserva.getFechaReserva());
    query.bindValue(":fecha_inicio", reserva.getFechaInicio());
    query.bindValue(":fecha_fin", reserva.getFechaFin());
    query.bindValue(":estado", reserva.getEstado());

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
    
    // Obtener información del objeto y usuarios para las notificaciones
    Objeto objeto;
    Usuario usuarioReservante;
    Usuario usuarioDueno;
    
    if (!obtenerObjetoPorId(idObjeto, objeto)) {
        qDebug() << "Error obteniendo información del objeto";
        return false;
    }
    
    if (!obtenerUsuarioPorId(idUsuario, usuarioReservante)) {
        qDebug() << "Error obteniendo información del usuario reservante";
        return false;
    }
    
    if (!obtenerUsuarioPorId(objeto.getIdDueno(), usuarioDueno)) {
        qDebug() << "Error obteniendo información del dueño";
        return false;
    }
    
    // Calcular fechas
    QDateTime fechaInicio = QDateTime::currentDateTime();
    QDateTime fechaFin = fechaInicio.addDays(tiempoPrestamo);
    
    // Crear reserva con estado activo (0)
    Reserva nuevaReserva(0, idObjeto, idUsuario, fechaInicio, fechaFin, QDateTime::currentDateTime(), 0);
    
    // Insertar la reserva
    if (!insertarReserva(nuevaReserva)) {
        return false;
    }
    
    // Obtener el ID de la reserva recién creada
    int idReserva = obtenerUltimoIdReserva();
    
    // Crear notificación para el dueño del objeto
    QString mensajeDueno = QString("Tu objeto '%1' ha sido reservado por %2 hasta el %3")
                          .arg(objeto.getNombre())
                          .arg(usuarioReservante.getNombre())
                          .arg(fechaFin.toString("dd/MM/yyyy"));
    
    Notificacion notifDueno(0, Notificacion::SOLICITUD_RECIBIDA, objeto.getIdDueno(), 
                           idReserva, mensajeDueno, QDateTime::currentDateTime(), false);
    
    // Crear notificación para el usuario que reserva
    QString mensajeReservante = QString("Has reservado el objeto '%1' de %2. Disponible hasta el %3")
                               .arg(objeto.getNombre())
                               .arg(usuarioDueno.getNombre())
                               .arg(fechaFin.toString("dd/MM/yyyy"));
    
    Notificacion notifReservante(0, Notificacion::PRESTAMO_CONFIRMADO, idUsuario, 
                                idReserva, mensajeReservante, QDateTime::currentDateTime(), false);
    
    // Insertar las notificaciones
    if (!insertarNotificacion(notifDueno)) {
        qDebug() << "Error creando notificación para el dueño";
    }
    
    if (!insertarNotificacion(notifReservante)) {
        qDebug() << "Error creando notificación para el reservante";
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
    query.prepare("SELECT COUNT(*) as count FROM reservas WHERE id_objeto = :id_objeto AND fecha_fin > :fecha_actual AND estado = 0");
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

bool DatabaseManager::obtenerReservasPorUsuario(int idUsuario, QList<Reserva>& reservas) {
    QSqlQuery query;
    query.prepare("SELECT * FROM reservas WHERE id_usuario = :id_usuario ORDER BY fecha_reserva DESC");
    query.bindValue(":id_usuario", idUsuario);
    
    if (!query.exec()) {
        qDebug() << "Error obteniendo reservas por usuario:" << query.lastError().text();
        return false;
    }
    
    while (query.next()) {
        Reserva reserva(
            query.value("id").toInt(),
            query.value("id_objeto").toInt(),
            query.value("id_usuario").toInt(),
            query.value("fecha_inicio").toDateTime(),
            query.value("fecha_fin").toDateTime(),
            query.value("fecha_reserva").toDateTime(),
            query.value("estado").toInt()
        );
        reservas.append(reserva);
    }
    return true;
}

bool DatabaseManager::obtenerObjetoPorId(int idObjeto, Objeto& objeto) {
    QSqlQuery query;
    query.prepare("SELECT * FROM objetos WHERE id = :id");
    query.bindValue(":id", idObjeto);
    
    if (!query.exec()) {
        qDebug() << "Error obteniendo objeto por ID:" << query.lastError().text();
        return false;
    }
    
    if (query.next()) {
        objeto = Objeto(
            query.value("id").toInt(),
            query.value("nombre").toString(),
            query.value("categoria").toString(),
            query.value("id_dueno").toInt(),
            query.value("estado").toInt(),
            query.value("descripcion").toString(),
            query.value("tiempo_prestamo").toInt(),
            query.value("fecha_publicacion").toDateTime()
        );
        return true;
    }
    
    qDebug() << "Objeto no encontrado con ID:" << idObjeto;
    return false;
}

bool DatabaseManager::cancelarReserva(int idReserva) {
    QSqlQuery query;
    
    // Primero obtener el ID del objeto para actualizar su estado
    query.prepare("SELECT id_objeto FROM reservas WHERE id = :id AND estado = 0");
    query.bindValue(":id", idReserva);
    
    if (!query.exec()) {
        qDebug() << "Error obteniendo objeto de la reserva:" << query.lastError().text();
        return false;
    }
    
    int idObjeto = -1;
    if (query.next()) {
        idObjeto = query.value("id_objeto").toInt();
    } else {
        qDebug() << "Reserva activa no encontrada con ID:" << idReserva;
        return false;
    }
    
    // Actualizar el estado de la reserva a "cancelada" (estado = 2)
    query.prepare("UPDATE reservas SET estado = 2 WHERE id = :id");
    query.bindValue(":id", idReserva);
    
    if (!query.exec()) {
        qDebug() << "Error cancelando reserva:" << query.lastError().text();
        return false;
    }
    
    // Actualizar el estado del objeto a "disponible" (estado = 0)
    query.prepare("UPDATE objetos SET estado = 0 WHERE id = :id");
    query.bindValue(":id", idObjeto);
    
    if (!query.exec()) {
        qDebug() << "Error actualizando estado del objeto tras cancelación:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "Reserva cancelada exitosamente. ID:" << idReserva;
    return true;
}

bool DatabaseManager::recrearBaseDatos() {
    // Cerrar la conexión actual
    db.close();
    
    // Eliminar el archivo de la base de datos
    QString dbPath = "biblioteca_vecinal.db";
    if (QFile::exists(dbPath)) {
        if (!QFile::remove(dbPath)) {
            qDebug() << "Error eliminando base de datos anterior";
            return false;
        }
    }
    
    // Reconectar y crear las tablas nuevamente
    if (!conectar()) {
        return false;
    }
    
    return crearTablas();
}

int DatabaseManager::obtenerUltimoIdReserva() {
    QSqlQuery query;
    query.prepare("SELECT last_insert_rowid()");
    
    if (!query.exec() || !query.next()) {
        qDebug() << "Error obteniendo último ID de reserva:" << query.lastError().text();
        return -1;
    }
    
    return query.value(0).toInt();
}
