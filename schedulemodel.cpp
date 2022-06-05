#include "schedulemodel.h"

ScheduleModel::ScheduleModel(QSqlDatabase _db, int _type)
{
    type = _type;
    db = _db;
    query = new QSqlQuery(db);
    testquery = new QSqlQuery(db);
}

bool ScheduleModel::queryPossible(){
    switch(type){
    case 0:
        testquery->exec("select schedule_id from schedule_info limit 1");
        if(testquery->lastError().text().isEmpty() == false){
            qDebug() << query->lastError();
            qDebug() << "Does not have GUEST rights";
            return false;
        }
        else return true;
    case 1:
        testquery->exec("select schedule_id from schedule_editable limit 1");
        if(testquery->lastError().text().isEmpty() == false){
            qDebug() << query->lastError();
            qDebug() << "Does not have EDIT_SCHEDULE rights";
            return false;
        }
        else return true;
    case 2:
        testquery->exec("select schedule_id from schedule_archive limit 1");
        if(testquery->lastError().text().isEmpty()==false){
            qDebug() << testquery->lastError();
            return false;
        }
        else return true;
    }
}

bool ScheduleModel::isEmpty(){
    return list.isEmpty();
}
Schedule* ScheduleModel::getData(QModelIndex index){
    return list.at(index.row());
}

void ScheduleModel::clear(){
    beginResetModel();
    list.clear();
    endResetModel();
}

void ScheduleModel::fromSqlQuery(){
    clear();
    if(type == 0){
         query->prepare("select * from schedule_info");
    }
    if(type == 1){
        query->prepare("select * from schedule_editable");
    }
    if(type == 2) query->prepare("select * from schedule_archive");
    query->exec();
    qDebug() << query->lastError();
    if(type==0)
    while(query->next()){
    addRows(new Schedule(
                query->value(0).toInt(),
                query->value(1).toInt(),
                query->value(2).toInt(),
                query->value(3).toInt(),
                query->value(4).toString(),
                query->value(5).toString(),
                query->value(6).toString(),
                query->value(7).toString(),
                query->value(8).toString(),
                query->value(9).toString(),
                query->value(10).toInt(),
                query->value(11).toInt(),
                query->value(12).toDateTime(),
                query->value(13).toDateTime()
                ));
}
    if(type==1 || type == 2)
    while(query->next()){
    addRows(new Schedule(
                    query->value(0).toInt(),
                    query->value(1).toInt(),
                    query->value(2).toInt(),
                    query->value(3).toInt(),
                    query->value(4).toString(),
                    query->value(5).toString(),
                    query->value(6).toString(),
                    query->value(7).toString(),
                    query->value(8).toString(),
                    query->value(9).toInt(),
                    query->value(10).toInt(),
                    query->value(11).toDateTime(),
                    query->value(12).toDateTime(),
                    query->value(13).toInt()
                    ));
}
}

void ScheduleModel::seldomBought(){
    clear();
    query->prepare("select * from seldomsold()");
    query->exec();
    qDebug() << query->lastError();
    while(query->next()){
    addRows(new Schedule(
                    query->value(0).toInt(),
                    query->value(1).toInt(),
                    query->value(2).toInt(),
                    query->value(3).toInt(),
                    query->value(4).toString(),
                    query->value(5).toString(),
                    query->value(6).toString(),
                    query->value(7).toString(),
                    query->value(8).toString(),
                    query->value(9).toInt(),
                    query->value(10).toInt(),
                    query->value(11).toDateTime(),
                    query->value(12).toDateTime(),
                    query->value(13).toInt()
                    ));
}
}
void ScheduleModel::addRows(Schedule* schedule){
    beginInsertRows(QModelIndex(),list.size(),list.size());
    list.append(schedule);
    endInsertRows();
}

int ScheduleModel::rowCount(const QModelIndex &parent) const
{

    return list.size();
};

int ScheduleModel::columnCount(const QModelIndex &parent) const
{
    return 10;
};

