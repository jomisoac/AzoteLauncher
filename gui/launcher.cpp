#include "launcher.h"
#include "ui_launcher.h"
#include "../logger/logger.h"

#include <QProcess>

Launcher::Launcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);

    setFixedSize(width(), height());
    ui->labelDownloadSpeed->setAttribute(Qt::WA_TranslucentBackground);

    log = &Singleton<Logger>::getInstance();
    log->showConsole();

    updater = new Updater();
    connect(updater, SIGNAL(updateProgressBarTotal(int)), ui->progressBarTotal, SLOT(setValue(int)));
    connect(updater, SIGNAL(updateProgressBarFile(int)), ui->progressBarFile, SLOT(setValue(int)));
    connect(updater, SIGNAL(updateDownloadSpeed(QString)), ui->labelDownloadSpeed, SLOT(setText(QString)));
    connect(updater, SIGNAL(enablePlayButton(bool)), ui->playButton, SLOT(setEnabled(bool)));
    updater->start();

    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(onClickPlayButton()));
}

Launcher::~Launcher()
{
    delete updater;
    delete ui;
}

void Launcher::closeEvent(QCloseEvent* /*event*/)
{
    updater->stopProcess();
    log->closeConsole();
}

void Launcher::onClickPlayButton()
{
    // TODO: choose random port
    // TODO: start sound server

    QProcess* dofus = new QProcess(this);
    QProcess* reg = new QProcess(this);

    QStringList paramsDofus;

    paramsDofus << "--lang=fr";
    paramsDofus << "--update-server-port=4444";
    paramsDofus << "--updater_version=v2";
    paramsDofus << "--reg-client-port=5555";

    QStringList paramsReg;

    paramsReg << "--reg-engine-port=5556";

    dofus->start("../app/Dofus.exe", paramsDofus);
    reg->start("../app/reg/Reg.exe", paramsReg);
}
