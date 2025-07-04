#include "ListaObjetos.h"
#include "ui_ListaObjetos.h"
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QHBoxLayout>

ListaObjetos::ListaObjetos(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListaObjetos)
    , usuarioActualId(-1)
    , mostrarSoloMisObjetos(false)
{
    ui->setupUi(this);
    setWindowTitle("Lista de Objetos");
    ui->labelTitulo->setText("Catálogo de Objetos");
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
        ui->labelTitulo->setText("Mis Objetos");
    } else {
        setWindowTitle("Catálogo de Objetos");
        ui->labelTitulo->setText("Catálogo de Objetos");
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
        
        // Configurar anchos mínimos para "Mis Objetos" - Se estiran proporcionalmente
        ui->tableWidgetObjetos->setColumnWidth(0, 180);  // Nombre (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(1, 140);  // Categoría (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(2, 300);  // Descripción (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(3, 150);  // Tiempo Préstamo (mínimo)
    } else {
        ui->tableWidgetObjetos->setColumnCount(5);
        QStringList headers;
        headers << "Nombre" << "Categoría" << "Descripción" << "Tiempo Préstamo (días)" << "Acción";
        ui->tableWidgetObjetos->setHorizontalHeaderLabels(headers);
        
        // Configurar anchos mínimos para "Catálogo" - Se estiran proporcionalmente
        ui->tableWidgetObjetos->setColumnWidth(0, 160);  // Nombre (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(1, 130);  // Categoría (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(2, 280);  // Descripción (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(3, 200);  // Tiempo Préstamo (mínimo)
        ui->tableWidgetObjetos->setColumnWidth(4, 120);  // Acción (mínimo, más ancho para el botón)
    }
    
    // Configurar altura de filas - Altura aumentada para botones más cómodos
    ui->tableWidgetObjetos->verticalHeader()->setDefaultSectionSize(50);
    
    // Configurar header vertical (números de fila) - Ocultar completamente
    ui->tableWidgetObjetos->verticalHeader()->setVisible(false);
    
    // Configurar columnas para usar todo el ancho disponible
    ui->tableWidgetObjetos->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetObjetos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetObjetos->setAlternatingRowColors(true);
    ui->tableWidgetObjetos->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    // Solo lectura
    ui->tableWidgetObjetos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Permitir que el usuario ajuste las columnas manualmente
    ui->tableWidgetObjetos->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
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
            // Crear widget contenedor para centrar el botón
            QWidget *contenedor = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(contenedor);
            
            QPushButton *btnReservar = new QPushButton("Reservar");
            btnReservar->setProperty("idObjeto", objeto.getId());
            btnReservar->setProperty("tiempoPrestamo", objeto.getTiempoPrestamo());
            btnReservar->setFixedSize(80, 30);
            btnReservar->setStyleSheet(
                "QPushButton { "
                "   background-color: #27ae60; "
                "   color: white; "
                "   border: none; "
                "   border-radius: 4px; "
                "   font-weight: bold; "
                "   font-size: 12px; "
                "} "
                "QPushButton:hover { "
                "   background-color: #229954; "
                "} "
                "QPushButton:pressed { "
                "   background-color: #1e8449; "
                "}"
            );
            connect(btnReservar, &QPushButton::clicked, this, &ListaObjetos::reservarObjeto);
            
            // Configurar layout para centrar el botón
            layout->addWidget(btnReservar);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(5, 5, 5, 5);
            
            ui->tableWidgetObjetos->setCellWidget(i, 4, contenedor);
        }
        
        // Establecer altura de fila para que los botones se vean proporcionados
        ui->tableWidgetObjetos->setRowHeight(i, 50);
    }
}

void ListaObjetos::on_pushButtonActualizar_clicked()
{
    cargarObjetos();
}

void ListaObjetos::reservarObjeto()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    
    int idObjeto = btn->property("idObjeto").toInt();
    int tiempoPrestamo = btn->property("tiempoPrestamo").toInt();
    
    // Crear una reserva en la base de datos
    if (db->crearReserva(idObjeto, usuarioActualId, tiempoPrestamo)) {
        QMessageBox::information(this, "Éxito", 
            QString("Objeto reservado correctamente por %1 días").arg(tiempoPrestamo));
        // Recargar la tabla para quitar el objeto reservado
        cargarObjetos();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo reservar el objeto");
    }
}
