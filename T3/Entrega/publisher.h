#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "component.h"
#include <QString>

class Publisher : public Component {
public:
    Publisher(const QString& name, Topic* topic);
    virtual ~Publisher() = default;
    void publish(const QString& message);
};

#endif
