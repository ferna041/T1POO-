#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "component.h"

class Subscriber : public Component {
public:
    Subscriber(const QString& name, Topic* topic);
    virtual ~Subscriber();
    
    virtual void update(const QString& message) = 0;

private:
    void subscribeToTopic();
    void unsubscribeFromTopic();
};

#endif
