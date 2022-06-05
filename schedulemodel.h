#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include "schedule.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
class ScheduleModel:  public QAbstractTableModel
{
    Q_OBJECT
private:
     QSqlDatabase db;
     int type;
     QSqlQuery *query;
     QSqlQuery *testquery;
     QList<Schedule*> list;
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
     void clear();
public:
    ScheduleModel(QSqlDatabase db, int type);
    bool queryPossible();
    bool isEmpty();
    void fromSqlQuery();
    void addRows(Schedule *schedule);
    void seldomBought();
    void search(QString);
    void search (QString,QString);
    Schedule* getData(QModelIndex index);
    QSqlError buy(QString fio,bool gender,QString phone,QDate dob,QModelIndex index);
    QSqlError autoArchive();
    QSqlError edit(int departId, int destId, int trainId, QDateTime departTime, QDateTime destTime,int ticketCost,int ticketAmount, QModelIndex index);
    QSqlError add(int departId, int destId, int trainId, QDateTime departTime, QDateTime destTime,int ticketCost,int ticketAmount);
    QSqlError remove(QModelIndex index);
    QSqlDatabase getDb();
    QSqlError genSchedule(QModelIndex, int, int);
signals:
};

#endif // SCHEDULEMODEL_H
