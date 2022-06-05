#ifndef SCHEDULEARCHIVEWIDGET_H
#define SCHEDULEARCHIVEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QGroupBox>
#include "schedulemodel.h"
#include <QRegExp>
class ScheduleArchiveWidget: public QWidget
{
    Q_OBJECT
private:
    QSortFilterProxyModel *proxy;
    ScheduleModel *model;
    QVBoxLayout *layout;
    QGridLayout *grid;
    QGroupBox *box;
    QPushButton *searchButton;
    QPushButton *seldomButton;
    QTableView *view;
public:
    ScheduleArchiveWidget(ScheduleModel *schedule);
signals:
   void update_required();
private slots:
      void on_seldom();
};

#endif // SCHEDULEARCHIVEWIDGET_H
