#include "trainwidget.h"

TrainWidget::TrainWidget(TrainModel *_model)
{
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск по номеру состава...");
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
    editButton->setText("Отредактировать сведения о поезде");
    grid = new QGridLayout;
    repairButton = new QPushButton;
    repairButton->setText("Починка");
    inspectionButton = new QPushButton;
    inspectionButton->setText("Техобслуживание");
    grid->addWidget(inspectionButton,0,0);
    grid->addWidget(repairButton,0,1);
    deleteButton = new QPushButton;
    deleteButton->setText("Удалить поезд");
    addButton = new QPushButton;
    addButton->setText("Добавить поезд");
    grid->addWidget(addButton,1,0);
    grid->addWidget(deleteButton,1,1);
    gridGroup = new QGroupBox();
    gridGroup->setFlat(true);
    gridGroup->setLayout(grid);
    layout->addWidget(searchBar);
    layout->addWidget(view);
    layout->addWidget(editButton);
    layout->addWidget(gridGroup);
    oldestButton = new QPushButton(this);
    oldestButton->setText("Наиболее частые поломки");
    layout->addWidget(oldestButton);
    connect(searchBar, SIGNAL(textChanged(const QString&)), this, SLOT(on_search()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(on_add()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(on_edit()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_delete()));
    connect(repairButton, SIGNAL(clicked()), this, SLOT(on_repair()));
    connect(inspectionButton, SIGNAL(clicked()), this, SLOT(on_inspect()));
    connect(oldestButton, SIGNAL(clicked()),this,SLOT(on_oldest()));
}

void TrainWidget::on_search(){
    QRegExp regExp(searchBar->text().toLower(),Qt::CaseInsensitive,QRegExp::FixedString);
    proxy->setFilterRegExp(regExp);
}

void TrainWidget::on_add(){
    dialog = new EditTrain(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_data_get()));
    dialog->show();
}

void TrainWidget::on_data_get(){
    QSqlError err = model->add(dialog->getName(), dialog->getType(), dialog->getSerial());
    if(err.text().isEmpty() == false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void TrainWidget::on_edit(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog = new EditTrain(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_edited()));
    QModelIndex index = proxy->mapToSource(selected.at(0));
    dialog->setData(model->getData(index));
    dialog->open();
}

void TrainWidget::on_edited(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    QModelIndex index = proxy->mapToSource(selected.at(0));
    QSqlError err = model->edit(dialog->getName(), dialog->getType(), dialog->getSerial(),index);
    if(err.text().isEmpty() == false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void TrainWidget::on_repair(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    QModelIndex index = proxy->mapToSource(selected.at(0));
    QSqlError err = model->repair(index);
    if(err.text().isEmpty() == false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void TrainWidget::on_inspect(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    QModelIndex index = proxy->mapToSource(selected.at(0));
    QSqlError err = model->inspect(index);
    if(err.text().isEmpty() == false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
}
    emit update_required();
}

void TrainWidget::on_delete(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    int reply = QMessageBox::question(this,"Внимание!","Вы собираетесь удалить поезд. Вы уверены?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){;
        for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->remove(index);
            if(err.text().isEmpty() == false){
                if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
                else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
                return;
    }
        emit update_required();
    }
    }
    else return;
}

void TrainWidget::on_oldest(){
    model->mostBroken();
}
