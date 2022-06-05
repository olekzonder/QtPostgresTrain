#ifndef SCHEDULEEDITWIDGET_H
#define SCHEDULEEDITWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include <QVBoxLayout>
#include "schedulemodel.h"
#include <scheduledialog.h>
#include <QSortFilterProxyModel>
#include <QGroupBox>
#include <QSpinBox>
#include <QComboBox>
class ScheduleEditWidget: public QWidget
{
    Q_OBJECT
private:
    ScheduleModel *model;
    QVBoxLayout *layout;
    QGridLayout *grid;
    QGroupBox *box;
    QTableView *view;
    QPushButton *generateButton;
    QPushButton *autoArchiveButton;
    QPushButton *editButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QSortFilterProxyModel *proxy;
    ScheduleDialog *dialog;
    QDialog *genDiag;
    QSpinBox *interCount;
    QSpinBox *timesCount;
public:
    ScheduleEditWidget(ScheduleModel *model);
private slots:
   void on_auto_archive();
   void on_edit();
   void on_edited();
   void on_add();
   void on_added();
   void on_delete();
   void on_generate();
   void on_generated();
signals:
   void update_required();
};

#endif // SCHEDULEWIDGET_H
