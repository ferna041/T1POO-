#include "subscriber.h"

Subscriber::Subscriber(const QString& name, Topic* topic)
    : Component(name, topic) {
    if (topic) {
        topic->addSubscriber(this);
    }
}
