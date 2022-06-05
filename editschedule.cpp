#include "editschedule.h"

EditSchedule::EditSchedule(QWidget *parent):QDialog{parent}
{
    this->setWindowTitle("Редактирование сведений");
    signal1 = false;
    signal2 = false;
    signal3 = false;
    signal4 = false;
    query = new QSqlQuery(db);
    layout = new QVBoxLayout(this);
    labelSourceCity = new QLabel(this);
    labelSourceCity->setText("Город отправления");
    layout->addWidget(labelSourceCity);
    srcCityBox = new QComboBox(this);
    query->exec("select * from src_cities");
    qDebug() << query->lastError();
    int cnt = 0;
    while(query->next()){
        cnt++;
        srcCityBox->insertItem(cnt,query->value(0).toString());
    };
    srcCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(srcCityBox);

    labelSourceStation = new QLabel;
    labelSourceStation->setText("Вокзал отправления");
    layout->addWidget(labelSourceStation);
    srcStationBox = new QComboBox;
    srcStationBox->setDisabled(true);
    srcStationBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(srcStationBox);

    labelDestinationCity = new QLabel;
    labelDestinationCity->setText("Город назначения");
    layout->addWidget(labelDestinationCity);
    destCityBox = new QComboBox;
    destCityBox->setDisabled(true);
    destCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(destCityBox);

    labelDestinationStation = new QLabel;
    labelDestinationStation->setText("Вокзал назначения");
    layout->addWidget(labelDestinationStation);
    destStationBox = new QComboBox;
    destStationBox->setDisabled(true);
    destStationBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(destStationBox);

    labelTimeOfDeparture = new QLabel;
    labelTimeOfDeparture->setText("Время отправления");
    layout->addWidget(labelTimeOfDeparture);
    timeBox = new QComboBox;
    timeBox->setDisabled(true);
    timeBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(timeBox);

    confirmButton = new QPushButton(this);
    confirmButton->setDisabled(true);
    cancelButton = new QPushButton(this);
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
    confirmButton->setText("Подтвердить");
    cancelButton->setText("Отменить");
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    srcCityBox->setCurrentIndex(-1);
    connect(srcCityBox,SIGNAL(currentTextChanged(QString)),this,SLOT(srcCity(QString)));
}

void EditSchedule::setDb(QSqlDatabase _db){
    db = _db;
}

