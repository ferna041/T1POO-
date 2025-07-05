#include "Notificaciones.h"
#include "ui_Notificaciones.h"
#include "../database/DatabaseManager.h"
#include "../models/Notificacion.h"
#include <QDateTime>
#include <QDebug>

Notificaciones::Notificaciones(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Notificaciones)
    , db(nullptr)
    , usuarioActualId(-1)
{
    ui->setupUi(this);
    configurarTabla();
    
    // Conectar signals
    connect(ui->btnActualizar, &QPushButton::clicked, this, &Notificaciones::on_btnActualizar_clicked);
    connect(ui->btnMarcarLeidas, &QPushButton::clicked, this, &Notificaciones::on_btnMarcarLeidas_clicked);
    connect(ui->btnEliminarTodas, &QPushButton::clicked, this, &Notificaciones::on_btnEliminarTodas_clicked);
}

Notificaciones::~Notificaciones()
{
    delete ui;
}

void Notificaciones::setDatabaseManager(DatabaseManager* database)
{
    this->db = database;
}

void Notificaciones::setUsuarioActual(int userId)
{
    this->usuarioActualId = userId;
    if (db != nullptr) {
        actualizarNotificaciones();
    }
}

void Notificaciones::configurarTabla()
{
    // Configuración inicial del widget
    ui->labelSinNotificaciones->setVisible(true);
    actualizarEstadisticas();
}

void Notificaciones::actualizarNotificaciones()
{
    if (db == nullptr || usuarioActualId == -1) {
        qDebug() << "Base de datos o usuario no configurados";
        return;
    }
    
    cargarNotificaciones();
    mostrarNotificaciones();
    actualizarEstadisticas();
}

void Notificaciones::cargarNotificaciones()
{
    notificaciones.clear();
    
    if (!db->obtenerNotificaciones(notificaciones)) {
        qDebug() << "Error al cargar notificaciones";
        return;
    }
    
    // Filtrar solo las notificaciones del usuario actual
    QList<Notificacion> notificacionesUsuario;
    for (const auto& notif : notificaciones) {
        if (notif.getIdUsuario() == usuarioActualId) {
            notificacionesUsuario.append(notif);
        }
    }
    notificaciones = notificacionesUsuario;
}

void Notificaciones::mostrarNotificaciones()
{
    limpiarListaNotificaciones();
    
    if (notificaciones.isEmpty()) {
        ui->labelSinNotificaciones->setVisible(true);
        ui->labelSinNotificaciones->setText("📭 No hay notificaciones disponibles");
        return;
    }
    
    ui->labelSinNotificaciones->setVisible(false);
    
    for (const auto& notificacion : notificaciones) {
        crearWidgetNotificacion(notificacion);
    }
}

void Notificaciones::actualizarEstadisticas()
{
    // Método vacío ya que se eliminaron los contadores de estadísticas
}

void Notificaciones::crearWidgetNotificacion(const Notificacion& notificacion)
{
    // Crear el frame principal de la notificación
    QFrame* frameNotificacion = new QFrame();
    frameNotificacion->setObjectName("notificacion_" + QString::number(notificacion.getId()));
    
    QString claseEstilo = notificacion.isLeida() ? "notificacion-item" : "notificacion-item notificacion-nueva";
    
    QString colorFondo = notificacion.isLeida() ? "white" : "#e3f2fd";
    QString colorBorde = notificacion.isLeida() ? "#e9ecef" : "#2196f3";
    
    QString estilo = QString("QFrame#%1 { "
                           "background-color: %2; "
                           "border: 1px solid %3; "
                           "border-radius: 8px; "
                           "margin: 4px; "
                           "padding: 12px; "
                           "}")
                           .arg(frameNotificacion->objectName())
                           .arg(colorFondo)
                           .arg(colorBorde);
    
    frameNotificacion->setStyleSheet(estilo);
    
    // Layout principal de la notificación
    QHBoxLayout* layoutPrincipal = new QHBoxLayout(frameNotificacion);
    layoutPrincipal->setSpacing(12);
    
    // Icono de tipo
    QLabel* labelIcono = new QLabel();
    labelIcono->setText(obtenerIconoTipo(static_cast<int>(notificacion.getTipo())));
    labelIcono->setStyleSheet("font-size: 24px; min-width: 30px; max-width: 30px;");
    labelIcono->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    
    // Contenido de la notificación
    QVBoxLayout* layoutContenido = new QVBoxLayout();
    layoutContenido->setSpacing(4);
    
    // Título y tipo
    QHBoxLayout* layoutTitulo = new QHBoxLayout();
    
    QLabel* labelTipo = new QLabel(obtenerTextoTipo(static_cast<int>(notificacion.getTipo())));
    labelTipo->setStyleSheet(QString("QLabel { font-size: 10px; font-weight: 600; padding: 2px 8px; "
                                   "border-radius: 12px; color: white; background-color: %1; }")
                           .arg(obtenerColorTipo(static_cast<int>(notificacion.getTipo()))));
    
    QLabel* labelFecha = new QLabel(notificacion.getFechaCreacion().toString("dd/MM/yyyy hh:mm"));
    labelFecha->setStyleSheet("font-size: 11px; color: #6c757d; font-style: italic;");
    
    layoutTitulo->addWidget(labelTipo);
    layoutTitulo->addStretch();
    layoutTitulo->addWidget(labelFecha);
    
    // Mensaje
    QLabel* labelMensaje = new QLabel(notificacion.getMensaje());
    labelMensaje->setStyleSheet("font-size: 13px; color: #555; line-height: 1.4;");
    labelMensaje->setWordWrap(true);
    
    layoutContenido->addLayout(layoutTitulo);
    layoutContenido->addWidget(labelMensaje);
    
    // Botón de marcar como leída (si no está leída)
    QVBoxLayout* layoutBotones = new QVBoxLayout();
    layoutBotones->setAlignment(Qt::AlignTop);
    
    if (!notificacion.isLeida()) {
        QPushButton* btnMarcarLeida = new QPushButton("✓");
        btnMarcarLeida->setStyleSheet("QPushButton { background-color: #28a745; color: white; "
                                    "border: none; border-radius: 15px; width: 30px; height: 30px; "
                                    "font-size: 14px; font-weight: bold; } "
                                    "QPushButton:hover { background-color: #1e7e34; }");
        btnMarcarLeida->setFixedSize(30, 30);
        btnMarcarLeida->setToolTip("Marcar como leída");
        
        connect(btnMarcarLeida, &QPushButton::clicked, [this, notificacion]() {
            marcarNotificacionComoLeida(notificacion.getId());
        });
        
        layoutBotones->addWidget(btnMarcarLeida);
    }
    
    // Ensamblar el layout
    layoutPrincipal->addWidget(labelIcono);
    layoutPrincipal->addLayout(layoutContenido, 1);
    layoutPrincipal->addLayout(layoutBotones);
    
    // Agregar al scroll area
    QVBoxLayout* layoutScroll = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (layoutScroll) {
        layoutScroll->insertWidget(layoutScroll->count() - 1, frameNotificacion);
    }
}

