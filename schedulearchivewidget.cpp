#include "schedulearchivewidget.h"

ScheduleArchiveWidget::ScheduleArchiveWidget(ScheduleModel *_model)
{
    model = _model;
    layout = new QVBoxLayout(this);
    view = new QTableView(this);
    proxy = new QSortFilterProxyModel(this);
    seldomButton = new QPushButton(this);
    seldomButton->setText("Наиболее редко приобретаемые билеты");
    proxy->setSourceModel(model);
    view->setModel(proxy);
    view->setSortingEnabled(true);
    view->sortByColumn(0,Qt::AscendingOrder);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(view);
    layout->addWidget(seldomButton);
    connect(this->seldomButton,SIGNAL(clicked()),this,SLOT(on_seldom()));
}

void ScheduleArchiveWidget::on_seldom(){
    model->seldomBought();
}
