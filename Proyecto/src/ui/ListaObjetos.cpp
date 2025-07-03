#include "ListaObjetos.h"
#include "ui_ListaObjetos.h"
#include <QPushButton>
#include <QMessageBox>

ListaObjetos::ListaObjetos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaObjetos)
    , usuarioActualId(-1)
    , mostrarSoloMisObjetos(false)
{
    ui->setupUi(this);
    setWindowTitle("Lista de Objetos");
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }

    configurarTabla();
    cargarObjetos();
}

ListaObjetos::ListaObjetos(int usuarioId, bool mostrarSoloMisObjetos, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaObjetos)
    , usuarioActualId(usuarioId)
    , mostrarSoloMisObjetos(mostrarSoloMisObjetos)
{
    ui->setupUi(this);
    if (mostrarSoloMisObjetos) {
        setWindowTitle("Mis Objetos");
    } else {
        setWindowTitle("Catálogo de Objetos");
    }
    
    db = new DatabaseManager();
    if (!db->conectar()) {
        qDebug() << "Error al conectar a la base de datos";
        return;
    }

    configurarTabla();
    cargarObjetos();
}

ListaObjetos::~ListaObjetos()
{
    delete ui;
}

void ListaObjetos::configurarTabla()
{
    // Configurar columnas
    if (mostrarSoloMisObjetos) {
        ui->tableWidgetObjetos->setColumnCount(4);
        QStringList headers;
        headers << "Nombre" << "Categoría" << "Descripción" << "Tiempo Préstamo (días)";
        ui->tableWidgetObjetos->setHorizontalHeaderLabels(headers);
    } else {
        ui->tableWidgetObjetos->setColumnCount(5);
        QStringList headers;
        headers << "Nombre" << "Categoría" << "Descripción" << "Tiempo Préstamo (días)" << "Acción";
        ui->tableWidgetObjetos->setHorizontalHeaderLabels(headers);
    }
    
    // Ajustar tamaño de columnas
    ui->tableWidgetObjetos->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetObjetos->setAlternatingRowColors(true);
    ui->tableWidgetObjetos->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Solo lectura
    ui->tableWidgetObjetos->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ListaObjetos::cargarObjetos(){
    // Limpiar tabla
    ui->tableWidgetObjetos->setRowCount(0);

    // Obtener objetos de la base de datos
    QList<Objeto> objetos;
    if (!db->obtenerObjetos(objetos)) {
        qDebug() << "Error al obtener objetos";
        return;
    }
    
    // Filtrar objetos según el modo
    QList<Objeto> objetosFiltrados;
    for (const Objeto& objeto : objetos) {
        // Solo mostrar objetos disponibles (estado 0)
        if (objeto.getEstado() != 0) {
            continue; // Saltar objetos reservados o no disponibles
        }
        
        if (mostrarSoloMisObjetos) {
            // Mostrar solo objetos del usuario actual
            if (objeto.getIdDueno() == usuarioActualId) {
                objetosFiltrados.append(objeto);
            }
        } else {
            // Mostrar solo objetos que NO sean del usuario actual (catálogo)
            if (usuarioActualId == -1 || objeto.getIdDueno() != usuarioActualId) {
                objetosFiltrados.append(objeto);
            }
        }
    }
    
    ui->tableWidgetObjetos->setRowCount(objetosFiltrados.size());
    for (int i = 0; i < objetosFiltrados.size(); ++i) {
        const Objeto& objeto = objetosFiltrados[i];
        ui->tableWidgetObjetos->setItem(i, 0, new QTableWidgetItem(objeto.getNombre()));
        ui->tableWidgetObjetos->setItem(i, 1, new QTableWidgetItem(objeto.getCategoria()));
        ui->tableWidgetObjetos->setItem(i, 2, new QTableWidgetItem(objeto.getDescripcion()));
        ui->tableWidgetObjetos->setItem(i, 3, new QTableWidgetItem(QString::number(objeto.getTiempoPrestamo())));
        
        // Agregar botón de reserva solo en el catálogo
        if (!mostrarSoloMisObjetos) {
            QPushButton* botonReserva = crearBotonReserva(objeto.getId(), objeto.getTiempoPrestamo());
            ui->tableWidgetObjetos->setCellWidget(i, 4, botonReserva);
        }
    }
}

void ListaObjetos::on_pushButtonActualizar_clicked()
{
    cargarObjetos();
}

QPushButton* ListaObjetos::crearBotonReserva(int objetoId, int tiempoPrestamo)
{
    QPushButton* boton = new QPushButton("Reservar");
    boton->setMinimumSize(80, 25);
    boton->setMaximumSize(80, 25);
    boton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border: none; border-radius: 3px; }"
                         "QPushButton:hover { background-color: #45a049; }"
                         "QPushButton:pressed { background-color: #3d8b40; }");
    
    // Conectar el botón con el slot, pasando el ID del objeto y tiempo de préstamo
    connect(boton, &QPushButton::clicked, [this, objetoId, tiempoPrestamo]() {
        // Crear una reserva en la base de datos
        if (db->crearReserva(objetoId, usuarioActualId, tiempoPrestamo)) {
            QMessageBox::information(this, "Éxito", 
                QString("Objeto reservado correctamente por %1 días").arg(tiempoPrestamo));
            // Recargar la tabla para quitar el objeto reservado
            cargarObjetos();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo reservar el objeto");
        }
    });
    
    return boton;
}

void ListaObjetos::reservarObjeto()
{
    // Este método puede ser usado para futuras funcionalidades
    // Por ahora, la lógica está en el lambda del botón
}
