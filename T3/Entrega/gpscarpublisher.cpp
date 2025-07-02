#include "gpscarpublisher.h"
#include "broker.h"
#include "publisher.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>

GPSCarPublisher::GPSCarPublisher(QObject* parent)
    : QObject(parent), currentTimeIndex(0), simulationTime(0), isRunning(false)
{
    publisher = new Publisher("GPSCarPublisher", Broker::getInstance().getTopic("GPS"));
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GPSCarPublisher::updatePosition);
}

GPSCarPublisher::~GPSCarPublisher()
{
    delete publisher;
}

bool GPSCarPublisher::loadPositionFile(const QString& filename)
{
    if (filename.isEmpty()) return false;
    
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    
    positions.clear();
    QTextStream in(&file);
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() >= 3) {
            Position pos;
            pos.time = parts[0].toInt();
            pos.x = parts[1].toDouble();
            pos.y = parts[2].toDouble();
            positions.append(pos);
        }
    }
    
    file.close();
    return !positions.isEmpty();
}

void GPSCarPublisher::startSimulation()
{
    if (positions.isEmpty()) return;
    
    currentTimeIndex = 0;
    simulationTime = positions.first().time;
    isRunning = true;
    timer->start(1000);
}

void GPSCarPublisher::stopSimulation()
{
    timer->stop();
    isRunning = false;
}

void GPSCarPublisher::updatePosition()
{
    if (positions.isEmpty() || !isRunning) return;
    
    Position currentPos = interpolatePosition(simulationTime);
    
    QString message = QString("Tiempo: %1, X: %2, Y: %3")
                     .arg(simulationTime)
                     .arg(currentPos.x, 0, 'f', 2)
                     .arg(currentPos.y, 0, 'f', 2);
    
    publisher->publish(message);
    
    simulationTime++;
    
    if (simulationTime > positions.last().time) {
        stopSimulation();
    }
}

Position GPSCarPublisher::interpolatePosition(int currentTime)
{
    if (positions.isEmpty()) return {0, 0.0, 0.0};
    
    int i = 0;
    while (i < positions.size() - 1 && positions[i + 1].time <= currentTime) {
        i++;
    }
    
    if (i >= positions.size() - 1) {
        return positions.last();
    }
    
    if (currentTime <= positions[i].time) {
        return positions[i];
    }
    
    Position p1 = positions[i];
    Position p2 = positions[i + 1];
    
    double factor = double(currentTime - p1.time) / (p2.time - p1.time);
    
    Position result;
    result.time = currentTime;
    result.x = p1.x + factor * (p2.x - p1.x);
    result.y = p1.y + factor * (p2.y - p1.y);
    
    return result;
}
