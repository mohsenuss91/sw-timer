#include "quotes.h"


Quotes::Quotes()
{
    Connect();
    CountQuotes('a');
    CountQuotes('f');
    CountQuotes('e');
}

void Quotes::CountQuotes(char lang)
{
    QSqlQuery query;

    switch (lang)
    {
        case 'a':
            query.exec("SELECT count(*) FROM arquotes");
            if (query.next())
                arquotesCount = query.value(0).toInt();
            break;
        case 'f':
            query.exec("SELECT count(*) FROM frquotes");
            if (query.next())
                frquotesCount = query.value(0).toInt();
            break;
        case 'e':
            query.exec("SELECT count(*) FROM enquotes");
            if (query.next())
                enquotesCount = query.value(0).toInt();
            break;
    }


}

bool Quotes::Connect()
{
    QFile::copy(":/quotes.sqlite", "quotes.sqlite");

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("quotes.sqlite");
    database.open();
    return database.isOpen();
}

void Quotes::Close()
{
    database.close();
    QSqlDatabase::removeDatabase("QSQLITE");
    QFile::remove("quotes.sqlite");
}

void Quotes::RandomQuote(char lang)
{
    QSqlQuery query;
    int id;

    switch (lang)
    {
        case 'a':
            id = random(arquotesCount);
            query.exec(QString("SELECT Quote, Author, Book FROM arquotes "
                               "WHERE ID = %1").arg(id));
            break;
        case 'f':
            id = random(frquotesCount);
            query.exec(QString("SELECT Quote, Author, Book FROM frquotes "
                               "WHERE ID = %1").arg(id));
            break;
        case 'e':
            id = random(enquotesCount);
            query.exec(QString("SELECT Quote, Author, Book FROM enquotes "
                               "WHERE ID = %1").arg(id));
            break;
    }

    while (query.next())
    {
        this->quote = query.value(0).toString();
        this->author = query.value(1).toString();
        this->book = query.value(2).toString();
    }
}

int Quotes::random(int max)
{
    return rand() % (max - 1) +1;
}
