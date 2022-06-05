#ifndef TRAIN_H
#define TRAIN_H
#include <QString>
#include <QDateTime>
class Train
{
private:
    int id;
    QString name;
    QString type;
    QString serial;
    QDateTime operation;
    QDateTime inspection;
    QDateTime repair;
    int repair_amount;
    int used;
public:
    Train(
            int id,
            QString name,
            QString type,
            QString serial,
            QDateTime operation,
            QDateTime inspection,
            QDateTime repair,
            int repair_amount,
            int used
            );
    int getId();
    QString getName();
    QString getType();
    QString getSerial();
    QDateTime getOperation();
    QDateTime getInspection();
    QDateTime getRepair();
    int getRepair_amount();
    int getUsed();
};

#endif // TRAIN_H
