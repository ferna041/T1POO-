#ifndef VIDEOFOLLOWER_H
#define VIDEOFOLLOWER_H

#include <QObject>
#include <QString>
#include <QAudioOutput>

class Subscriber;

class VideoFollower : public QObject {
    Q_OBJECT
public:
    VideoFollower(QObject* parent = nullptr);
    ~VideoFollower();
    QString getCurrentUrl() const { return currentUrl; }
    void setVolume(double volume);
    void onMessageReceived(const QString& message);

signals:
    void urlUpdated(const QString& url);
    void audioOutputCreated(QAudioOutput* audioOutput);

public slots:
    void playVideo();

private:
    QString currentUrl;
    double currentVolume;
    Subscriber* subscriber;
};

#endif
