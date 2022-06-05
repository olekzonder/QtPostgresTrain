#include "statsmodel.h"


StatsModel::StatsModel(QSqlDatabase _db)
{
    db = _db;
    query = new QSqlQuery(db);
    testquery = new QSqlQuery(db);
    list = new QVector<int>;
}

bool StatsModel::queryPossible(){
    testquery->exec("select * from stats()");
    if(testquery->lastError().text().isEmpty()) return true;
    else return false;
}

QVector<int>* StatsModel::fromSqlQuery(){
    query->exec("select * from stats()");
    query->first();
    list->append(query->value(0).toInt());
    list->append(query->value(1).toInt());
    list->append(query->value(2).toInt());
    list->append(query->value(3).toInt());
    list->append(query->value(4).toInt());
    list->append(query->value(5).toInt());
    list->append(query->value(6).toInt());
    return list;
}

