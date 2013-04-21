#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QSettings>
#include <QDebug>
#include "quotes.h"
#include "swtimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refreshUI();
    void pitchFire();
    void qa();
    void presentation();

    void loadSettings();

    void on_pitchfireButton_clicked();

    void on_presentationButton_clicked();

    void on_aboutButton_clicked();

    void on_sponsorsButton_clicked();

    void on_pitchfireRestartButton_clicked();

    void on_homeButton_clicked();

    void on_qaButton_clicked();

    void on_qaRestartButton_clicked();

    void on_preRestartButton_clicked();

private:
    Ui::MainWindow *ui;
    Quotes *quotes;
    SWTimer *timer;
    SWTimer *pitchTimer;
    SWTimer *qaTimer;
    SWTimer *preTimer;
    int quotestime;
    int pitchfiretime;
    int qatime;
    int pretime;

    QDateTime *start;
    QDateTime *end;



};

#endif // MAINWINDOW_H
