#include "scheduledialog.h"

ScheduleDialog::ScheduleDialog(QWidget *parent):QDialog{parent}
{
    this->setWindowTitle("Редактирование сведений");
    signal1 = false;
    signal2 = false;
    query = new QSqlQuery(db);
    layout = new QGridLayout(this);
    labelSourceCity = new QLabel(this);
    labelSourceCity->setText("Город отправления");
    layout->addWidget(labelSourceCity,0,0);
    srcCityBox = new QComboBox(this);
    query->exec("select city from station_interface group by city");
    int cnt = 0;
    while(query->next()){
        srcCityBox->insertItem(cnt,query->value(0).toString());
        cnt++;
    };
    srcCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(srcCityBox,0,1);

    labelSourceStation = new QLabel;
    labelSourceStation->setText("Вокзал отправления");
    layout->addWidget(labelSourceStation,0,2);
    srcStationBox = new QComboBox;
    srcStationBox->setDisabled(true);
    srcStationBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(srcStationBox,0,3);

    labelDestinationCity = new QLabel;
    labelDestinationCity->setText("Город назначения");
    layout->addWidget(labelDestinationCity,1,0);
    destCityBox = new QComboBox;
    destCityBox->setDisabled(true);
    destCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(destCityBox,1,1);

    labelDestinationStation = new QLabel;
    labelDestinationStation->setText("Вокзал назначения");
    layout->addWidget(labelDestinationStation,1,2);
    destStationBox = new QComboBox;
    destStationBox->setDisabled(true);
    destStationBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(destStationBox,1,3);

    connect(destStationBox,SIGNAL(currentIndexChanged(int)),this,SLOT(n(int)));
    labelTimeOfDeparture = new QLabel;
    labelTimeOfDeparture->setText("Время отправления");
    layout->addWidget(labelTimeOfDeparture,2,0);
    departEdit = new QDateTimeEdit(this);
    departEdit->setMinimumDateTime(QDateTime::currentDateTime());

    connect(departEdit,SIGNAL(dateTimeChanged(const QDateTime)),this,SLOT(minimum(const QDateTime)));
    layout->addWidget(departEdit,2,1);
    labelTimeOfDestination = new QLabel;
    labelTimeOfDestination->setText("Время прибытия");
    destEdit = new QDateTimeEdit(this);
    destEdit->setMinimumDateTime(QDateTime::currentDateTime());
    layout->addWidget(labelTimeOfDestination,2,2);
    layout->addWidget(destEdit,2,3);
    labelTrainSerial = new QLabel;
    labelTrainSerial->setText("Номер поезда");
    layout->addWidget(labelTrainSerial,3,0);
    trainBox = new QComboBox(this);
    query->exec("select id,serial from train_interface");
    listTrain = new QList<QPair<int,QString>>;
    cnt = 0;
    while(query->next()){
        listTrain->append(*new QPair<int,QString>(query->value(0).toInt(),query->value(1).toString()));
        trainBox->insertItem(cnt,query->value(1).toString());
        cnt++;
    }
    layout->addWidget(trainBox,3,1);
    labelTicketCost = new QLabel(this);
    labelTicketCost->setText("Цена билета");
    layout->addWidget(labelTicketCost,3,2);
    ticketCost = new QSpinBox(this);
    ticketCost->setMinimum(0);
    ticketCost->setMaximum(100000);
    layout->addWidget(ticketCost,3,3);
    labelTicketCost = new QLabel(this);
    labelTicketCost->setText("Количество билетов");
    layout->addWidget(labelTicketCost,4,0);
    ticketAmount = new QSpinBox(this);
    ticketAmount->setMinimum(0);
    ticketAmount->setMaximum(10000);
    layout->addWidget(ticketAmount,4,1);
    confirmButton = new QPushButton(this);
    confirmButton->setDisabled(true);
    cancelButton = new QPushButton(this);
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
    confirmButton->setText("Подтвердить");
    cancelButton->setText("Отменить");
    layout->addWidget(confirmButton,4,2);
    layout->addWidget(cancelButton,4,3);
    srcCityBox->setCurrentIndex(-1);


    connect(srcCityBox,SIGNAL(currentTextChanged(QString)),this,SLOT(srcCity(QString)));
}
void ScheduleDialog::setDb(QSqlDatabase _db){
    db = _db;
}

