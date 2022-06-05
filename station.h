#ifndef STATION_H
#define STATION_H
#include <QString>
#include <QDate>
class Station
{
public:
    Station(int id, QString city, QString station, QString filial, QDate opening_date, int out, int in);
    int getId();
    QString getCity();
    QString getStation();
    QString getFilial();
    QDate getOpening_date();
    int getOut();
    int getIn();
private:
    int id;
    QString city;
    QString station;
    QString filial;
    QDate opening_date;
    int out;
    int in;
};

#endif // STATION_H
