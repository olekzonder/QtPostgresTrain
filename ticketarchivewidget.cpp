#include "ticketarchivewidget.h"

TicketArchiveWidget::TicketArchiveWidget(OfficeModel *_model)
{
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Поиск по ФИО...");
    connect(searchBar, SIGNAL(textChanged(const QString&)), this, SLOT(on_search()));
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
    layout->addWidget(searchBar);
    layout->addWidget(view);
}

void TicketArchiveWidget::on_search(){
    QRegExp regExp(searchBar->text().toLower(),Qt::CaseInsensitive,QRegExp::FixedString);
    proxy->setFilterRegExp(regExp);
}
