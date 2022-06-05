#ifndef STATIONMODEL_H
#define STATIONMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include "station.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
class StationModel:  public QAbstractTableModel
{
    Q_OBJECT
private:
     QSqlDatabase db;
     QSqlQuery *query;
     QSqlQuery *testquery;
     QList<Station*> list;
     int type;
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     void clear();
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public:
    StationModel(QSqlDatabase db);
    bool queryPossible();
    bool isEmpty();
    void fromSqlQuery();
    void addRows(Station *station);
    Station* getData(QModelIndex index);
    QSqlError remove(QModelIndex index);
    QSqlError add(QString city, QString station, QString filial);
    QSqlError add(QString city, QString station, QString filial, QDate date);
    QSqlError edit(QString city, QString station, QString filial, QDate date, QModelIndex index);
};

#endif // OFFICEMODEL_H
