#ifndef EDITSTATION_H
#define EDITSTATION_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <station.h>
#include <QDateEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QDebug>
class EditStation : public QDialog
{
    Q_OBJECT

public:
    EditStation(QWidget *parent = nullptr);
    void setData(Station* station);
    QString getCity();
    QString getStation();
    QString getFilial();
    QDate getOpeningDate();
    int getChecked();
private:
    int checked;
    QString city;
    QString station;
    QString filial;
    QDate openingDate;
    QVBoxLayout *layout;
    QLabel *labelCity;
    QLabel *labelStation;
    QLabel *labelFilial;
    QCheckBox *checkDate;
    QLabel *labelDate;
    QLineEdit *editCity;
    QLineEdit *editStation;
    QLineEdit *editFilial;
    QDateEdit *editDate;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
signals:
    void data_changed();
private slots:
    void on_cancel();
    void on_confirm();
    void on_check(int);
};

#endif // EDITSTATION_H
