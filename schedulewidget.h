#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include "schedulemodel.h"
#include <editcustomer.h>
#include <searchschedule.h>
#include <QLineEdit>
#include <QSortFilterProxyModel>
class ScheduleWidget: public QWidget
{
    Q_OBJECT
private:
    ScheduleModel *model;
    QVBoxLayout *layout;
    QTableView *view;
    QPushButton *buyButton;
    EditCustomer *dialog;
    QSortFilterProxyModel *proxy;
    QPushButton *searchButton;
    SearchSchedule* dialogSearch;
    QDialog *gendiag;
public:
    ScheduleWidget(ScheduleModel *model);
private slots:
   void on_buy();
   void on_data_get();
   void on_search();
   void on_query();
signals:
   void update_required();
};

#endif // SCHEDULEWIDGET_H
