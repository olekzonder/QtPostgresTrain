#include "statswidget.h"

StatsWidget::StatsWidget(QVector<int>* list)
{
    layout = new QVBoxLayout(this);
    totalProfit = new QLabel(this);
    totalProfit->setText(QString("Итоговая выручка: %1 руб.").arg(list->at(0)));
    avgProfit = new QLabel(this);
    avgProfit->setText(QString("Средняя выручка за каждый маршрут: %1 руб.").arg(list->at(1)));
    currentClients = new QLabel(this);
    currentClients->setText(QString("Ожидается пассажиров: %1").arg(list->at(2)));
    totalClients = new QLabel(this);
    totalClients->setText(QString("Всего клиентов: %1").arg(list->at(3)));
    currentSchedules = new QLabel(this);
    currentSchedules->setText(QString("Ожидается поездок: %1").arg(list->at(4)));
    archivedSchedules = new QLabel(this);
    archivedSchedules->setText(QString("Выполнено перевозок: %1").arg(list->at(5)));
    invalidSchedules = new QLabel(this);
    invalidSchedules->setText(QString("Отменено рейсов: %1").arg(list->at(6)));
    layout->addWidget(totalProfit);
    layout->addWidget(avgProfit);
    layout->addWidget(currentClients);
    layout->addWidget(totalClients);
    layout->addWidget(currentSchedules);
    layout->addWidget(archivedSchedules);
    layout->addWidget(invalidSchedules);
}
