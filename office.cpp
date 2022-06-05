#include "office.h"


Office::Office(int _schedule_id,
int _ticket_id,
int _source_id,
int _destination_id,
QString _fio,
QString _gender,
QDate _dob,
QString _phone,
QString _source_city,
QString _source_station,
QString _destination_city,
QString _destination_station,
QDateTime _time_of_departure,
QDateTime _time_of_destination)
{
  schedule_id = _schedule_id;
  ticket_id = _ticket_id;
  source_id = _source_id;
  destination_id = _destination_id;
  fio = _fio;
  gender = _gender;
  phone = _phone;
  dob = _dob;
  source_city = _source_city;
  destination_city = _destination_city;
  source_station = _source_station;
  destination_station = _destination_station;
  time_of_departure = _time_of_departure;
  time_of_destination = _time_of_destination;
};

Office::Office(int _schedule_id,
                   int _ticket_id,
                   int _source_id,
                   int _destination_id,
                   QString _fio,
                   QString _gender,
                   QDate _dob,
                   QString _phone,
                   QString _source_city,
                   QString _source_station,
                   QString _destination_city,
                   QString _destination_station,
                   QDateTime _time_of_departure,
                   QDateTime _time_of_destination,
                   QDate _refund)
{
    schedule_id = _schedule_id;
    ticket_id = _ticket_id;
    source_id = _source_id;
    destination_id = _destination_id;
    fio = _fio;
    gender = _gender;
    phone = _phone;
    dob = _dob;
    source_city = _source_city;
    destination_city = _destination_city;
    source_station = _source_station;
    destination_station = _destination_station;
    time_of_departure = _time_of_departure;
    time_of_destination = _time_of_destination;
    refund = _refund;
}

QString Office::getFio(){
    return fio;
};
QString Office::getGender(){
    return gender;
};
QString Office::getPhone(){
    return phone;
};
QDate Office::getDob(){
    return dob;
};
QString Office::getSource_city(){
    return source_city;
};
QString Office::getDestination_city(){
    return destination_city;
};
QString Office::getSource_station(){
    return source_station;
};
QString Office::getDestination_station(){
    return destination_station;
}

int Office::getSchedule_id(){
    return schedule_id;
};
int Office::getTicket_id(){
    return ticket_id;
};
int Office::getSource_id(){
    return source_id;
};
int Office::getDestination_id(){
    return destination_id;
};
QDateTime Office::getTime_of_departure(){
    return time_of_departure;
};
QDateTime Office::getTime_of_destination(){
    return time_of_destination;
};
QDate Office::getRefund(){
    return refund;
}
