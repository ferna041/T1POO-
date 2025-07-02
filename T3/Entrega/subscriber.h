#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "component.h"
#include <QString>

class Subscriber : public Component {
public:
    Subscriber(const QString& name, Topic* topic);
    virtual ~Subscriber() = default;
    virtual void update(const QString& message) = 0;
};

#endif
