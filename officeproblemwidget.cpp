#include "officeproblemwidget.h"

OfficeProblemWidget::OfficeProblemWidget(OfficeModel *_model)
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
    autofixButton = new QPushButton;
    autofixButton->setText("Автоматическое исправление");
    vbox->addWidget(view);
    vbox->addWidget(autofixButton);
    vgroup = new QGroupBox();
    vgroup -> setLayout(vbox);
    view->setSortingEnabled(true);
    view->sortByColumn(Qt::AscendingOrder);
    grid = new QGridLayout;
    refundButton = new QPushButton;
    refundButton->setText("Возврат денег");

    moveButton = new QPushButton;
    moveButton->setText("Исправить");
    grid->addWidget(refundButton,0,0);
    grid->addWidget(moveButton,0,1);
    gridGroup = new QGroupBox();
    gridGroup->setLayout(grid);
    gridGroup->setFlat(true);
    layout->addWidget(searchBar);
    layout->addWidget(vgroup);
    layout->addWidget(gridGroup);
    connect(this->refundButton,SIGNAL(clicked()),this,SLOT(on_refund()));
    connect(this->moveButton,SIGNAL(clicked()),this,SLOT(on_move()));
    connect(this->autofixButton,SIGNAL(clicked()),this,SLOT(on_autofix()));
}

void OfficeProblemWidget::on_move(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    dialog_sch= new EditSchedule(this);
    connect(this->dialog_sch,SIGNAL(move()),this,SLOT(on_moved()));
    dialog_sch->setDb(model->getDb());
    QModelIndex index = proxy->mapToSource(selected.at(0));
    dialog_sch->setData(model->getData(index));
    dialog_sch->open();
}

void OfficeProblemWidget::on_refund(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    qDebug() << selected.size();
    for (int i = 0; i < selected.size(); i++){
        QModelIndex index = proxy->mapToSource(selected.at(i));
        QSqlError err = model->refund(index);
        if(err.text().isEmpty() == false){
            return;
        }
    }
     emit update_required();
}

void OfficeProblemWidget::on_autofix(){
    QSqlError err = model->autoFix();
    if(err.text().isEmpty() == false){
        QMessageBox::warning(this,"Ошибка",err.text());
        return;
    }
    emit update_required();
}

void OfficeProblemWidget::on_search(){
    QRegExp regExp(searchBar->text().toLower(),Qt::CaseInsensitive,QRegExp::FixedString);
    proxy->setFilterRegExp(regExp);
}

void OfficeProblemWidget::on_moved(){
    QModelIndexList selected = view->selectionModel()->selectedRows();
    if(selected.size() == 0) return;
    for (int i = 0; i < selected.size(); i++){
            QModelIndex index = proxy->mapToSource(selected.at(i));
            QSqlError err = model->move(index, dialog_sch->getChoice());
           if(err.text().isEmpty() == false){
                return;
            }
}
    emit update_required();
}
