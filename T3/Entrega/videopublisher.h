#ifndef VIDEOPUBLISHER_H
#define VIDEOPUBLISHER_H

#include <QObject>
#include "publisher.h"

class VideoPublisher : public QObject, public Publisher {
    Q_OBJECT
    
public:
    VideoPublisher(QObject* parent = nullptr);
    ~VideoPublisher() = default;
    
    void publishUrl(const QString& url);
};

#endif
