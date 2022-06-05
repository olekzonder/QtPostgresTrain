#include "scheduleeditwidget.h"

ScheduleEditWidget::ScheduleEditWidget(ScheduleModel *_model)
{
    model = _model;
    layout = new QVBoxLayout(this);
    grid = new QGridLayout(this);
    view = new QTableView(this);
    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    view->setModel(proxy);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSortingEnabled(true);
    view->sortByColumn(0,Qt::AscendingOrder);
    layout->addWidget(view);
    generateButton = new QPushButton;
    generateButton->setText("Автоматическое создание расписаний");
    layout->addWidget(generateButton);
    autoArchiveButton = new QPushButton;
    autoArchiveButton->setText("Архивировать устаревшее");
    grid->addWidget(autoArchiveButton,0,0);
    view->setSortingEnabled(true);
    editButton = new QPushButton;
    editButton->setText("Изменить");
    grid->addWidget(editButton,0,1);
    addButton = new QPushButton;
    addButton->setText("Добавить новое");
    grid->addWidget(addButton,1,0);
    deleteButton = new QPushButton;
    deleteButton->setText("Удалить");
    grid->addWidget(deleteButton,1,1);
    box = new QGroupBox;
    box->setLayout(grid);
    layout->addWidget(box);
    connect(this->generateButton,SIGNAL(clicked()),this,SLOT(on_generate()));
    connect(this->addButton,SIGNAL(clicked()),this,SLOT(on_add()));
    connect(this->autoArchiveButton,SIGNAL(clicked()),this,SLOT(on_auto_archive()));
    connect(this->editButton,SIGNAL(clicked()),this,SLOT(on_edit()));
    connect(this->deleteButton,SIGNAL(clicked()),this,SLOT(on_delete()));
}

void ScheduleEditWidget::on_delete(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    int reply = QMessageBox::question(this,"Внимание!","Вы собираетесь удалить расписание. Вы уверены?", QMessageBox::Yes | QMessageBox::No);
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
    }
        emit update_required();
    }

void ScheduleEditWidget::on_auto_archive(){
    QSqlError err = model->autoArchive();
    if (err.NoError!=0){
        QMessageBox::warning(this,"Ошибка",err.text());
        return;
    }
     else emit update_required();
}

void ScheduleEditWidget::on_edit(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog = new ScheduleDialog(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_edited()));
    dialog->setData(model->getData(selected.at(0)));
    dialog->open();
    dialog->setDb(model->getDb());
}

void ScheduleEditWidget::on_add(){
    dialog = new ScheduleDialog(this);
    connect(this->dialog,SIGNAL(data_changed()),this,SLOT(on_added()));
    dialog->setDb(model->getDb());
    dialog->open();
}

void ScheduleEditWidget::on_edited(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    qDebug() << selected.size();
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->edit(dialog->getSrcCityVal(),
                                        dialog->getDstCityVal(),
                                        dialog->getTrain(),
                                        dialog->getDepart(),
                                        dialog->getDest(),
                                        dialog->getCost(),
                                        dialog->getAmount(),
                                        index
                                        );
            if(err.text().isEmpty() == false){
                if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
                else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
                return;
}
}
    emit update_required();
}
void ScheduleEditWidget::on_added(){
    QSqlError err = model->add(dialog->getSrcCityVal(),
                                dialog->getDstCityVal(),
                                dialog->getTrain(),
                                dialog->getDepart(),
                                dialog->getDest(),
                                dialog->getCost(),
                                dialog->getAmount()
                                );
    if(err.text().isEmpty()==false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
    }
    emit update_required();
}


void ScheduleEditWidget::on_generate(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    genDiag = new QDialog(this);
    QLabel *labelInterval =  new QLabel(genDiag);
    labelInterval->setText("Интервал повторения (в днях)");
    interCount = new QSpinBox(genDiag);
    interCount->setMinimum(0);
    interCount->setMaximum(30);
    QVBoxLayout *lay = new QVBoxLayout(genDiag);
    lay->addWidget(labelInterval);
    lay->addWidget(interCount);
    QLabel *labelTimes = new QLabel(genDiag);
    labelTimes->setText("Количество повторений");
    lay->addWidget(labelTimes);
    timesCount = new QSpinBox(genDiag);
    timesCount->setMinimum(0);
    timesCount->setMaximum(12);
    lay->addWidget(timesCount);
    QPushButton *ok = new QPushButton(genDiag);
    ok->setText("OK");
    connect(ok,SIGNAL(clicked()),SLOT(on_generated()));
    lay->addWidget(ok);
    genDiag->show();
}

void ScheduleEditWidget::on_generated(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    for (int i = 0; i < selected.size(); i++){
    QModelIndex index = proxy->mapToSource(selected.at(i));
    genDiag->close();
    QSqlError err = model->genSchedule(index, interCount->value(),timesCount->value());
    if(err.text().isEmpty()==false){
        if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
        else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
        return;
    }
    emit update_required();
}
}
