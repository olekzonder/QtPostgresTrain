#include "stationmodel.h"

StationModel::StationModel(QSqlDatabase _db)
{
    db = _db;
    query = new QSqlQuery(db);
    testquery = new QSqlQuery(db);
}

bool StationModel::queryPossible(){
    testquery->exec("select id from station_interface limit 1");
    if(testquery->lastError().text().isEmpty() == false){
        qDebug() << query->lastError();
        qDebug() << "Does not have STATION rights";
        return false;
    }
    qDebug() << "Has STATION rights";
    return true;
}
bool StationModel::isEmpty(){
    return list.isEmpty();
}
Station* StationModel::getData(QModelIndex index){
    return list.at(index.row());
}
void StationModel::fromSqlQuery(){
    query->prepare("select * from station_interface");
    query->exec();
    qDebug() << query->lastError();

    while(query->next()){
    addRows(new Station(

                query->value(0).toInt(),
                query->value(1).toString(),
                query->value(2).toString(),
                query->value(3).toString(),
                QDate::fromString(query->value(4).toString(),"yyyy-MM-dd"),
                query->value(5).toInt(),
                query->value(6).toInt()
                ));
}
}

void StationModel::addRows(Station* station){
    beginInsertRows(QModelIndex(),list.size(),list.size());
    list.append(station);
    endInsertRows();
}

int StationModel::rowCount(const QModelIndex &parent) const
{

    return list.size();
};

int StationModel::columnCount(const QModelIndex &parent) const
{
    return 6;
};

QVariant StationModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if (role==Qt::TextAlignmentRole) return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole){
            int row = index.row();
            int column = index.column();
            Station *station = list.at(row);
            if(column==0){
                return station->getCity();
            }
            if(column==1){
                return station->getStation();
            }
            if(column==2){
                return station->getFilial();
            }
            if(column==3){
                return station->getOpening_date();
            }
            if(column==4){
                return station->getOut();
            }
            if(column==5){
                return station->getIn();
            }
    }
    return QVariant();
}

QVariant StationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Город");
        case 1:
            return QString("Вокзал");
        case 2:
            return QString("Филиал");
        case 3:
            return QString("Дата открытия");
        case 4:
            return QString("Убыло за неделю");
        case 5:
            return QString("Прибыло за неделю");
        }
    }
    return QVariant();
}

QSqlError StationModel::remove(QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    QString func = "call delete_station(%1)";
    func = func.arg(QString::number(id));
    qr.exec(func);
    qDebug() << qr.lastError();
    return qr.lastError();
};

QSqlError StationModel::add(QString city, QString station, QString filial){
   QSqlQuery qr(db);
   QString func = "call add_station('%1','%2','%3')";
   func = func.arg(city,station,filial);
   qr.exec(func);
   qDebug() << qr.lastError();
   return qr.lastError();
};
QSqlError StationModel::add(QString city, QString station, QString filial, QDate date){
   QSqlQuery qr(db);
   QString func = "call add_station('%1','%2','%3','%4')";
   qDebug() << date;
   func = func.arg(city,station,filial,date.toString("MM/dd/yyyy"));
   qr.exec(func);
   qDebug() << qr.lastError();
   return qr.lastError();
};
QSqlError StationModel::edit(QString city, QString station, QString filial, QDate date, QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    qDebug() << date;
    QString func = "call edit_station(%1,'%2','%3','%4','%5')";
    func = func.arg(QString::number(id),city,station,filial,date.toString("MM/dd/yyyy"));
    qDebug() << func;
    qr.exec(func);
    qDebug() << qr.lastError();
    return qr.lastError();
};
