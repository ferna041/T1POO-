#ifndef GPSCARPUBLISHER_H
#define GPSCARPUBLISHER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QVector>

class Publisher;

struct Position {
    int time;
    double x;
    double y;
};

class GPSCarPublisher : public QObject {
    Q_OBJECT
public:
    GPSCarPublisher(QObject* parent = nullptr);
    ~GPSCarPublisher();
    
    bool loadPositionFile(const QString& filename);
    void startSimulation();
    void stopSimulation();

private slots:
    void updatePosition();

private:
    Position interpolatePosition(int currentTime);
    
    QTimer* timer;
    QVector<Position> positions;
    int currentTimeIndex;
    int simulationTime;
    bool isRunning;
    Publisher* publisher;
};

#endif
