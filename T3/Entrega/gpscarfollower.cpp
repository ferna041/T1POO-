#include "gpscarfollower.h"
#include "broker.h"
#include "subscriber.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QRegularExpression>

class GPSSubscriber : public Subscriber {
public:
    GPSSubscriber(GPSCarFollower* follower) 
        : Subscriber("GPSCarFollower", Broker::getInstance().getTopic("GPS"))
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
    : QObject(parent), currentX(0), currentY(0)
{
    trackingWindow = nullptr;
    subscriber = new GPSSubscriber(this);
    connect(this, &GPSCarFollower::positionUpdated, this, &GPSCarFollower::onPositionUpdated);
}

GPSCarFollower::~GPSCarFollower()
{
    delete subscriber;
}

void GPSCarFollower::onMessageReceived(const QString& message)
{
    QRegularExpression regex(R"(Tiempo:\s*(\d+),\s*X:\s*([\d.-]+),\s*Y:\s*([\d.-]+))");
    QRegularExpressionMatch match = regex.match(message);
    
    if (match.hasMatch()) {
        currentX = match.captured(2).toDouble();
        currentY = match.captured(3).toDouble();
        currentInfo = message;
        
        emit positionUpdated(currentInfo, currentX, currentY);
    }
}

void GPSCarFollower::showTrackingWindow()
{
    if (!trackingWindow) {
        trackingWindow = new QWidget();
        trackingWindow->setWindowTitle("Seguidor de Posición del Móvil");
        trackingWindow->resize(600, 550);
        
        QVBoxLayout* layout = new QVBoxLayout(trackingWindow);
        
        TrackingWidget* trackingWidget = new TrackingWidget();
        layout->addWidget(trackingWidget);
        
        infoLabel = new QLabel("Esperando datos GPS...");
        infoLabel->setAlignment(Qt::AlignCenter);
        infoLabel->setStyleSheet("padding: 10px; background-color: #f0f0f0; border: 1px solid #ccc;");
        layout->addWidget(infoLabel);
        
        connect(this, &GPSCarFollower::positionUpdated, 
                [trackingWidget](const QString&, double x, double y) {
                    trackingWidget->updatePosition(x, y);
                });
    }
    
    trackingWindow->show();
    trackingWindow->raise();
}

void GPSCarFollower::onPositionUpdated(const QString& info, double x, double y)
{
    if (infoLabel) {
        infoLabel->setText(info);
    }
}

TrackingWidget::TrackingWidget(QWidget* parent)
    : QWidget(parent), carX(200), carY(150)
{
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid #ccc;");
}

void TrackingWidget::updatePosition(double x, double y)
{
    double scaleX = 2.0;
    double scaleY = 2.0;
    
    carX = WINDOW_WIDTH / 2 + (x * scaleX);
    carY = WINDOW_HEIGHT / 2 - (y * scaleY);
    
    carX = qBound(CAR_SIZE/2.0, carX, WINDOW_WIDTH - CAR_SIZE/2.0);
    carY = qBound(CAR_SIZE/2.0, carY, WINDOW_HEIGHT - CAR_SIZE/2.0);
    
    update(); 
}

void TrackingWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    for (int i = 0; i < WINDOW_WIDTH; i += 20) {
        painter.drawLine(i, 0, i, WINDOW_HEIGHT);
    }
    for (int i = 0; i < WINDOW_HEIGHT; i += 20) {
        painter.drawLine(0, i, WINDOW_WIDTH, i);
    }
    
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(QPointF(carX, carY), CAR_SIZE, CAR_SIZE);
    
    painter.setPen(QPen(Qt::blue, 1));
    painter.drawLine(WINDOW_WIDTH/2 - 10, WINDOW_HEIGHT/2, WINDOW_WIDTH/2 + 10, WINDOW_HEIGHT/2);
    painter.drawLine(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 10, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 10);
}
