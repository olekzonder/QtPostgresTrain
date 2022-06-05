#include "trainmodel.h"

TrainModel::TrainModel(QSqlDatabase _db)
{
    db = _db;
    query = new QSqlQuery(db);
    testquery = new QSqlQuery(db);
}

bool TrainModel::queryPossible(){
    testquery->exec("select id from train_interface limit 1");
    if(testquery->lastError().text().isEmpty() == false){
        qDebug() << "Does not have TRAIN rights";
        return false;
    }
    qDebug() << "Has TRAIN rights";
    return true;
}
bool TrainModel::isEmpty(){
    return list.isEmpty();
}
Train* TrainModel::getData(QModelIndex index){
    return list.at(index.row());
}

void TrainModel::reset(){
    beginResetModel();
    list.clear();
    endResetModel();
}
void TrainModel::fromSqlQuery(){
    reset();
    query->prepare("select * from train_interface");
    query->exec();
    qDebug() << query->lastError();
    while(query->next()){
    addRows(new Train(
                query->value(0).toInt(),
                query->value(1).toString(),
                query->value(2).toString(),
                query->value(3).toString(),
                query->value(4).toDateTime(),
                query->value(5).toDateTime(),
                query->value(6).toDateTime(),
                query->value(7).toInt(),
                query->value(8).toInt()
                ));
}
}
void TrainModel::mostBroken(){
    reset();
    query->prepare("select * from barakhlo()");
    query->exec();
    qDebug() << query->lastError();
    while(query->next()){
    addRows(new Train(
                query->value(0).toInt(),
                query->value(1).toString(),
                query->value(2).toString(),
                query->value(3).toString(),
                query->value(4).toDateTime(),
                query->value(5).toDateTime(),
                query->value(6).toDateTime(),
                query->value(7).toInt(),
                query->value(8).toInt()
                ));
}
}
void TrainModel::addRows(Train* train){
    beginInsertRows(QModelIndex(),list.size(),list.size());
    list.append(train);
    endInsertRows();
}

int TrainModel::rowCount(const QModelIndex &parent) const
{

    return list.size();
};

int TrainModel::columnCount(const QModelIndex &parent) const
{
    return 8;
};

QVariant TrainModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()){
        return QVariant();
    }

    if (role==Qt::TextAlignmentRole) return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    if(role==Qt::DisplayRole || role==Qt::ToolTipRole){
            int row = index.row();
            int column = index.column();
            Train *train = list.at(row);
            if(column==0){
                return train->getSerial();
            }
            if(column==1){
                return train->getName();
            }
            if(column==2){
                return train->getType();
            }
            if(column==3){
                return train->getOperation();
            }
            if(column==4){
                return train->getInspection();
            }
            if(column==5){
                return train->getRepair();
            }
            if(column==6){
                return train->getRepair_amount();
            }
            if(column==7){
                return train->getUsed();
            }
    }
    return QVariant();
}

QVariant TrainModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Серийный номер");
        case 1:
            return QString("Название");
        case 2:
            return QString("Тип");
        case 3:
            return QString("Дата постановки на учёт");
        case 4:
            return QString("Дата техосмотра");
        case 5:
            return QString("Дата починки");
        case 6:
            return QString("Количество починок");
        case 7:
            return QString("Пройдено маршрутов");
        }
    }
    return QVariant();
}

QSqlError TrainModel::add(QString name, QString type, QString serial){
   QSqlQuery qr(db);
   QString func = "call add_train('%1','%2','%3')";
   func = func.arg(name,type,serial);
   qr.exec(func);
   qDebug() << qr.lastError().text();
   return qr.lastError();
};
QSqlError TrainModel::edit(QString name, QString type, QString serial, QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    QString func = "call edit_train(%1,'%2','%3','%4')";
    func = func.arg(QString::number(id),name,type,serial);
    qDebug() << func;
    qr.exec(func);
    qDebug() << qr.lastError().text();
    return qr.lastError();
};
QSqlError TrainModel::repair(QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    QString func = "call repair(%1)";
    func = func.arg(QString::number(id));
    qr.exec(func);
    qDebug() << qr.lastError().text();
    return qr.lastError();
};
QSqlError TrainModel::inspect(QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    QString func = "call inspect(%1)";
    func = func.arg(QString::number(id));
    qr.exec(func);
    qDebug() << qr.lastError().text();
    return qr.lastError();
};

QSqlError TrainModel::remove(QModelIndex index){
    QSqlQuery qr(db);
    int id = list.at(index.row())->getId();
    QString func = "call delete_train(%1)";
    func = func.arg(QString::number(id));
    qr.exec(func);
    qDebug() << qr.lastError().text();
    return qr.lastError();
};
