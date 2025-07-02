#include "component.h"

Component::Component(const QString& name, Topic* topic)
    : name(name), topic(topic) {}

QString Component::getName() const {
    return name;
}

Topic* Component::getTopic() const {
    return topic;
}