QVariant ScheduleModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if (role==Qt::TextAlignmentRole) return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole){
            int row = index.row();
            int column = index.column();
            Schedule *schedule = list.at(row);
            switch(type){
            case 0:
            if(column==0){
                return schedule->getSource_city();
            }
            if(column==1){
                return schedule->getSource_station();
            }
            if(column==2){
                return schedule->getDestination_city();
            }
            if(column==3){
                return schedule->getDestination_station();
            }
            if(column==4){
                return schedule->getTrain_type();
            }
            if(column==5){
                return schedule->getTrain_name();
            }
            if(column==6){
                return schedule->getTicket_cost();
            }
            if(column==7){
                return schedule->getTicket_amount();
            }
            if(column==8){
                return schedule->getTime_of_departure();
            }
            if(column==9){
                return schedule->getTime_of_destination();
            }
                break;
            case 1:
                if(column==0){
                    return schedule->getSource_city();
                }
                if(column==1){
                    return schedule->getSource_station();
                }
                if(column==2){
                    return schedule->getDestination_city();
                }
                if(column==3){
                    return schedule->getDestination_station();
                }
                if(column==4){
                    return schedule->getSerial();
                }
                if(column==5){
                    return schedule->getTicket_cost();
                }
                if(column==6){
                    return schedule->getTicket_amount();
                }
                if(column==7){
                    return schedule->getTime_of_departure();
                }
                if(column==8){
                    return schedule->getTime_of_destination();
                }
                if(column==9){
                    return schedule->getCount();
                }
                break;
            case 2:
                if(column==0){
                    return schedule->getSource_city();
                }
                if(column==1){
                    return schedule->getSource_station();
                }
                if(column==2){
                    return schedule->getDestination_city();
                }
                if(column==3){
                    return schedule->getDestination_station();
                }
                if(column==4){
                    return schedule->getSerial();
                }
                if(column==5){
                    return schedule->getTicket_cost();
                }
                if(column==6){
                    return schedule->getTicket_amount();
                }
                if(column==7){
                    return schedule->getTime_of_departure();
                }
                if(column==8){
                    return schedule->getTime_of_destination();
                }
                if(column==9){
                    return schedule->getCount();
                }
    }
    }
    return QVariant();
}

QVariant ScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(type){
        case 0:
            switch (section) {
            case 0:
                return QString("Город отправления");
            case 1:
                return QString("Вокзал");
            case 2:
                return QString("Город назначения");
            case 3:
                return QString("Вокзал");
            case 4:
                return QString("Название поезда");
            case 5:
                return QString("Тип поезда");
            case 6:
                return QString("Цена билета");
            case 7:
                return QString("Осталось билетов");
            case 8:
                return QString("Дата отправления");
            case 9:
                return QString("Дата прибытия");
            }
         case 1:
            switch (section) {
            case 0:
                return QString("Город отправления");
            case 1:
                return QString("Вокзал");
            case 2:
                return QString("Город назначения");
            case 3:
                return QString("Вокзал");
            case 4:
                return QString("Серийный номер поезда");
            case 5:
                return QString("Цена билета");
            case 6:
                return QString("Осталось билетов");
            case 7:
                return QString("Дата отправления");
            case 8:
                return QString("Дата прибытия");
            case 9:
                return QString("Куплено билетов");
            }
        case 2:
           switch (section) {
           case 0:
               return QString("Город отправления");
           case 1:
               return QString("Вокзал");
           case 2:
               return QString("Город назначения");
           case 3:
               return QString("Вокзал");
           case 4:
               return QString("Серийный номер поезда");
           case 5:
               return QString("Цена билета");
           case 6:
               return QString("Осталось билетов");
           case 7:
               return QString("Дата отправления");
           case 8:
               return QString("Дата прибытия");
           case 9:
               return QString("Куплено билетов");
           }
        }
    }
    return QVariant();
};

QSqlError ScheduleModel::buy(QString fio,bool gender,QString phone,QDate dob,QModelIndex index){
    QSqlQuery qr = QSqlQuery(db);
    QString genderStr;
    qDebug() << gender;
    if(gender == false)genderStr="false";
    else genderStr="true";
    int schedule_id = list.at(index.row())->getSchedule_id();
    qDebug() << schedule_id;
    QString func = "call buy('%1','%2','%3','%4','%5')";
    func = func.arg(fio,phone,genderStr,dob.toString("MM/dd/yyyy"),QString::number(schedule_id));
    qDebug()<<func;
    qr.exec(func);
    qDebug() << qr.executedQuery();
    qDebug() << qr.lastError();
    return qr.lastError();
};

