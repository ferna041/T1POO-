#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videopublisher.h"
#include "videofollower.h"

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
    void onUrlUpdated(const QString& url);

private:
    Ui::MainWindow *ui;
    VideoPublisher* videoPublisher;
    VideoFollower* videoFollower;
};

#endif
