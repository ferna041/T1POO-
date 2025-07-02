#include "gpscarfollower.h"
#include "broker.h"
#include "subscriber.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QDebug>
#include <QRegularExpression>

class GPSSubscriber : public Subscriber {
public:
    GPSSubscriber(GPSCarFollower* follower) 
        : Subscriber("GPSCarFollower", Broker::getInstance().getTopic("gps"))
        , follower(follower) {}
    
    void update(const QString& message) override {
        if (follower) {
            follower->onMessageReceived(message);
        }
    }
    
private:
    GPSCarFollower* follower;
};

GPSCarFollower::GPSCarFollower(QObject* parent)
    : QObject(parent), trackingWindow(nullptr), currentX(0), currentY(0)
{
    subscriber = new GPSSubscriber(this);
    
    // Conectar señal interna para actualización
    connect(this, &GPSCarFollower::positionUpdated, this, &GPSCarFollower::onPositionUpdated);
}

GPSCarFollower::~GPSCarFollower()
{
    delete subscriber;
    if (trackingWindow) {
        trackingWindow->deleteLater();
    }
}

void GPSCarFollower::showTrackingWindow()
{
    if (!trackingWindow) {
        trackingWindow = new QWidget;
        trackingWindow->setWindowTitle("Seguimiento de Posición GPS");
        trackingWindow->resize(400, 200);
        
        QVBoxLayout* layout = new QVBoxLayout(trackingWindow);
        
        // Información principal
        infoLabel = new QLabel("Esperando datos GPS...");
        QFont infoFont = infoLabel->font();
        infoFont.setPointSize(12);
        infoLabel->setFont(infoFont);
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setStyleSheet("background-color: #f0f0f0; padding: 20px; border: 1px solid #ccc; margin: 10px;");
        layout->addWidget(infoLabel);
        
        // Posición detallada
        positionLabel = new QLabel("Coordenadas: X = 0.00, Y = 0.00");
        QFont posFont = positionLabel->font();
        posFont.setPointSize(11);
        posFont.setBold(true);
        positionLabel->setFont(posFont);
        positionLabel->setAlignment(Qt::AlignCenter);
        positionLabel->setStyleSheet("background-color: #e8f4f8; padding: 15px; border: 1px solid #b0d4e3; margin: 10px;");
        layout->addWidget(positionLabel);
    }
    
    trackingWindow->show();
    trackingWindow->raise();
    trackingWindow->activateWindow();
}

void GPSCarFollower::onMessageReceived(const QString& message) {
    QString info;
    double x, y;
    parsePositionMessage(message, info, x, y);
    
    currentInfo = info;
    currentX = x;
    currentY = y;
    
    emit positionUpdated(info, x, y);
}

void GPSCarFollower::onPositionUpdated(const QString& info, double x, double y) {
    if (trackingWindow && infoLabel && positionLabel) {
        infoLabel->setText(info);
        positionLabel->setText(QString("Coordenadas: X = %1, Y = %2")
                              .arg(x, 0, 'f', 2)
                              .arg(y, 0, 'f', 2));
    }
}

void GPSCarFollower::parsePositionMessage(const QString& message, QString& info, double& x, double& y) {
    // Parsear mensaje en formato: "Tiempo: Xs, X: xx.xx, Y: yy.yy"
    info = message;
    x = 0.0;
    y = 0.0;
    
    QRegularExpression regexX("X: ([\\d.-]+)");
    QRegularExpression regexY("Y: ([\\d.-]+)");
    
    QRegularExpressionMatch matchX = regexX.match(message);
    QRegularExpressionMatch matchY = regexY.match(message);
    
    if (matchX.hasMatch()) {
        x = matchX.captured(1).toDouble();
    }
    
    if (matchY.hasMatch()) {
        y = matchY.captured(1).toDouble();
    }
}
