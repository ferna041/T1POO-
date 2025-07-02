#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentAudioOutput(nullptr)
{
    ui->setupUi(this);
    
    // Crear instancias del patrón publicador-suscriptor
    videoPublisher = new VideoPublisher(this);
    videoFollower = new VideoFollower(this);
    gpsPublisher = new GPSCarPublisher(this);
    gpsFollower = new GPSCarFollower(this);
    
    // Conectar señales de video
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onUrlEntered);
    connect(ui->videoButton, &QPushButton::clicked, this, &MainWindow::onVideoButtonClicked);
    connect(videoFollower, &VideoFollower::urlUpdated, this, &MainWindow::onUrlUpdated);
    connect(videoFollower, &VideoFollower::audioOutputCreated, [this](QAudioOutput* audioOutput) {
        currentAudioOutput = audioOutput;
    });
    
    // Conectar señales de GPS
    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(ui->startSimButton, &QPushButton::clicked, this, &MainWindow::onStartSimulationClicked);
    connect(ui->stopSimButton, &QPushButton::clicked, this, &MainWindow::onStopSimulationClicked);
    connect(ui->showTrackingButton, &QPushButton::clicked, this, &MainWindow::onShowTrackingClicked);
    connect(gpsFollower, &GPSCarFollower::positionUpdated, this, &MainWindow::onGPSPositionUpdated);
    
    // Conectar slider de volumen
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    
    // Configuración inicial de la interfaz
    setWindowTitle("Simulador Patrón Publicador-Suscriptor - Etapa 3 (GPS sin Gráficos)");
    ui->videoButton->setEnabled(false);
    ui->videoButton->setText("Esperando URL...");
    
    // Configurar botones GPS
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(false);
    ui->showTrackingButton->setEnabled(true);
    
    // Configurar volumen inicial
    onVolumeChanged(80); // 80% de volumen inicial
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUrlEntered()
{
    QString url = ui->urlLineEdit->text().trimmed();
    if (!url.isEmpty()) {
        videoPublisher->publishUrl(url);
        ui->urlLineEdit->clear();
    }
}

void MainWindow::onVideoButtonClicked()
{
    videoFollower->playVideo();
}

void MainWindow::onUrlUpdated(const QString& url)
{
    QString displayText = url.length() > 40 ? url.left(40) + "..." : url;
    ui->videoButton->setText(QString("Reproducir: %1").arg(displayText));
    ui->videoButton->setEnabled(true);
}

void MainWindow::onVolumeChanged(int value)
{
    double volume = value / 100.0;
    ui->volumeValueLabel->setText(QString("Volumen: %1%").arg(value));
    
    videoFollower->setVolume(volume);
    
    if (currentAudioOutput) {
        currentAudioOutput->setVolume(volume);
    }
}

void MainWindow::onLoadFileClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Seleccionar archivo de posiciones GPS",
        "",
        "Archivos de texto (*.txt);;Todos los archivos (*)"
    );
    
    if (!fileName.isEmpty()) {
        if (gpsPublisher->loadPositionFile(fileName)) {
            currentGPSFile = fileName;
            QFileInfo fileInfo(fileName);
            ui->fileStatusLabel->setText(QString("Archivo cargado: %1").arg(fileInfo.fileName()));
            ui->fileStatusLabel->setStyleSheet("color: green; font-style: normal;");
            ui->startSimButton->setEnabled(true);
        } else {
            ui->fileStatusLabel->setText("Error al cargar el archivo");
            ui->fileStatusLabel->setStyleSheet("color: red; font-style: italic;");
            ui->startSimButton->setEnabled(false);
        }
    }
}

void MainWindow::onStartSimulationClicked()
{
    gpsPublisher->startSimulation();
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(true);
    ui->loadFileButton->setEnabled(false);
    ui->gpsStatusLabel->setText("Simulación en progreso...");
    ui->gpsStatusLabel->setStyleSheet("color: blue; font-weight: bold;");
}

void MainWindow::onStopSimulationClicked()
{
    gpsPublisher->stopSimulation();
    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    ui->loadFileButton->setEnabled(true);
    ui->gpsStatusLabel->setText("Simulación detenida");
    ui->gpsStatusLabel->setStyleSheet("color: orange; font-style: italic;");
}

void MainWindow::onShowTrackingClicked()
{
    gpsFollower->showTrackingWindow();
}

void MainWindow::onGPSPositionUpdated(const QString& info, double x, double y)
{
    ui->lastPositionLabel->setText(QString("Última posición: X=%1, Y=%2")
                                  .arg(x, 0, 'f', 2)
                                  .arg(y, 0, 'f', 2));
}
