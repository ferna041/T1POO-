#include "publisher.h"

Publisher::Publisher(const QString& name, Topic* topic) 
    : Component(name, topic) {}

void Publisher::publish(const QString& message) {
    notifySubscribers(message);
}

void Publisher::notifySubscribers(const QString& message) {
    if (topic) {
        topic->notifySubscribers(message);
    }
}
