#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include "topic.h"

class Component {
public:
    Component(const QString& name, Topic* topic);
    virtual ~Component() = default;
    QString getName() const;
    Topic* getTopic() const;

protected:
    QString name;
    Topic* topic;
};

#endif
