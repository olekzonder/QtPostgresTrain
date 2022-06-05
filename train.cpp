#include "train.h"

Train::Train(
        int _id,
        QString _name,
        QString _type,
        QString _serial,
        QDateTime _operation,
        QDateTime _inspection,
        QDateTime _repair,
        int _repair_amount,
        int _used
        ){
    id = _id;
    name = _name;
    type = _type;
    serial = _serial;
    operation = _operation;
    inspection = _inspection;
    repair = _repair;
    repair_amount = _repair_amount;
    used = _used;
};
int Train::getId(){
    return id;
};
QString Train::getName(){
    return name;
};
QString Train::getType(){
    return type;
};
QString Train::getSerial(){
    return serial;
};
QDateTime Train::getOperation(){
    return operation;
};
QDateTime Train::getInspection(){
    return inspection;
};
QDateTime Train::getRepair(){
    return repair;
};
int Train::getRepair_amount(){
    return repair_amount;
};
int Train::getUsed(){
    return used;
};
