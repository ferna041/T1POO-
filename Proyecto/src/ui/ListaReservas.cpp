#include "ListaReservas.h"
#include "ui_ListaReservas.h"
#include <QDebug>

ListaReservas::ListaReservas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaReservas)
    , usuarioActualId(-1)
{
    ui->setupUi(this);
    setWindowTitle("Mis Reservas");
    ui->labelTitulo->setText("Mis Reservas");
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }

    configurarTabla();
    cargarReservas();
}

ListaReservas::ListaReservas(int usuarioId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaReservas)
    , usuarioActualId(usuarioId)
{
    ui->setupUi(this);
    setWindowTitle("Mis Reservas");
    ui->labelTitulo->setText("Mis Reservas");
    
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }

    configurarTabla();
    cargarReservas();
}

ListaReservas::~ListaReservas()
{
    delete ui;
    delete db;
}

void ListaReservas::configurarTabla()
{
    // Configurar columnas para reservas
    ui->tableWidgetReservas->setColumnCount(6);
    QStringList headers;
    headers << "Objeto" << "Categoría" << "Fecha Reserva" << "Fecha Vencimiento" << "Estado" << "Acción";
    ui->tableWidgetReservas->setHorizontalHeaderLabels(headers);
    
    // Configurar anchos mínimos - Se estiran proporcionalmente
    ui->tableWidgetReservas->setColumnWidth(0, 200);  // Objeto (mínimo)
    ui->tableWidgetReservas->setColumnWidth(1, 140);  // Categoría (mínimo)
    ui->tableWidgetReservas->setColumnWidth(2, 150);  // Fecha Reserva (mínimo)
    ui->tableWidgetReservas->setColumnWidth(3, 150);  // Fecha Vencimiento (mínimo)
    ui->tableWidgetReservas->setColumnWidth(4, 120);  // Estado (mínimo)
    ui->tableWidgetReservas->setColumnWidth(5, 100);  // Acción (mínimo)
    
    // Configurar altura de filas - Altura optimizada
    ui->tableWidgetReservas->verticalHeader()->setDefaultSectionSize(40);
    
    // Configurar header vertical (números de fila) - Ocultar completamente
    ui->tableWidgetReservas->verticalHeader()->setVisible(false);
    
    // Configurar columnas para usar todo el ancho disponible
    ui->tableWidgetReservas->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetReservas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetReservas->setAlternatingRowColors(true);
    ui->tableWidgetReservas->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Solo lectura
    ui->tableWidgetReservas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Permitir que el usuario ajuste las columnas manualmente
    ui->tableWidgetReservas->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

void ListaReservas::cargarReservas()
{
    // Limpiar tabla
    ui->tableWidgetReservas->setRowCount(0);

    // Obtener reservas de la base de datos
    QList<Reserva> reservas;
    if (!db->obtenerReservasPorUsuario(usuarioActualId, reservas)) {
        qDebug() << "Error al obtener reservas";
        return;
    }
    
    ui->tableWidgetReservas->setRowCount(reservas.size());
    for (int i = 0; i < reservas.size(); ++i) {
        const Reserva& reserva = reservas[i];
        
        // Obtener información del objeto - creamos un objeto temporal con valores por defecto
        Objeto objetoTemp(0, "", "", 0, 0, "", 0);
        if (db->obtenerObjetoPorId(reserva.getIdObjeto(), objetoTemp)) {
            ui->tableWidgetReservas->setItem(i, 0, new QTableWidgetItem(objetoTemp.getNombre()));
            ui->tableWidgetReservas->setItem(i, 1, new QTableWidgetItem(objetoTemp.getCategoria()));
        } else {
            ui->tableWidgetReservas->setItem(i, 0, new QTableWidgetItem("Objeto no encontrado"));
            ui->tableWidgetReservas->setItem(i, 1, new QTableWidgetItem("-"));
        }
        
        // Fecha de reserva
        ui->tableWidgetReservas->setItem(i, 2, new QTableWidgetItem(reserva.getFechaReserva().toString("dd/MM/yyyy")));
        
        // Fecha de vencimiento
        ui->tableWidgetReservas->setItem(i, 3, new QTableWidgetItem(reserva.getFechaVencimiento().toString("dd/MM/yyyy")));
        
        // Estado de la reserva
        QString estadoTexto;
        switch (reserva.getEstado()) {
            case 0: estadoTexto = "Activa"; break;
            case 1: estadoTexto = "Vencida"; break;
            case 2: estadoTexto = "Cancelada"; break;
            default: estadoTexto = "Desconocido"; break;
        }
        ui->tableWidgetReservas->setItem(i, 4, new QTableWidgetItem(estadoTexto));
        
        // Botón para cancelar reserva (solo si está activa)
        if (reserva.getEstado() == 0) {
            QPushButton* botonCancelar = crearBotonCancelar(reserva.getId());
            ui->tableWidgetReservas->setCellWidget(i, 5, botonCancelar);
        } else {
            ui->tableWidgetReservas->setItem(i, 5, new QTableWidgetItem("-"));
        }
    }
}

void ListaReservas::on_pushButtonActualizar_clicked()
{
    cargarReservas();
}

QPushButton* ListaReservas::crearBotonCancelar(int reservaId)
{
    QPushButton* boton = new QPushButton("Cancelar");
    boton->setMinimumSize(80, 25);
    boton->setMaximumSize(80, 25);
    boton->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border: none; border-radius: 3px; }"
                         "QPushButton:hover { background-color: #c82333; }"
                         "QPushButton:pressed { background-color: #bd2130; }");
    
    // Conectar el botón con el slot, pasando el ID de la reserva
    connect(boton, &QPushButton::clicked, [this, reservaId]() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Cancelar Reserva", 
                                    "¿Está seguro de que desea cancelar esta reserva?",
                                    QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            if (db->cancelarReserva(reservaId)) {
                QMessageBox::information(this, "Éxito", "Reserva cancelada correctamente");
                // Recargar la tabla para reflejar los cambios
                cargarReservas();
            } else {
                QMessageBox::warning(this, "Error", "No se pudo cancelar la reserva");
            }
        }
    });
    
    return boton;
}

void ListaReservas::cancelarReserva()
{
    // Este método puede ser usado para futuras funcionalidades
    // Por ahora, la lógica está en el lambda del botón
}
