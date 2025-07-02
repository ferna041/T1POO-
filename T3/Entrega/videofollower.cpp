#include "videofollower.h"
#include "broker.h"
#include "subscriber.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QUrl>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

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
    : QObject(parent), currentVolume(0.8)
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

void VideoFollower::setVolume(double volume) {
    currentVolume = volume;
}

void VideoFollower::playVideo() {
    if (!currentUrl.isEmpty()) {
        // Crear ventana de video independiente
        QWidget *videoWindow = new QWidget;
        videoWindow->setWindowTitle("Reproductor de Video - Con Control de Volumen");
        videoWindow->resize(900, 700);
        
        // Layout principal
        QVBoxLayout *mainLayout = new QVBoxLayout(videoWindow);
        
        // Widget de video
        QVideoWidget *videoWidget = new QVideoWidget;
        videoWidget->setMinimumSize(800, 600);
        
        // Controles de volumen
        QHBoxLayout *controlsLayout = new QHBoxLayout;
        QLabel *volumeLabel = new QLabel("Volumen:");
        QSlider *volumeSlider = new QSlider(Qt::Horizontal);
        volumeSlider->setRange(0, 100);
        volumeSlider->setValue(static_cast<int>(currentVolume * 100));
        QLabel *volumeValueLabel = new QLabel(QString("%1%").arg(static_cast<int>(currentVolume * 100)));
        
        controlsLayout->addWidget(volumeLabel);
        controlsLayout->addWidget(volumeSlider);
        controlsLayout->addWidget(volumeValueLabel);
        controlsLayout->addStretch();
        
        // Agregar al layout principal
        mainLayout->addWidget(videoWidget);
        mainLayout->addLayout(controlsLayout);
        
        // Configurar reproductor
        QMediaPlayer *player = new QMediaPlayer(videoWindow);
        QAudioOutput *audioOutput = new QAudioOutput(videoWindow);
        audioOutput->setVolume(currentVolume);
        
        player->setVideoOutput(videoWidget);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl(currentUrl));
        
        // Conectar señales del slider de volumen
        connect(volumeSlider, &QSlider::valueChanged, [audioOutput, volumeValueLabel](int value) {
            double volume = value / 100.0;
            audioOutput->setVolume(volume);
            volumeValueLabel->setText(QString("%1%").arg(value));
        });
        
        // Emitir señal para notificar que se creó el audio output
        emit audioOutputCreated(audioOutput);
        
        // Mostrar ventana y reproducir
        videoWindow->show();
        player->play();
        
        // Cleanup automático cuando se cierre la ventana
        connect(videoWindow, &QWidget::destroyed, [player, audioOutput]() {
            if (player) {
                player->stop();
                delete player;
            }
            if (audioOutput) {
                delete audioOutput;
            }
        });
    }
}
