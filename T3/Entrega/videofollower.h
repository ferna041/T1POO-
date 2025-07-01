#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include <QObject>
#include <QString>

class Subscriber;

class VideoFollower : public QObject {
    Q_OBJECT
public:
    VideoFollower(QObject* parent = nullptr);
    ~VideoFollower();
    QString getCurrentUrl() const { return currentUrl; }
    void onMessageReceived(const QString& message);

signals:
    void urlUpdated(const QString& url);

private:
    QString currentUrl;
    Subscriber* subscriber;
};

#endif
