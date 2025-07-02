#include "videopublisher.h"
#include "broker.h"
#include "publisher.h"

VideoPublisher::VideoPublisher(QObject* parent)
    : QObject(parent) {
    publisher = new Publisher("VideoPublisher", Broker::getInstance().getTopic("video"));
}

VideoPublisher::~VideoPublisher()
{
    delete publisher;
}

void VideoPublisher::publishUrl(const QString& url) {
    if (!url.isEmpty()) {
        publisher->publish(url);
    }
}