void EditSchedule::srcCity(QString new_val){
    if(srcStationBox->currentIndex()==-1 ||
       srcCityBox->currentIndex()==-1 ||
       destCityBox->currentIndex()==-1 ||
       destStationBox->currentIndex()==-1 ||
       timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    list1 = new QList<QPair<int,QString>>;
    srcStationBox->clear();
    destCityBox->setDisabled(true);
    destStationBox->setDisabled(true);
    QSqlQuery qr1(db);
    QString chosen = new_val;
    QString func = "select * from src_stations('%1')";
    func = func.arg(chosen);
    qr1.exec(func);
    int cnt=0;
    while(qr1.next()){
        list1->append(*new QPair<int,QString>(qr1.value(0).toInt(),qr1.value(1).toString()));
        srcStationBox->insertItem(cnt,list1->at(cnt).second);
        cnt++;
    };
    srcStationBox->setCurrentIndex(-1);
    emit srcStation(srcStationBox->currentIndex());
    enableSignals(1);
    srcStationBox->setDisabled(false);
}

void EditSchedule::srcStation(int new_val){
    if(srcStationBox->currentIndex()==-1 ||
       srcCityBox->currentIndex()==-1 ||
       destCityBox->currentIndex()==-1 ||
       destStationBox->currentIndex()==-1 ||
       timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    if(new_val == -1) return;
    destCityBox->clear();
    destStationBox->clear();
    destCityBox->setDisabled(true);
    destStationBox->setDisabled(true);
    timeBox->setDisabled(true);
    timeBox->clear();
    timeBox->setDisabled(true);
    confirmButton->setDisabled(true);
    int chosen = list1->at(new_val).first;
    QSqlQuery qr2(db);
    QString func = "select * from dst_cities(%1)";
    func = func.arg(chosen);
    qr2.exec(func);
    qDebug() << qr2.lastError();
    int cnt = 0;
    while(qr2.next()){
        qDebug() << cnt <<  ' ' << qr2.value(0).toString();
        destCityBox->insertItem(cnt,qr2.value(0).toString());
        cnt++;
    };
    destCityBox->setCurrentIndex(-1);
    enableSignals(2);
    destCityBox->setDisabled(false);
}

void EditSchedule::dstCity(QString new_val){
    if(srcStationBox->currentIndex()==-1 ||
       srcCityBox->currentIndex()==-1 ||
       destCityBox->currentIndex()==-1 ||
       destStationBox->currentIndex()==-1 ||
       timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    if(new_val.isEmpty()) return;
    list2 = new QList<QPair<int,QString>>;
    destStationBox->clear();
    confirmButton->setDisabled(true);
    destStationBox->setDisabled(true);
    timeBox->setDisabled(true);
    QSqlQuery qr3(db);
    QString chosen = new_val;
    QString func = "select * from dst_stations('%1')";
    func = func.arg(chosen);
    qr3.exec(func);
    qDebug() << qr3.lastError();
    int cnt=0;
    while(qr3.next()){
        list2->append(*new QPair<int,QString>(qr3.value(0).toInt(),qr3.value(1).toString()));
        destStationBox->insertItem(cnt,list2->at(cnt).second);
        cnt++;
    };
    destStationBox->setCurrentIndex(-1);
    enableSignals(3);
    destStationBox->setDisabled(false);
}

void EditSchedule::dstStation(int new_val){
    if(srcStationBox->currentIndex()==-1 ||
       srcCityBox->currentIndex()==-1 ||
       destCityBox->currentIndex()==-1 ||
       destStationBox->currentIndex()==-1 ||
       timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    if(new_val == -1) return;
    list3 = new QList<QPair<int,QString>>;
    QSqlQuery qr4(db);
    timeBox->clear();
    timeBox->setDisabled(true);
    int chosen = list2->at(new_val).first;
    QString func = "select * from final_schedule(%1)";
    func = func.arg(chosen);
    qr4.exec(func);
    int cnt = 0;
    while(qr4.next()){
        list3->append(*new QPair<int,QString>(qr4.value(0).toInt(),qr4.value(1).toDateTime().toString("dd/MM/yyyy hh:mm")));
        timeBox->insertItem(cnt,list3->at(cnt).second);
        cnt++;
    }
    timeBox->setCurrentIndex(-1);
    enableSignals(4);
    timeBox->setDisabled(false);
    if(timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
}

void EditSchedule::time(int new_val){
    if(new_val == -1) return;
    if(srcStationBox->currentIndex()==-1 ||
       srcCityBox->currentIndex()==-1 ||
       destCityBox->currentIndex()==-1 ||
       destStationBox->currentIndex()==-1 ||
       timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    else confirmButton->setDisabled(false);
    if(timeBox->currentIndex() == -1) confirmButton->setDisabled(true);
    setChoice(list3->at(new_val).first);
}

void EditSchedule::on_confirm(){
    emit move();
    this->close();
}

void EditSchedule::on_cancel(){
    this->close();
}

int EditSchedule::getChoice(){
    return choice;
}

void EditSchedule::setChoice(int _choice){
    choice = _choice;
}
void EditSchedule::setData(Office* office){
    srcCityBox->setCurrentText(office->getSource_city());
    srcStationBox->setCurrentText(office->getSource_station());
    destCityBox->setCurrentText(office->getDestination_city());
    destStationBox->setCurrentText(office->getDestination_station());
    timeBox->setCurrentText(office->getTime_of_departure().toString("dd/MM/yyyy hh:mm"));
};

void EditSchedule::enableSignals(int type){
    if (type==1 and signal1 == false){
        connect(srcStationBox,SIGNAL(currentIndexChanged(int)),this,SLOT(srcStation(int)));
        signal1 = true;
    }
    if (type==2 and signal2 == false){
        connect(destCityBox,SIGNAL(currentTextChanged(QString)),this,SLOT(dstCity(QString)));
        signal2 = true;
    }
    if (type==3 and signal3 == false){
        connect(destStationBox,SIGNAL(currentIndexChanged(int)),this,SLOT(dstStation(int)));
        signal3 = true;
    }
    if (type==4 and signal4 == false){
        connect(timeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(time(int)));
        signal4 = true;
    }
}