QSqlError ScheduleModel::autoArchive(){
     QSqlQuery qr = QSqlQuery(db);
     qr.exec("call archive_all()");
     return qr.lastError();
}

QSqlDatabase ScheduleModel::getDb(){
    return db;
};

QSqlError ScheduleModel::remove(QModelIndex index){
    int row = index.row();
    QSqlQuery qr = QSqlQuery(db);
    QString func = "call delete_schedule(%1)";
    func = func.arg(QString::number(list.at(row)->getSchedule_id()));
    qr.exec(func);
    return qr.lastError();
}

QSqlError ScheduleModel::edit(int departId, int destId, int trainId, QDateTime departTime, QDateTime destTime,int ticketCost,int ticketAmount, QModelIndex index){
    QSqlQuery qr = QSqlQuery(db);
    int schedule_id = list.at(index.row())->getSchedule_id();
    QString func = "call edit_schedule(%1,%2,%3,%4,to_timestamp('%5','YYYY-MM-DD HH24:MI'),to_timestamp('%6','YYYY-MM-DD HH24:MI'),%7,%8)";
    func = func.arg(QString::number(schedule_id),QString::number(departId),QString::number(destId),QString::number(trainId),departTime.toString("yyyy-MM-dd hh:mm"),destTime.toString("yyyy-MM-dd hh:mm"),QString::number(ticketCost),QString::number(ticketAmount));
    qDebug() << func;
    qr.exec(func);
    qDebug() << qr.lastError();
    return qr.lastError();
};
QSqlError ScheduleModel::add(int departId, int destId, int trainId, QDateTime departTime, QDateTime destTime,int ticketCost,int ticketAmount){
    QSqlQuery qr = QSqlQuery(db);
    QString func = "call add_schedule(%1,%2,%3,to_timestamp('%4','YYYY-MM-DD HH24:MI'),to_timestamp('%5','YYYY-MM-DD HH24:MI'),%6,%7)";
    func = func.arg(QString::number(departId),QString::number(destId),QString::number(trainId),departTime.toString("yyyy-MM-dd hh:mm"),destTime.toString("yyyy-MM-dd hh:mm"),QString::number(ticketCost),QString::number(ticketAmount));
    qr.exec(func);
    return qr.lastError();
};

void ScheduleModel::search(QString src){
    clear();
    QSqlQuery qr = QSqlQuery(db);
    QString func = "select * from view_schedules('%1')";
    func = func.arg(src);
    qr.exec(func);
    while(qr.next()){
    addRows(new Schedule(
                qr.value(0).toInt(),
                qr.value(1).toInt(),
                qr.value(2).toInt(),
                qr.value(3).toInt(),
                qr.value(4).toString(),
                qr.value(5).toString(),
                qr.value(6).toString(),
                qr.value(7).toString(),
                qr.value(8).toString(),
                qr.value(9).toString(),
                qr.value(10).toInt(),
                qr.value(11).toInt(),
                qr.value(12).toDateTime(),
                qr.value(13).toDateTime()
                ));
}
}
void ScheduleModel::search(QString src, QString dst){
    clear();
    QSqlQuery qr = QSqlQuery(db);
    QString func = "select * from view_schedules('%1','%2')";
    func = func.arg(src,dst);
    qDebug() << func;
    qr.exec(func);
    qDebug() << qr.lastError();
    while(qr.next()){
    addRows(new Schedule(
                qr.value(0).toInt(),
                qr.value(1).toInt(),
                qr.value(2).toInt(),
                qr.value(3).toInt(),
                qr.value(4).toString(),
                qr.value(5).toString(),
                qr.value(6).toString(),
                qr.value(7).toString(),
                qr.value(8).toString(),
                qr.value(9).toString(),
                qr.value(10).toInt(),
                qr.value(11).toInt(),
                qr.value(12).toDateTime(),
                qr.value(13).toDateTime()
                ));
}
}

QSqlError ScheduleModel::genSchedule(QModelIndex index, int interval, int count){
    QSqlQuery qr = QSqlQuery(db);
    QString func = "call genschedule(%1,'%2 days',%3)";
    func = func.arg(QString::number(list.at(index.row())->getSchedule_id()),QString::number(interval),QString::number(count));
    qr.exec(func);
    return qr.lastError();
}
