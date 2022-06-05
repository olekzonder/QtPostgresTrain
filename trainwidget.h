#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include "trainmodel.h"
#include <QLineEdit>
#include "edittrain.h"
class TrainWidget: public QWidget
{
    Q_OBJECT
private:
    TrainModel *model;
    QVBoxLayout *vbox;
    QGridLayout *grid;
    QVBoxLayout *layout;
    QGroupBox *vgroup;
    QGroupBox *gridGroup;
    QTableView *view;
    QPushButton *repairButton;
    QPushButton *inspectionButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *addButton;
    QPushButton *oldestButton;
    QSortFilterProxyModel *proxy;
    QLineEdit *searchBar;
    EditTrain *dialog;
public:
    TrainWidget(TrainModel *model);
private slots:
    void on_search();
    void on_add();
    void on_data_get();
    void on_edit();
    void on_edited();
    void on_repair();
    void on_inspect();
    void on_delete();
    void on_oldest();
signals:
    void update_required();
};

#endif // OFFICEWIDGET_H
