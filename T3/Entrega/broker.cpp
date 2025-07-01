#include "broker.h"

Broker& Broker::getInstance() {
    static Broker instance;
    return instance;
}

Topic* Broker::getTopic(const QString& topicName) {
    auto it = topics.find(topicName);
    if (it != topics.end()) {
        return it->second;
    }
    
    // Crear el tópico si no existe
    Topic* newTopic = new Topic(topicName);
    topics[topicName] = newTopic;
    return newTopic;
}

void Broker::createTopic(const QString& topicName) {
    if (topics.find(topicName) == topics.end()) {
        topics[topicName] = new Topic(topicName);
    }
}

Broker::~Broker() {
    for (auto& pair : topics) {
        delete pair.second;
    }
    topics.clear();
}
