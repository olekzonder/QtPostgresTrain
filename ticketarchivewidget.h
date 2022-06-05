#ifndef TICKETARCHIVEWIDGET_H
#define TICKETARCHIVEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include "officemodel.h"
#include <QRegExp>
class TicketArchiveWidget: public QWidget
{
    Q_OBJECT
private:
    QLineEdit *searchBar;
    QSortFilterProxyModel *proxy;
    OfficeModel *model;
    QVBoxLayout *layout;
    QTableView *view;
    QPushButton *searchButton;
public:
    TicketArchiveWidget(OfficeModel *model);
private slots:
   void on_search();
signals:
   void update_required();
};

#endif // TICKETARCHIVEWIDGET_H
