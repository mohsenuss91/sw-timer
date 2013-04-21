#include "swtimer.h"

SWTimer::SWTimer()
{
    timer = new QTimer();
    timer->start(1000);
    timeValue = new QTime(0, 0, 1);
    this->startDate = new QDateTime(QDate(2012, 11, 15), QTime(15, 00), Qt::LocalTime);
    this->endDate = new QDateTime(QDate(2012, 11, 17), QTime(19, 30), Qt::LocalTime);
    totaltime = startDate->secsTo(*endDate);
}

int SWTimer::progress()
{
    int passed = startDate->secsTo(*now);
    return (passed * 100) / totaltime;
}

bool SWTimer::eventStarted()
{
    now = new QDateTime(QDateTime::currentDateTime());
    if (*now < *startDate)
    {
        theEnd = startDate;
        return false;
    }
    else
    {
        theEnd = endDate;
        return true;
    }
}

QString SWTimer::seconds()
{
    int seconds = now->secsTo(*theEnd);
    seconds = seconds % 60 % 60;
    return QString().sprintf(":%02d", seconds);;
}

QString SWTimer::minutes()
{
    int seconds = now->secsTo(*theEnd);
    int minutes = seconds / 60;
    minutes = minutes % 60;
    return QString().sprintf("%02d", minutes);;
}

QString SWTimer::hours()
{
    int hours = now->secsTo(*theEnd);
    hours = hours / 3600;
    return QString().sprintf("%02d:", hours);
}
