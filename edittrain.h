#ifndef EDITTRAIN_H
#define EDITTRAIN_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <train.h>
#include <QDateEdit>
#include <QComboBox>
class EditTrain : public QDialog
{
    Q_OBJECT

public:
    EditTrain(QWidget *parent = nullptr);
    void setData(Train* train);
    QString getName();
    QString getType();
    QString getSerial();
private:
    QString name;
    QString type;
    QString serial;
    QVBoxLayout *layout;
    QLabel *labelName;
    QLabel *labelType;
    QLabel *labelSerial;
    QLineEdit *editName;
    QLineEdit *editType;
    QLineEdit *editSerial;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
signals:
    void data_changed();
private slots:
    void on_cancel();
    void on_confirm();
};

#endif // EDITCUSTOMER_H
