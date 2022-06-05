#include "officemodel.h"

OfficeModel::OfficeModel(QSqlDatabase _db,int _type)
{
    db = _db;
    query = new QSqlQuery(db);
    testquery = new QSqlQuery(db);
    type = _type;
}

bool OfficeModel::queryPossible(){
    switch(type){
    case 0:
        testquery->exec("select ticket_id from customer limit 1");
       if(testquery->lastError().text().isEmpty() == false){
           qDebug() << query->lastError();
            qDebug() << "Does not have GUEST rights";
            return false;
        }
        qDebug() << "Has GUEST rights";
        return true;
    case 1:
        testquery->exec("select ticket_id from inv_customer limit 1");
        if(testquery->lastError().text().isEmpty() == false){
            qDebug() << query->lastError();
            qDebug() << "Does not have OFFICE rights";
            return false;
        }
        qDebug() << "Has OFFICE rights";
        return true;
    case 2:
        testquery->exec("select ticket_id from arc_customer limit 1");
        if(testquery->lastError().text().isEmpty() == false){
            qDebug() << query->lastError();
            qDebug() << "Does not have OFFICE rights";
            return false;
        }
        qDebug() << "Has OFFICE rights";
        return true;
    }
    return false;
}
bool OfficeModel::isEmpty(){
    return list.isEmpty();
}
Office* OfficeModel::getData(QModelIndex index){
    return list.at(index.row());
}
void OfficeModel::fromSqlQuery(){
    if(type == 0){
        query->prepare("select * from customer");
    }
    if(type==1){
        query->prepare("select * from inv_customer");
    }
    if(type==2){
        query->prepare("select * from arc_customer");
    }
    query->exec();
    qDebug() << query->lastError();
    while(query->next()){
    addRows(new Office(
                query->value(0).toInt(),
                query->value(1).toInt(),
                query->value(2).toInt(),
                query->value(3).toInt(),
                query->value(4).toString(),
                query->value(5).toString(),
                query->value(6).toDate(),
                query->value(7).toString(),
                query->value(8).toString(),
                query->value(9).toString(),
                query->value(10).toString(),
                query->value(11).toString(),
                query->value(12).toDateTime(),
                query->value(13).toDateTime()
                ));
}
}

void OfficeModel::addRows(Office* office){
    beginInsertRows(QModelIndex(),list.size(),list.size());
    list.append(office);
    endInsertRows();
}

int OfficeModel::rowCount(const QModelIndex &parent) const
{

    return list.size();
};

int OfficeModel::columnCount(const QModelIndex &parent) const
{
    return 10;
};

QVariant OfficeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if (role==Qt::TextAlignmentRole) return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole){
            int row = index.row();
            int column = index.column();
            Office *office = list.at(row);
            if(column==0){
                return office->getFio();
            }
            if(column==1){
                return office->getGender();
            }
            if(column==2){
                return office->getDob();
            }
            if(column==3){
                return office->getPhone();
            }
            if(column==4){
                return office->getSource_city();
            }
            if(column==5){
                return office->getSource_station();
            }
            if(column==6){
                return office->getDestination_city();
            }
            if(column==7){
                return office->getDestination_station();
            }
            if(column==8){
                return office->getTime_of_departure();
            }
            if(column==9){
                return office->getTime_of_destination();
            }
}
    return QVariant();
}

QVariant OfficeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ФИО");
        case 1:
            return QString("Пол");
        case 2:
            return QString("Дата рождения");
        case 3:
            return QString("Телефон");
        case 4:
            return QString("Город отправления");
        case 5:
            return QString("Вокзал");
        case 6:
            return QString("Город прибытия");
        case 7:
            return QString("Вокзал");
        case 8:
            return QString("Дата отправления");
        case 9:
            return QString("Дата прибытия");
        }
    }
    return QVariant();
}

QSqlError OfficeModel::refund(QModelIndex index){
        QSqlQuery qr = QSqlQuery(db);
        int ticket_id = list.at(index.row())->getTicket_id();
        qr.exec("call refund_ticket("+QString::number(ticket_id)+")");
        return qr.lastError();
}

QSqlError OfficeModel::autoFix(){
    QSqlQuery qr = QSqlQuery(db);
    qr.exec("call auto_move_invalid()");
    return qr.lastError();
}

QSqlError OfficeModel::edit(QString fio,bool gender,QString phone,QDate dob,QModelIndex index){
    QSqlQuery qr = QSqlQuery(db);
    QString genderStr;
    qDebug() << gender;
    if(gender == false)genderStr="false";
    else genderStr="true";
    int ticket_id = list.at(index.row())->getTicket_id();
    QString func = "call edit_ticket('%1','%2','%3','%4','%5')";
    func = func.arg(fio,phone,genderStr,dob.toString("MM/dd/yyyy"),QString::number(ticket_id));
    qr.exec(func);
    return qr.lastError();
};

QSqlError OfficeModel::move(QModelIndex index, int s_id){
    QSqlQuery qr = QSqlQuery(db);
    int ticket_id = list.at(index.row())->getTicket_id();
    QString func = "call move_schedule(%1,%2)";
    func = func.arg(QString::number(ticket_id),QString::number(s_id));
    qr.exec(func);
    return qr.lastError();
};

int OfficeModel::starikashka(int a){
    QSqlQuery qr = QSqlQuery(db);
    QString func = "select * from starikashka('%1 years')";
    func = func.arg(QString::number(a));
    qr.exec(func);
    while(qr.next()) {
        qDebug() << qr.value(0).toInt();
        return qr.value(0).toInt();
    }
}

QSqlDatabase OfficeModel::getDb(){
    return db;
};
