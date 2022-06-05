#ifndef SEARCHSCHEDULE_H
#define SEARCHSCHEDULE_H
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
class SearchSchedule : public QDialog
{
    Q_OBJECT

public:
    SearchSchedule(QWidget *parent = nullptr);
    void setDb(QSqlDatabase);
    QString getSrc();
    QString getDst();

private:
    QSqlQuery *query;
    QVBoxLayout *layout;
    QLabel *labelSourceCity;
    QComboBox *srcCityBox;
    QLabel *labelDestinationCity;
    QComboBox *destCityBox;
    QSqlDatabase db;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QString src;
    QString dst;
    void setChoice(QString, QString);
signals:
    void confirmed();
private slots:
    void srcCity(QString);
    void on_cancel();
    void on_confirm();
};

#endif // SEARCHSCHEDULE_H
