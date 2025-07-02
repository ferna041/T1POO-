#include "subscriber.h"

Subscriber::Subscriber(const QString& name, Topic* topic) 
    : Component(name, topic) {
    subscribeToTopic();
}

Subscriber::~Subscriber() {
    unsubscribeFromTopic();
}

void Subscriber::subscribeToTopic() {
    if (topic) {
        topic->addSubscriber(this);
    }
}

void Subscriber::unsubscribeFromTopic() {
    if (topic) {
        topic->removeSubscriber(this);
    }
}
