#ifndef TRAINMODEL_H
#define TRAINMODEL_H
#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include "train.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class TrainModel:  public QAbstractTableModel
{
    Q_OBJECT
private:
     QSqlDatabase db;
     QSqlQuery *query;
     QSqlQuery *testquery;
     QList<Train*> list;
     int type;
     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     void clear();
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
     void addRows(Train *train);
     void reset();
public:
    TrainModel(QSqlDatabase db);
    bool queryPossible();
    bool isEmpty();
    void fromSqlQuery();
    void mostBroken();
    Train* getData(QModelIndex index);
    QSqlError add(QString name, QString type, QString serial);
    QSqlError edit(QString name, QString type, QString serial, QModelIndex index);
    QSqlError repair(QModelIndex index);
    QSqlError inspect(QModelIndex index);
    QSqlError remove(QModelIndex index);
signals:
    void update_required();
};

#endif // OFFICEMODEL_H
