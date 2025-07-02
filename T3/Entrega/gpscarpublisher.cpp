#include "gpscarpublisher.h"
#include "broker.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>

GPSCarPublisher::GPSCarPublisher(QObject* parent)
    : QObject(parent), Publisher("GPSCarPublisher", Broker::getInstance().getTopic("gps"))
    , timer(nullptr), currentTime(0), maxTime(0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GPSCarPublisher::publishCurrentPosition);
    timer->setInterval(1000); // 1 segundo
}

bool GPSCarPublisher::loadPositionFile(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: No se pudo abrir el archivo" << fileName;
        return false;
    }
    
    positions.clear();
    QTextStream in(&file);
    
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("#")) {
            continue; // Ignorar líneas vacías y comentarios
        }
        
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() >= 3) {
            bool timeOk, xOk, yOk;
            double time = parts[0].toDouble(&timeOk);
            double x = parts[1].toDouble(&xOk);
            double y = parts[2].toDouble(&yOk);
            
            if (timeOk && xOk && yOk) {
                positions.append(GPSPosition(time, x, y));
                if (time > maxTime) {
                    maxTime = static_cast<int>(time);
                }
            }
        }
    }
    
    file.close();
    
    if (positions.isEmpty()) {
        qDebug() << "Error: No se encontraron posiciones válidas en el archivo";
        return false;
    }
    
    // Ordenar por tiempo (por si acaso)
    std::sort(positions.begin(), positions.end(), 
              [](const GPSPosition& a, const GPSPosition& b) {
                  return a.time < b.time;
              });
    
    qDebug() << "Cargadas" << positions.size() << "posiciones GPS desde" << fileName;
    qDebug() << "Tiempo máximo:" << maxTime << "segundos";
    
    return true;
}

void GPSCarPublisher::startSimulation() {
    if (positions.isEmpty()) {
        qDebug() << "Error: No hay posiciones cargadas";
        return;
    }
    
    currentTime = 0;
    timer->start();
    qDebug() << "Simulación GPS iniciada";
}

void GPSCarPublisher::stopSimulation() {
    if (timer) {
        timer->stop();
        qDebug() << "Simulación GPS detenida";
    }
}

void GPSCarPublisher::publishCurrentPosition() {
    if (currentTime > maxTime) {
        stopSimulation();
        qDebug() << "Simulación GPS completada";
        return;
    }
    
    QPair<double, double> pos = interpolatePosition(currentTime);
    QString message = formatPositionMessage(currentTime, pos.first, pos.second);
    
    publish(message);
    qDebug() << "Posición publicada:" << message;
    
    currentTime++;
}

QPair<double, double> GPSCarPublisher::interpolatePosition(double time) {
    // Buscar los dos puntos entre los cuales interpolar
    for (int i = 0; i < positions.size() - 1; i++) {
        const GPSPosition& p1 = positions[i];
        const GPSPosition& p2 = positions[i + 1];
        
        if (time >= p1.time && time <= p2.time) {
            // Interpolación lineal
            if (p2.time == p1.time) {
                return QPair<double, double>(p1.x, p1.y);
            }
            
            double factor = (time - p1.time) / (p2.time - p1.time);
            double x = p1.x + factor * (p2.x - p1.x);
            double y = p1.y + factor * (p2.y - p1.y);
            
            return QPair<double, double>(x, y);
        }
    }
    
    // Si está fuera de rango, devolver la primera o última posición
    if (time < positions.first().time) {
        return QPair<double, double>(positions.first().x, positions.first().y);
    } else {
        return QPair<double, double>(positions.last().x, positions.last().y);
    }
}

QString GPSCarPublisher::formatPositionMessage(double time, double x, double y) {
    return QString("Tiempo: %1s, X: %2, Y: %3")
           .arg(time, 0, 'f', 0)
           .arg(x, 0, 'f', 2)
           .arg(y, 0, 'f', 2);
}
