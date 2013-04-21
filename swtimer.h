#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QTime>
#include <QSettings>

class SWTimer
{
public:
    SWTimer();
    QTimer *timer;
    bool eventStarted();
    int progress();

    QString hours();
    QString minutes();
    QString seconds();


private:

    QTime*  timeValue;
    QDateTime *now;
    QDateTime *theEnd;
    QDateTime *startDate;
    QDateTime *endDate;
    int totaltime;


};

#endif // TIMER_H
