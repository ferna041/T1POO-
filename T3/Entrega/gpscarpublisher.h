#ifndef GPSCARPUBLISHER_H
#define GPSCARPUBLISHER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QVector>
#include "publisher.h"

struct GPSPosition {
    double time;
    double x;
    double y;
    
    GPSPosition(double t, double posX, double posY) : time(t), x(posX), y(posY) {}
};

class GPSCarPublisher : public QObject, public Publisher {
    Q_OBJECT
    
public:
    GPSCarPublisher(QObject* parent = nullptr);
    ~GPSCarPublisher() = default;
    
    bool loadPositionFile(const QString& fileName);
    void startSimulation();
    void stopSimulation();
    bool isRunning() const { return timer && timer->isActive(); }

private slots:
    void publishCurrentPosition();

private:
    QTimer* timer;
    QVector<GPSPosition> positions;
    int currentTime;
    int maxTime;
    
    QPair<double, double> interpolatePosition(double time);
    QString formatPositionMessage(double time, double x, double y);
};

#endif
