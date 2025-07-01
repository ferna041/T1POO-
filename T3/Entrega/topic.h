#ifndef TOPIC_H
#define TOPIC_H

#include <QString>
#include <vector>

class Subscriber;

class Topic {
public:
    Topic(const QString& name);
    ~Topic() = default;
    
    QString getName() const;
    void addSubscriber(Subscriber* subscriber);
    void removeSubscriber(Subscriber* subscriber);
    void notifySubscribers(const QString& message);

private:
    QString name;
    std::vector<Subscriber*> subscribers;
};

#endif
