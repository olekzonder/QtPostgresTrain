#include <editcustomer.h>

EditCustomer::EditCustomer(QWidget *parent):QDialog{parent}
{
    this->setWindowTitle("Редактирование сведений");
    layout = new QVBoxLayout(this);
    setModal(true);
    setVisible(true);
    setWindowTitle("Редактор сведений");
    labelFio = new QLabel(this);
    labelFio->setText("ФИО");
    labelGender = new QLabel(this);
    labelGender->setText("Пол");
    labelDob = new QLabel(this);
    labelDob->setText("Дата рождения");
    labelPhone = new QLabel(this);
    labelPhone->setText("Номер телефона");
    editFio = new QLineEdit(this);
    editPhone = new QLineEdit(this);
    editDob = new QDateEdit(this);
    editDob->setMinimumDate(QDate::fromString("01.01.1900","dd.mm.yyyy"));
    editDob->setMaximumDate(QDate::currentDate());
    editGender = new QComboBox(this);
    confirmButton = new QPushButton(this);
    confirmButton->setText("Сохранить");
    cancelButton = new QPushButton(this);
    cancelButton->setText("Отмена");
    editGender->insertItem(1,"Мужской");
    editGender->insertItem(0,"Женский");
    layout->addWidget(labelFio);
    layout->addWidget(editFio);
    layout->addWidget(labelGender);
    layout->addWidget(editGender);
    layout->addWidget(labelDob);
    layout->addWidget(editDob);
    layout->addWidget(labelPhone);
    layout->addWidget(editPhone);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
}

void EditCustomer::on_cancel(){
    this->close();
}


void EditCustomer::on_confirm(){
    bool error = false;
    QRegExp matchphone("^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$");
    if(matchphone.exactMatch(editPhone->text())==false){
        QMessageBox::warning(this,"Внимание","Неверный номер телефона.");
        error = true;
    }
    if(editFio->text().trimmed().isEmpty()==true){
        QMessageBox::warning(this,"Внимание","Не указано ФИО.");
        error = true;
    }
    if(error==false){
    fio = editFio->text().trimmed();
    phone = editPhone->text();
    dob = editDob->date();
    gender = editGender->currentIndex();
    this->close();
    emit data_changed();
    }
}

void EditCustomer::setData(Office* office){
    int diag_gender;
    if(office->getGender()=="Женский") diag_gender = 0;
    else diag_gender = 1;
    editFio->setText(office->getFio());
    editPhone->setText(office->getPhone());
    editGender->setCurrentIndex(diag_gender);
    editDob->setDate(office->getDob());
};

QString EditCustomer::getFio(){
    return fio;
};
QString EditCustomer::getPhone(){
    return phone;
};
QDate EditCustomer::getDob(){
    return dob;
};
bool EditCustomer::getGender(){
    return gender;
};

