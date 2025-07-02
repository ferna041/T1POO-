#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentAudioOutput(nullptr)
{
    ui->setupUi(this);
    
    videoPublisher = new VideoPublisher(this);
    videoFollower = new VideoFollower(this);
    gpsPublisher = new GPSCarPublisher(this);
    gpsFollower = new GPSCarFollower(this);
    
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onUrlEntered);
    connect(ui->videoButton, &QPushButton::clicked, this, &MainWindow::onVideoButtonClicked);
    connect(videoFollower, &VideoFollower::urlUpdated, this, &MainWindow::onUrlUpdated);
    connect(videoFollower, &VideoFollower::audioOutputCreated, [this](QAudioOutput* audioOutput) {
        currentAudioOutput = audioOutput;
    });
    
    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(ui->startSimButton, &QPushButton::clicked, this, &MainWindow::onStartSimulationClicked);
    connect(ui->stopSimButton, &QPushButton::clicked, this, &MainWindow::onStopSimulationClicked);
    connect(ui->showTrackingButton, &QPushButton::clicked, this, &MainWindow::onShowTrackingClicked);
    connect(gpsFollower, &GPSCarFollower::positionUpdated, this, &MainWindow::onGPSPositionUpdated);
    
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    
    setWindowTitle("Simulador Patrón Publicador-Suscriptor - Entrega Final");
    ui->videoButton->setEnabled(false);
    ui->videoButton->setText("Esperando URL...");
    
    onVolumeChanged(80);
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
    ui->videoButton->setText(QString("Reproducir: %1").arg(url.length() > 40 ? url.left(40) + "..." : url));
    ui->videoButton->setEnabled(true);
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
            QMessageBox::warning(this, "Error", "No se pudo cargar el archivo GPS.");
            ui->fileStatusLabel->setText("Error al cargar archivo");
            ui->fileStatusLabel->setStyleSheet("color: red; font-style: italic;");
        }
    }
}

void MainWindow::onStartSimulationClicked()
{
    gpsPublisher->startSimulation();
    ui->startSimButton->setEnabled(false);
    ui->stopSimButton->setEnabled(true);
    ui->loadFileButton->setEnabled(false);
}

void MainWindow::onStopSimulationClicked()
{
    gpsPublisher->stopSimulation();
    ui->startSimButton->setEnabled(true);
    ui->stopSimButton->setEnabled(false);
    ui->loadFileButton->setEnabled(true);
}

void MainWindow::onShowTrackingClicked()
{
    gpsFollower->showTrackingWindow();
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

void MainWindow::onGPSPositionUpdated(const QString& info, double x, double y)
{
    ui->gpsStatusLabel->setText("Estado: Recibiendo datos GPS");
    ui->positionInfoLabel->setText(info);
}
