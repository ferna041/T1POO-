#ifndef BROKER_H
#define BROKER_H

#include <QMap>
#include <QString>
#include "topic.h"

class Broker {
public:
    static Broker& getInstance();
    Topic* getTopic(const QString& name);
    void addTopic(Topic* topic);
    void removeTopic(const QString& name);

private:
    Broker() = default;
    QMap<QString, Topic*> topics;
};

#endif
