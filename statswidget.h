#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <statsmodel.h>
#include <QLabel>
#include <QString>
class StatsWidget: public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *layout;
    QLabel *totalProfit;
    QLabel *avgProfit;
    QLabel *currentClients;
    QLabel *totalClients;
    QLabel *currentSchedules;
    QLabel *archivedSchedules;
    QLabel *invalidSchedules;
public:
    StatsWidget(QVector<int>*);
};

#endif // OFFICEWIDGET_H
