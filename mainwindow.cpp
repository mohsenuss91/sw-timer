#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    quotes = new Quotes();
    timer = new SWTimer();
    loadSettings();
    connect(timer->timer, SIGNAL(timeout()), this, SLOT(refreshUI()));

    qaTimer = new SWTimer();
    connect(qaTimer->timer, SIGNAL(timeout()), this, SLOT(qa()));

    pitchTimer = new SWTimer();
    connect(pitchTimer->timer, SIGNAL(timeout()), this, SLOT(pitchFire()));

    preTimer = new SWTimer();
    connect(preTimer->timer, SIGNAL(timeout()), this, SLOT(presentation()));

    ui->stackedWidget->setCurrentIndex(0);
    quotestime = 15; //sec
}

MainWindow::~MainWindow()
{
    quotes->Close();
    delete ui;
}

void MainWindow::refreshUI()
{
    quotestime--;
    if (quotestime == 0)
    {
        // Get english quotes, to change the langage just choose e for english, f for french, a for arabic :p
        quotes->RandomQuote('e');

        ui->quoteLabel->setText(quotes->quote);
        ui->authorLabel->setText(quotes->author);
        ui->grBookLabel->setText(quotes->book);
        quotestime = 15;
    }

    if (timer->eventStarted())
        ui->statusMessageLabel->setText(tr("No Talk, All Action!"));
    else
        ui->statusMessageLabel->setText(tr("Until the event starts!"));

    QString hours = timer->hours();
    int length = hours.length();
    ui->hourLCDNumber->setDigitCount(length);
    ui->hourLCDNumber->display(hours);
    ui->minutesLCDNumber->display(timer->minutes());
    ui->secondsLCDNumber->display(timer->seconds());

    int progress = timer->progress();
    ui->progressBar->setValue(progress);
}

void MainWindow::loadSettings()
{
    QSettings regSettings("SWAnnaba", "Timer");
    regSettings.beginGroup("DateTime");
        QVariant _startDate = regSettings.value("startDate", QDateTime(QDate(2012, 11, 15), QTime(18, 30)));
        QVariant _endDate = regSettings.value("endDate", QDateTime(QDate(2012, 11, 17), QTime(21, 00)));

        start = new QDateTime(_startDate.toDateTime());
        end = new QDateTime(_endDate.toDateTime());
    regSettings.endGroup();
    refreshUI();
}

void MainWindow::on_homeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Pitch Fire
void MainWindow::on_pitchfireButton_clicked()
{
    pitchTimer->timer->stop();
    ui->stackedWidget->setCurrentIndex(1);
    ui->secLCDNumber_pitchfire->display(60);
    pitchfiretime = 60;

}

void MainWindow::on_pitchfireRestartButton_clicked()
{
    pitchfiretime = 60;
    ui->secLCDNumber_pitchfire->display(pitchfiretime);
    pitchTimer->timer->start();
}

void MainWindow::pitchFire()
{
    pitchfiretime--;
    QString sec = (pitchfiretime > 9)? QString::number(pitchfiretime) : "0" + QString::number(pitchfiretime);
    ui->secLCDNumber_pitchfire->display(sec);
    if (pitchfiretime == 0)
        pitchTimer->timer->stop();
}

// Q/A
void MainWindow::on_qaButton_clicked()
{
    qaTimer->timer->stop();
    ui->stackedWidget->setCurrentIndex(2);
    ui->minutesLCDNumber_qa->display(5);
    ui->secondsLCDNumber_qa->display("00");
    qatime = 300;
}

void MainWindow::qa()
{
    qatime--;
    int min = qatime / 60;
    int secs = qatime % 60;
    QString sec = (secs > 9)? QString::number(secs) : "0" + QString::number(secs);

    ui->secondsLCDNumber_qa->display(sec);
    ui->minutesLCDNumber_qa->display(QString::number(min));
    if (qatime == 0)
        qaTimer->timer->stop();
}

void MainWindow::on_qaRestartButton_clicked()
{
    ui->minutesLCDNumber_qa->display(5);
    ui->secondsLCDNumber_qa->display("00");
    qatime = 300;
    qaTimer->timer->start();
}

// Presentation
void MainWindow::on_presentationButton_clicked()
{
    preTimer->timer->stop();
    ui->stackedWidget->setCurrentIndex(3);
    ui->minutesLCDNumber_pre->display(10);
    ui->secondsLCDNumber_pre->display("00");
    pretime = 600;
}

void MainWindow::on_preRestartButton_clicked()
{
    ui->minutesLCDNumber_pre->display(10);
    ui->secondsLCDNumber_pre->display("00");
    pretime = 600;
    preTimer->timer->start();
}

void MainWindow::presentation()
{
    pretime--;
    int min = pretime / 60;
    int secs = pretime % 60;
    QString sec = (secs > 9)? QString::number(secs) : "0" + QString::number(secs);

    ui->secondsLCDNumber_pre->display(sec);
    ui->minutesLCDNumber_pre->display(QString::number(min));
    if (pretime == 0)
        preTimer->timer->stop();
}


// Sponsors
void MainWindow::on_sponsorsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

// About
void MainWindow::on_aboutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

