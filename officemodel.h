#ifndef OFFICEMODEL_H
#define OFFICEMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include "office.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
class OfficeModel:  public QAbstractTableModel
{
    Q_OBJECT
private:
     QSqlDatabase db;
     QSqlQuery *query;
     QSqlQuery *testquery;
     QList<Office*> list;
     int type;
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     void clear();
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public:
    OfficeModel(QSqlDatabase db,int type);
    bool queryPossible();
    bool isEmpty();
    void fromSqlQuery();
    void fromSqlQuery(QString func);
    void addRows(Office *office);
    int starikashka(int);
    Office* getData(QModelIndex index);
    QSqlError refund(QModelIndex index);
    QSqlError autoFix();
    QSqlError edit(QString fio,bool gender,QString phone,QDate dob,QModelIndex index);
    QSqlDatabase getDb();
    QSqlError move(QModelIndex, int s_id);
};

#endif // OFFICEMODEL_H