void Notificaciones::limpiarListaNotificaciones()
{
    QVBoxLayout* layoutScroll = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!layoutScroll) return;
    
    // Eliminar todos los widgets excepto el label de "sin notificaciones" y el spacer
    for (int i = layoutScroll->count() - 1; i >= 0; --i) {
        QLayoutItem* item = layoutScroll->itemAt(i);
        if (item && item->widget()) {
            QWidget* widget = item->widget();
            if (widget != ui->labelSinNotificaciones) {
                layoutScroll->removeWidget(widget);
                widget->deleteLater();
            }
        }
    }
}

QString Notificaciones::obtenerColorTipo(int tipo)
{
    switch (static_cast<Notificacion::Tipo>(tipo)) {
        case Notificacion::PRESTAMO_CONFIRMADO: return "#28a745";
        case Notificacion::PRESTAMO_RECHAZADO: return "#dc3545";
        case Notificacion::RECORDATORIO_DEVOLUCION: return "#ffc107";
        case Notificacion::OBJETO_DEVUELTO: return "#17a2b8";
        case Notificacion::SOLICITUD_RECIBIDA: return "#6c757d";
        case Notificacion::SOLICITUD_ENVIADA: return "#007bff";
        default: return "#007bff";
    }
}

QString Notificaciones::obtenerTextoTipo(int tipo)
{
    switch (static_cast<Notificacion::Tipo>(tipo)) {
        case Notificacion::PRESTAMO_CONFIRMADO: return "PRÉSTAMO";
        case Notificacion::PRESTAMO_RECHAZADO: return "RECHAZADO";
        case Notificacion::RECORDATORIO_DEVOLUCION: return "RECORDATORIO";
        case Notificacion::OBJETO_DEVUELTO: return "DEVUELTO";
        case Notificacion::SOLICITUD_RECIBIDA: return "SOLICITUD";
        case Notificacion::SOLICITUD_ENVIADA: return "ENVIADA";
        default: return "GENERAL";
    }
}

QString Notificaciones::obtenerIconoTipo(int tipo)
{
    switch (static_cast<Notificacion::Tipo>(tipo)) {
        case Notificacion::PRESTAMO_CONFIRMADO: return "✅";
        case Notificacion::PRESTAMO_RECHAZADO: return "❌";
        case Notificacion::RECORDATORIO_DEVOLUCION: return "⏰";
        case Notificacion::OBJETO_DEVUELTO: return "📦";
        case Notificacion::SOLICITUD_RECIBIDA: return "📥";
        case Notificacion::SOLICITUD_ENVIADA: return "�";
        default: return "📢";
    }
}

// Slots
void Notificaciones::on_btnActualizar_clicked()
{
    actualizarNotificaciones();
}

void Notificaciones::on_btnMarcarLeidas_clicked()
{
    if (db == nullptr) return;
    
    for (auto& notificacion : notificaciones) {
        if (!notificacion.isLeida()) {
            notificacion.setLeida(true);
            db->actualizarNotificacion(notificacion);
        }
    }
    
    actualizarNotificaciones();
}

void Notificaciones::on_btnEliminarTodas_clicked()
{
    if (db == nullptr) return;
    
    for (const auto& notificacion : notificaciones) {
        db->eliminarNotificacion(notificacion.getId());
    }
    
    actualizarNotificaciones();
}

void Notificaciones::marcarNotificacionComoLeida(int notificacionId)
{
    if (db == nullptr) return;
    
    for (auto& notificacion : notificaciones) {
        if (notificacion.getId() == notificacionId) {
            notificacion.setLeida(true);
            db->actualizarNotificacion(notificacion);
            break;
        }
    }
    
    actualizarNotificaciones();
}
