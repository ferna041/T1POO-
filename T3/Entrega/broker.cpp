#include "broker.h"

Broker& Broker::getInstance() {
    static Broker instance;
    return instance;
}

Topic* Broker::getTopic(const QString& name) {
    if (!topics.contains(name)) {
        topics[name] = new Topic(name);
    }
    return topics[name];
}

void Broker::addTopic(Topic* topic) {
    if (topic) {
        topics[topic->getName()] = topic;
    }
}

void Broker::removeTopic(const QString& name) {
    if (topics.contains(name)) {
        delete topics[name];
        topics.remove(name);
    }
}
