#include "videopublisher.h"
#include "broker.h"

VideoPublisher::VideoPublisher(QObject* parent)
    : QObject(parent), Publisher("VideoPublisher", Broker::getInstance().getTopic("video"))
{
}

void VideoPublisher::publishUrl(const QString& url) {
    if (!url.isEmpty()) {
        publish(url);
    }
}
