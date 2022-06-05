#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QDateTime>
#include <logindialog.h>
#include <officewidget.h>
#include <officemodel.h>
#include <officeproblemwidget.h>
#include <ticketarchivewidget.h>

#include <schedulemodel.h>
#include <scheduleeditwidget.h>
#include <schedulewidget.h>
#include <schedulearchivewidget.h>

#include "trainmodel.h"
#include "trainwidget.h"


#include "stationmodel.h"
#include "stationwidget.h"

#include "statsmodel.h"
#include "statswidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_login();

    void on_relogin_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    LoginDialog *login;
    StatsModel *statsModel;
    OfficeModel *officeModel;
    OfficeModel *officeProblemModel;
    OfficeModel *officeArchiveModel;
    ScheduleModel *scheduleModel;
    ScheduleModel *scheduleEditModel;
    ScheduleModel *scheduleArchiveModel;
    TrainModel *trainModel;
    StationModel *stationModel;
    void renderTabs(int pos);
};
#endif // MAINWINDOW_H
