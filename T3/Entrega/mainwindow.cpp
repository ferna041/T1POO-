#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentAudioOutput(nullptr)
{
    ui->setupUi(this);
    
    // Crear instancias del patrón publicador-suscriptor
    videoPublisher = new VideoPublisher(this);
    videoFollower = new VideoFollower(this);
    
    // Conectar señales básicas
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onUrlEntered);
    connect(ui->videoButton, &QPushButton::clicked, this, &MainWindow::onVideoButtonClicked);
    connect(videoFollower, &VideoFollower::urlUpdated, this, &MainWindow::onUrlUpdated);
    
    // Conectar señal de audio output creado
    connect(videoFollower, &VideoFollower::audioOutputCreated, [this](QAudioOutput* audioOutput) {
        currentAudioOutput = audioOutput;
    });
    
    // Conectar slider de volumen
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);
    
    // Configuración inicial de la interfaz
    setWindowTitle("Simulador Patrón Publicador-Suscriptor - Etapa 2 (Con Reproductor)");
    ui->videoButton->setEnabled(false);
    ui->videoButton->setText("Esperando URL...");
    
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
    // Actualizar el texto del botón con la URL publicada
    QString displayText = url.length() > 40 ? url.left(40) + "..." : url;
    ui->videoButton->setText(QString("Reproducir: %1").arg(displayText));
    ui->videoButton->setEnabled(true);
}

void MainWindow::onVolumeChanged(int value)
{
    double volume = value / 100.0;
    
    // Actualizar el label de volumen
    ui->volumeLabel->setText(QString("Volumen: %1%").arg(value));
    
    // Aplicar volumen al VideoFollower
    videoFollower->setVolume(volume);
    
    // Si hay un audio output activo, aplicar el volumen inmediatamente
    if (currentAudioOutput) {
        currentAudioOutput->setVolume(volume);
    }
}
