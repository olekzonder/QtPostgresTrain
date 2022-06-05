#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QApplication>
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QSqlDatabase getdb();
private:
    QSqlDatabase db;
    QThreadPool *pool;
    QDialog *connection_notice;
    QLabel *labelLoading;
    QVBoxLayout *connection_layout;
    QVBoxLayout *layout;
    QFutureWatcher<void> *watcher;
    QLabel *labelIP;
    QLabel *labelLogin;
    QLabel *labelPassword;
    QLineEdit *editIP;
    QLineEdit *editLogin;
    QLineEdit *editPassword;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QString ip;
    QString user;
    QString password;
    QSqlDatabase db_connect(QString ip, QString user, QString password);

signals:
    void login();
private slots:
    void on_cancel();
    void on_confirm();
    void on_connected();
};
extern void connectToDb(QSqlDatabase,QString,QString);
#endif // LOGINDIALOG_H
