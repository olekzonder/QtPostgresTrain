#include "officewidget.h"

OfficeWidget::OfficeWidget(OfficeModel *_model)
{
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск по ФИО...");
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
    editButton->setText("Изменить сведения о клиенте");
    grid = new QGridLayout;
    refundButton = new QPushButton;
    refundButton->setText("Возврат денег");
    moveButton = new QPushButton;
    moveButton->setText("Изменить маршрут");
    grid->addWidget(refundButton,0,0);
    grid->addWidget(moveButton,0,1);
    gridGroup = new QGroupBox();
    gridGroup->setAlignment(Qt::AlignHCenter);
    gridGroup->setLayout(grid);
    gridGroup->setFlat(true);
    layout->addWidget(searchBar);
    layout->addWidget(view);
    layout->addWidget(editButton);
    layout->addWidget(gridGroup);
    starikashkaButton = new QPushButton;
    starikashkaButton -> setText("Проверка возраста");
    layout->addWidget(starikashkaButton);
    connect(this->starikashkaButton,SIGNAL(clicked()),this,SLOT(on_starikashka()));
    connect(this->refundButton,SIGNAL(clicked()),this,SLOT(on_refund()));
    connect(this->moveButton,SIGNAL(clicked()),this,SLOT(on_move()));
    connect(this->editButton,SIGNAL(clicked()),this,SLOT(on_edit()));
}

void OfficeWidget::on_move(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog_sch= new EditSchedule(this);
    connect(this->dialog_sch,SIGNAL(move()),this,SLOT(on_moved()));
    dialog_sch->setDb(model->getDb());
    QModelIndex index = proxy->mapToSource(selected.at(0));
    dialog_sch->setData(model->getData(index));
    dialog_sch->open();
}

void OfficeWidget::on_refund(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->refund(index);
           if(err.text().isEmpty() == false) return;
    }
    emit update_required();
}

void OfficeWidget::on_edit(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog_cust = new EditCustomer(this);
    connect(this->dialog_cust,SIGNAL(data_changed()),this,SLOT(on_data_get()));
        QModelIndex index = proxy->mapToSource(selected.at(0));
        dialog_cust->setData(model->getData(index));
        dialog_cust->show();
}

void OfficeWidget::on_data_get(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->edit(dialog_cust->getFio(),dialog_cust->getGender(),dialog_cust->getPhone(),dialog_cust->getDob(),index);
           if(err.text().isEmpty() == false){
               if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
               else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
                return;
            }
}
    emit update_required();
}
void OfficeWidget::on_search(){
    QRegExp regExp(searchBar->text().toLower(),Qt::CaseInsensitive,QRegExp::FixedString);
    proxy->setFilterRegExp(regExp);
}

void OfficeWidget::on_moved(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->move(index, dialog_sch->getChoice());
            if(err.text().isEmpty() == false){
                if(err.number()==42501) QMessageBox::warning(this,"Ошибка","Доступ запрещён");
                else QMessageBox::warning(this,"Ошибка","Произошла ошибка. Повторите попытку позже");
                return;
            }

}
    emit update_required();
}

void OfficeWidget::on_starikashka(){
    agecheck = new QDialog(this);
    QLabel *labelAge =  new QLabel(agecheck);
    labelAge->setText("Возраст в годах");
    wheel = new QSpinBox(agecheck);
    wheel->setMinimum(0);
    QVBoxLayout *lay = new QVBoxLayout(agecheck);
    lay->addWidget(labelAge);
    lay->addWidget(wheel);
    QPushButton *ok = new QPushButton(agecheck);
    ok->setText("OK");
    connect(ok,SIGNAL(clicked()),SLOT(on_agecheck()));
    lay->addWidget(ok);
    agecheck->show();
}

void OfficeWidget::on_agecheck(){
    agecheck->close();
    int result = model->starikashka(wheel->value());
    qDebug() << result;
    if(result == 1) QMessageBox::information(this,"Информация","Все пассажиры старше указанного возраста");
    else QMessageBox::information(this,"Информация","Есть пассажиры младше указанного возраста");
}
