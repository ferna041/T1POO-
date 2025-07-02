#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include "videopublisher.h"
#include "videofollower.h"
#include "gpscarpublisher.h"
#include "gpscarfollower.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onUrlEntered();
    void onVideoButtonClicked();
    void onUrlUpdated(const QString& url);
    void onLoadFileClicked();
    void onStartSimulationClicked();
    void onStopSimulationClicked();
    void onShowTrackingClicked();
    void onVolumeChanged(int value);
    void onGPSPositionUpdated(const QString& info, double x, double y);

private:
    Ui::MainWindow *ui;
    VideoPublisher* videoPublisher;
    VideoFollower* videoFollower;
    GPSCarPublisher* gpsPublisher;
    GPSCarFollower* gpsFollower;
    QAudioOutput* currentAudioOutput;
    QString currentGPSFile;
};
#endif
