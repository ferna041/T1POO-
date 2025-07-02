#ifndef TOPIC_H
#define TOPIC_H

#include <QString>
#include <QList>

class Subscriber;

class Topic {
public:
    Topic(const QString& name);
    QString getName() const;
    void addSubscriber(Subscriber* subscriber);
    void removeSubscriber(Subscriber* subscriber);
    void notifySubscribers(const QString& message);

private:
    QString name;
    QList<Subscriber*> subscribers;
};

#endif
