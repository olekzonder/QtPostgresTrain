#include "logindialog.h"

LoginDialog::LoginDialog(QWidget *parent):QDialog{parent}
{
    layout = new QVBoxLayout(this);
    setModal(true);
    setVisible(true);
    setWindowTitle("Вход");
    labelIP = new QLabel(this);
    labelIP->setText("IP-адрес");
    labelLogin = new QLabel(this);
    labelLogin->setText("Логин");
    labelPassword = new QLabel(this);
    labelPassword->setText("Пароль");
    editIP = new QLineEdit(this);
    editLogin = new QLineEdit(this);
    editPassword = new QLineEdit(this);
    editPassword->setEchoMode(QLineEdit::Password);
    confirmButton = new QPushButton(this);
    confirmButton->setText("Подключиться");
    cancelButton = new QPushButton(this);
    cancelButton->setText("Отмена");
    layout->addWidget(labelIP);
    layout->addWidget(editIP);
    layout->addWidget(labelLogin);
    layout->addWidget(editLogin);
    layout->addWidget(labelPassword);
    layout->addWidget(editPassword);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(on_cancel()));
    connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(on_confirm()));
}


void LoginDialog::on_cancel(){
    this->close();
}


void LoginDialog::on_confirm(){
    db = QSqlDatabase::addDatabase("QPSQL");
    connection_notice = new QDialog(this);
    connection_notice->setWindowTitle("Загрузка");
    labelLoading = new QLabel(connection_notice);
    labelLoading->setText("Пожалуйста, подождите");
    connection_layout = new QVBoxLayout(connection_notice);
    connection_layout->addWidget(labelLoading);
    connection_notice->setLayout(connection_layout);

    ip = this->editIP->text();
    user = this->editLogin->text();
    password = this->editPassword->text();
    db.setHostName(ip);
    db.setDatabaseName("kursach");
    db.setUserName(user);
    db.setPassword(password);
    pool = new QThreadPool;
    watcher = new QFutureWatcher<void>;
    QFuture<void> future = QtConcurrent::run(pool,connectToDb,db,user,password);
    watcher->setFuture(future);
    connect(this->watcher,SIGNAL(finished()),this,SLOT(on_connected()));
    connection_notice->setModal(true);
    connection_notice->show();

}
QSqlDatabase LoginDialog::getdb(){
    return db;
}

extern void connectToDb(QSqlDatabase db,QString user, QString password){
    db.open(user,password);
}

void LoginDialog::on_connected(){
    connection_notice->close();
    if(db.isOpen() == false){
         QMessageBox::warning(this,"Ошибка подключения к базе данных",db.lastError().text(),QMessageBox::Cancel,Qt::PlainText);
}
    else{
        this->close();
        emit login();
    };
}