void ScheduleDialog::srcCity(QString new_val){
    listSrcCity = new QList<QPair<int,QString>>;
    srcStationBox->clear();
    destCityBox->setDisabled(true);
    destStationBox->setDisabled(true);
    QSqlQuery qr1(db);
    QString chosen = new_val;
    QString func = "select id,station_name from station_interface where lower(city) = lower('%1')";
    func = func.arg(chosen);
    qr1.exec(func);
    int cnt=0;
    while(qr1.next()){
        listSrcCity->append(*new QPair<int,QString>(qr1.value(0).toInt(),qr1.value(1).toString()));
        srcStationBox->insertItem(cnt,listSrcCity->at(cnt).second);
        cnt++;
    };
    srcStationBox->setCurrentIndex(-1);
    destCityBox->clear();
    srcStationBox->setDisabled(false);
    func = "select id,city from station_interface where lower(city) <> lower('%1')";
    func = func.arg(chosen);
    query->exec(func);
    cnt = 0;
    while(query->next()){
        cnt++;
        destCityBox->insertItem(cnt,query->value(1).toString());
    };
    destCityBox->setDisabled(false);
    enableSignals(1);
    emit dstCity(destCityBox->currentText());
}

void ScheduleDialog::dstCity(QString new_val){
    if(new_val.isEmpty()) return;
    listDstCity = new QList<QPair<int,QString>>;
    destStationBox->clear();
    confirmButton->setDisabled(true);
    destStationBox->setDisabled(true);
    QSqlQuery qr3(db);
    QString chosen = new_val;
    QString func = "select id, station_name from station_interface where lower(city) = lower('%1')";
    func = func.arg(chosen);
    qr3.exec(func);
    int cnt=0;
    while(qr3.next()){
        listDstCity->append(*new QPair<int,QString>(qr3.value(0).toInt(),qr3.value(1).toString()));
        destStationBox->insertItem(cnt,listDstCity->at(cnt).second);
        cnt++;
    };
    destStationBox->setCurrentIndex(-1);
    destStationBox->setDisabled(false);
    confirmButton->setDisabled(false);
}


void ScheduleDialog::on_confirm(){
    if(srcStationBox->currentIndex() == -1 || destCityBox->currentIndex() == -1 ||
       srcCityBox->currentIndex()== -1  || destStationBox->currentIndex() == -1 ){
        QMessageBox::warning(this,"Ошибка","Не все поля введены");
        return;}
    srcCityVal = listSrcCity->at(srcStationBox->currentIndex()).first;
    dstCityVal = listDstCity->at(destStationBox->currentIndex()).first;
    train = listTrain->at(trainBox->currentIndex()).first;
    depart = departEdit->dateTime();
    dest = destEdit->dateTime();
    cost = ticketCost->value();
    amount = ticketAmount->value();
    emit data_changed();
    this->close();
}

void ScheduleDialog::on_cancel(){
    this->close();
}

Schedule* ScheduleDialog::getChoice(){
    return choice;
}

void ScheduleDialog::setData(Schedule *sched){
    srcCityBox->setCurrentText(sched->getSource_city());
    srcStationBox->setCurrentText(sched->getSource_station());
    destCityBox->setCurrentText(sched->getDestination_city());
    destStationBox->setCurrentText(sched->getDestination_station());
    trainBox->setCurrentText(sched->getSerial());
    ticketCost->setValue(sched->getTicket_cost());
    ticketAmount->setValue(sched->getTicket_amount());
}

void ScheduleDialog::enableSignals(int type){
    if (type==1 and signal1 == false){
        connect(destCityBox,SIGNAL(currentTextChanged(QString)),this,SLOT(dstCity(QString)));
        signal2 = true;
    }
}

void ScheduleDialog::minimum(const QDateTime cur){
    destEdit->setMinimumDateTime(cur);
}

int ScheduleDialog::getSrcCityVal(){
    return srcCityVal;
};
int ScheduleDialog::getDstCityVal(){
    return dstCityVal;
};
int ScheduleDialog::getTrain(){
    return train;
};
QDateTime ScheduleDialog::getDepart(){
    return depart;
};
QDateTime ScheduleDialog::getDest(){
    return dest;
};
int ScheduleDialog::getCost(){
    return cost;
};
int ScheduleDialog::getAmount(){
    return amount;
};
