#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>
#include "../updater/updater.h"
#include "../logger/logger.h"
#include <QPoint>
#include <QMouseEvent>
#include <QProcess>

namespace Ui {
class Launcher;
}

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit Launcher(QWidget *parent = 0);
    ~Launcher();

private:
    Ui::Launcher* ui;
    Updater* updater;
    Logger* log;
    QPoint mpos;
    int port;
    bool isRegStarted;
    QProcess* reg;

    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void onClickPlayButton();
    void onPressedPlayButton();
    void onReleasedPlayButton();
    void onClickCloseButton();
    void onClickMinimizeButton();
    void onClickSettingsButton();
};

#endif // LAUNCHER_H
