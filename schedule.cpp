#include "schedule.h"


Schedule::Schedule(
int _schedule_id,
int _source_id,
int _destination_id,
int _train_id,
QString _source_city,
QString _destination_city,
QString _source_station,
QString _destination_station,
QString _train_name,
QString _train_type,
int _ticket_cost,
int _ticket_amount,
QDateTime _time_of_departure,
QDateTime _time_of_destination)
{
  schedule_id = _schedule_id;
  source_id = _source_id;
  destination_id = _destination_id;
  train_id = _train_id;
  train_name = _train_name;
  train_type = _train_type;
  ticket_cost = _ticket_cost;
  ticket_amount = _ticket_amount;
  source_city = _source_city;
  destination_city = _destination_city;
  source_station = _source_station;
  destination_station = _destination_station;
  time_of_departure = _time_of_departure;
  time_of_destination = _time_of_destination;
};

Schedule::Schedule(
int _schedule_id,
int _source_id,
int _destination_id,
int _train_id,
QString _source_city,
QString _source_station,
QString _destination_city,
QString _destination_station,
QString _serial,
int _ticket_cost,
int _ticket_amount,
QDateTime _time_of_departure,
QDateTime _time_of_destination,
int _count)
{
  schedule_id = _schedule_id;
  source_id = _source_id;
  destination_id = _destination_id;
  train_id = _train_id;
  serial = _serial;
  ticket_cost = _ticket_cost;
  ticket_amount = _ticket_amount;
  source_city = _source_city;
  destination_city = _destination_city;
  source_station = _source_station;
  destination_station = _destination_station;
  time_of_departure = _time_of_departure;
  time_of_destination = _time_of_destination;
  count = _count;
};

QString Schedule::getSource_city(){
    return source_city;
};
QString Schedule::getDestination_city(){
    return destination_city;
};
QString Schedule::getSource_station(){
    return source_station;
};
QString Schedule::getDestination_station(){
    return destination_station;
}
QString Schedule::getTrain_name(){
    return train_name;
}
QString Schedule::getTrain_type(){
    return train_type;
}
int Schedule::getSchedule_id(){
    return schedule_id;
};
int Schedule::getSource_id(){
    return source_id;
};
int Schedule::getDestination_id(){
    return destination_id;
};
QDateTime Schedule::getTime_of_departure(){
    return time_of_departure;
};
QDateTime Schedule::getTime_of_destination(){
    return time_of_destination;
};
int Schedule::getTicket_cost(){
    return ticket_cost;
}
int Schedule::getTicket_amount(){
    return ticket_amount;
}
int Schedule::getCount(){
    return count;
}
QString Schedule::getSerial(){
    return serial;
}
