#ifndef OFFICEWIDGET_H
#define OFFICEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include "officemodel.h"
#include <editcustomer.h>
#include <QLineEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <editschedule.h>
class OfficeWidget: public QWidget
{
    Q_OBJECT
private:
    OfficeModel *model;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    QVBoxLayout *layout;
    QGroupBox *vgroup;
    QGroupBox *gridGroup;
    QTableView *view;
    QPushButton *refundButton;
    QPushButton *moveButton;
    QPushButton *editButton;
    QPushButton *starikashkaButton;
    EditCustomer *dialog_cust;
    EditSchedule *dialog_sch;
    QSortFilterProxyModel *proxy;
    QLineEdit *searchBar;
    QDialog *agecheck;
    QSpinBox *wheel;
    QLabel *labelAge;
public:
    OfficeWidget(OfficeModel *model);
private slots:
   void on_refund();
   void on_move();
   void on_edit();
   void on_data_get();
   void on_moved();
   void on_search();
   void on_starikashka();
   void on_agecheck();
signals:
   void update_required();
};

#endif // OFFICEWIDGET_H
