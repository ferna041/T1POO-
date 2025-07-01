#include "videofollower.h"
#include "broker.h"
#include "subscriber.h"

class VideoSubscriber : public Subscriber {
public:
    VideoSubscriber(VideoFollower* follower) 
        : Subscriber("VideoFollower", Broker::getInstance().getTopic("video"))
        , follower(follower) {}
    
    void update(const QString& message) override {
        if (follower) {
            follower->onMessageReceived(message);
        }
    }
    
private:
    VideoFollower* follower;
};

VideoFollower::VideoFollower(QObject* parent)
    : QObject(parent)
{
    subscriber = new VideoSubscriber(this);
}

VideoFollower::~VideoFollower()
{
    delete subscriber;
}

void VideoFollower::onMessageReceived(const QString& message) {
    currentUrl = message;
    emit urlUpdated(message);
}
