#include "stationwidget.h"

StationWidget::StationWidget(StationModel *_model)
{
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск по городу...");
    connect(searchBar, SIGNAL(textChanged(const QString&)), this, SLOT(on_search()));
    model = _model;
    layout = new QVBoxLayout(this);
    vbox = new QVBoxLayout;
    view = new QTableView(this);
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    view->setModel(proxy);
    view->sortByColumn(0,Qt::AscendingOrder);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    editButton = new QPushButton;
    editButton->setText("Отредактировать");
    grid = new QGridLayout;
    addButton = new QPushButton;
    addButton->setText("Добавить вокзал");
    deleteButton = new QPushButton;
    deleteButton->setText("Удалить вокзал");
    grid->addWidget(addButton,0,0);
    grid->addWidget(deleteButton,0,1);
    gridGroup = new QGroupBox();
    gridGroup->setAlignment(Qt::AlignHCenter);
    gridGroup->setFlat(true);
    gridGroup->setLayout(grid);
    layout->addWidget(searchBar);
    layout->addWidget(view);
    layout->addWidget(editButton);
    layout->addWidget(gridGroup);
    connect(addButton, SIGNAL(clicked()), this, SLOT(on_add()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(on_edit()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_delete()));
}

void StationWidget::on_search(){
    QRegExp regExp(searchBar->text().toLower(),Qt::CaseInsensitive,QRegExp::FixedString);
    proxy->setFilterRegExp(regExp);
}


void StationWidget::on_add(){
    dialog = new EditStation(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_data_get()));
    dialog->show();
}

void StationWidget::on_data_get(){
    QSqlError err;
    if(dialog->getChecked() == 0) QSqlError err = model->add(dialog->getCity(), dialog->getStation(), dialog->getFilial());
    else QSqlError err = model->add(dialog->getCity(), dialog->getStation(), dialog->getFilial(), dialog->getOpeningDate());
    if(err.text().isEmpty() == false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void StationWidget::on_edit(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog = new EditStation(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_edited()));
    QModelIndex index = proxy->mapToSource(selected.at(0));
    dialog->setData(model->getData(index));
    dialog->open();
}

void StationWidget::on_edited(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    QModelIndex index = proxy->mapToSource(selected.at(0));
    QSqlError err = model->edit(dialog->getCity(), dialog->getStation(), dialog->getFilial(),dialog->getOpeningDate(),index);
    if(err.NoError!=0){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void StationWidget::on_delete(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    int reply = QMessageBox::question(this,"Внимание!","Вы собираетесь удалить станцию. Вы уверены?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){;
        for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->remove(index);
            if(err.text().isEmpty()==false){
                if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
                else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
                return;
    }
    }
        emit update_required();
    }
    else return;
}
