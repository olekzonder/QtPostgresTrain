#include <edittrain.h>

EditTrain::EditTrain(QWidget *parent):QDialog{parent}
{
    this->setWindowTitle("Редактирование сведений");
    layout = new QVBoxLayout(this);
    setModal(true);
    setVisible(true);
    setWindowTitle("Редактор сведений");
    labelName = new QLabel(this);
    labelName->setText("Название");
    labelType = new QLabel(this);
    labelType->setText("Тип поезда");
    labelSerial = new QLabel(this);
    labelSerial->setText("Серийный номер");
    editName = new QLineEdit(this);
    editType = new QLineEdit(this);
    editSerial = new QLineEdit(this);
    confirmButton = new QPushButton(this);
    confirmButton->setText("Сохранить");
    cancelButton = new QPushButton(this);
    cancelButton->setText("Отмена");
    layout->addWidget(labelName);
    layout->addWidget(editName);
    layout->addWidget(labelType);
    layout->addWidget(editType);
    layout->addWidget(labelSerial);
    layout->addWidget(editSerial);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
}

void EditTrain::on_cancel(){
    this->close();
}


void EditTrain::on_confirm(){
    bool error = false;
    if(editName->text().trimmed().isEmpty()==true || editSerial->text().trimmed().isEmpty() == true ||
            editType->text().trimmed().isEmpty() == true){
        QMessageBox::warning(this,"Внимание","Не все поля заполнены.");
        error = true;
    }
    if(error==false){
    name = editName->text().trimmed();
    type = editType->text().trimmed();
    serial = editSerial->text().trimmed();
    this->close();
    emit data_changed();
    }
}

void EditTrain::setData(Train* train){
    editName->setText(train->getName());
    editType->setText(train->getType());
    editSerial->setText(train->getSerial());
};

QString EditTrain::getName(){
    return name;
};
QString EditTrain::getType(){
    return type;
};
QString EditTrain::getSerial(){
    return serial;
};

