#include <editstation.h>

EditStation::EditStation(QWidget *parent):QDialog{parent}
{
    checked = 0;
    this->setWindowTitle("Редактирование сведений");
    layout = new QVBoxLayout(this);
    setModal(true);
    setVisible(true);
    setWindowTitle("Редактор сведений");
    labelCity = new QLabel(this);
    labelCity->setText("Город");
    labelStation = new QLabel(this);
    labelStation->setText("Вокзал");
    editCity = new QLineEdit(this);
    editStation = new QLineEdit(this);
    labelFilial = new QLabel(this);
    labelFilial->setText("Филиал");
    editFilial = new QLineEdit(this);
    checkDate = new QCheckBox(this);
    checkDate->setText("Установить новую дату?");
    editDate = new QDateEdit(this);
    editDate->setMaximumDate(QDate::currentDate());
    confirmButton = new QPushButton(this);
    confirmButton->setText("Сохранить");
    cancelButton = new QPushButton(this);
    cancelButton->setText("Отмена");
    layout->addWidget(labelCity);
    layout->addWidget(editCity);
    layout->addWidget(labelStation);
    layout->addWidget(editStation);
    layout->addWidget(labelFilial);
    layout->addWidget(editFilial);
    layout->addWidget(checkDate);
    layout->addWidget(editDate);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    editDate->hide();
    connect(this->checkDate,SIGNAL(stateChanged(int)),this,SLOT(on_check(int)));
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
}

void EditStation::on_cancel(){
    this->close();
}


void EditStation::on_confirm(){
    bool error = false;
    if(editCity->text().trimmed().isEmpty()==true || editStation->text().trimmed().isEmpty() == true ||
            editFilial->text().trimmed().isEmpty() == true){
        QMessageBox::warning(this,"Внимание","Не все поля заполнены.");
        error = true;
    }
    if(error==false){
    city = editCity->text().trimmed();
    station = editStation->text().trimmed();
    filial = editFilial->text().trimmed();
    if(checked == 1) openingDate = editDate->date();
    this->close();
    emit data_changed();
    }
}

void EditStation::on_check(int choice){
    qDebug() << choice;
    if(choice == 0){
        checked = 0;
        editDate->hide();
    }
    if(choice == 2){
        checked = 1;
        editDate->show();
    }
}

void EditStation::setData(Station* station){
    editCity->setText(station->getCity());
    editStation->setText(station->getStation());
    editFilial->setText(station->getFilial());
    checkDate->setChecked(true);
    editDate->setHidden(false);
    editDate->setDate(station->getOpening_date());
    checkDate->setHidden(true);
};

QString EditStation::getCity(){
    return city;
};
QString EditStation::getStation(){
    return station;
};
QString EditStation::getFilial(){
    return filial;
};
QDate EditStation::getOpeningDate(){
    return openingDate;
}

int EditStation::getChecked(){
    return checked;
}
