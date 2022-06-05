#ifndef STATIONWIDGET_H
#define STATIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include "stationmodel.h"
#include "editstation.h"
#include <QLineEdit>

class StationWidget: public QWidget
{
    Q_OBJECT
private:
    StationModel *model;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    QVBoxLayout *layout;
    QGroupBox *vgroup;
    QGroupBox *gridGroup;
    QTableView *view;
    EditStation *dialog;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QSortFilterProxyModel *proxy;
    QLineEdit *searchBar;

public:
    StationWidget(StationModel *model);

private slots:
    void on_search();
    void on_add();
    void on_data_get();
    void on_edit();
    void on_edited();
    void on_delete();
signals:
    void update_required();
};

#endif // OFFICEWIDGET_H
