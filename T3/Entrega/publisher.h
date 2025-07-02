#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "component.h"

class Publisher : public Component {
public:
    Publisher(const QString& name, Topic* topic);
    virtual ~Publisher() = default;
    
    virtual void publish(const QString& message);

protected:
    void notifySubscribers(const QString& message);
};

#endif
