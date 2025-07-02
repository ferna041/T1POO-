#ifndef GPSCARFOLLOWER_H
#define GPSCARFOLLOWER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>

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
    double currentX;
    double currentY;
    QString currentInfo;
    Subscriber* subscriber;
};

class TrackingWidget : public QWidget {
    Q_OBJECT
public:
    TrackingWidget(QWidget* parent = nullptr);
    void updatePosition(double x, double y);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    double carX;
    double carY;
    static const int WINDOW_WIDTH = 600;
    static const int WINDOW_HEIGHT = 500;
    static const int CAR_SIZE = 10;
};

#endif
