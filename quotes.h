#ifndef QUOTES_H
#define QUOTES_H

#include <QtSql>

class Quotes
{
public:
    Quotes();
    bool Connect();
    void RandomQuote(char lang);
    void Close();

    QString quote;
    QString author;
    QString book;

private:
    QSqlDatabase database;
    int random(int max);
    int arquotesCount;
    int frquotesCount;
    int enquotesCount;
    void CountQuotes(char lang);



};

#endif // QUOTES_H
