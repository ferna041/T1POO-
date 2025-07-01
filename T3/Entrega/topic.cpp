#include "topic.h"
#include "subscriber.h"
#include <algorithm>

Topic::Topic(const QString& name) : name(name) {}

QString Topic::getName() const {
    return name;
}

void Topic::addSubscriber(Subscriber* subscriber) {
    if (subscriber && std::find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
        subscribers.push_back(subscriber);
    }
}

void Topic::removeSubscriber(Subscriber* subscriber) {
    auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
    if (it != subscribers.end()) {
        subscribers.erase(it);
    }
}

void Topic::notifySubscribers(const QString& message) {
    for (Subscriber* subscriber : subscribers) {
        if (subscriber) {
            subscriber->update(message);
        }
    }
}
