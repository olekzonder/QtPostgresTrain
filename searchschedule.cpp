#include "searchschedule.h"

SearchSchedule::SearchSchedule(QWidget *parent):QDialog{parent}
{
    this->setWindowTitle("Фильтр...");
    query = new QSqlQuery(db);
    layout = new QVBoxLayout(this);
    labelSourceCity = new QLabel(this);
    labelSourceCity->setText("Город отправления");
    layout->addWidget(labelSourceCity);
    srcCityBox = new QComboBox(this);
    query->exec("select * from src_cities");
    qDebug() << query->lastError();
    int cnt = 0;
    {
    while(query->next()){
        cnt++;
        srcCityBox->insertItem(cnt,query->value(0).toString());
    };
    }
    srcCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(srcCityBox);
    labelDestinationCity = new QLabel;
    labelDestinationCity->setText("Город назначения");
    layout->addWidget(labelDestinationCity);
    destCityBox = new QComboBox;
    destCityBox->setDisabled(true);
    destCityBox->setInsertPolicy(QComboBox::InsertAtBottom);
    layout->addWidget(destCityBox);

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

void SearchSchedule::setDb(QSqlDatabase _db){
    db = _db;
}

void SearchSchedule::srcCity(QString new_val){
    if(srcCityBox->currentIndex()==-1) confirmButton->setDisabled(true);
    destCityBox->clear();
    destCityBox->setDisabled(true);
    QSqlQuery qr1(db);
    QString chosen = new_val;
    QString func = "select * from dstfromsrc('%1')";
    func = func.arg(chosen);
    qr1.exec(func);
    qDebug() << qr1.lastError();
    int cnt=0;
    while(qr1.next()){
        destCityBox->insertItem(cnt,qr1.value(0).toString());
        cnt++;
    };
    destCityBox->setDisabled(false);
    confirmButton->setDisabled(false);
    destCityBox->setCurrentIndex(-1);
}

void SearchSchedule::on_confirm(){
    qDebug() << srcCityBox->currentText() << destCityBox->currentText();
    setChoice(srcCityBox->currentText(), destCityBox->currentText());
    emit confirmed();
    this->close();
}

void SearchSchedule::on_cancel(){
    this->close();
}



void SearchSchedule::setChoice(QString _choice1, QString _choice2){
    src = _choice1;
    dst = _choice2;
}

QString SearchSchedule::getSrc(){
    return src;
}
QString SearchSchedule::getDst(){
    return dst;
}
