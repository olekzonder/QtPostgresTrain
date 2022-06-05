#ifndef OFFICE_H
#define OFFICE_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
class Office
{
private:
    int schedule_id;
    int ticket_id;
    int source_id;
    int destination_id;
    QString fio;
    QString gender;
    QString phone;
    QDate dob;
    QString source_city;
    QString destination_city;
    QString source_station;
    QString destination_station;
    QDateTime time_of_departure;
    QDateTime time_of_destination;
    QDate refund;
public:
    Office(
            int schedule_id,
            int ticket_id,
            int source_id,
            int destination_id,
            QString fio,
            QString gender,
            QDate dob,
            QString phone,
            QString source_city,
            QString source_station,
            QString destination_city,
            QString destination_station,
            QDateTime time_of_departure,
            QDateTime time_of_destination
            );
    Office(            int schedule_id,
                       int ticket_id,
                       int source_id,
                       int destination_id,
                       QString fio,
                       QString gender,
                       QDate dob,
                       QString phone,
                       QString source_city,
                       QString source_station,
                       QString destination_city,
                       QString destination_station,
                       QDateTime time_of_departure,
                       QDateTime time_of_destination,
                       QDate refund);
    QDate getRefund();
    QString getFio();
    QString getGender();
    QString getPhone();
    QDate getDob();
    QString getSource_city();
    QString getDestination_city();
    QString getSource_station();
    QString getDestination_station();
    QDateTime getTime_of_departure();
    QDateTime getTime_of_destination();
    int getSchedule_id();
    int getTicket_id();
    int getSource_id();
    int getDestination_id();
};

#endif // OFFICE_H
