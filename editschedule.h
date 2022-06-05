#ifndef EDITSCHEDULE_H
#define EDITSCHEDULE_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateEdit>
#include <QComboBox>
#include <QDebug>
#include <QList>
#include <QPair>
#include <office.h>
class EditSchedule : public QDialog
{
    Q_OBJECT

public:
    EditSchedule(QWidget *parent = nullptr);
    void setDb(QSqlDatabase);
    void setData(Office* office);
    int getChoice();

private:
    QSqlQuery *query;
    QVBoxLayout *layout;
    QLabel *labelSourceCity;
    QComboBox *srcCityBox;
    QLabel *labelSourceStation;
    QComboBox *srcStationBox;
    QLabel *labelDestinationCity;
    QComboBox *destCityBox;
    QLabel *labelDestinationStation;
    QComboBox *destStationBox;
    QLabel *labelTimeOfDeparture;
    QComboBox *timeBox;
    QSqlDatabase db;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QList<QPair<int,QString>> *list1;
    QList<QPair<int,QString>> *list2;
    QList<QPair<int,QString>> *list3;
    int choice;
    void setChoice(int);
    bool signal1;
    bool signal2;
    bool signal3;
    bool signal4;
    void enableSignals(int);
signals:
    void move();
private slots:
    void srcCity(QString);
    void srcStation(int);
    void dstCity(QString);
    void dstStation(int);
    void time(int);
    void on_cancel();
    void on_confirm();
};

#endif // EDITSCHEDULE_H
