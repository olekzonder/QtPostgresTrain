#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "officeproblemwidget.h"
#include <QSqlError>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login = new LoginDialog(this);
    login->show();
    connect(this->login,SIGNAL(login()),this,SLOT(on_login()));
    this->setWindowTitle("Железнодорожная информационно-справочная система");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::renderTabs(int pos){
    ui->label->setText("Последнее обновление: "+QDateTime::currentDateTime().toString("dd/MM/yy hh:mm"));
    ui->tabWidget->clear();
    statsModel = new StatsModel(db);
    if(statsModel->queryPossible() == true){
        StatsWidget *statsWidget = new StatsWidget(statsModel->fromSqlQuery());
        ui->tabWidget->addTab(statsWidget,"Статистика");
    }

    scheduleModel = new ScheduleModel(db,0);
    if(scheduleModel->queryPossible()==true){
    scheduleModel->fromSqlQuery();
    ScheduleWidget *scheduleWidget = new ScheduleWidget(scheduleModel);
    ui->tabWidget->addTab(scheduleWidget,"Купить билеты");
    connect(scheduleWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }

    officeModel = new OfficeModel(db,0);
    if(officeModel->queryPossible()==true){
    officeModel->fromSqlQuery();
    OfficeWidget *officeWidget = new OfficeWidget(officeModel);
    ui->tabWidget->addTab(officeWidget,"Текущие клиенты");
    connect(officeWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }

    officeProblemModel = new OfficeModel(db,1);
    if(officeProblemModel->queryPossible()==true){
        officeProblemModel->fromSqlQuery();
        if(officeProblemModel->isEmpty() == false){
        OfficeProblemWidget *officeProblemWidget = new OfficeProblemWidget(officeProblemModel);
        ui->tabWidget->addTab(officeProblemWidget,"Проблемы");
        QMessageBox::warning(this,"Внимание!","Обнаружены билеты с неверным расписанием",QMessageBox::Cancel);
         connect(officeProblemWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }
    }
    officeArchiveModel = new OfficeModel(db,2);
    if(officeArchiveModel->queryPossible()==true){
        officeArchiveModel->fromSqlQuery();
        if(officeArchiveModel->isEmpty() == false){
        TicketArchiveWidget *archiveWidget = new TicketArchiveWidget(officeArchiveModel);
        ui->tabWidget->addTab(archiveWidget,"Архив клиентов");
         connect(archiveWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }
    }
    scheduleArchiveModel = new ScheduleModel(db,2);
    if(scheduleArchiveModel->queryPossible()==true){
    scheduleArchiveModel->fromSqlQuery();
    ScheduleArchiveWidget *scheduleArchiveWidget = new ScheduleArchiveWidget(scheduleArchiveModel);
    ui->tabWidget->addTab(scheduleArchiveWidget,"Архив маршрутов");
    connect(scheduleArchiveWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }
   scheduleEditModel = new ScheduleModel(db,1);
    if(scheduleEditModel->queryPossible()==true){
    scheduleEditModel->fromSqlQuery();
    ScheduleEditWidget *scheduleEditWidget = new ScheduleEditWidget(scheduleEditModel);
    ui->tabWidget->addTab(scheduleEditWidget,"Текущие маршруты");
    connect(scheduleEditWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }
    trainModel = new TrainModel(db);
    if(trainModel->queryPossible()==true){
        trainModel->fromSqlQuery();
        TrainWidget *trainWidget = new TrainWidget(trainModel);
        ui->tabWidget->addTab(trainWidget,"Поезда");
        connect(trainWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }

    stationModel = new StationModel(db);
    if(stationModel->queryPossible()==true){
        stationModel->fromSqlQuery();
        StationWidget *stationWidget = new StationWidget(stationModel);
        ui->tabWidget->addTab(stationWidget,"Станции");
        connect(stationWidget,SIGNAL(update_required()),this,SLOT(on_pushButton_clicked()));
    }
    ui->tabWidget->setCurrentIndex(pos);
}

void MainWindow::on_pushButton_clicked()
{
    int pos = ui->tabWidget->currentIndex();
    this->renderTabs(pos);
}


void MainWindow::on_login(){
    db = login->getdb();
    this->show();
    this->renderTabs(0);
}
void MainWindow::on_relogin_triggered()
{
    delete login;
    this->hide();
    login = new LoginDialog(this);
    connect(this->login,SIGNAL(login()),this,SLOT(on_login()));
    login->show();
}

