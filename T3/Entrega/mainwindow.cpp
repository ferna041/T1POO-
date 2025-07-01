#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Crear instancias del patrón publicador-suscriptor
    videoPublisher = new VideoPublisher(this);
    videoFollower = new VideoFollower(this);
    
    // Conectar señales
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onUrlEntered);
    connect(videoFollower, &VideoFollower::urlUpdated, this, &MainWindow::onUrlUpdated);
    
    // Configuración inicial de la interfaz
    setWindowTitle("Simulador Patrón Publicador-Suscriptor - Etapa 1");
    ui->videoButton->setEnabled(false);
    ui->videoButton->setText("Esperando URL...");
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

void MainWindow::onUrlUpdated(const QString& url)
{
    // Actualizar el texto del botón con la URL publicada
    QString displayText = url.length() > 30 ? url.left(30) + "..." : url;
    ui->videoButton->setText(QString("URL: %1").arg(displayText));
    ui->videoButton->setEnabled(true);
}
