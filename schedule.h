#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
class Schedule
{
private:
    int schedule_id;
    int source_id;
    int destination_id;
    int train_id;
    int ticket_cost;
    int ticket_amount;
    QString source_city;
    QString destination_city;
    QString source_station;
    QString destination_station;
    QString train_name;
    QString train_type;
    QDateTime time_of_departure;
    QDateTime time_of_destination;
    QString serial;
    int count;
public:
    Schedule(
            int schedule_id,
            int source_id,
            int destination_id,
            int train_id,
            QString source_city,
            QString destination_city,
            QString source_station,
            QString destination_station,
            QString train_name,
            QString train_type,
            int ticket_cost,
            int ticket_amount,
            QDateTime time_of_departure,
            QDateTime time_of_destination
            );
    Schedule(
            int schedule_id,
            int source_id,
            int destination_id,
            int train_id,
            QString source_city,
            QString destination_city,
            QString source_station,
            QString destination_station,
            QString serial,
            int ticket_cost,
            int ticket_amount,
            QDateTime time_of_departure,
            QDateTime time_of_destination,
            int count
            );
    QString getTrain_name();
    QString getTrain_type();
    QString getSource_city();
    QString getDestination_city();
    QString getSource_station();
    QString getDestination_station();
    QDateTime getTime_of_departure();
    QDateTime getTime_of_destination();
    QString getSerial();
    int getCount();
    int getTicket_cost();
    int getTicket_amount();
    int getSchedule_id();
    int getTicket_id();
    int getSource_id();
    int getDestination_id();
    int getTrain_id();
};

#endif // SCHEDULE_H
