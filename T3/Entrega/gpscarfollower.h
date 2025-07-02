#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>

class Subscriber;

class GPSCarFollower : public QObject {
    Q_OBJECT
public:
    GPSCarFollower(QObject* parent = nullptr);
    ~GPSCarFollower();
    void showTrackingWindow();
    void onMessageReceived(const QString& message);

signals:
    void positionUpdated(const QString& info, double x, double y);

private slots:
    void onPositionUpdated(const QString& info, double x, double y);

private:
    QWidget* trackingWindow;
    QLabel* infoLabel;
    QLabel* positionLabel;
    double currentX;
    double currentY;
    QString currentInfo;
    Subscriber* subscriber;
    
    void parsePositionMessage(const QString& message, QString& info, double& x, double& y);
};

#endif
