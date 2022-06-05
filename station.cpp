#include "station.h"

Station::Station(
        int _id,
        QString _city,
        QString _station,
        QString _filial,
        QDate _opening_date,
        int _out,
        int _in
        ){
    id = _id;
    city = _city;
    station = _station;
    filial = _filial;
    opening_date = _opening_date;
    out = _out;
    in = _in;
};

int Station::getId(){
    return id;
};
QString Station::getCity(){
    return city;
};
QString Station::getStation(){
    return station;
};
QString Station::getFilial(){
    return filial;
};
QDate Station::getOpening_date(){
    return opening_date;
};

int Station::getOut(){
    return out;
}

int Station::getIn(){
    return in;
}
