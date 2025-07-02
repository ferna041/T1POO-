#ifndef VIDEOPUBLISHER_H
#define VIDEOPUBLISHER_H

#include <QObject>

class Publisher;

class VideoPublisher : public QObject {
    Q_OBJECT
public:
    VideoPublisher(QObject* parent = nullptr);
    ~VideoPublisher();

public slots:
    void publishUrl(const QString& url);

private:
    Publisher* publisher;
};

#endif
