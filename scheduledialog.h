#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QDebug>
#include <QList>
#include <QPair>
#include <schedule.h>
#include <QSpinBox>
class ScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    ScheduleDialog(QWidget *parent = nullptr);

    void setDb(QSqlDatabase);
    void setData(Schedule* schedule);
    Schedule* getChoice();
    int getSrcCityVal();
    int getDstCityVal();
    int getTrain();
    QDateTime getDepart();
    QDateTime getDest();
    int getCost();
    int getAmount();
private:
    QSqlQuery *query;
    QGridLayout *layout;
    QLabel *labelSourceCity;
    QComboBox *srcCityBox;
    QLabel *labelSourceStation;
    QComboBox *srcStationBox;
    QLabel *labelDestinationCity;
    QComboBox *destCityBox;
    QLabel *labelDestinationStation;
    QComboBox *destStationBox;
    QLabel *labelTrainSerial;
    QComboBox *trainBox;
    QLabel *labelTimeOfDeparture;
    QDateTimeEdit *departEdit;
    QLabel *labelTimeOfDestination;
    QDateTimeEdit *destEdit;
    QSqlDatabase db;
    QLabel *labelTicketCost;
    QSpinBox *ticketCost;
    QLabel *labelTicketAmount;
    QSpinBox *ticketAmount;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QList<QPair<int,QString>> *listSrcCity;
    QList<QPair<int,QString>> *listDstCity;
    QList<QPair<int,QString>> *listTrain;
    Schedule* choice;
    void setChoice(int);
    bool signal1;
    bool signal2;
    bool signal3;
    bool signal4;
    int srcCityVal;
    int dstCityVal;
    int train;
    QDateTime depart;
    QDateTime dest;
    int cost;
    int amount;
    void enableSignals(int);
signals:
    void data_changed();
private slots:
    void srcCity(QString);
    void dstCity(QString);
    void on_cancel();
    void on_confirm();
    void minimum(const QDateTime);
};

#endif // SCHEDULEDIALOG_H
