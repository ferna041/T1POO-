#include "topic.h"
#include "subscriber.h"

Topic::Topic(const QString& name) : name(name) {}

QString Topic::getName() const {
    return name;
}

void Topic::addSubscriber(Subscriber* subscriber) {
    if (!subscribers.contains(subscriber)) {
        subscribers.append(subscriber);
    }
}

void Topic::removeSubscriber(Subscriber* subscriber) {
    subscribers.removeOne(subscriber);
}

void Topic::notifySubscribers(const QString& message) {
    for (Subscriber* subscriber : subscribers) {
        subscriber->update(message);
    }
}
