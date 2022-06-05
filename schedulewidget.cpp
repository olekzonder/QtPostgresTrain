#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(ScheduleModel *_model)
{
    model = _model;
    layout = new QVBoxLayout(this);
    view = new QTableView(this);
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    view->setModel(proxy);
    view->setSortingEnabled(true);
    view->sortByColumn(0,Qt::AscendingOrder);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    searchButton = new QPushButton;
    searchButton->setText("Фильтр...");
    buyButton = new QPushButton;
    buyButton->setText("Купить билет");
    layout->addWidget(searchButton);
    layout->addWidget(view);
    layout->addWidget(buyButton);
    connect(this->searchButton,SIGNAL(clicked()),this,SLOT(on_search()));
    connect(this->buyButton,SIGNAL(clicked()),this,SLOT(on_buy()));
}

void ScheduleWidget::on_buy(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog = new EditCustomer(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_data_get()));
    qDebug() << selected.size();
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            model->getData(index);
            dialog->show();
}
}

void ScheduleWidget::on_data_get(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->buy(dialog->getFio(),dialog->getGender(),dialog->getPhone(),dialog->getDob(),index);
            if(err.NoError!=0){
                QMessageBox::warning(this,"Ошибка","Билеты закончились");
            }
            else QMessageBox::information(this,"Успешно", "Билет успешно куплен.");
    emit update_required();
}
}


void ScheduleWidget::on_search(){
    dialogSearch = new SearchSchedule(this);
    dialogSearch->setDb(model->getDb());
    connect(dialogSearch,SIGNAL(confirmed()),this,SLOT(on_query()));
    dialogSearch->show();
}

void ScheduleWidget::on_query(){
    qDebug() << "SEARCH:" << dialogSearch->getSrc() << dialogSearch->getDst();
    if(dialogSearch->getDst() == "") model->search(dialogSearch->getSrc());
    else model->search(dialogSearch->getSrc(),dialogSearch->getDst());
}
