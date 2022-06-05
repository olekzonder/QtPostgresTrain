#ifndef EDITCUSTOMER_H
#define EDITCUSTOMER_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <office.h>
#include <schedule.h>
#include <QDateEdit>
#include <QComboBox>
class EditCustomer : public QDialog
{
    Q_OBJECT

public:
    EditCustomer(QWidget *parent = nullptr);
    void setData(Office* office);
    QString getFio();
    QString getPhone();
    QDate getDob();
    bool getGender();
private:
    QString fio;
    QString phone;
    bool gender;
    QDate dob;
    QVBoxLayout *layout;
    QLabel *labelFio;
    QLabel *labelPhone;
    QLabel *labelGender;
    QLabel *labelDob;
    QLineEdit *editFio;
    QLineEdit *editPhone;
    QDateEdit *editDob;
    QComboBox  *editGender;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
signals:
    void data_changed();
private slots:
    void on_cancel();
    void on_confirm();
};

#endif // EDITCUSTOMER_H
