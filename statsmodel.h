#ifndef STATSMODEL_H
#define STATSMODEL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QVariant>
#include <QDebug>
class StatsModel
{
private:
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQuery *testquery;
    QVector<int> *list;
public:
    StatsModel(QSqlDatabase db);
    bool queryPossible();
    QVector<int>* fromSqlQuery();
};

#endif // STATSMODEL_H
