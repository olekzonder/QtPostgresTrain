#ifndef OFFICEPROBLEMWIDGET_H
#define OFFICEPROBLEMWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGroupBox>
#include "officemodel.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <editschedule.h>
class OfficeProblemWidget: public QWidget
{
    Q_OBJECT
public:
    OfficeProblemWidget(OfficeModel *model);
private:
    QLineEdit *searchBar;
    OfficeModel *model;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    QVBoxLayout *layout;
    QGroupBox *vgroup;
    QGroupBox *gridGroup;
    QTableView *view;
    QPushButton *refundButton;
    QPushButton *moveButton;
    QPushButton *autofixButton;
    QSortFilterProxyModel *proxy;
    EditSchedule *dialog_sch;
private slots:
    void on_refund();
    void on_moved();
    void on_move();
    void on_autofix();
    void on_search();
signals:
    void update_required();
};

#endif // OFFICEPROBLEMWIDGET_H
