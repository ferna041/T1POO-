#ifndef BROKER_H
#define BROKER_H

#include <QString>
#include <map>
#include "topic.h"

class Broker {
public:
    static Broker& getInstance();
    
    Topic* getTopic(const QString& topicName);
    void createTopic(const QString& topicName);

private:
    Broker() = default;
    ~Broker();
    Broker(const Broker&) = delete;
    Broker& operator=(const Broker&) = delete;
    
    std::map<QString, Topic*> topics;
};

#endif
